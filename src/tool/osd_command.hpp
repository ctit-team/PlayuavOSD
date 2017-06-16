#ifndef OSD_COMMAND_HPP_INCLUDED
#define OSD_COMMAND_HPP_INCLUDED

#include <cinttypes>
#include <vector>

class osd_command {
public:
	virtual ~osd_command();

	virtual osd_command &operator=(osd_command const &rhs);

	virtual std::uint8_t id() const = 0;
	virtual std::vector<std::uint8_t> build_payload() const = 0;
protected:
	osd_command();
	osd_command(osd_command const &rhs);
};

#endif // OSD_COMMAND_HPP_INCLUDED
