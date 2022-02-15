#ifndef FIELDPOINTS_H
#define FIELDPOINTS_H

#include "cdpoint.h"

class FieldPoints
{
public:
    FieldPoints(std::vector<CDPoint> &zonePoints, std::vector<CDPoint> &pathPoints,
                std::vector<CDPoint> &pathIntersectionPoints);

public:
    std::vector<CDPoint> &zonePoints;
    std::vector<CDPoint> &pathPoints;
    std::vector<CDPoint> &pathIntersectionPoints;
};

#endif // FIELDPOINTS_H
