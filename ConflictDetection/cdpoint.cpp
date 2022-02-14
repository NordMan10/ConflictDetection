#include "cdpoint.h"

CDPoint::CDPoint(int id, int x, int y, CDPointType type)
{
    m_Id = id;
    m_X = x;
    m_Y = y;
    m_Type = type;
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
