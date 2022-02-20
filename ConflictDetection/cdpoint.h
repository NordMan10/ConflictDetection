#ifndef CDPOINT_H
#define CDPOINT_H

#include "convert.h"

//enum CDPointType {
//    ZONE,
//    PATH,
//    PATH_INTERSECTION
//};

class CDPoint
{
public:
    CDPoint(int x, int y, int z = 3000, bool rawCoords = true);

    //static int getNextId();

    //int getId();

    int x();
    int y();
    int z();

    //CDPointType getType();

    friend bool operator==(const CDPoint& p1, const CDPoint& p2);
    friend bool operator!=(const CDPoint& p1, const CDPoint& p2);

private:
    //int m_Id;

    int m_X;
    int m_Y;
    int m_Z;

    //CDPointType m_Type;

    //static int ms_PointCount;
};

#endif // CDPOINT_H
