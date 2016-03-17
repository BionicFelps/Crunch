/*
 * IndexManager.hpp
 *
 *  Created on: Feb 1, 2016
 *      Author: Daniel G Billings Jr
 *
 *      This class will manage a global index system, all instances of the class will utilize the same global indexes.
 *      The goal is to be able to look up any object by type, but also be able to lookup what type of object a particular index is.
 */

#ifndef GLOBALINDEXMANAGER_HPP_
#define GLOBALINDEXMANAGER_HPP_

#include <map>
#include <vector>
#include <stack>
#include <cstdint>
#include "../AngelScriptAddons/scriptarray/scriptarray.h"

namespace crunch
{
typedef uint32_t index_t;
class GlobalIndexManager
{
public:
	GlobalIndexManager();
	virtual ~GlobalIndexManager();

	static index_t getIndex(bool checkAvailable = true);						///< fetch a new index
	static void returnIndex(index_t index);									///< return an index that is no longer being used

protected:
	static index_t nextIndex;													///< stores the next index to use
	static std::stack<index_t> available;										///< stores a list of presently unoccupied indicies

};
// TODO make derived class which allows adding a "group" identifier to an index
} /* namespace crunch */

#endif /* INDEXMANAGER_HPP_ */
