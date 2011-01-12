#ifndef GAMEKERNEL_H
#define GAMEKERNEL_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <Box2D/Box2D.h>
#include <cstdio>
#include <list>

#include "DebugDraw.h"
#include "Globals.h"

class GameKernel
{
    public:
        //Constructor/Destructors
        GameKernel();
        GameKernel(int widgth, int heigth);
        virtual ~GameKernel();

        //methods
        void ActivateDebugDraw();
        b2World *getPhysicsWorld();
        sf::RenderWindow *getApp();
        std::list<b2Body*> getphysicsObjectList();
        DebugDraw *getdebugDraw();
        void addDynamicBox(int x, int y);
        void addDynamicBox(int x, int y, float heigth, float widgth);
        void addStaticBox(int x, int y);
        void addStaticBox(int x, int y, float heigth, float widgth);
        void addDynamicCircle(int x, int y);
        void addDynamicCircle(int x, int y, float radius);
        void addStaticCircle(int x, int y);
        void addStaticCircle(int x, int y, float radius);
        void setWindowIcon(std::string imagePath);
        static int randomNumber(int min, int max);
        void printDebugInfo();
        void removePhysicBodies(int leftLimit, int rightLimit, int upLimit, int downLimit);


    private:
        //atributes
        static b2World *physicsWorld;
        static sf::RenderWindow *app;
        static std::list<b2Body*> physicsObjectList; //list of pointers to the physics bodies
        static DebugDraw *debugDraw;
        int resWidgth;
        int resHeigth;

        //methods
};

#endif // GAMEKERNEL_H
