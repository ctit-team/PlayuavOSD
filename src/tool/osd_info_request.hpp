#ifndef OSD_INFO_REQUEST_HPP_INCLUDED
#define OSD_INFO_REQUEST_HPP_INCLUDED

#include <cinttypes>

#include "osd_command.hpp"

class osd_info_request final : public osd_command {
public:
	enum class info_type : std::uint8_t {
		firmware_revision = 0x27
	};

	osd_info_request(info_type type);
	osd_info_request(osd_info_request const &other);
	~osd_info_request() override;

	osd_info_request &operator=(osd_command const &rhs) override;
	osd_info_request &operator=(osd_info_request const &) = delete;

	std::uint8_t id() const override;
	std::vector<std::uint8_t> build_payload() const override;
private:
	info_type type;
};

#endif // OSD_INFO_REQUEST_HPP_INCLUDED
