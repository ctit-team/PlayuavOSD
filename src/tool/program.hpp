#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "command.hpp"
#include "command_argument.hpp"
#include "variable.hpp"

#include <functional>
#include <map>
#include <string>

typedef std::map<std::string, std::reference_wrapper<command>> command_table;

class program final {
public:
	// fields
	static program instance;

	// constructors/destructors
	program(program const &) = delete;

	// operators
	program &operator=(program const &) = delete;

	// methods
	command_table const &commands() const { return cmds; }
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
	command_table cmds;

	program();
	~program();

	void initialize_command_table();

	int run_interactive();
	int run_non_interactive(int argc, char *argv[]);
	command_result execute_command(std::string const &name, std::vector<std::string> const &args);
	std::vector<command_argument> transform_command_arguments(command const &cmd, std::vector<std::string> const &args);
};

#endif // PROGRAM_HPP_INCLUDED
