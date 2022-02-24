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

    int x() const ;
    int y() const ;
    int z() const ;

    int x_inMeters() const ;
    int y_inMeters() const ;
    int z_inMeters() const ;

    //CDPointType getType();

    friend bool operator==(const CDPoint& p1, const CDPoint& p2);
    friend bool operator!=(const CDPoint& p1, const CDPoint& p2);

private:
    //int m_Id;

    int m_X;
    int m_Y;
    int m_Z;

    int m_X_inMeters;
    int m_Y_inMeters;
    int m_Z_inMeters;

    //CDPointType m_Type;

    //static int ms_PointCount;
};

#endif // CDPOINT_H
