#include "osd_connection.hpp"

#include <algorithm>
#include <iterator>
#include <cinttypes>
#include <unordered_map>
#include <utility>
#include <vector>

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
	auto payload = cmd.build_payload();
	std::vector<std::uint8_t> data;

	data.push_back(cmd.id());
	std::copy(payload.begin(), payload.end(), std::back_inserter(data));
	data.push_back(0x20);

	write(data.data(), data.size()); return *this;
}

// methods

osd_connection &osd_connection::get(std::string const &dev)
{
	if (!connections.count(dev)) {
		osd_connection con;

		try {
			con.open(dev);
		} catch (...) {
			std::throw_with_nested(std::runtime_error("failed to open device"));
		}

		try {
			con.set_speed(B115200);
		} catch (...) {
			std::throw_with_nested(std::runtime_error("failed to set connection speed"));
		}

		connections.insert(std::make_pair(dev, std::move(con)));
	}

	return connections.find(dev)->second;
}

void osd_connection::synchronize()
{
	if (!valid()) {
		throw std::logic_error("no connection");
	}

	// expect 0x12
	std::uint8_t val; read(&val, sizeof(val));
	if (val != 0x12) {
		throw std::runtime_error("out of sync with device");
	}

	// get status code
	read(&val, sizeof(val));

	switch (val) {
	case 0x10:
		return;
	case 0x13:
		throw std::runtime_error("the last command that sent to the device is not valid");
	default:
		throw std::runtime_error("device response with unknown status");
	}
}
