/*
    Copyright (C) 2011 Xabier Larrakoetxea (slok)
    Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com

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

#include "QueryCallback.h"

QueryCallback::QueryCallback(const b2Vec2& point)
{
    m_point = point;
    m_fixture = NULL;
}

bool QueryCallback::ReportFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();
    if (body->GetType() == b2_dynamicBody)
    {
        bool inside = fixture->TestPoint(m_point);
        if (inside)
        {
            m_fixture = fixture;

            // We are done, terminate the query.
            return false;
        }
    }

    // Continue the query.
    return true;
}

