#ifndef EXIT_COMMAND_HPP_INCLUDED
#define EXIT_COMMAND_HPP_INCLUDED

#include "command.hpp"

class exit_command final : public command {
public:
	static exit_command instance;

	char const *name() const override;
	std::vector<argument_descriptor const> const &arguments() const override;
	char const *description() const override;

	void show_help() const override;

	bool execute(std::vector<std::string> const &args) override;
private:
	exit_command();
	~exit_command();
};

#endif // EXIT_COMMAND_HPP_INCLUDED
