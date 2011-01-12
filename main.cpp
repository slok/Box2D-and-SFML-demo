#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <Box2D/Box2D.h>
#include <cstdio>

#include "GameKernel.h"
#include "DebugDraw.h"
#include "Globals.h"
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
    bool debugString= true;
    int p1x,p1y,p2x,p2y; //for the creation of boxes with the mouse;
    bool mouseIsPressed = false; //needed to know if we have to draw
    bool isForBox = true; // needed to know if we have to draw a box or a circle
    const sf::Input& input = rWindow->GetInput(); //for getting x and y coordiantes of the mouse
    sf::Shape drawingMouseBox; //for displaying white rectangle
    sf::Clock clock; //for the timing of the deletion of bodies out of the screen

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
                            gameController.addDynamicBox(GameKernel::randomNumber(0,800),GameKernel::randomNumber(0,600));

                        break;
                    }
                    case sf::Key::Return: //add circle
                    {
                        if(staticMode)
                            gameController.addStaticCircle(GameKernel::randomNumber(0,800),GameKernel::randomNumber(0,600));
                        else
                            gameController.addDynamicCircle(GameKernel::randomNumber(0,800),GameKernel::randomNumber(0,600));

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
                }
            }
            if(Event.Type == sf::Event::MouseButtonPressed)
            {
                mouseIsPressed = true;
                p1x = input.GetMouseX();
                p1y = input.GetMouseY();

                switch (Event.MouseButton.Button)
                {
                    case sf::Mouse::Left: isForBox = true; break;
                    case sf::Mouse::Right: isForBox = false; break;
                }
            }
            if(Event.Type == sf::Event::MouseMoved && mouseIsPressed)
            {
                p2x = input.GetMouseX();
                p2y = input.GetMouseY();
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

             if(Event.Type == sf::Event::MouseButtonReleased)
            {
                mouseIsPressed = false;
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
                        gameController.addDynamicBox(tempP1x,tempP1y,wX/2,hY/2);

                }
                else
                {
                   if(staticMode)
                        gameController.addStaticCircle(p1x,p1y,(p2x-p1x));
                    else
                        gameController.addDynamicCircle(p1x,p1y,(p2x-p1x));
                }

            }
        }

        /*cout << "p1: (" << p1x << "," << p1y << ")\n";
        cout << "p2: (" << p2x << "," << p2y << ")\n";*/
        rWindow->Clear();
        //draw background
        //rWindow.Draw(backgroundSprite);
        //draw debug
        pWorld->DrawDebugData();
        //draw debug information
        //rWindow.DrawString(0,0,fpsString.c_str());

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		if(!pause)
            pWorld->Step(timeStep, velocityIterations, positionIterations);
        else
            gameController.getdebugDraw()->DrawString(0,50,"*PAUSE*");

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
