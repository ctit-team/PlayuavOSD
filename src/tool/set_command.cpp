#include "set_command.hpp"

#include "variable.hpp"

#include <boost/format.hpp>

#include <iostream>

static std::vector<argument_descriptor const> const args_desc = {
	argument_descriptor{ .name = "VARIABLE", .required = true },
	argument_descriptor{ .name = "VALUE", .required = true }
};

set_command set_command::instance;

set_command::set_command()
{
}

set_command::~set_command()
{
}

std::vector<argument_descriptor const> const &set_command::arguments() const
{
	return args_desc;
}

char const *set_command::description() const
{
	return "set the variable value";
}

char const *set_command::help_text() const
{
	return "Assign the value to the variable.";
}

char const *set_command::name() const
{
	return "set";
}

bool set_command::execute(std::vector<command_argument> const &args)
{
	auto name = args[0].get<std::string>();
	auto value = args[1].get<std::string>();

	// load variable's properties
	auto it = variables_props.find(name);
	if (it == variables_props.end()) {
		throw std::runtime_error(boost::str(boost::format("the variable '%s' does not exists") % name));
	}
	auto &props = it->second;

	// set value
	if (props.test_deserialize) {
		props.test_deserialize(value);
	}

	variables_value[name] = value;

	return true;
}
