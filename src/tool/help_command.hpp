#ifndef HELP_COMMAND_HPP_INCLUDED
#define HELP_COMMAND_HPP_INCLUDED

#include "command.hpp"

#include <string>

class help_command final : public command {
public:
	static help_command instance;

	const char * name() const override;
	const char * argument_description() const override;
	const char * description() const override;
	void show_help() const override;

	bool execute(const std::vector<std::string>& args) override;
private:
	help_command();
	~help_command();

	void print_commands();
	bool print_command_help(const std::string& name);
};

#endif // HELP_COMMAND_HPP_INCLUDED
