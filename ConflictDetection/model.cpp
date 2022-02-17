#include "model.h"

Model::Model() :
    m_FieldPoints(m_ZonePoints, m_PathPoints, m_PathIntersectionPoints)
{
    initPoints();
    initPaths();
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

std::vector<std::vector<CDPoint>>& Model::getPaths() {
    return m_Paths;
}

void Model::initPoints() {
    initZonePoints();
    initPathPoints();
    initPathIntersectionPoints();
}

void Model::initZonePoints() {
    m_ZonePoints.push_back(CDPoint(95000, -25000));
    m_ZonePoints.push_back(CDPoint(50000, -60000));
    m_ZonePoints.push_back(CDPoint(305000, -183000));
    m_ZonePoints.push_back(CDPoint(405000, -50000));
    m_ZonePoints.push_back(CDPoint(190000, -25000));
}

void Model::initPathPoints() {
    m_PathPoints.push_back(CDPoint(70000, -44000));
    m_PathPoints.push_back(CDPoint(90000, -79000));
    m_PathPoints.push_back(CDPoint(150000, -108000));
    m_PathPoints.push_back(CDPoint(300000, -180500));
    m_PathPoints.push_back(CDPoint(397000, -60000));
    m_PathPoints.push_back(CDPoint(300000, -38000));
    m_PathPoints.push_back(CDPoint(220000, -28000));

}

void Model::initPathIntersectionPoints() {
    m_PathIntersectionPoints.push_back(CDPoint(215000, -75000));
}

void Model::initPaths() {
    m_Paths.push_back({m_PathPoints[0], m_PathPoints[3]});
    m_Paths.push_back({m_PathPoints[1], m_PathPoints[5]});
    m_Paths.push_back({m_PathPoints[2], m_PathPoints[4]});
    m_Paths.push_back({m_PathPoints[5], m_PathPoints[3]});
    m_Paths.push_back({m_PathPoints[6], m_PathIntersectionPoints[0], m_PathPoints[3]});
}

long long Model::getStopwatchValue() {
    return m_StopwatchValue;
}

void Model::updateStopwatchValue(int value) {
    m_StopwatchValue += value;
}

void Model::setStopwatchValue(int value) {
    m_StopwatchValue = value;
}

void Model::registerAircraftTimerObserver(IAircraftTimerObserver* observer) {
    m_AircraftTimerObservers.push_back(observer);
}

void Model::removeAircraftTimerObserver(IAircraftTimerObserver* observer) {
    m_AircraftTimerObservers.erase(std::remove(m_AircraftTimerObservers.begin(), m_AircraftTimerObservers.end(), observer), m_AircraftTimerObservers.end());
}

void Model::notifyAircraftTimerObservers() {
//    for (int i = 0; i < m_AircraftTimerObservers.size(); i++)
//    {
//        m_AircraftTimerObservers[i]->updateAircraftData();
//    }
}

void Model::addAircraftsObserver(IAircraftObserver* observer) {
    m_AircraftObserver = observer;
}

void Model::createAircraft() {
    Aircraft* aircraft = new Aircraft("A301", 100, 200, 3000);
    aircraft->registerObserver(m_AircraftObserver);
    m_Aircrafts.push_back(aircraft);
    connect(m_TimerAircraftsMotion, SIGNAL(timeout()), aircraft, SLOT(updateAircraftData()));
}

void Model::start() {
    m_TimerAircraftsMotion->start(m_TimerAircraftsMotionTickValue);
}

void Model::stop() {

}

void Model::pause() {

}

void Model::continueWork() {

}
