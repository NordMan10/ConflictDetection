#include "cdpoint.h"

CDPoint::CDPoint(int x, int y, int z, bool rawCoords)
{
    //m_Id = id;
    //m_Type = type;

    if (rawCoords) {
        auto coords = Convert::TransformCoordsFromSchemeToProgram(x, y);
        m_X = std::get<0>(coords);
        m_Y = std::get<1>(coords);
    }
    else {
        m_X = x;
        m_Y = y;
    }
}

bool operator==(const CDPoint& p1, const CDPoint& p2) {
    return p1.m_X == p2.m_X && p1.m_Y == p2.m_Y && p1.m_Z == p2.m_Z;
}

bool operator!=(const CDPoint& p1, const CDPoint& p2) {
    return !(p1 == p2);
}

//int CDPoint::getId() { return m_Id; }

int CDPoint::x() { return m_X; }

int CDPoint::y() { return m_Y; }

int CDPoint::z() { return m_Z; }

//CDPointType CDPoint::getType() { return m_Type; }
