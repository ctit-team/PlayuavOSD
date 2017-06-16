#include <boost/format.hpp>

template<>
inline device_properties command_argument_converter<device_properties>::from_string(std::string const &s) const
{
	// finding separator
	auto i = s.find(':');
	if (i == std::string::npos) {
		throw std::invalid_argument("the value is invalid format");
	}

	// extract values
	auto name = s.substr(0, i);
	auto type = s.substr(i + 1);

	if (name.empty() || type.empty()) {
		throw std::invalid_argument("the value is invalid format");
	}

	// deserialize
	device_properties props;

	if (type == "osd") {
		props.type = device_type::osd_board;
	} else {
		throw std::invalid_argument(boost::str(boost::format("device's type '%s' is not valid") % type));
	}

	props.name = name;

	return props;
}
