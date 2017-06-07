#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "command.hpp"

#include <functional>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::reference_wrapper<command>> command_table;

class program final {
public:
	static program instance;

	program(const program&) = delete;

	program& operator=(const program&) = delete;

	const command_table& get_commands() const;
	std::string get_usage_text() const;
	std::string get_usage_text(const std::string& cmd, const std::string& arg_desc) const;
	std::string get_usage_text(const std::string& cmd, const std::string& arg_desc, bool prog_name) const;

	std::string read_input(const std::string& prompt);

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
	command_result execute_command(const std::string& cmd, const std::vector<std::string>& args);
};

#endif // PROGRAM_HPP_INCLUDED
