#ifndef EXIT_COMMAND_HPP_INCLUDED
#define EXIT_COMMAND_HPP_INCLUDED

#include "command.hpp"

class exit_command final : public command {
public:
	static exit_command instance;

	const char * name() const override;
	const char * argument_description() const override;
	const char * description() const override;
	void show_help() const override;

	bool execute(const std::vector<std::string>& args) override;
private:
	exit_command();
	~exit_command();
};

#endif // EXIT_COMMAND_HPP_INCLUDED
