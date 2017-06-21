#include "osd_command.hpp"

osd_command::osd_command()
{
}

osd_command::osd_command(osd_command const &rhs)
{
}

osd_command::~osd_command()
{
}

osd_command& osd_command::operator=(osd_command const &rhs)
{
	return *this;
}

std::vector<std::uint8_t> osd_command::build_payload() const
{
	return std::vector<std::uint8_t>();
}
