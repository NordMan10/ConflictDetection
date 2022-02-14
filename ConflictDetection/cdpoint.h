#ifndef CDPOINT_H
#define CDPOINT_H


enum CDPointType {
    ZONE,
    PATH,
    PATH_INTERSECTION
};

class CDPoint
{
public:
    CDPoint(int id, int x, int y, CDPointType type);

    static int getNextId();

    int getId();

    int x();
    int y();

    CDPointType getType();

private:
    int m_Id;

    int m_X;
    int m_Y;

    CDPointType m_Type;

    static int ms_PointCount;
};

#endif // CDPOINT_H
