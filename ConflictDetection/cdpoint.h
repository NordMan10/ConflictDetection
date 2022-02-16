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
    CDPoint(int x, int y, bool rawCoords = true);

    //static int getNextId();

    //int getId();

    int x();
    int y();

    //CDPointType getType();

private:
    //int m_Id;

    int m_X;
    int m_Y;

    std::tuple<int> t;
    //CDPointType m_Type;

    //static int ms_PointCount;
};

#endif // CDPOINT_H
