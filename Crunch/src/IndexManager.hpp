/*
 * IndexManager.hpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Daniel G Billings Jr
 *
 *      This class will manage a global index system, all instances of the class will utilize the same global indexes.
 *      The goal is to be able to look up any object by type, but also be able to lookup what type of object a particular index is.
 */

#ifndef INDEXMANAGER_HPP_
#define INDEXMANAGER_HPP_

#include <map>
#include <vector>
#include <stack>
#include "indexType.hpp"
#include "../AngelScriptAddons/scriptarray/scriptarray.h"

namespace crunch
{

template <class t>
class IndexManager
{
public:
	IndexManager()
	{
		// TODO Auto-generated constructor stub
	}
	~IndexManager()
	{
		// TODO Auto-generated destructor stub
	}
	t getIndex(bool checkAvailable = true)
	{
		t temp;
		if(checkAvailable)
		{
			if(!available.empty())
			{
				temp = available.top();
				available.pop();
				return (temp);
			}
		}
		temp = nextIndex++;
		return (temp);
	}
	void returnIndex(t index)
	{
		available.push(index);
	}

protected:
	t nextIndex;							///< stores the next index to use
	std::stack<t> available;				///< stores a list of presently unoccupied indicies

};
// TODO make derived class which allows adding a "group" identifier to an index
} /* namespace crunch */

#endif /* INDEXMANAGER_HPP_ */
