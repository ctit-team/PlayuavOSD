#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED

#include <string>
#include <vector>

class command {
public:
	command(const command&) = delete;

	command& operator=(const command&) = delete;

	virtual const char * name() const = 0;
	virtual const char * argument_description() const = 0;
	virtual const char * description() const = 0;
	virtual void show_help() const;

	virtual bool execute(const std::vector<std::string>& args) = 0;
protected:
	command();
	~command();
};

#endif // COMMAND_HPP_INCLUDED
