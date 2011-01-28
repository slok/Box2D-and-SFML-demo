/*
    Copyright (C) 2010 Allen Jordan ()
    Copyright (C) 2011 Xabier Larrakoetxea (slok)

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
	sf::Shape polygon;
    polygon.AddPoint(aabb->lowerBound.x*RATIO, aabb->lowerBound.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));
    polygon.AddPoint(aabb->upperBound.x*RATIO, aabb->lowerBound.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));
    polygon.AddPoint(aabb->upperBound.x*RATIO, aabb->upperBound.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));
    polygon.AddPoint(aabb->lowerBound.x*RATIO, aabb->upperBound.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));

    polygon.SetOutlineWidth(1.0f);
	this->window->Draw(polygon);
    std::cout << "DrawAABB\n";
}


void DebugDraw::DrawString(int x, int y, const char* string)
{
    sf::String fpsText;
    fpsText.SetFont(sf::Font::GetDefaultFont());
    fpsText.SetSize(15);
    fpsText.SetPosition(x,y);
    fpsText.SetText(string);
    this->window->Draw(fpsText);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    std::cout << "DrawPoint\n";
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
    float x,y, lineSize, lineProportion;
    x = xf.position.x * RATIO;
    y = xf.position.y * RATIO;
    lineProportion = 0.15; // 0.15 ~ 10 pixels
    b2Vec2 p1 = xf.position, p2;

	//red (X axis)
	p2 = p1 + (lineProportion * xf.R.col1);
    sf::Shape redLine = sf::Shape::Line(p1.x*RATIO, p1.y*RATIO, p2.x*RATIO, p2.y*RATIO, 1, sf::Color::Red);

	//green (Y axis)
	p2 = p1 - (lineProportion * xf.R.col2);
	sf::Shape greenLine = sf::Shape::Line(p1.x*RATIO, p1.y*RATIO, p2.x*RATIO, p2.y*RATIO, 1, sf::Color::Green);

    this->window->Draw(redLine);
    this->window->Draw(greenLine);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

    sf::Shape line = sf::Shape::Line(p1.x*RATIO, p1.y*RATIO, p2.x*RATIO, p2.y*RATIO, 1, this->B2SFColor(color));
    line.EnableFill(true);
    this->window->Draw(line);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    //no converion in cordinates of center and upper left corner, Circle in sfml is managed by default with the center
    sf::Shape circle = sf::Shape::Circle(center.x*RATIO, center.y*RATIO, (radius*RATIO), this->B2SFColor(color, 50), 1.0f,this->B2SFColor(color));

    // line of the circle wich shows the angle
    b2Vec2 p = center + (radius * axis);
    sf::Shape line = sf::Shape::Line(center.x*RATIO, center.y*RATIO, p.x*RATIO, p.y*RATIO, 1, this->B2SFColor(color));

    this->window->Draw(circle);
    this->window->Draw(line);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::Shape circle = sf::Shape::Circle(center.x*RATIO, center.y*RATIO, radius*RATIO, this->B2SFColor(color, 50), 1.0f,this->B2SFColor(color));
    circle.EnableFill(false);
    this->window->Draw(circle);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

    sf::Shape polygon;
	for (int32 i=0; i<vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		polygon.AddPoint(vertex.x*RATIO, vertex.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color));
	}
	polygon.SetOutlineWidth(1.0f);
	this->window->Draw(polygon);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::Shape polygon;
	for (int32 i=0; i<vertexCount; i++)
	{
		b2Vec2 vertex = vertices[i];
		polygon.AddPoint(vertex.x*RATIO, vertex.y*RATIO, this->B2SFColor(color, 50), this->B2SFColor(color, 255));
	}
	polygon.SetOutlineWidth(1.0f);
	polygon.EnableFill(false);
	this->window->Draw(polygon);
}


void DebugDraw::DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor)
{
    sf::Shape polygon;
    sf::Shape polygon2;
    float p1x = p1.x * RATIO;
    float p1y = p1.y * RATIO;
    float p2x = p2.x * RATIO;
    float p2y = p2.y * RATIO;
    float size = 4.0f;

    sf::Color boxClr = this->B2SFColor(boxColor);
    sf::Color lineClr = this->B2SFColor(lineColor);

    //first green box for the joint
    polygon.AddPoint(p1x-size/2, p1y-size/2, boxClr);
    polygon.AddPoint(p1x+size/2, p1y-size/2, boxClr);
    polygon.AddPoint(p1x+size/2, p1y+size/2, boxClr);
    polygon.AddPoint(p1x-size/2, p1y+size/2, boxClr);

    //second green box for the joint
    polygon2.AddPoint(p2x-size/2, p2y-size/2, boxClr);
    polygon2.AddPoint(p2x+size/2, p2y-size/2, boxClr);
    polygon2.AddPoint(p2x+size/2, p2y+size/2, boxClr);
    polygon2.AddPoint(p2x-size/2, p2y+size/2, boxClr);

    sf::Shape line = sf::Shape::Line(p1x, p1y, p2x, p2y, 1, lineClr);
    line.EnableFill(true);

    this->window->Draw(polygon);
    this->window->Draw(polygon2);
    this->window->Draw(line);
}

