#ifndef VARIABLE_HPP_INCLUDED
#define VARIABLE_HPP_INCLUDED

#include <functional>
#include <map>
#include <string>
#include <unordered_map>

namespace vars {
	extern char const *device;
}

struct variable_properties final {
	std::function<void(std::string const &)> test_deserialize;
};

extern std::map<std::string, variable_properties> const &variables_props;
extern std::unordered_map<std::string, std::string> variables_value;

#endif // VARIABLE_HPP_INCLUDED
