#include "command_argument.hpp"

command_argument::command_argument(std::string const &name, std::string const &val) :
	n(name),
	v(val)
{
}

std::string const &command_argument::name() const
{
	return n;
}
