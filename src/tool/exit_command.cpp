#include "exit_command.hpp"

#include <iostream>

exit_command exit_command::instance;

exit_command::exit_command()
{
}

exit_command::~exit_command()
{
}

const char * exit_command::argument_description() const
{
	return "";
}

const char * exit_command::description() const
{
	return "exit the program";
}

bool exit_command::execute(const std::vector<std::string>& args)
{
	return false;
}

const char * exit_command::name() const
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
