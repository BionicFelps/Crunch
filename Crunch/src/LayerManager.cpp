/*
 * LayerManager.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: daniel
 */

#include "LayerManager.hpp"

namespace crunch
{

LayerManager::LayerManager()
{
	// TODO Auto-generated constructor stub

}

LayerManager::~LayerManager()
{
	// TODO Auto-generated destructor stub
}
/*
 * Takes an integer (the layer) and a reference to a sprite object as inputs
 * returns an index used to manipulate that particular object on that particular layer.
 * That is, if an object resides in several layers, it must keep several indexes, as they don't indicate a specific layer
 */
virtualIndex_t LayerManager::addSpriteToLayer(const int layer, const virtualIndex_t spriteIndex)
{
	return(layers[layer].add(Layer::dummySprite, spriteIndex));
}
/*
 * Erasing an index which does not exist is undefined behavior currently.
 */
void LayerManager::removeSpriteFromLayer(int layer, virtualIndex_t index)
{
	layers[layer].remove(index);
}

void LayerManager::queue(DrawManager& drawManager)
{
	for(auto it = layers.begin();it != layers.end();it++)
	{
		it->second.queue(drawManager);
	}
}

} /* namespace crunch */
