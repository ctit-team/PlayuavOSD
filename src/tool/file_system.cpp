#include "file_system.hpp"

#include <cerrno>
#include <system_error>
#include <utility>

#include <fcntl.h>

file_system::file_system() noexcept
{
}

file_system::file_system(file_system &&other) : file_descriptor(std::forward<file_descriptor>(other))
{
}

void file_system::open(std::string const &name, int flags, mode_t mode)
{
	// check if already opened
	if (valid()) {
		throw std::logic_error("file is already opened");
	}

	// open device
	fd = ::open(name.c_str(), flags, mode);
	if (fd < 0) {
		throw std::system_error(errno, std::system_category());
	}
}
