/*
 * DrawManager.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: daniel
 */

#include "DrawManager.hpp"
namespace crunch
{
DrawManager::DrawManager(sf::RenderStates states) : renderStates(states)
{
}

DrawManager::~DrawManager()
{

}

void DrawManager::queue(const crunch::Sprite&, virtualIndex_t index)
{
	drawQueue.push({&DrawManager::drawSprite, index});
}
void DrawManager::clearQueue()
{
	//you should never need this code, but if you need it, you need it.
	while(!drawQueue.empty())
	{
		drawQueue.pop();
	}
}

void DrawManager::draw(sf::RenderWindow& window, drawObjects& objects, sf::RenderStates states, const float coordScale)
{
	while(!drawQueue.empty())
	{
		drawIndex current = drawQueue.front();
		current.func(this, window, objects, states, current.index, coordScale);
		drawQueue.pop();
	}
}
void DrawManager::drawSprite(sf::RenderWindow& window, drawObjects& objects, sf::RenderStates states, virtualIndex_t current, const float coordScale)
{
	objects.sprites[current].render(window, states, coordScale);
}
}/*namespace crunch*/
