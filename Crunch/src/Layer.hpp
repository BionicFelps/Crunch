/*
 * Layer.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: daniel
 */

#ifndef LAYER_HPP_
#define LAYER_HPP_
#include <functional>
#include <queue>
#include <SFML/Graphics.hpp>
#include "DrawManager.hpp"
#include "VectIndexMap.hpp"
#include "Sprite.hpp"
namespace crunch
{

class Layer
{
	struct drawIndex;
public:
	Layer();
	virtual ~Layer();

	virtualIndex_t add(const Sprite&, virtualIndex_t);
	void remove(virtualIndex_t);
	void queue(DrawManager&);

	static const Sprite dummySprite;		///< A dummy sprite to activate the sprite overload of certain functions
private:
	void queueSprite(DrawManager&, virtualIndex_t);
	VectIndexMap<drawIndex> draws;
};

struct Layer::drawIndex
{
	std::function<void (Layer*, DrawManager&, virtualIndex_t)> func;
	virtualIndex_t index;
};
} /* namespace crunch */

#endif /* LAYER_HPP_ */
