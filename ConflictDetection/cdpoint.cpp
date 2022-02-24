#include "cdpoint.h"

CDPoint::CDPoint(int x, int y, int z, bool rawCoords)
{
    //m_Id = id;
    //m_Type = type;

    if (rawCoords) {
        auto coords = Convert::TransformCoordsFromSchemeToProgram(x, y);
        m_X_inMeters = std::get<0>(coords);
        m_Y_inMeters = std::get<1>(coords);
        m_Z_inMeters = z;

        coords = Convert::TransformCoordsFromSchemeToProgramWithConvert(x, y);
        m_X = std::get<0>(coords);
        m_Y = std::get<1>(coords);
        m_Z = Convert::ConvertMetersToPixels(z);
    }
    else {
        m_X = x;
        m_Y = y;
        m_Z = z;
    }
}

bool operator==(const CDPoint& p1, const CDPoint& p2) {
    return p1.m_X == p2.m_X && p1.m_Y == p2.m_Y && p1.m_Z == p2.m_Z;
}

bool operator!=(const CDPoint& p1, const CDPoint& p2) {
    return !(p1 == p2);
}

//int CDPoint::getId() { return m_Id; }

int CDPoint::x() const { return m_X; }

int CDPoint::y() const { return m_Y; }

int CDPoint::z() const { return m_Z; }


int CDPoint::x_inMeters() const {
    return m_X_inMeters;
}

int CDPoint::y_inMeters() const {
    return m_Y_inMeters;
}

int CDPoint::z_inMeters() const {
    return m_Z_inMeters;
}


//CDPointType CDPoint::getType() { return m_Type; }
