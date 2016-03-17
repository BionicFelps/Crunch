/*
 * Sprite.hpp
 *
 *  Created on: Feb 19, 2016
 *      Author: daniel
 *
 *      A crunch::Sprite is typically rendered through a function callback registered to a crunch::Texture, for now it's essentially a wrapper over
 *      an sf::Sprite, but will eventually render itself through OpenGL allowing greater support for special effects
 */
#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <functional>
#include "VectIndexMap.hpp"
#include "virtualIndexType.hpp"

namespace crunch
{

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();
	void render(sf::RenderWindow&, sf::RenderStates states = sf::RenderStates::Default, const float coordScale = 30.0f);
	void setTexture(sf::Texture&);
	void setPhysicsObj(b2Body*);		//< This will associate the sprite with a physics body, matching the position and orientation at all times (meaning setPos and setRot will not work)
	void unsetPhysicsObj();
	void setPos(sf::Vector2<float> in){sprite.setPosition(in);}
	void setPos(float x, float y){sprite.setPosition(x, y);}
	void setRot(float in){sprite.setRotation(in);}
	void setScale(float x, float y){sprite.setScale(x, y);}
	void move(sf::Vector2<float> in){sprite.move(in);}
	void move(float x, float y){sprite.move(x, y);}
	void setTextureRect(const sf::IntRect rectangle){sprite.setTextureRect(rectangle);}
	void setTextureRect(const int x, int y, int width, int height){sprite.setTextureRect(sf::IntRect(x, y, width, height));}
	bool hidden;
	sf::Vector2f offset;

	static sf::Vector2f convertVec2SFML(b2Vec2 in);
private:
	sf::Sprite sprite;
	b2Body* body = nullptr;
	/*TextureManager& textureManager;*/ //placeholder
};

} /* namespace crunch */

#endif /* SPRITE_HPP_ */
