#include <memory>

template<class Data>
Data file_descriptor::read()
{
	Data d;
	read(std::addressof(d), sizeof(d));
	return d;
}

template<class Data>
void file_descriptor::write(Data const &data)
{
	write(std::addressof(data), sizeof(data));
}
