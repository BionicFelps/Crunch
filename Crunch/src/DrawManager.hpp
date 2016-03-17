/*
 * DrawManager.hpp
 *
 *  Created on: Feb 22, 2016
 *      Author: daniel
 */

#ifndef DRAWMANAGER_HPP
#define DRAWMANAGER_HPP

#include <queue>
#include <iostream>
#include <functional>
#include <cstdint>
#include "VectIndexMap.hpp"
#include "Sprite.hpp"

namespace crunch
{
enum drawType{shape, sprite, animatedSprite, skeleton};

struct drawObjects
{
	VectIndexMap<Sprite> sprites;
	/*VectIndexMap<animatedSprite> animatedSprites*/
	/*VectIndexMap<skeleton> skeletons*/		//placeholders for future features
};

class DrawManager
{
	struct drawIndex;
public:
	DrawManager(sf::RenderStates = sf::RenderStates::Default);
	virtual ~DrawManager();

	void queue(const Sprite&, virtualIndex_t);
	void clearQueue();
	void draw(sf::RenderWindow& window, drawObjects& objects, sf::RenderStates states, const float coordScale);
private:
	void drawSprite(sf::RenderWindow& window, drawObjects& objects, sf::RenderStates states, virtualIndex_t current, const float coordScale);

	sf::RenderStates renderStates;
	std::queue<drawIndex> drawQueue;
};
struct DrawManager::drawIndex
{
	//kind of a long function signature, it's meant to be used inside the drawManager class to queue up draw calls
	//which adds a pointer to the instance to the call
	std::function<void(DrawManager*, sf::RenderWindow&, drawObjects&, sf::RenderStates, virtualIndex_t, float)> func;
	virtualIndex_t index;
};
}
#endif // DRAWMANAGER_HPP
