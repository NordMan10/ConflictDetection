#ifndef IMODEL_H
#define IMODEL_H

#include <vector>

#include "cdpoint.h"
#include "fieldpoints.h"
#include "IAircraftTimerTickObserver.h"

class IModel
{
public:
    virtual ~IModel(){};

    virtual std::vector<CDPoint>& getZonePoints() = 0;
    virtual std::vector<CDPoint>& getPathPoints() = 0;
    virtual std::vector<CDPoint>& getPathIntersectionPoints() = 0;

    virtual FieldPoints& getFieldPoints() = 0;

    virtual std::vector<std::vector<CDPoint>>& getPaths() = 0;

    virtual long long getStopwatchValue() = 0;
    virtual void updateStopwatchValue(int value) = 0;
    virtual void setStopwatchValue(int value) = 0;

    // Observer pattern methods
    virtual void registerObserver(IAircraftTimerObserver& observer) = 0;
};

#endif // IMODEL_H
