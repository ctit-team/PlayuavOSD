#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED

#include "argument_descriptor.hpp"
#include "command_argument.hpp"

#include <string>
#include <vector>

class command {
public:
	command(command const &) = delete;

	command &operator=(command const &) = delete;

	// command properties
	virtual char const *name() const = 0;
	virtual std::vector<argument_descriptor const> const &arguments() const = 0;
	std::string argument_description() const;
	virtual std::string description() const = 0;
	virtual std::string help_text() const = 0;

	void show_help() const;

	virtual bool execute(std::vector<command_argument> const &args) = 0;
protected:
	static std::vector<argument_descriptor const> noarg;

	command();
	~command();
};

#endif // COMMAND_HPP_INCLUDED
