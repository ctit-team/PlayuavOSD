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

bool exit_command::execute(std::vector<std::string> const &args)
{
	return false;
}

char const *exit_command::name() const
{
	return "exit";
}

void exit_command::show_help() const
{
	command::show_help();

	std::cout << std::endl
			  << "Exit the program."
			  << std::endl;
}
