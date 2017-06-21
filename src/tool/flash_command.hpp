#ifndef FLASH_COMMAND_HPP_INCLUDED
#define FLASH_COMMAND_HPP_INCLUDED

#include "command.hpp"

class flash_command final : public command {
public:
	static flash_command instance;

	flash_command(flash_command const &) = delete;

	flash_command &operator=(flash_command const &) = delete;

	char const *name() const override;
	std::vector<argument_descriptor const> const &arguments() const override;
	std::string description() const override;
	std::string help_text() const override;

	bool execute(std::vector<command_argument> const &args) override;
private:
	flash_command();
	~flash_command();

	void flash_osd(std::string const &dev);
};

#endif // FLASH_COMMAND_HPP_INCLUDED
