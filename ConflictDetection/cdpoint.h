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
    CDPoint();

public:
    int id;

    int x;
    int y;

    CDPointType type;

    static int pointCount;
};

#endif // CDPOINT_H
