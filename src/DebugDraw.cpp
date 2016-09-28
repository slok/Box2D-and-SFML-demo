/*
	Copyright (C) 2010 Allen Jordan ()
	Copyright (C) 2011 Xabier Larrakoetxea (slok)
	Copyright (C) 2016 Christian Pinter

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DebugDraw.h"

DebugDraw::DebugDraw(sf::RenderWindow &window)
{
		this->window = &window;
}

DebugDraw::~DebugDraw()
{

}

//convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
sf::Color DebugDraw::B2SFColor(const b2Color &color, int alpha = 255)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
	return result;
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(4);
	polygon.setPoint(0, sf::Vector2f(aabb->lowerBound.x*RATIO, aabb->lowerBound.y*RATIO));
	polygon.setPoint(1, sf::Vector2f(aabb->upperBound.x*RATIO, aabb->lowerBound.y*RATIO));
	polygon.setPoint(2, sf::Vector2f(aabb->upperBound.x*RATIO, aabb->upperBound.y*RATIO));
	polygon.setPoint(3, sf::Vector2f(aabb->lowerBound.x*RATIO, aabb->upperBound.y*RATIO));

	polygon.setFillColor(this->B2SFColor(color, 50));
	polygon.setOutlineColor(this->B2SFColor(color));
	polygon.setOutlineThickness(1.0f);

	this->window->draw(polygon);
	std::cout << "DrawAABB\n";
}


void DebugDraw::DrawString(int x, int y, const char* string)
{
	sf::Text fpsText;
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\verdana.ttf");
	fpsText.setFont(font);
	fpsText.setCharacterSize(15);
	fpsText.setPosition((float)x, (float)y);
	fpsText.setString(string);
	this->window->draw(fpsText);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	sf::Vertex point[] =
	{
		sf::Vertex(sf::Vector2f(p.x * RATIO, p.y * RATIO), this->B2SFColor(color))
	};

	window->draw(point, 1, sf::Points);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
	float x, y, lineProportion;
	x = xf.p.x * RATIO;
	y = xf.p.y * RATIO;
	lineProportion = 0.15f; // 0.15 ~ 10 pixels
	b2Vec2 p1 = xf.p, p2;

	//red (X axis)
	p2 = p1 + (lineProportion * xf.q.GetXAxis());
	sf::Vertex redLine [] =
	{
		sf::Vertex(sf::Vector2f(p1.x * RATIO, p1.y * RATIO), sf::Color::Red),
		sf::Vertex(sf::Vector2f(p2.x * RATIO, p2.y * RATIO), sf::Color::Red)
	};

	//green (Y axis)
	p2 = p1 - (lineProportion * xf.q.GetYAxis());
	sf::Vertex greenLine[] =
	{
		sf::Vertex(sf::Vector2f(p1.x * RATIO, p1.y * RATIO), sf::Color::Green),
		sf::Vertex(sf::Vector2f(p2.x * RATIO, p2.y * RATIO), sf::Color::Green)
	};

	this->window->draw(redLine, 2, sf::Lines);
	this->window->draw(greenLine, 2, sf::Lines);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(p1.x * RATIO, p1.y * RATIO), this->B2SFColor(color)),
		sf::Vertex(sf::Vector2f(p2.x * RATIO, p2.y * RATIO), this->B2SFColor(color))
	};
	this->window->draw(line, 2, sf::Lines);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	//no converion in cordinates of center and upper left corner, Circle in sfml is managed by default with the center
	sf::CircleShape circle(radius * RATIO);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(center.x*RATIO, center.y*RATIO);	
	circle.setFillColor(this->B2SFColor(color, 50));
	circle.setOutlineColor(this->B2SFColor(color));
	circle.setOutlineThickness(1.0f);

	// line of the circle wich shows the angle
	b2Vec2 p = center + (radius * axis);
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(center.x * RATIO, center.y * RATIO), this->B2SFColor(color)),
		sf::Vertex(sf::Vector2f(p.x * RATIO, p.y * RATIO), this->B2SFColor(color))
	};
	
	this->window->draw(circle);
	this->window->draw(line, 2, sf::Lines);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{		
	sf::CircleShape circle(radius * RATIO);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(center.x*RATIO, center.y*RATIO);	
	circle.setFillColor(this->B2SFColor(color, 0));
	circle.setOutlineColor(this->B2SFColor(color));
	circle.setOutlineThickness(1.0f);
	
	this->window->draw(circle);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertexCount);
	for (int32 i = 0; i < vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		polygon.setPoint(i, sf::Vector2f(vertex.x*RATIO, vertex.y*RATIO));
	}
	polygon.setFillColor(this->B2SFColor(color, 50));
	polygon.setOutlineColor(this->B2SFColor(color));
	polygon.setOutlineThickness(1.0f);

	this->window->draw(polygon);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(vertexCount);
	for (int32 i = 0; i < vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		polygon.setPoint(i, sf::Vector2f(vertex.x*RATIO, vertex.y*RATIO));		
	}
	polygon.setFillColor(this->B2SFColor(color, 0));
	polygon.setOutlineColor(this->B2SFColor(color));
	polygon.setOutlineThickness(1.0f);

	this->window->draw(polygon);
}


void DebugDraw::DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor)
{
	sf::ConvexShape polygon;
	sf::ConvexShape polygon2;
	float p1x = p1.x * RATIO;
	float p1y = p1.y * RATIO;
	float p2x = p2.x * RATIO;
	float p2y = p2.y * RATIO;
	float size = 4.0f;

	sf::Color boxClr = this->B2SFColor(boxColor);
	sf::Color lineClr = this->B2SFColor(lineColor);

	//first green box for the joint
	polygon.setPointCount(4);
	polygon.setPoint(0, sf::Vector2f(p1x - size / 2, p1y - size / 2));
	polygon.setPoint(1, sf::Vector2f(p1x + size / 2, p1y - size / 2));
	polygon.setPoint(2, sf::Vector2f(p1x + size / 2, p1y + size / 2));
	polygon.setPoint(3, sf::Vector2f(p1x - size / 2, p1y + size / 2));
	polygon.setFillColor(boxClr);

	//second green box for the joint
	polygon2.setPointCount(4);
	polygon2.setPoint(0, sf::Vector2f(p2x - size / 2, p2y - size / 2));
	polygon2.setPoint(1, sf::Vector2f(p2x + size / 2, p2y - size / 2));
	polygon2.setPoint(2, sf::Vector2f(p2x + size / 2, p2y + size / 2));
	polygon2.setPoint(3, sf::Vector2f(p2x - size / 2, p2y + size / 2));
	polygon2.setFillColor(boxClr);

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(p1x, p1y), lineClr),
		sf::Vertex(sf::Vector2f(p2x, p2y), lineClr)
	};

	this->window->draw(polygon);
	this->window->draw(polygon2);
	this->window->draw(line, 2, sf::Lines);
}

