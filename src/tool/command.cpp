#include "command.hpp"
#include "program.hpp"

#include <iostream>
#include <sstream>

std::vector<argument_descriptor const> command::noarg;

command::command()
{
}

command::~command()
{
}

std::string command::argument_description() const
{
	// convert argument objects to string representation
	auto &args = arguments();
	std::vector<std::string> descs;

	std::transform(args.begin(), args.end(), std::back_inserter(descs), [](argument_descriptor const &desc) -> std::string {
		auto name = desc.variable ? '$' + desc.name : desc.name;
		auto str = desc.required ? name : '[' + name + ']';
		return desc.multiple ? str + "..." : str;
	});

	// merge strings to one line
	std::ostringstream merged;
	std::copy(descs.begin(), descs.end(), std::ostream_iterator<std::string>(merged, " "));

	return merged.str();
}

void command::show_help() const
{
	std::cout << "Usage: " << program::instance.get_usage_text(name(), argument_description()) << std::endl
			  << std::endl
			  << help_text() << std::endl;
}
