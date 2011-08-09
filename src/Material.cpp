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

#include "../include/Material.h"

//Static member data
const Material Material::DEFAULT(1.00f,  0.30f, 0.1f);
const Material Material::METAL(7.85f,  0.20f, 0.2f);
const Material Material::STONE(2.40f,  0.50f, 0.1f);
const Material Material::WOOD(0.53f,  0.40f, 0.15f);
const Material Material::GLASS(2.50f,  0.10f, 0.2f);
const Material Material::RUBBER(1.50f,  0.80f, 0.4f);
const Material Material::ICE(0.92f,  0.01f, 0.1f);
const Material Material::PUMICE(0.25f,  0.60f, 0.0f);
const Material Material::POLYSTYRENE(0.10f,  0.60f, 0.05f);
const Material Material::FABRIC(0.03f,  0.60f, 0.1f);
const Material Material::SPONGE(0.018f, 0.90f, 0.05f);
const Material Material::AIR(0.001f, 0.90f, 0.0f);
const Material Material::HELIUM(0.0001f, 0.9f, 0.0f);

Material::Material(float density, float friction, float restitution)
{
    this->density = density;
    this->friction = friction;
    this->restitution = restitution;
}

Material::Material()
{
    //ctor
}

Material::~Material()
{
    //dtor
}

void Material::setRestitution(float r)
{
    this->restitution = r;
}

float Material::getRestitution()
{
    return this->restitution;
}

void Material::setFriction(float f)
{
    this->restitution = f;
}

float Material::getFriction()
{
    return this->friction;
}

void Material::setDensity(float d)
{
    this->density = d;
}

float Material::getDensity()
{
    return this->density;
}

