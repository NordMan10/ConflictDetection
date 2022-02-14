#include "model.h"

Model::Model()
{

}

std::vector<CDPoint> Model::getZonePoints() const {
    return m_ZonePoints;
}

std::vector<CDPoint> Model::getPathPoints() const {
    return m_PathPoints;
}

std::vector<CDPoint> Model::getPathIntersectionPoints() const {
    return m_PathIntersectionPoints;
}

