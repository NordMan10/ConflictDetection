#ifndef AIRCRAFTPATH_H
#define AIRCRAFTPATH_H

#include "cdpoint.h"

class AircraftPath
{
public:
    AircraftPath(std::vector<CDPoint> path);

    std::vector<CDPoint>& getPath();

private:
    std::vector<CDPoint> m_Path;
};

#endif // AIRCRAFTPATH_H
