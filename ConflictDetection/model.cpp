#include "model.h"

Model::Model() :
    m_FieldPoints(m_ZonePoints, m_PathPoints, m_PathIntersectionPoints)
{
    initPoints();
    initPaths();

    m_TimerAircraftsMotion = new QTimer();

    QObject::connect(m_TimerAircraftsMotion, &QTimer::timeout, this, &Model::notifyAircraftTimerObservers);


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

std::vector<AircraftPath>& Model::getPaths() {
    return m_AircraftPaths;
}

std::vector<Aircraft*>& Model::getAircrafts() {
    return m_Aircrafts;
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
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[0], m_PathPoints[3]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[1], m_PathPoints[5]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[2], m_PathPoints[4]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[5], m_PathPoints[3]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[6], m_PathIntersectionPoints[0], m_PathPoints[3]}));
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
    for (int i = 0; i < m_AircraftTimerObservers.size(); i++) {
        m_AircraftTimerObservers[i]->updateData(m_TimerAircraftsMotionTickValue);
    }

    // В этот метод передается -1, поскольку интерфейс, к которому принадлежит данный метод,
    // используется и классом MainWindow (Представлением), и моделью. В модели нужно принимать число,
    // в Представлении нет. Такие дела.
    m_AircraftObserver->updateAircraftData(-1);

    for (int i = 0; i < m_Aircrafts.size() - 1; i++) {
        for (int j = i + 1; j < m_Aircrafts.size(); j++) {
            auto potDangerousAircrafts = m_Aircrafts[i]->getPotentiallyDangerousAircrafts();
            if (m_Aircrafts[i]->isAircraftPotentiallyDangerous(*m_Aircrafts[j]) &&
                    !(m_Aircrafts[i]->contains(m_Aircrafts[i]->getPotentiallyDangerousAircrafts(), *m_Aircrafts[j])))
            {
                m_Aircrafts[i]->addPotentiallyDangerousAircraft(*m_Aircrafts[j]);
            }
        }
    }
}

void Model::registerAircraftsObserver(IAircraftObserver* observer) {
    m_AircraftObserver = observer;
}

void Model::createAircraft() {
    m_Aircrafts.push_back(new Aircraft("A301", m_AircraftPaths[0], this,
                          (int)m_Aircrafts.size(), m_TimerAircraftsMotionTickValue));
    registerAircraftTimerObserver(m_Aircrafts[m_Aircrafts.size() - 1]);

    m_Aircrafts.push_back(new Aircraft("A302", m_AircraftPaths[0], this,
                          (int)m_Aircrafts.size(), m_TimerAircraftsMotionTickValue));
    registerAircraftTimerObserver(m_Aircrafts[m_Aircrafts.size() - 1]);
}

void Model::updateAircraftData(int aircraftListIndex) {
    m_Aircrafts.erase(m_Aircrafts.begin() + aircraftListIndex);
}

void Model::start() {
    m_TimerAircraftsMotion->start(m_TimerAircraftsMotionTickValue);

    createAircraft();
}

void Model::stop() {
    m_TimerAircraftsMotion->stop();
    m_Aircrafts.clear();
}

void Model::pause() {
    m_TimerAircraftsMotion->stop();
}

void Model::continueWork() {
    m_TimerAircraftsMotion->start();
}
