#ifndef DEVICE_PROPERTIES_HPP_INCLUDED
#define DEVICE_PROPERTIES_HPP_INCLUDED

#include "command_argument.hpp"

#include <string>

enum class device_type {
	osd_board
};

struct device_properties final {
	std::string name;
	device_type type;
};

#include "device_properties.inl"

#endif // DEVICE_PROPERTIES_HPP_INCLUDED
