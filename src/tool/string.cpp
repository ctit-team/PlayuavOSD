#include "string.hpp"

#include <vector>

static void get_exception_messages(std::vector<std::string> &messages, std::exception const &e)
{
	messages.push_back(e.what());

	try {
		std::rethrow_if_nested(e);
	} catch (std::exception &e) {
		get_exception_messages(messages, e);
	}
}

std::string to_string(std::exception const &e)
{
	std::vector<std::string> messages;
	get_exception_messages(messages, e);
	return join(messages.begin(), messages.end(), " -> ");
}

std::string to_string(device_type t)
{
	switch (t) {
	case device_type::osd_board:
		return "osd_board";
	default:
		throw std::invalid_argument("the value is not valid");
	}
}
