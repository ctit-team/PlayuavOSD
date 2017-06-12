#ifndef VARIABLE_HPP_INCLUDED
#define VARIABLE_HPP_INCLUDED

#include <set>
#include <string>
#include <unordered_map>

namespace vars {
	extern std::set<std::string> const all;
	extern char const *device;
}

extern std::unordered_map<std::string, std::string> variables_value;

#endif // VARIABLE_HPP_INCLUDED
