#ifndef ARGUMENT_DESCRIPTOR_HPP_INCLUDED
#define ARGUMENT_DESCRIPTOR_HPP_INCLUDED

#include <string>

struct argument_descriptor final {
	std::string name;
	bool required;
	bool multiple;
	bool variable;
};

#endif // ARGUMENT_DESCRIPTOR_HPP_INCLUDED
