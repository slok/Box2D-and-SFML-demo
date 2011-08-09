Box2d and SFML demo
===================

About
-----
This little project is a demo of the merge of two great libs, SFML and Box2D

Dependencies
------------
* [SFML](http://www.sfml-dev.org/) >= 1.6
* [Box2D](http://www.box2d.org/) >= 2.1.2

Build & execute
---------------
    mkdir ./build
    cd ./build
    cmake ..
    make
    make install
    cd ../
    ./box2dsfml

Features
--------
* Materials
* Dinamyc and static bodies (Box and circles)
* Debug information (body count, contacts...)
* Box2D debugDraw implementation for SFML
* Mouse and key events to interact with the world
* Mouse joint implemented to grab bodies
* CMake build script

Author
------
Xabier (sLoK) Larrakoetxea [slok69 [at] gmail.com]

License
-------
[GPL V3](http://www.gnu.org/licenses/gpl-3.0.html)
