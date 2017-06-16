#include <vector>

template<class Response>
inline osd_connection &osd_connection::operator>>(Response &resp)
{
	auto d = resp.deserialize();

	for (auto want = d.want(); want;) {
		std::vector<std::uint8_t> data;
		read(data, want);
		d.feed(data);
	}

	synchronize(); return *this;
}
