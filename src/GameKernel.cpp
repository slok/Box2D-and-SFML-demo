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

#include "GameKernel.h"

//re-declare statics
sf::RenderWindow *GameKernel::app;
b2World *GameKernel::physicsWorld;
std::list<b2Body*> GameKernel::physicsObjectList;
DebugDraw *GameKernel::debugDraw;

GameKernel::GameKernel(int widgth, int heigth)
{
    //create and set the render window
    sf::RenderWindow *tempApp = new sf::RenderWindow(sf::VideoMode(widgth, heigth), "Box2DDebug");
    tempApp->SetFramerateLimit(60);
    tempApp->UseVerticalSync(true);
    GameKernel::app = tempApp;

    //create and set physics world.
	b2World* world = new b2World(b2Vec2(0.0f,10.0f), true); //gravity and sleep bodies
    GameKernel::physicsWorld = world;
    //set variables
    this->resHeigth = heigth;
    this->resWidgth = widgth;

    if (this->physicsObjectList.empty())
    {
       std::list<b2Body*>  physicsObjectList();
    }
    std::cout << "[System][new] Memory allocation physicsWorld (Box2D world)\n";
    std::cout << "[System][new] Memory allocation app (SFML render window)\n";
    std::cout << "[System] Creating Game Kernel object \n";
}

GameKernel::GameKernel()
{

}

GameKernel::~GameKernel()
{
    delete GameKernel::app;
    delete GameKernel::physicsWorld;
    delete GameKernel::debugDraw;
    std::cout << "[System][delete] Deleting app (SFML render window) \n";
    std::cout << "[System][delete] Deleting physicsWorld (Box2D world) \n";
    std::cout << "[System][delete] Deleting debugDraw \n";
}


void GameKernel::ActivateDebugDraw()
{
    //activate debug
    uint32 flags = b2DebugDraw::e_shapeBit;
    //flags += b2DebugDraw::e_jointBit;
    //flags += b2DebugDraw::e_aabbBit;
    //flags += b2DebugDraw::e_pairBit;
    //flags += b2DebugDraw::e_centerOfMassBit;

    GameKernel::debugDraw = new DebugDraw(*GameKernel::app);
    GameKernel::debugDraw->SetFlags(flags);
    GameKernel::physicsWorld->SetDebugDraw(GameKernel::debugDraw);

    std::cout << "[System][new] Memory allocation debugdraw\n";
}

b2World* GameKernel::getPhysicsWorld()
{
    return GameKernel::physicsWorld;
}

sf::RenderWindow* GameKernel::getApp()
{
    return GameKernel::app;
}

std::list<b2Body*> GameKernel::getphysicsObjectList()
{
    return this->physicsObjectList;
}


DebugDraw* GameKernel::getdebugDraw()
{
        return GameKernel::debugDraw;
}

