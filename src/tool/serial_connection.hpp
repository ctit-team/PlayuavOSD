#ifndef SERIAL_CONNECTION_HPP_INCLUDED
#define SERIAL_CONNECTION_HPP_INCLUDED

#include "file_system.hpp"

#include <termios.h>

class serial_connection : public file_system {
public:
	serial_connection() noexcept;
	serial_connection(serial_connection &&other);
	serial_connection(serial_connection const &) = delete;
	~serial_connection() override;

	serial_connection &operator=(serial_connection const &) = delete;

	void open(std::string const &dev, speed_t spd = B115200);
	void open(std::string const &name, int flags, mode_t mode = default_mode) override;
	void close() override;

	void set_attributes(speed_t spd);
protected:
	termios attr;
private:
	void clear();
};

#endif // SERIAL_CONNECTION_HPP_INCLUDED
