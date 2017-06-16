#include <boost/format.hpp>

template<class Value>
inline Value command_argument::get() const
{
	command_argument_converter<Value> c;

	try {
		return c.from_string(v);
	} catch (...) {
		auto msg = boost::format("value for '%s' is not valid") % n;
		std::throw_with_nested(std::runtime_error(boost::str(msg)));
	}
}

template<class Value>
inline Value command_argument_converter<Value>::from_string(std::string const &s) const
{
	return Value(s);
}
