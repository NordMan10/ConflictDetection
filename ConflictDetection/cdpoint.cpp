#include "cdpoint.h"

CDPoint::CDPoint(int id, int x, int y, CDPointType type, bool rawCoords)
{
    m_Id = id;
    m_Type = type;

    if (rawCoords) {
        auto coords = Convert::TransformCoordsFromSchemeToProgram(y, x);
        m_X = std::get<0>(coords);
        m_Y = std::get<1>(coords);
    }
    else {
        m_X = x;
        m_Y = y;
    }
}

int CDPoint::ms_PointCount = 0;

int CDPoint::getNextId() {
    ms_PointCount++;
    return ms_PointCount;
}

int CDPoint::getId() { return m_Id; }

int CDPoint::x() { return m_X; }

int CDPoint::y() { return m_Y; }

CDPointType CDPoint::getType() { return m_Type; }
