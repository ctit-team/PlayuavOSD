#include "help_command.hpp"
#include "program.hpp"

#include <boost/format.hpp>

#include <iostream>

help_command help_command::instance;

help_command::help_command()
{
}

help_command::~help_command()
{
}

const char * help_command::argument_description() const
{
	return "[COMMAND]";
}

const char * help_command::description() const
{
	return "show help message for the command(s)";
}

bool help_command::execute(const std::vector<std::string>& args)
{
	switch (args.size()) {
	case 0:
		print_commands();
		break;
	case 1:
		if (!print_command_help(args[0])) {
			throw std::runtime_error(boost::str(boost::format("help for command '%s' does not exists") % args[0]));
		}
		break;
	default:
		throw std::runtime_error("invalid command's arguments");
	}

	return true;
}

const char * help_command::name() const
{
	return "help";
}

bool help_command::print_command_help(const std::string& name)
{
	auto& commands = program::instance.get_commands();

	auto it = commands.find(name);
	if (it == commands.end()) {
		return false;
	}

	it->second.get().show_help();

	return true;
}

void help_command::print_commands()
{
	std::cout << "Available commands:" << std::endl;

	for (auto& e : program::instance.get_commands()) {
		auto& cmd = e.second.get();
		auto usage = program::instance.get_usage_text(cmd.name(), cmd.argument_description(), false);

		std::cout << boost::format("%-40s %s") % usage % cmd.description() << std::endl;
	}
}

void help_command::show_help() const
{
	command::show_help();

	std::cout << std::endl
			  << "Print the instruction message for a specified COMMAND." << std::endl
			  << "If COMMAND is omitted, print the summary of all available commands." << std::endl;
}
