#include "command.hpp"
#include "program.hpp"

#include <iostream>

command::command()
{
}

command::~command()
{
}

void command::show_help() const
{
	std::cout << "Usage: " << program::instance.get_usage_text(name(), argument_description()) << std::endl;
}
