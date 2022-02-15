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

void Model::initPoints() {
    initZonePoints();
    initPathPoints();
    initPathIntersectionPoints();
}

void Model::initZonePoints() {
    m_ZonePoints.push_back(CDPoint(CDPoint::getNextId(), 95000, -25000, CDPointType::ZONE));
    m_ZonePoints.push_back(CDPoint(CDPoint::getNextId(), 50000, -60000, CDPointType::ZONE));
    m_ZonePoints.push_back(CDPoint(CDPoint::getNextId(), 305000, -183000, CDPointType::ZONE));
    m_ZonePoints.push_back(CDPoint(CDPoint::getNextId(), 405000, -50000, CDPointType::ZONE));
    m_ZonePoints.push_back(CDPoint(CDPoint::getNextId(), 190000, -25000, CDPointType::ZONE));
}

void Model::initPathPoints() {

}

void Model::initPathIntersectionPoints() {

}