void GameKernel::addDynamicBox(int x, int y)
{
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	bodyDef.angle = randomNumber(0,360)*RADTODEG;
	b2Body* bodyBox = GameKernel::physicsWorld->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(randomNumber(10,50)*UNRATIO, randomNumber(10,50)*UNRATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	/////add material class in the futurec.
	fixtureDef.density = 0.6f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.6f;
	//////

	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    GameKernel::physicsObjectList.push_front(bodyBox);

     std::cout << "[Box2D] Adding dynamic rectangle \n";
}

void GameKernel::addDynamicBox(int x, int y, float heigth, float widgth)
{
     b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	b2Body* bodyBox = GameKernel::physicsWorld->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(heigth*UNRATIO, widgth*UNRATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	/////add material class in the futurec.
	fixtureDef.density = 0.6f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.6f;
	//////

	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    GameKernel::physicsObjectList.push_front(bodyBox);

     std::cout << "[Box2D] Adding dynamic rectangle \n";
}

void GameKernel::addStaticBox(int x, int y)
{
    b2BodyDef bodyDef;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	bodyDef.angle = randomNumber(0,360)*RADTODEG;
	b2Body* bodyBox = GameKernel::physicsWorld->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox(randomNumber(10,50)*UNRATIO, randomNumber(10,50)*UNRATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    GameKernel::physicsObjectList.push_front(bodyBox);

     std::cout << "[Box2D] Adding static rectangle \n";
}

void GameKernel::addStaticBox(int x, int y, float heigth, float widgth)
{
     b2BodyDef bodyDef;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
	b2Body* bodyBox = GameKernel::physicsWorld->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox(heigth*UNRATIO, widgth*UNRATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	bodyBox->CreateFixture(&fixtureDef);

    //add the body to the list
    GameKernel::physicsObjectList.push_front(bodyBox);

     std::cout << "[Box2D] Adding static rectangle \n";
}

void GameKernel::addDynamicCircle(int x, int y)
{
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
    b2Body *bdCircle = GameKernel::physicsWorld->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = (randomNumber(10,50)*UNRATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;

    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;

    bdCircle->CreateFixture(&fixtureDef);

    //add the body to the list
    GameKernel::physicsObjectList.push_front(bdCircle);

    std::cout << "[Box2D] Adding dynamic circle \n";
}

void GameKernel::addDynamicCircle(int x, int y, float radius)
{
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
    b2Body *bdCircle = GameKernel::physicsWorld->CreateBody(&bodyDef);
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = (radius*UNRATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;

    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;

    bdCircle->CreateFixture(&fixtureDef);

    //add the body to the list
     GameKernel::physicsObjectList.push_front(bdCircle);

    std::cout << "[Box2D] Adding dynamic circle \n";
}

void GameKernel::addStaticCircle(int x, int y)
{
    b2BodyDef bodyDef;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
    b2Body *bdCircle = GameKernel::physicsWorld->CreateBody(&bodyDef);
    b2CircleShape staticCircle;
    staticCircle.m_radius = (randomNumber(10,50)*UNRATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &staticCircle;

    bdCircle->CreateFixture(&fixtureDef);

    //add the body to the list
     GameKernel::physicsObjectList.push_front(bdCircle);

    std::cout << "[Box2D] Adding static circle \n";
}

void GameKernel::addStaticCircle(int x, int y, float radius)
{
    b2BodyDef bodyDef;
	bodyDef.position.Set(x*UNRATIO, y*UNRATIO);
    b2Body *bdCircle = GameKernel::physicsWorld->CreateBody(&bodyDef);
    b2CircleShape staticCircle;
    staticCircle.m_radius = (radius*UNRATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &staticCircle;

    bdCircle->CreateFixture(&fixtureDef);

    //add the body to the list
     GameKernel::physicsObjectList.push_front(bdCircle);

    std::cout << "[Box2D] Adding static circle \n";
}

int GameKernel::randomNumber(int min, int max)
{
    /*
    srand(time(0));
    int result = min+rand()%(max-min);
    //std::cout << "result: " << result << "\n";

    */
    sf::Randomizer::SetSeed(time(0));
    return sf::Randomizer::Random(min, max);
}

void GameKernel::setWindowIcon(std::string imagePath)
{
    sf::Image windowIcon;
    sf::Image background;
    sf::Sprite backgroundSprite;
    windowIcon.LoadFromFile(imagePath);
    GameKernel::app->SetIcon(windowIcon.GetWidth(),windowIcon.GetHeight(), windowIcon.GetPixelsPtr());

}

void GameKernel::setBackground(std::string imagePath, sf::Sprite *bkSprite)
{
    sf::Image background;
    sf::Sprite backgroundSprite;

    background.LoadFromFile("resources/backgrounds/logoHD.png");
    backgroundSprite.SetPosition(0,0);
    backgroundSprite.SetImage(background);
    backgroundSprite.Resize(this->resWidgth,this->resHeigth);
    backgroundSprite.SetColor(sf::Color(255,255,255,150)); //alpha
    bkSprite = &backgroundSprite;

}

void GameKernel::printDebugInfo()
{
    std::string fpsString;
    std::ostringstream os;

    //calculate FPS
    float framerate = (1.0f / GameKernel::app->GetFrameTime());

    //start adding data to the string
    os << framerate;
    fpsString = "Box2D & SFML Debug Draw V0.01a\nFPS: ";
    fpsString.append(os.str());
    fpsString.append("\nbodies/contacts/joints/proxies = ");
    os.str(std::string());
    os << GameKernel::physicsWorld->GetBodyCount() << "/" <<
            GameKernel::physicsWorld->GetContactCount() << "/" <<
            GameKernel::physicsWorld->GetJointCount() << "/" <<
            GameKernel::physicsWorld->GetProxyCount();

   fpsString.append(os.str());
   GameKernel::debugDraw->DrawString(0,0,fpsString.c_str());
}

void GameKernel::removePhysicBodies(int leftLimit, int rightLimit, int upLimit, int downLimit)
{
    int count = 0;

    for(std::list<b2Body*>::iterator i = GameKernel::physicsObjectList.begin();i != GameKernel::physicsObjectList.end();)
    {

        if( ((*i)->GetPosition().x*RATIO < leftLimit)  || ((*i)->GetPosition().x*RATIO > rightLimit) ||
            ((*i)->GetPosition().y*RATIO < upLimit)    || ((*i)->GetPosition().y*RATIO > downLimit))
        {
            GameKernel::physicsWorld->DestroyBody(*i);
            i = GameKernel::physicsObjectList.erase(i); //update iterator
            count++;
        }
        else
            i++; //nex body
    }

    std::cout << "[Box2D] bodies deleted: " << count << "\n";
}


