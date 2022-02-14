#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <vector>

#include "cdpoint.h"

class IController
{
public:
    virtual ~IController(){};

    virtual std::vector<CDPoint> getZonePoints() const = 0;
    virtual std::vector<CDPoint> getPathPoints() const = 0;
    virtual std::vector<CDPoint> getPathIntersectionPoints() const = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void pause() = 0;
    // Не названа как "continue", потому что слово зарезервировано.
    virtual void continueWork() = 0;

};

#endif // ICONTROLLER_H
