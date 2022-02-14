#ifndef IMODEL_H
#define IMODEL_H

#include <vector>

#include "cdpoint.h"

class IModel
{
public:
    virtual ~IModel(){};

    virtual std::vector<CDPoint> getZonePoints() const = 0;
    virtual std::vector<CDPoint> getPathPoints() const = 0;
    virtual std::vector<CDPoint> getPathIntersectionPoints() const = 0;

};

#endif // IMODEL_H
