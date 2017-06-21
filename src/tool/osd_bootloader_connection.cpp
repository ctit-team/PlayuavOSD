#include "osd_bootloader_connection.hpp"

osd_bootloader_connection::osd_bootloader_connection() noexcept
{
}

osd_bootloader_connection::osd_bootloader_connection(osd_bootloader_connection &&other) : serial_connection(std::forward<serial_connection>(other))
{
}

void osd_bootloader_connection::check_command_status()
{
	switch (get_command_status()) {
	case command_status::ok:
		break;
	case command_status::failed:
		throw std::runtime_error("the last command that sent to device is failed");
	case command_status::invalid:
		throw std::runtime_error("the last command that sent to device is not valid");
	default:
		throw std::runtime_error("device response with unknown status");
	}
}

osd_bootloader_connection::command_status osd_bootloader_connection::get_command_status()
{
	if (!valid()) {
		throw std::logic_error("connection is closed");
	}

	// expect 0x12 before status
	if (read<std::uint8_t>() != 0x12) {
		throw std::runtime_error("out of sync with device");
	}

	// get status code
	return static_cast<command_status>(read<std::uint8_t>());
}

osd_bootloader_connection::device_info osd_bootloader_connection::get_device_info()
{
	device_info info;

	// boot loader revision
	send<std::uint8_t>(0x22, 1);
	info.bootloader_rev = get_response<std::uint32_t>();

	// board type
	send<std::uint8_t>(0x22, 2);
	info.board_type = get_response<std::uint32_t>();

	// board revision
	send<std::uint8_t>(0x22, 3);
	info.board_rev = get_response<std::uint32_t>();

	// firmware's size
	send<std::uint8_t>(0x22, 4);
	info.firmware_size = get_response<std::uint32_t>();

	return info;
}

void osd_bootloader_connection::send(std::uint8_t cmd, void const *p, std::size_t plen)
{
	if (!valid()) {
		throw std::logic_error("connection is closed");
	}

	// allocate message buffer
	auto eoc = std::uint8_t(0x20);
	auto len = sizeof(cmd) + plen + sizeof(eoc);
	auto data = std::make_unique<std::uint8_t>(len);

	// build message
	std::memcpy(data.get(), &cmd, sizeof(cmd));
	if (p && plen) {
		std::memcpy(data.get() + sizeof(cmd), p, plen);
	}
	std::memcpy(data.get() + sizeof(cmd) + plen, &eoc, sizeof(eoc));

	// send
	write(data.get(), len);
}

void osd_bootloader_connection::send_no_response(std::uint8_t cmd, void const *p, std::size_t plen)
{
	send(cmd, p, plen);
	check_command_status();
}

void osd_bootloader_connection::synchronize()
{
	send_no_response(0x21);
}
