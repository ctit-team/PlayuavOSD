#ifndef OSD_BOOTLOADER_CONNECTION_HPP_INCLUDED
#define OSD_BOOTLOADER_CONNECTION_HPP_INCLUDED

#include "serial_connection.hpp"

#include <cinttypes>

class osd_bootloader_connection final : public serial_connection {
public:
	enum class command_status : std::uint8_t {
		ok = 0x10,
		failed = 0x11,
		invalid = 0x13
	};

	struct device_info {
		std::uint32_t bootloader_rev;
		std::uint32_t board_type;
		std::uint32_t board_rev;
		std::uint32_t firmware_size;
	};

	osd_bootloader_connection() noexcept;
	osd_bootloader_connection(osd_bootloader_connection &&other);
	osd_bootloader_connection(osd_bootloader_connection const &) = delete;

	osd_bootloader_connection &operator=(osd_bootloader_connection const &) = delete;

	command_status get_command_status();
	void check_command_status();
	template<class Response>
	Response get_response();

	device_info get_device_info();
	void synchronize();

private:
	template<class Data>
	void send(std::uint8_t cmd, Data const &p);
	void send(std::uint8_t cmd, void const *p = nullptr, std::size_t plen = 0);
	void send_no_response(std::uint8_t cmd, void const *p = nullptr, std::size_t plen = 0);
};

#include "osd_bootloader_connection.inl"

#endif // OSD_BOOTLOADER_CONNECTION_HPP_INCLUDED
