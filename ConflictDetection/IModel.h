#ifndef IMODEL_H
#define IMODEL_H

#include <vector>

#include "cdpoint.h"
#include "fieldpoints.h"

class IModel
{
public:
    virtual ~IModel(){};

    virtual std::vector<CDPoint>& getZonePoints() = 0;
    virtual std::vector<CDPoint>& getPathPoints() = 0;
    virtual std::vector<CDPoint>& getPathIntersectionPoints() = 0;

    virtual FieldPoints& getFieldPoints() = 0;

};

#endif // IMODEL_H
