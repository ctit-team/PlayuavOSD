#include "variable.hpp"

namespace vars {
	std::set<std::string> const all({
		device
	});

	char const *device = "DEVICE";
}

std::unordered_map<std::string, std::string> variables_value;
