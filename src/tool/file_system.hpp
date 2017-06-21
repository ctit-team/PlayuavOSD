#ifndef FILE_SYSTEM_HPP_INCLUDED
#define FILE_SYSTEM_HPP_INCLUDED

#include "file_descriptor.hpp"

#include <string>

#include <sys/stat.h>

class file_system : public file_descriptor {
public:
	static mode_t const default_mode = S_IRWXU | S_IRWXG | S_IRWXO;

	file_system() noexcept;
	file_system(file_system &&other);
	file_system(file_system const &) = delete;

	file_system &operator=(file_system const &) = delete;

	std::string const &name() const;

	virtual void open(std::string const &name, int flags, mode_t mode = default_mode);
	void close() override;
private:
	std::string n;
};

#endif // FILE_SYSTEM_HPP_INCLUDED
