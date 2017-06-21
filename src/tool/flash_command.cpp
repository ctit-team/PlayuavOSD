#include "flash_command.hpp"

#include "device_properties.hpp"
#include "osd_connection.hpp"
#include "variable.hpp"

#include <boost/format.hpp>

#include <iostream>

static std::vector<argument_descriptor const> const args_desc = {
	argument_descriptor{ .name = vars::device, .required = true, .variable = true },
	argument_descriptor{ .name = "FILE", .required = true }
};

flash_command flash_command::instance;

flash_command::flash_command()
{
}

flash_command::~flash_command()
{
}

std::vector<argument_descriptor const> const &flash_command::arguments() const
{
	return args_desc;
}

std::string flash_command::description() const
{
	return "flash device's firmware";
}

bool flash_command::execute(std::vector<command_argument> const &args)
{
	auto dev = args[0].as<device_properties>();
	auto fname = args[1].as<std::string>();

	switch (dev.type) {
	case device_type::osd_board:
		flash_osd(dev.name);
		break;
	default:
		throw std::runtime_error(boost::str(boost::format("device's type '%s' is not supported") % to_string(dev.type)));
	}

	return true;
}

void flash_command::flash_osd(std::string const &dev)
{
	// switch to boot loader
	std::cout << "switching connection to boot loader...\n";

	auto con = osd_connection::get(dev).reboot_to_bootloader(std::chrono::seconds(30));

	// check boot loader
	auto di = con.get_device_info();

	if (di.bootloader_rev < 2 || di.bootloader_rev > 4) {
		throw std::runtime_error("device's bootloader is not supported");
	}

	std::cout << std::endl;
	std::cout << "=== [DI] Device's information ===" << std::endl
			  << "[BR] Bootloader revision: " << di.bootloader_rev << std::endl
			  << "[DT] Device type:         " << di.board_type << std::endl
			  << "[DR] Device revision:     " << di.board_rev << std::endl
			  << "[FS] Firmware size:       " << di.firmware_size << std::endl;
}

std::string flash_command::help_text() const
{
	auto text = boost::format("flash firmware image %s to device %s.") % args_desc[1].name % args_desc[0].name;
	return boost::str(text);
}

char const *flash_command::name() const
{
	return "flash";
}
