#include "fieldpoints.h"

FieldPoints::FieldPoints(std::vector<CDPoint> &zonePoints, std::vector<CDPoint> &pathPoints,
                         std::vector<CDPoint> &pathIntersectionPoints) :
    zonePoints(zonePoints),
    pathPoints(pathPoints),
    pathIntersectionPoints (pathIntersectionPoints)
{

}

