#ifndef ARGUMENT_HPP_INCLUDED
#define ARGUMENT_HPP_INCLUDED

#include <string>

class command_argument final {
public:
	command_argument(std::string const &name, std::string const &val);

	std::string const &name() const;
	template<class Value>
	Value as() const;
private:
	std::string n;
	std::string v;
};

template<class Value>
struct command_argument_converter final {
	Value from_string(std::string const &s) const;
};

#include "command_argument.inl"

#endif // ARGUMENT_HPP_INCLUDED
