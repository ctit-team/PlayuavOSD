#include "osd_info_request.hpp"

osd_info_request::osd_info_request(info_type type) :
	type(type)
{
}

osd_info_request::osd_info_request(osd_info_request const &other) :
	type(other.type)
{
}

osd_info_request::~osd_info_request()
{
}

osd_info_request &osd_info_request::operator=(osd_command const &rhs)
{
	osd_command::operator=(rhs);

	auto *cmd = dynamic_cast<osd_info_request const *>(std::addressof(rhs));
	if (cmd) {
		type = cmd->type;
	}

	return *this;
}

std::vector<std::uint8_t> osd_info_request::build_payload() const
{
	return { static_cast<std::uint8_t>(type) };
}

std::uint8_t osd_info_request::id() const
{
	return 0x22;
}
