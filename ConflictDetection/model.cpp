#include "model.h"

Model::Model() :
    m_FieldPoints(m_ZonePoints, m_PathPoints, m_PathIntersectionPoints)
{
    initPoints();

}

std::vector<CDPoint>& Model::getZonePoints() {
    return m_ZonePoints;
}

std::vector<CDPoint>& Model::getPathPoints() {
    return m_PathPoints;
}

std::vector<CDPoint>& Model::getPathIntersectionPoints() {
    return m_PathIntersectionPoints;
}

FieldPoints& Model::getFieldPoints() {
    return m_FieldPoints;
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
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 70000, -44000, CDPointType::PATH));
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 90000, -79000, CDPointType::PATH));
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 150000, -108000, CDPointType::PATH));
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 300000, -180500, CDPointType::PATH));
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 397000, -60000, CDPointType::PATH));
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 300000, -38000, CDPointType::PATH));
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 220000, -28000, CDPointType::PATH));
    m_PathPoints.push_back(CDPoint(CDPoint::getNextId(), 215000, -75000, CDPointType::PATH));
}

void Model::initPathIntersectionPoints() {

}
