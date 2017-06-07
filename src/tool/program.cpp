#include "program.hpp"

#include "exit_command.hpp"
#include "help_command.hpp"

#include <boost/algorithm/string.hpp>

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

program::command_result program::execute_command(const std::string& cmd, const std::vector<std::string>& args)
{
	try {
		auto it = commands.find(cmd);
		if (it == commands.end()) {
			throw std::runtime_error("command does not exists");
		}

		return it->second.get().execute(args) ? command_result::success : command_result::stop_program;
	} catch (std::exception& e) {
		std::cerr << "failed to execute '" << cmd << "' command: " << e.what() << std::endl;
		return command_result::error;
	}
}

const command_table& program::get_commands() const
{
	return commands;
}

std::string program::get_usage_text() const
{
	return name + " COMMAND [ARG]...";
}

std::string program::get_usage_text(const std::string& cmd, const std::string& arg_desc) const
{
	return get_usage_text(cmd, arg_desc, !interactive);
}

std::string program::get_usage_text(const std::string& cmd, const std::string& arg_desc, bool prog_name) const
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
		{ help_command::instance.name(), std::ref<command>(help_command::instance) }
	});
}

std::string program::read_input(const std::string& prompt)
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
	std::vector<std::string> args(argc - 2);

	std::transform(&argv[2], &argv[argc], args.begin(), [](const char *arg) {
		return std::string(arg);
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
