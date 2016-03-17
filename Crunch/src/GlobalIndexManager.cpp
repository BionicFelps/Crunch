/*
 * GlobalIndexManager.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: daniel
 */

#include "GlobalIndexManager.hpp"


namespace crunch
{
index_t GlobalIndexManager::nextIndex = 0;
std::stack<index_t> GlobalIndexManager::available;

GlobalIndexManager::GlobalIndexManager()
{
	// TODO Auto-generated constructor stub
}

GlobalIndexManager::~GlobalIndexManager()
{
	// TODO Auto-generated destructor stub
}

index_t GlobalIndexManager::getIndex(bool checkAvailable)
{
	index_t temp;
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
void GlobalIndexManager::returnIndex(index_t index)
{
	available.push(index);
}

} /* namespace crunch */
