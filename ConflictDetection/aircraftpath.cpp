#include "aircraftpath.h"

AircraftPath::AircraftPath(std::vector<CDPoint> path)
{
    m_Path = path;
}


std::vector<CDPoint>& AircraftPath::getPath() {
    return m_Path;
}
