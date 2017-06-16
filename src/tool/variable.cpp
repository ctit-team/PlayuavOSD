#include "variable.hpp"

#include "device_properties.hpp"

template<class Value>
static void test_deserialize(std::string const &s)
{
	command_argument_converter<Value>().from_string(s);
}

static std::map<std::string, variable_properties> props = {
	{ vars::device, variable_properties{
		.test_deserialize = test_deserialize<device_properties>
	}}
};

char const *vars::device = "DEVICE";

std::map<std::string, variable_properties> const &variables_props = props;
std::unordered_map<std::string, std::string> variables_value;
