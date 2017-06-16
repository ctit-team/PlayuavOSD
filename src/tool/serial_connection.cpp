#include "serial_connection.hpp"

#include <cerrno>
#include <cstdlib>
#include <system_error>
#include <utility>

#include <fcntl.h>

// constructor/destructors

serial_connection::serial_connection() noexcept
{
	std::memset(&attr, 0, sizeof(attr));
}

serial_connection::serial_connection(serial_connection &&other) : file_system(std::forward<file_system>(other)),
	attr(other.attr)
{
	std::memset(&other.attr, 0, sizeof(other.attr));
}

serial_connection::~serial_connection()
{
	clear();
}

// methods

void serial_connection::clear()
{
	std::memset(&attr, 0, sizeof(attr));
}

void serial_connection::close()
{
	file_system::close();
	clear();
}

void serial_connection::open(std::string const &dev)
{
	open(dev, O_RDWR | O_NOCTTY);
}

void serial_connection::open(std::string const &name, int flags, mode_t mode)
{
	file_system::open(name, flags, mode);

	try {
		if (tcgetattr(fd, &attr)) {
			throw std::system_error(errno, std::system_category());
		}
	} catch (...) {
		close();
		std::throw_with_nested(std::runtime_error("failed to get terminal attributes"));
	}
}

void serial_connection::set_speed(speed_t value)
{
	if (!valid()) {
		throw std::logic_error("the connection is closed");
	}

	if (cfsetospeed(&attr, value) || cfsetispeed(&attr, value)) {
		throw std::system_error(errno, std::system_category());
	}

	if (tcsetattr(fd, TCSAFLUSH, &attr)) {
		throw std::system_error(errno, std::system_category());
	}
}
