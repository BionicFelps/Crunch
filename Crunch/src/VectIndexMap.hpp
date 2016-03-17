/*
 * VectIndexMap.hpp
 *
 *  Created on: Feb 10, 2016
 *      Author: daniel
 */

#ifndef VECTINDEXMAP_HPP_
#define VECTINDEXMAP_HPP_


#include <algorithm>
#include <vector>
#include <unordered_map>
#include "IndexManager.hpp"
#include "virtualIndexType.hpp"
#include "indexType.hpp"

namespace crunch
{

//strong typedef uint32_t virtualIndex_t
//NOTE: Only specific operators have been implemented, as needed.


template<class t> class VectIndexMap
{
public:
	VectIndexMap() : currentIndex(0)
	{
		// TODO Auto-generated constructor stub
		storage.reserve(262144);
	}
	~VectIndexMap()
	{
		// TODO Auto-generated destructor stub
	}
	void begin()
	{
		currentIndex = 0;
	}
	void end()
	{
		currentIndex = std::distance(storage.begin(), storage.end()-1);
	}
	void next()
	{
		currentIndex=currentIndex>=storage.size()-1?0:currentIndex+1;
	}
	void prev()
	{
		currentIndex=currentIndex<=0?currentIndex=storage.size()-1:currentIndex-1;
	}
	t& current()
	{
		return (storage[currentIndex]);
	}
	bool empty()
	{
		return(storage.empty());
	}
	virtualIndex_t newItem(const t& in)
	{
		index_t real;
		real = storage.size();
		vEnd = indexStore.getIndex();

		storage.push_back(in);
		indexMap[vEnd] = real;
		return (vEnd);
	}
	bool last()	//< for while loops
	{
		return(currentIndex == storage.size()-1);
	}
	size_t size()	//< for for loops
	{
		return(storage.size());
	}
	void erase(virtualIndex_t in)
	{
		index_t end = storage.size()-1;//< the last index in our vectors
		index_t realIndexToErase = indexMap[in];					//< the index of our vector to erase

		if(end != realIndexToErase)
		{
			std::swap(storage[realIndexToErase], storage[end]);			//< swap element to delete to the back
			std::swap(indexMap[in], indexMap[vEnd]);					//< correct indexMap
		}
		storage.pop_back();		//< erase the element (previously moved to the back of the storage, this prevents shuffling)
		indexMap.erase(vEnd);	//< indexMap's structure is very different.  In addition to not having a back to pop from, vEnd is very likely not identical to end.
		vEnd = in;				//< set virtual end index
	}
	t& operator[](virtualIndex_t in)
	{
		return(storage[indexMap[in]]);
	}
	bool exists(virtualIndex_t in)
	{
		return((bool)indexMap.count(in));
	}

private:
	std::vector<t> storage;
	IndexManager<virtualIndex_t> indexStore;
	std::unordered_map<virtualIndex_t, index_t> indexMap;
	virtualIndex_t vEnd;

	index_t currentIndex;
	//TODO: Store real indexes to the vector in the map
	//TODO: Fetch vector elements with virtual index
	//TODO: swap end of vector with element to erase and erase, modify map accordingly
	//TODO: store a reverse map to find element that needs to be swapped.
};

} /* namespace crunch */
//#include "VectIndexMap.cpp"
#endif /* VECTINDEXMAP_HPP_ */
