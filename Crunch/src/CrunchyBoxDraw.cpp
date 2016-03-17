/*
 * CrunchyBoxDraw.cpp
 *
 *  Created on: Jan 31, 2016
 *      Author: daniel
 */

#include "CrunchyBoxDraw.hpp"

#include <cmath>


namespace crunch
{

CrunchyBoxDraw::CrunchyBoxDraw(sf::RenderWindow &win, float initialScale) : window(&win),scale(initialScale)
{
	// TODO Auto-generated constructor stub
}

CrunchyBoxDraw::~CrunchyBoxDraw()
{
	// TODO Auto-generated destructor stub
}
sf::Color CrunchyBoxDraw::convertColor(const b2Color& color)
{
	sf::Color ret;
	ret.r = uint8_t(color.r*255);
	ret.g = uint8_t(color.g*255);
	ret.b = uint8_t(color.b*255);
	ret.a = uint8_t(color.a*255);
	return (ret);
}
void CrunchyBoxDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
		const b2Color& color)
{
	sf::ConvexShape shape;
	shape.setPointCount(vertexCount);
	for(int32_t i = 0;i < vertexCount; ++i)
	{

		shape.setPoint(i,{vertices[i].x*scale,vertices[i].y*scale});
	}
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(convertColor(color));
	shape.setFillColor(sf::Color (0xFFFFFF00));
	window->draw(shape);
}

void CrunchyBoxDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
		const b2Color& color)
{
	sf::ConvexShape shape;
	shape.setPointCount(vertexCount);
	for(int32_t i = 0;i < vertexCount; ++i)
	{

		shape.setPoint(i,{vertices[i].x*scale,vertices[i].y*scale});
	}
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(convertColor(color));
	shape.setFillColor(convertColor({color.r, color.g, color.b, 0.2f}));
	window->draw(shape);
}

void CrunchyBoxDraw::DrawCircle(const b2Vec2& center, float32 radius,
		const b2Color& color)
{
	sf::CircleShape shape;
	shape.setPosition({center.x*scale, center.y*scale});
	shape.setRadius(radius);
	shape.setFillColor(sf::Color (0xFFFFFF00));
	shape.setOutlineColor(convertColor(color));
	window->draw(shape);
}

void CrunchyBoxDraw::DrawSolidCircle(const b2Vec2& center, float32 radius,
		const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape shape;
	float32 scaledRadius = radius*scale;
	shape.setPosition({center.x*scale-scaledRadius, center.y*scale-scaledRadius});
	shape.setRadius(scaledRadius);
	shape.setFillColor(convertColor({color.r, color.g, color.b, 0.2f}));
	shape.setOutlineColor(convertColor(color));
	window->draw(shape);

	DrawSegment(center, radius*axis+center, color);
}

void CrunchyBoxDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2,
		const b2Color& color)
{
	sf::Vertex verts[] {{{p1.x*scale, p1.y*scale}, convertColor(color)}, {{p2.x*scale, p2.y*scale},convertColor(color)}};
	window->draw(verts,2,sf::Lines);
}

void CrunchyBoxDraw::DrawTransform(const b2Transform& xf)
{
	float scale = 0.5;
	b2Vec2 redLine,greenLine;
	redLine = xf.p + scale * xf.q.GetXAxis();
	greenLine = xf.p + scale * xf.q.GetYAxis();
	//RED
	DrawSegment(xf.p,redLine,{1.0f,0.0f,0.0f,1.0f});
	//GREEN
	DrawSegment(xf.p,greenLine,{0.0f,1.0f,0.0f,1.0f});
}

} /* namespace crunch */
