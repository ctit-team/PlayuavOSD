#ifndef OSD_CONNECTION_HPP_INCLUDED
#define OSD_CONNECTION_HPP_INCLUDED

#include "osd_command.hpp"
#include "serial_connection.hpp"

class osd_connection final : public serial_connection {
public:
	osd_connection(osd_connection &&other);
	osd_connection(osd_connection const &) = delete;

	osd_connection &operator=(osd_connection const &) = delete;
	osd_connection &operator<<(osd_command const &cmd);
	template<class Response>
	osd_connection &operator>>(Response &resp);

	static osd_connection &get(std::string const &dev);

	void synchronize();
private:
	osd_connection() noexcept;
};

#include "osd_connection.inl"

#endif // OSD_CONNECTION_HPP_INCLUDED
