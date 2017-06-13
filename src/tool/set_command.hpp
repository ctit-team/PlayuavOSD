#ifndef SET_COMMAND_HPP_INCLUDED
#define SET_COMMAND_HPP_INCLUDED

#include "command.hpp"

class set_command final : public command {
public:
	static set_command instance;

	char const *name() const override;
	std::vector<argument_descriptor const> const &arguments() const override;
	char const *description() const override;
	char const *help_text() const override;

	bool execute(std::vector<std::string> const &args) override;
private:
	set_command();
	~set_command();
};

#endif // SET_COMMAND_HPP_INCLUDED
