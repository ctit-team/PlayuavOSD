#include "file_descriptor.hpp"

#include "string.hpp"

#include <cassert>
#include <cerrno>
#include <iostream>
#include <system_error>
#include <thread>

#include <unistd.h>

// constructors/destructors

file_descriptor::file_descriptor() noexcept : file_descriptor(-1)
{
}

file_descriptor::file_descriptor(bool transfer_ownership) noexcept : file_descriptor(-1, transfer_ownership)
{
}

file_descriptor::file_descriptor(int fd, bool transfer_ownership) noexcept :
	fd(fd),
	owned(transfer_ownership)
{
}

file_descriptor::file_descriptor(file_descriptor &&other) noexcept :
	fd(other.fd),
	owned(other.owned)
{
	other.fd = -1;
	other.owned = false;
}

file_descriptor::~file_descriptor()
{
	if (owned && valid()) {
		try {
			close();
		} catch (std::exception &e) {
			std::cerr << "failed to close file descriptor #" << fd << ": " << to_string(e) << std::endl;
		}
	}
}

// methods

void file_descriptor::close()
{
	if (!valid()) {
		throw std::logic_error("the file descriptor is not valid");
	}

	if (::close(fd)) {
		throw std::system_error(errno, std::system_category());
	}

	fd = -1;
}

void file_descriptor::read(void *buf, std::size_t nbyte)
{
	assert(buf);

	if (!valid()) {
		throw std::logic_error("the file descriptor is not valid");
	}

	if (!nbyte) {
		return;
	}

	std::size_t got = 0;

	while (got < nbyte) {
		auto n = ::read(fd, reinterpret_cast<std::uint8_t *>(buf) + got, nbyte - got);

		if (n == -1) {
			auto err = errno;
			if (err == EAGAIN) {
				std::this_thread::yield(); // FIXME: figure out solution in case of slow connection
				continue;
			}
			throw std::system_error(err, std::system_category());
		}

		got += static_cast<std::size_t>(n);
	}
}

bool file_descriptor::valid() const
{
	return fd >= 0;
}

void file_descriptor::write(void const *data, std::size_t nbyte)
{
	assert(data);

	if (!valid()) {
		throw std::logic_error("the file descriptor is not valid");
	}

	std::size_t written = 0;

	while (written < nbyte) {
		auto n = ::write(fd, reinterpret_cast<std::uint8_t const *>(data) + written, nbyte - written);

		if (n == -1) {
			auto err = errno;
			if (err == EAGAIN) {
				std::this_thread::yield();
				continue;
			}
			throw std::system_error(err, std::system_category());
		}

		written += static_cast<std::size_t>(n);
	}
}
