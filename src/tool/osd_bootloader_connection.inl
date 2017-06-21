template<class Response>
Response osd_bootloader_connection::get_response()
{
	auto r = read<Response>();
	check_command_status();
	return r;
}

template<class Data>
void osd_bootloader_connection::send(std::uint8_t cmd, Data const &p)
{
	send(cmd, std::addressof(p), sizeof(p));
}
