#include "exit_command.hpp"

#include <iostream>

exit_command exit_command::instance;

exit_command::exit_command()
{
}

exit_command::~exit_command()
{
}

std::vector<argument_descriptor const> const &exit_command::arguments() const
{
	return noarg;
}

char const *exit_command::description() const
{
	return "exit the program";
}

bool exit_command::execute(std::vector<command_argument> const &args)
{
	return false;
}

char const *exit_command::help_text() const
{
	return "Exit the program.";
}

char const *exit_command::name() const
{
	return "exit";
}
