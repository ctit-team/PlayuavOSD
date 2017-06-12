#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "command.hpp"
#include "variable.hpp"

#include <functional>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::reference_wrapper<command>> command_table;

class program final {
public:
	static program instance;

	program(program const &) = delete;

	program &operator=(program const &) = delete;

	command_table const &get_commands() const;
	std::string get_usage_text() const;
	std::string get_usage_text(std::string const &cmd, std::string const &arg_desc) const;
	std::string get_usage_text(std::string const &cmd, std::string const &arg_desc, bool prog_name) const;

	std::string read_input(std::string const &prompt);

	int run(int argc, char *argv[]);
private:
	enum class command_result {
		success,
		stop_program,
		error
	};

	std::string name;
	bool running;
	bool interactive;
	command_table commands;

	program();
	~program();

	void initialize_command_table();

	int run_interactive();
	int run_non_interactive(int argc, char *argv[]);
	command_result execute_command(std::string const &name, std::vector<std::string> const &args);
	std::vector<std::string> transform_command_arguments(command const &cmd, std::vector<std::string> const &args);
};

#endif // PROGRAM_HPP_INCLUDED
