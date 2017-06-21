#ifndef INFO_COMMAND_HPP_INCLUDED
#define INFO_COMMAND_HPP_INCLUDED

#include <cinttypes>

#include "command.hpp"
#include "osd_connection.hpp"

class info_command final : public command {
public:
	static info_command instance;

	char const *name() const override;
	std::vector<argument_descriptor const> const &arguments() const override;
	std::string description() const override;
	std::string help_text() const override;

	bool execute(std::vector<command_argument> const &args) override;
private:
	info_command();
	~info_command();

	void print_osd_info(std::string const &dev);
	std::uint8_t get_osd_firmware_revision(osd_connection &con);
};

#endif // INFO_COMMAND_HPP_INCLUDED
