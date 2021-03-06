/*
 * CrunchyBoxDraw.h
 *
 *  Created on: Jan 31, 2016
 *      Author: daniel
 */

#ifndef CRUNCHYBOXDRAW_HPP_
#define CRUNCHYBOXDRAW_HPP_

#include <Box2D/Common/b2Draw.h>
#include <SFML/Graphics.hpp>

namespace crunch
{

class CrunchyBoxDraw: public b2Draw
{
public:
	CrunchyBoxDraw(sf::RenderWindow &win, float initialScale);
	virtual ~CrunchyBoxDraw();
	/// Draw a closed polygon provided in CCW order.
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	/// Draw a solid closed polygon provided in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	/// Draw a circle.
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	/// Draw a solid circle.
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	/// Draw a line segment.
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	void DrawTransform(const b2Transform& xf);
private:
	sf::Color convertColor(const b2Color& color);
	sf::RenderWindow *window;
	float scale;
};

} /* namespace crunch */

#endif /* CRUNCHYBOXDRAW_HPP_ */
