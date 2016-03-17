
#include <ostream>
#include <cstdint>
#include <algorithm>

#ifndef VIRTUALINDEXTYPE_HPP_
#define VIRTUALINDEXTYPE_HPP_

namespace crunch
{
struct virtualIndex_t
{
	virtualIndex_t()
	{
		value = 0;
	}
	virtualIndex_t(uint32_t in) : value(in)
	{

	}
	operator uint32_t() const
	{
		 return (value);
	}
	bool operator<(const virtualIndex_t in) const
	{
		return (value < in.value);
	}
	bool operator<=(const virtualIndex_t in) const
	{
		return (value <= in.value);
	}
	bool operator>(const virtualIndex_t in) const
	{
		return (value > in.value);
	}
	bool operator>=(const virtualIndex_t in) const
	{
		return (value >= in.value);
	}
	virtualIndex_t operator++ (int)
	{
		virtualIndex_t temp = *this;
		++value;
		return (temp);
	}
	virtualIndex_t operator++ ()
	{
		++value;
		return (*this);
	}
	virtualIndex_t operator-- (int)
	{
		virtualIndex_t temp = *this;
		--value;
		return (temp);
	}
	virtualIndex_t operator-- ()
	{
		--value;
		return (*this);
	}
	bool operator== (const virtualIndex_t in) const
	{
		return (value == in.value);
	}
	virtualIndex_t& operator= (virtualIndex_t in)
	{
		value = in.value;
		return (*this);
	}
	virtualIndex_t& operator= (uint32_t in)
	{
		value = in;
		return (*this);
	}
	friend std::ostream& operator << (std::ostream &o, const virtualIndex_t &a)
	{
		o << a.value;
		return o;
	}
	uint32_t value;
};
}/* namespace crunch */
namespace std
{
template<> struct hash<crunch::virtualIndex_t>
{
	size_t operator() (const crunch::virtualIndex_t& index) const
	{
		return (index.value);
	}
};
} /* namespace std */
#endif /* VIRTUALINDEXTYPE_HPP_ */
