/*
 * Layer.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: daniel
 */

#include "Layer.hpp"

namespace crunch
{
const Sprite Layer::dummySprite;
Layer::Layer()
{
	// TODO Auto-generated constructor stub

}

Layer::~Layer()
{
	// TODO Auto-generated destructor stub
}
//overload the dummy type with the type, and register appropriate function
virtualIndex_t Layer::add(const Sprite&, virtualIndex_t spriteIndex)
{
	return (draws.newItem({&Layer::queueSprite, spriteIndex}));
}

void Layer::remove(virtualIndex_t index)
{
	draws.erase(index);
}

void Layer::queue(DrawManager& drawManager)
{
	draws.begin();

	for(size_t i = 0;i < draws.size();++i)
	{
		drawIndex cur = draws.current();
		cur.func(this, drawManager, cur.index); //< calls the function registered earlier for the specific type
		draws.next();
	}
}

void Layer::queueSprite(DrawManager& drawManager, virtualIndex_t index)
{
	drawManager.queue(dummySprite, index);
}

} /* namespace crunch */
