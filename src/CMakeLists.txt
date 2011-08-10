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

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

# all source files
set(SRC
    ${SRCROOT}/DebugDraw.cpp
    ${SRCROOT}/GameKernel.cpp
    ${SRCROOT}/Material.cpp 
    ${SRCROOT}/QueryCallback.cpp
    ${SRCROOT}/main.cpp
)

find_package(SFML REQUIRED COMPONENTS System Window Graphics)
find_package(Box2D REQUIRED)

#set headers stuff
set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/src
    ${SFML_INCLUDE_DIR}
    ${BOX2D_INCLUDE_DIR}
)

#set lib stuff
set(DEPEND_LIBS
    ${SFML_LIBRARIES}
    ${BOX2D_LIBRARY}
)

include_directories(${INCLUDE_DIRS})
add_executable(box2dsfml ${SRC})
target_link_libraries(box2dsfml ${DEPEND_LIBS})

