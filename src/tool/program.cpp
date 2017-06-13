#include "program.hpp"

#include "exit_command.hpp"
#include "help_command.hpp"
#include "set_command.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include <readline/readline.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

program program::instance;

int main(int argc, char *argv[])
{
	return program::instance.run(argc, argv);
}

program::program() :
	running(false),
	interactive(false)
{
	initialize_command_table();
}

program::~program()
{
}

program::command_result program::execute_command(std::string const &name, std::vector<std::string> const &args)
{
	try {
		// locate the command to execute
		auto it = commands.find(name);
		if (it == commands.end()) {
			throw std::runtime_error("command does not exists");
		}

		auto &cmd = it->second.get();

		// execute
		return cmd.execute(transform_command_arguments(cmd, args)) ? command_result::success : command_result::stop_program;
	} catch (std::exception &e) {
		std::cerr << "failed to execute '" << name << "' command: " << e.what() << std::endl;
		return command_result::error;
	}
}

command_table const &program::get_commands() const
{
	return commands;
}

std::string program::get_usage_text() const
{
	return name + " COMMAND [ARG]...";
}

std::string program::get_usage_text(std::string const &cmd, std::string const &arg_desc) const
{
	return get_usage_text(cmd, arg_desc, !interactive);
}

std::string program::get_usage_text(std::string const &cmd, std::string const &arg_desc, bool prog_name) const
{
	std::string text = prog_name ? name + ' ' : "";

	text += cmd;

	if (!arg_desc.empty()) {
		text += ' ' + arg_desc;
	}

	return text;
}

void program::initialize_command_table()
{
	commands.insert({
		{ exit_command::instance.name(), std::ref<command>(exit_command::instance) },
		{ help_command::instance.name(), std::ref<command>(help_command::instance) },
		{ set_command::instance.name(), std::ref<command>(set_command::instance) }
	});
}

std::string program::read_input(std::string const &prompt)
{
	std::unique_ptr<char[], void (*) (void *)> line(readline(prompt.c_str()), std::free);

	if (line) {
		add_history(line.get());
		return line.get();
	} else {
		return "";
	}
}

int program::run(int argc, char *argv[])
{
	// prevent double call
	if (running) {
		throw std::logic_error("the program is already running");
	}

	running = true;

	// run
	name = argv[0];

	if (argc >= 2) {
		return run_non_interactive(argc, argv);
	} else {
		interactive = true;
		return run_interactive();
	}
}

int program::run_interactive()
{
	for (;;) {
		// read input
		std::string input = read_input("\33[34mosd-tool\33[0m: ");
		std::vector<std::string> argv;

		boost::algorithm::split(argv, input, boost::is_any_of("\t "), boost::token_compress_on);

		if (!argv.size()) {
			continue;
		}

		auto cmd = argv[0];
		if (cmd.empty()) {
			continue;
		}

		// execute command
		auto args = argv.size() > 1 ? std::vector<std::string>(&argv[1], &argv[argv.size()]) : std::vector<std::string>();

		if (execute_command(argv[0], args) == command_result::stop_program) {
			return EXIT_SUCCESS;
		}
	}
}

int program::run_non_interactive(int argc, char *argv[])
{
	// parse arguments
	std::string cmd = argv[1];
	std::vector<std::string> args;

	std::transform(&argv[2], &argv[argc], std::back_inserter(args), [](char const *arg) -> std::string {
		return arg;
	});

	// execute command
	if (cmd == help_command::instance.name() && !args.size()) {
		std::cout << "Usage: " << get_usage_text() << std::endl;
		std::cout << std::endl;
	}

	switch (execute_command(cmd, args)) {
	case command_result::success:
	case command_result::stop_program:
		return EXIT_SUCCESS;
	case command_result::error:
		return EXIT_FAILURE;
	default:
		throw std::logic_error("the command executor return unexpected result");
	}
}

std::vector<std::string> program::transform_command_arguments(command const &cmd, std::vector<std::string> const &args)
{
	// transfer arguments
	auto current_arg = args.begin();
	auto opt_phase = false;
	std::vector<std::string> result;

	for (auto &desc : cmd.arguments()) {
		// check argument's order
		if (opt_phase && desc.required) {
			auto msg = boost::str(boost::format("the required arguments of the command '%s' must come before optionals") % cmd.name());
			throw std::logic_error(msg);
		}

		if (!desc.required) {
			opt_phase = true;
		}

		// load variable
		if (desc.variable) {
			if (!desc.required) {
				auto msg = boost::format("the argument '%s' for the command '%s' is a variable but it's not required") % desc.name % cmd.name();
				throw std::logic_error(boost::str(msg));
			}

			if (!vars::all.count(desc.name)) {
				auto msg = boost::format("the argument '%s' for the command '%s' is not a valid variable") % desc.name % cmd.name();
				throw std::logic_error(boost::str(msg));
			}

			auto it = variables_value.find(desc.name);
			if (it != variables_value.end()) {
				result.push_back(it->second);
				continue;
			}
		}

		// use value that user supplied
		if (current_arg == args.end()) {
			if (opt_phase) break;
			throw std::runtime_error("insufficient arguments");
		}

		result.push_back(*current_arg);
		current_arg++;
	}

	if (current_arg != args.end()) {
		throw std::runtime_error("too many arguments");
	}

	return result;
}
