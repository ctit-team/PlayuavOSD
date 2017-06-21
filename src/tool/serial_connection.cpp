#include "serial_connection.hpp"

#include <cerrno>
#include <cstdlib>
#include <stdexcept>
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
	clear();
	file_system::close();
}

void serial_connection::open(std::string const &dev, speed_t spd)
{
	open(dev, O_RDWR | O_NOCTTY);

	try {
		set_attributes(spd);
	} catch (...) {
		close();
		std::throw_with_nested(std::runtime_error("failed to set connection attributes"));
	}
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

void serial_connection::set_attributes(speed_t spd)
{
	if (!valid()) {
		throw std::logic_error("the connection is closed");
	}

	// configure attributes
	auto attr = this->attr;

	if (cfsetospeed(&attr, spd) || cfsetispeed(&attr, spd)) {
		throw std::system_error(errno, std::system_category());
	}

	attr.c_cflag &= ~(CSIZE | PARENB | CSTOPB | CRTSCTS);
	attr.c_cflag |= CS8 | CLOCAL | CREAD;
	attr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | IEXTEN | ISIG);

	attr.c_iflag &= ~(INPCK | PARMRK | ISTRIP | IXON | IXOFF | IXANY | INLCR | ICRNL | BRKINT);
	attr.c_iflag |= IGNPAR | IGNCR | IGNBRK;
	attr.c_oflag &= ~OPOST;

	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 5;

	// apply attributes
	try {
		if (tcflush(fd, TCIOFLUSH)) {
			throw std::system_error(errno, std::system_category());
		}
	} catch (...) {
		std::throw_with_nested(std::runtime_error("failed to flush data"));
	}

	if (tcsetattr(fd, TCSANOW, &attr)) {
		throw std::system_error(errno, std::system_category());
	}

	this->attr = attr;
}
