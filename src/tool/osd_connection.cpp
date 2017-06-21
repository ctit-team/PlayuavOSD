#include "osd_connection.hpp"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include <cinttypes>
#include <memory>
#include <unordered_map>
#include <utility>

#include <unistd.h>

// variables

static std::unordered_map<std::string, osd_connection> connections;

// constructor/destructors

osd_connection::osd_connection() noexcept
{
}

osd_connection::osd_connection(osd_connection &&other) : serial_connection(std::forward<serial_connection>(other))
{
}

// operators

osd_connection &osd_connection::operator<<(osd_command const &cmd)
{
	auto p = cmd.build_payload();
	send(cmd.id(), p.data(), p.size());
	return *this;
}

// methods

void osd_connection::check_command_status()
{
	switch (get_command_status()) {
	case command_status::ok:
		break;
	case command_status::invalid:
		throw std::runtime_error("the last command that sent to the device is not valid");
	default:
		throw std::runtime_error("device response with unknown status");
	}
}

osd_connection &osd_connection::get(std::string const &dev)
{
	// find previous connection
	auto it = connections.find(dev);
	if (it != connections.end()) {
		auto &con = it->second;

		if (!con.valid()) {
			try {
				con.open(dev);
			} catch (...) {
				std::throw_with_nested(std::runtime_error("failed to open device"));
			}
		}

		return con;
	}

	// no previous connection, open a new one
	osd_connection con;

	try {
		con.open(dev);
	} catch (...) {
		std::throw_with_nested(std::runtime_error("failed to open device"));
	}

	connections.insert(std::make_pair(dev, std::move(con)));

	return connections.find(dev)->second;
}

osd_connection::command_status osd_connection::get_command_status()
{
	if (!valid()) {
		throw std::logic_error("no connection");
	}

	// expect 0x12 before command's status
	if (read<std::uint8_t>() != 0x12) {
		throw std::runtime_error("out of sync with device");
	}

	// get status code
	return static_cast<command_status>(read<std::uint8_t>());
}

osd_bootloader_connection osd_connection::reboot_to_bootloader(std::chrono::seconds const &timeout)
{
	auto name = this->name();
	auto start = std::chrono::steady_clock::now();

	// reboot device to boot loader
	send_no_response(0x55);

	try {
		// wait until connection with device is closed
		for (;;) {
			read<std::uint8_t>();
		}
	} catch (std::system_error) {
		close();
	}

	// open a connection to boot loader
	while (!boost::filesystem::exists(name)) {
		if (std::chrono::steady_clock::now() - start >= timeout) {
			throw std::runtime_error("timeout while waiting for boot loader");
		}
		sleep(1);
	}

	osd_bootloader_connection con;

	try {
		con.open(name);
	} catch (...) {
		auto msg = boost::format("failed to open '%s'") % name;
		std::throw_with_nested(std::runtime_error(boost::str(msg)));
	}

	return con;
}

void osd_connection::send(std::uint8_t cmd, void const *p, std::size_t plen)
{
	// allocate buffer
	auto eoc = std::uint8_t(0x20);
	auto len = sizeof(cmd) + plen + sizeof(eoc);
	auto data = std::make_unique<std::uint8_t[]>(len);

	// command's id
	std::memcpy(data.get(), &cmd, sizeof(cmd));

	// payload
	if (p && plen) {
		std::memcpy(data.get() + sizeof(cmd), p, plen);
	}

	// end of command marker
	std::memcpy(data.get() + sizeof(cmd) + plen, &eoc, sizeof(eoc));

	write(data.get(), len);
}

void osd_connection::send_no_response(std::uint8_t cmd, void const *p, std::size_t plen)
{
	send(cmd, p, plen);
	check_command_status();
}

void osd_connection::synchronize()
{
	send_no_response(0x21);
}
