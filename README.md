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
### GNU/Linux

    mkdir ./build
    cd ./build
    cmake ..
    make
    make install
    cd ../
    ./box2dsfml

### Windows
You need a compiler like mingw and CMake
In windows you have to set the env variabes. To do this add to PATH env. variable the location of this 3 paths:

* The lib directory of SFML (where the SFML libs are: *.a, *.dll... )
* The include directory of SFML (Where "SFML" folder is)
* The lib directory where Box2D lib file is (In my case the lib is called: libBox2D.a)
* The include directory of Box2D (Where "Box2D" folder is)

The PATH variable you should add (note: add ';' at the front) at the end of the PATH is something like this (Note that my Box2D lib is in the same folder of the Box2D header dir so I only add one path for the box2D)  
	C:\sources\SFML-1.6\include;C:\sources\SFML-1.6\lib;C:\sources\Box2D_v2.1.2_bin

Then use the same way to compile as in GNU/Linux (for example with mingw32-make)

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
