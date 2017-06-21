#ifndef OSD_CONNECTION_HPP_INCLUDED
#define OSD_CONNECTION_HPP_INCLUDED

#include "osd_bootloader_connection.hpp"
#include "osd_command.hpp"
#include "serial_connection.hpp"

#include <chrono>
#include <cinttypes>

class osd_connection final : public serial_connection {
public:
	// types
	enum class command_status : std::uint8_t {
		ok = 0x10,
		failed = 0x11,
		invalid = 0x13
	};

	// constructors/destructors
	osd_connection(osd_connection &&other);
	osd_connection(osd_connection const &) = delete;

	// operators
	osd_connection &operator=(osd_connection const &) = delete;
	osd_connection &operator<<(osd_command const &cmd);
	template<class Response>
	osd_connection &operator>>(Response &resp);

	// methods
	static osd_connection &get(std::string const &dev);

	void send(std::uint8_t cmd, void const *p = nullptr, std::size_t plen = 0);
	void send_no_response(std::uint8_t cmd, void const *p = nullptr, std::size_t plen = 0);

	command_status get_command_status();
	void check_command_status();
	void synchronize();

	osd_bootloader_connection reboot_to_bootloader(std::chrono::seconds const &timeout);
private:
	osd_connection() noexcept;
};

#include "osd_connection.inl"

#endif // OSD_CONNECTION_HPP_INCLUDED
