/*
 * LayerManager.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: daniel
 */

#ifndef LAYERMANAGER_HPP_
#define LAYERMANAGER_HPP_

#include <map>
#include <functional>
#include "Layer.hpp"
#include "DrawManager.hpp"

namespace crunch
{

class LayerManager
{
public:
	LayerManager();
	virtual ~LayerManager();

	virtualIndex_t addSpriteToLayer(int, virtualIndex_t);
	void removeSpriteFromLayer(int, virtualIndex_t);
	void queue(DrawManager&);
private:
	std::map<int, Layer> layers;
};

} /* namespace crunch */

#endif /* LAYERMANAGER_HPP_ */
