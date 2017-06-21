#include "device_properties.hpp"

std::string to_string(device_type t)
{
	switch (t) {
	case device_type::osd_board:
		return "osd_board";
	default:
		throw std::invalid_argument("the value is not valid");
	}
}
