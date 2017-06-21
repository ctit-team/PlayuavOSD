#ifndef FILE_DESCRIPTOR_HPP_INCLUDED
#define FILE_DESCRIPTOR_HPP_INCLUDED

#include <cstdlib>

class file_descriptor {
public:
	// constructors/destructors
	explicit file_descriptor(int fd, bool transfer_ownership = true) noexcept;
	file_descriptor(file_descriptor &&other) noexcept;
	file_descriptor(file_descriptor const &) = delete;
	virtual ~file_descriptor();

	// operators
	file_descriptor &operator=(file_descriptor const &) = delete;

	// methods
	bool valid() const;

	virtual void close();

	template<class Data>
	Data read();
	void read(void *buf, std::size_t nbyte);
	template<class Data>
	void write(Data const &data);
	void write(void const *data, std::size_t nbyte);

protected:
	int fd;

	file_descriptor() noexcept;
	file_descriptor(bool transfer_ownership) noexcept;

private:
	bool owned;
};

#include "file_descriptor.inl"

#endif // FILE_DESCRIPTOR_HPP_INCLUDED
