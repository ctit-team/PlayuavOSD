#include "info_command.hpp"

#include "device_properties.hpp"
#include "osd_info_request.hpp"
#include "string.hpp"
#include "variable.hpp"

#include <boost/format.hpp>

#include <iostream>

// variables

static std::vector<argument_descriptor const> const args_desc = {
	argument_descriptor{ .name = vars::device, .required = true, .variable = true }
};

info_command info_command::instance;

// constructors/destructors

info_command::info_command()
{
}

info_command::~info_command()
{
}

// methods

std::vector<argument_descriptor const> const &info_command::arguments() const
{
	return args_desc;
}

char const * info_command::description() const
{
	return "get device's details";
}

bool info_command::execute(std::vector<command_argument> const &args)
{
	auto dev = args[0].get<device_properties>();

	switch (dev.type) {
	case device_type::osd_board:
		print_osd_info(dev.name);
		break;
	default:
		throw std::runtime_error(boost::str(boost::format("device type '%s' is not supported") % to_string(dev.type)));
	}

	return true;
}

std::uint8_t info_command::get_osd_firmware_revision(osd_connection &con)
{
	osd_info_request req(osd_info_request::info_type::firmware_revision);
	con << req;

	std::uint8_t rev;
	con.read(&rev, sizeof(rev));
	con.synchronize();

	return rev;
}

char const *info_command::help_text() const
{
	return "Get the specified device's details.";
}

char const * info_command::name() const
{
	return "info";
}

void info_command::print_osd_info(std::string const &dev)
{
	auto &con = osd_connection::get(dev);

	std::cout << "[FR] firmware revision: " << int(get_osd_firmware_revision(con)) << std::endl;
}
