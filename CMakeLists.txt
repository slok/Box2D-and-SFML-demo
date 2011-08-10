#
# Box2D and SFML demo cmake build script
# (C) 2011 - Xabier (sLoK) Larrakoetxea <slok69@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or 
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.8)

# project name
project(Box2DSFML)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

# define the build type
set(CMAKE_BUILD_TYPE Release)

# add the header path
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/box2dsfml DESTINATION ${PROJECT_SOURCE_DIR})

# add the subdirectories
add_subdirectory(src)






