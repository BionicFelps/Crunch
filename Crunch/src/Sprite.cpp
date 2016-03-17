/*
 * Sprite.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: daniel
 */

#include "Sprite.hpp"
#include <iostream>
namespace crunch
{
sf::Vector2f convertVectorB2SF(b2Vec2 in)
{
	sf::Vector2f ret = {in.x, in.y};
	return (ret);
}

Sprite::Sprite() : hidden(false)
{
	// TODO Auto-generated constructor stub
}
Sprite::~Sprite()
{
	// TODO Auto-generated destructor stub
}

void Sprite::render(sf::RenderWindow& window, sf::RenderStates states, const float coordScale)
{
	if(body != nullptr)
	{
		b2Vec2 b2Pos = body->GetPosition();
		b2Vec2 b2Org = body->GetLocalCenter();
		sf::FloatRect bounds = sprite.getLocalBounds();
		sf::Vector2f b2SFScale = sprite.getScale();
		b2SFScale.x = 1/b2SFScale.x;
		b2SFScale.y = 1/b2SFScale.y;
		sf::Vector2f origin = {bounds.width*0.5f - b2Org.x*coordScale*b2SFScale.x + offset.x, bounds.height*0.5f - b2Org.y*coordScale*b2SFScale.y + offset.y};

		setPos({b2Pos.x*coordScale, b2Pos.y*coordScale});
		sprite.setOrigin(origin);
		setRot(body->GetAngle()*(180/3.14));
	}
	if(!hidden)
	{
		window.draw(sprite, states);
	}
}

void Sprite::setTexture(sf::Texture& in)
{
	sprite.setTexture(in);
}

void Sprite::setPhysicsObj(b2Body* in)
{
	body = in;
}

void Sprite::unsetPhysicsObj()
{
	body = nullptr;
}

} /* namespace crunch */
