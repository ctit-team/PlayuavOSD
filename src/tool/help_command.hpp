#ifndef HELP_COMMAND_HPP_INCLUDED
#define HELP_COMMAND_HPP_INCLUDED

#include "command.hpp"

#include <string>

class help_command final : public command {
public:
	static help_command instance;

	char const *name() const override;
	std::vector<argument_descriptor const> const &arguments() const override;
	char const *description() const override;
	char const *help_text() const override;

	bool execute(std::vector<command_argument> const &args) override;
private:
	help_command();
	~help_command();

	void print_commands();
	bool print_command_help(std::string const &name);
};

#endif // HELP_COMMAND_HPP_INCLUDED
