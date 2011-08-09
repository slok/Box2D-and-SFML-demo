/*
    Copyright (C) 2011 Xabier Larrakoetxea (slok)
    Copyright (C) 2009 (Edge)

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

#ifndef MATERIAL_H
#define MATERIAL_H


class Material
{
    public:
        Material();
        Material(float density, float friction, float restitution);
        virtual ~Material();
        float getDensity();
        void setDensity(float d);
        float getFriction();
        void setFriction(float f);
        float getRestitution();
        void setRestitution(float r);

        //static member data
        static const Material DEFAULT;
        static const Material METAL;
        static const Material STONE;
        static const Material WOOD;
        static const Material GLASS;
        static const Material RUBBER;
        static const Material ICE;
        static const Material PUMICE;
        static const Material POLYSTYRENE;
        static const Material FABRIC;
        static const Material SPONGE;
        static const Material AIR;
        static const Material HELIUM;

    private:
        float density;
        float friction;
        float restitution;
};

#endif // MATERIAL_H
