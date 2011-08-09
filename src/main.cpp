/*
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

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <Box2D/Box2D.h>
#include <cstdio>

#include "GameKernel.h"
#include "DebugDraw.h"
#include "Globals.h"
#include "QueryCallback.h"
using namespace std;

int main(int argc, char **argv)
{
    GameKernel gameController(800,600);

    b2World *pWorld = gameController.getPhysicsWorld();
    gameController.ActivateDebugDraw();
    sf::RenderWindow *rWindow = gameController.getApp();

    //add icon to the render window
    gameController.setWindowIcon("resources/icons/box2d.png");

	//box2D step info
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 10;
	int32 positionIterations = 10;

    sf::Event Event;
    bool pause = false;
    bool staticMode= false;
    bool grabMode= false;
    bool debugString= true;
    bool helpMode= false;
    int p1x,p1y,p2x,p2y; //for the creation of boxes with the mouse;
    bool mouseIsPressed = false; //needed to know if we have to draw
    bool isForBox = true; // needed to know if we have to draw a box or a circle
    const sf::Input& input = rWindow->GetInput(); //for getting x and y coordiantes of the mouse
    sf::Shape drawingMouseBox; //for displaying white rectangle
    sf::Clock clock; //for the timing of the deletion of bodies out of the screen

    sf::Sprite bkSprite;
    sf::Image bkImage;
    
    gameController.setBackground("", &bkImage, &bkSprite); //without background path

    //help string
    std::string  helpString =   "    *H: Enable/disable this help\n\
    *S: switch between static and dynamic bodies\n\
    *P: Pause/unpause the game\n\
    *Space: Aleatory box\n\
    *Enter: Aleatory circle\n\
    *G: Enable/disable grab mode (mouse joint)\n\
    *Right click: if not grab mode, add circle (move and release )\n\
    *Left click: if not grab mode, add box (move and release)\n\
    *0-9 num keys to change material";

    //for the joints
    b2BodyDef bodyDef;
	b2Body* groundBody = pWorld->CreateBody(&bodyDef);
	b2MouseJoint* mouseJoint = NULL;

    //material of the bodies
    Material material = Material::DEFAULT;
    std::string materialStr = "Default";

	while(rWindow->IsOpened())
	{
	    // Process events
        while(rWindow->GetEvent(Event))
        {
            // Close window : exit
            if(Event.Type == sf::Event::Closed)
                rWindow->Close();

            if(Event.Type == sf::Event::KeyPressed)//key press events
            {

                switch (Event.Key.Code)
                {
                    //close events
                    case sf::Key::Escape: rWindow->Close(); break;

                    //game logic events
                    case sf::Key::Space: //add box
                    {
                        if(staticMode)
                            gameController.addStaticBox(GameKernel::randomNumber(0,800),GameKernel::randomNumber(0,600));
                        else
                            gameController.addDynamicBox(GameKernel::randomNumber(0,800),GameKernel::randomNumber(0,600), material);

                        break;
                    }
                    case sf::Key::Return: //add circle
                    {
                        if(staticMode)
                            gameController.addStaticCircle(GameKernel::randomNumber(0,800),GameKernel::randomNumber(0,600));
                        else
                            gameController.addDynamicCircle(GameKernel::randomNumber(0,800),GameKernel::randomNumber(0,600), material);

                        break;
                    }
                    case sf::Key::I: //activate/desactivate debug upper-left information string
                    {
                        if(debugString)
                            debugString = false;
                        else
                            debugString = true;

                        break;
                    }
                    case sf::Key::S: //activate/desactivate static objects creation
                    {
                        if(staticMode)
                            staticMode = false;
                        else
                            staticMode = true;

                        break;
                    }
                    case sf::Key::P: //activate/desactivate static objects creation
                    {
                        if(pause)
                            pause = false;
                        else
                            pause = true;

                        break;
                    }
                    case sf::Key::G: //activate/desactivate grab mode
                    {
                        if(grabMode)
                            grabMode = false;
                        else
                            grabMode = true;
                        break;
                    }
                    case sf::Key::H: //activate/desactivate grab mode
                    {
                        if(!helpMode)
                        {
                            helpMode = true;
                            pause = true;
                        }
                        else
                        {
                            helpMode = false;
                            pause = false;
                        }
                        break;
                    }
                    //materials
                    case sf::Key::Num1: material = Material::DEFAULT; materialStr = "Default"; break;
                    case sf::Key::Num2: material = Material::METAL; materialStr = "Metal"; break;
                    case sf::Key::Num3: material = Material::STONE; materialStr = "Stone"; break;
                    case sf::Key::Num4: material = Material::WOOD; materialStr = "Wood"; break;
                    case sf::Key::Num5: material = Material::GLASS; materialStr = "Glass"; break;
                    case sf::Key::Num6: material = Material::RUBBER; materialStr = "Rubber"; break;
                    case sf::Key::Num7: material = Material::ICE; materialStr = "Ice"; break;
                    case sf::Key::Num8: material = Material::PUMICE; materialStr = "Pumice"; break;
                    case sf::Key::Num9: material = Material::POLYSTYRENE; materialStr = "Polystyrene"; break;
                    case sf::Key::Num0: material = Material::SPONGE; materialStr = "Sponge"; break;
                }
            }
            if(Event.Type == sf::Event::MouseButtonPressed)
            {
                mouseIsPressed = true;

                p1x = input.GetMouseX();
                p1y = input.GetMouseY();

                if(!grabMode)
                {
                    switch (Event.MouseButton.Button)
                    {
                        case sf::Mouse::Left: isForBox = true; break;
                        case sf::Mouse::Right: isForBox = false; break;
                    }
                }
                else
                {
                    // Make a small box.
                    b2Vec2 p;

                    p.x = p1x*UNRATIO;
                    p.y = p1y*UNRATIO;

                    b2AABB aabb;
                    b2Vec2 d;
                    d.Set(0.001f, 0.001f);
                    aabb.lowerBound = p + d;
                    aabb.upperBound = p - d;

                    QueryCallback callback(p);
                    pWorld->QueryAABB(&callback, aabb);

                    if (callback.m_fixture)
                    {
                        b2Body* body = callback.m_fixture->GetBody();
                        b2MouseJointDef md;
                        md.bodyA = groundBody;
                        md.bodyB = body;
                        md.target = p;
                        md.maxForce = 1000.0f * body->GetMass();
                        mouseJoint = (b2MouseJoint*)pWorld->CreateJoint(&md);
                        body->SetAwake(true);
                        std::cout << "[Box2D][new] joint created\n";
                    }

                }
            }
            if(Event.Type == sf::Event::MouseMoved && mouseIsPressed)
            {
                p2x = input.GetMouseX();
                p2y = input.GetMouseY();
                if (!grabMode)
                {
                    if (isForBox)
                    {
                        drawingMouseBox = sf::Shape::Rectangle(p1x, p1y, p2x, p2y, sf::Color::White,1, sf::Color::White);
                        drawingMouseBox.EnableFill(false);
                        drawingMouseBox.EnableOutline(true);

                    }
                    else
                    {
                        drawingMouseBox = sf::Shape::Circle(p1x, p1y, p2x-p1x, sf::Color::White, 1, sf::Color::White);
                        drawingMouseBox.EnableFill(false);
                        drawingMouseBox.EnableOutline(true);
                    }

                }
                else
                {
                    //move the joint (and the object)
                    if (mouseJoint != NULL)
                    {
                        b2Vec2 p;
                        p.x = p2x*UNRATIO;
                        p.y = p2y*UNRATIO;
                        mouseJoint->SetTarget(p);
                    }
                }
            }

             if(Event.Type == sf::Event::MouseButtonReleased)
            {
                mouseIsPressed = false;

                if(!grabMode)
                {
                    drawingMouseBox.EnableOutline(false); //because there is a second that shows in other position, sow we do "transparent"
                    if (isForBox)
                    {
                        //calculate good coordinates (from upper-left, not center) for box2D (box2D is with center, sfml no)
                        int tempP1x, tempP1y, wX, hY;

                        wX = p2x-p1x;
                        hY = p2y-p1y;
                        tempP1x = p1x+wX/2;
                        tempP1y = p1y+hY/2;

                        if(staticMode)
                            gameController.addStaticBox(tempP1x,tempP1y,wX/2,hY/2);
                        else
                            gameController.addDynamicBox(tempP1x,tempP1y,wX/2,hY/2, material);

                    }
                    else
                    {
                       if(staticMode)
                            gameController.addStaticCircle(p1x,p1y,(p2x-p1x));
                        else
                            gameController.addDynamicCircle(p1x,p1y,(p2x-p1x), material);
                    }
                }
                else
                {
                    //delete joint
                    if (mouseJoint != NULL)
                    {
                        pWorld->DestroyJoint(mouseJoint);
                        mouseJoint = NULL;
                        std::cout << "[Box2D][delete] joint deleted\n";
                    }
                }
            }
        }

        rWindow->Clear();

        //draw debug
        pWorld->DrawDebugData();
        rWindow->Draw(bkSprite);

        //if there is a mouse joint, draw the joints and the line
        if(mouseJoint != NULL)
        {
            b2Vec2 p1 = mouseJoint->GetAnchorB();
            b2Vec2 p2 = mouseJoint->GetTarget();
            gameController.getdebugDraw()->DrawMouseJoint(p1, p2, b2Color(0.0f, 1.0f, 0.0f), b2Color(0.8f, 0.8f, 0.8f));
        }

        //draw help string
        if(helpMode)
        {
            gameController.getdebugDraw()->DrawString(100,100,helpString.c_str());
        }

        //print actual material
        gameController.getdebugDraw()->DrawString(0,50,materialStr.c_str());

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		if(!pause)
            pWorld->Step(timeStep, velocityIterations, positionIterations);
        else
            gameController.getdebugDraw()->DrawString(0,70,"*PAUSE*");

		// Clear applied body forces. We didn't apply any forces, but you
        // should know about this function.
        pWorld->ClearForces();

        //print or not to print, that's the question :D
        if (debugString)
            gameController.printDebugInfo();

        if (mouseIsPressed)
            rWindow->Draw(drawingMouseBox);


        rWindow->Display();
        if (clock.GetElapsedTime()> 30.0f) //every 30 seconds deletes the bodies out of bounds
        {
            clock.Reset();
            gameController.removePhysicBodies(-50,850,-50, 650);
        }


	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.
    return 0;
}
