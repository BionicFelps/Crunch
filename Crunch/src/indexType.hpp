/*
 * indexType.hpp
 *
 *  Created on: Feb 14, 2016
 *      Author: daniel
 */

#include <ostream>
#include <cstdint>
#include <algorithm>

#ifndef INDEXTYPE_HPP_
#define INDEXTYPE_HPP_

namespace crunch
{
struct index_t
{
	index_t() : value(0)
	{

	}
	index_t(size_t v) : value(v)
	{

	}
	operator uint32_t()
	{
		return (value);
	}
	bool operator<(const index_t in) const
	{
		return (value < in.value);
	}
	bool operator<=(const index_t in) const
	{
		return (value <= in.value);
	}
	bool operator>(const index_t in) const
	{
		return (value > in.value);
	}
	bool operator>=(const index_t in) const
	{
		return (value >= in.value);
	}

	bool operator<(const size_t in) const
	{
		return (value < in);
	}
	bool operator<=(const size_t in) const
	{
		return (value <= in);
	}
	bool operator>(const size_t in) const
	{
		return (value > in);
	}
	bool operator>=(const size_t in) const
	{
		return (value >= in);
	}

	index_t operator++ (int)
	{
	index_t temp = *this;
		++value;
		return (temp);
	}
	index_t operator++ ()
	{
		++value;
		return (*this);
	}
		index_t operator-- (int)
	{
	index_t temp = *this;
		--value;
		return (temp);
	}
	index_t operator-- ()
	{
		--value;
		return (*this);
	}
	bool operator== (const index_t in) const
	{
		return (value == in.value);
	}
	friend std::ostream& operator << (std::ostream &o, const index_t &a)
	{
		o << a.value;
		return o;
	}
	size_t value;
};
} /* namespace crunch */
namespace std
{
template<> struct hash<crunch::index_t>
{
	size_t operator() (const crunch::index_t& index) const
	{
		return (index.value);
	}
};
} /* namespace std */

#endif /* INDEXTYPE_HPP_ */
