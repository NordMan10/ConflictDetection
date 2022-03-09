#include "model.h"

Model::Model() :
    m_FieldPoints(m_ZonePoints, m_PathPoints, m_PathIntersectionPoints)
{
    initPoints();
    initPaths();

    m_TimerAircraftsMotion = new QTimer();
    QObject::connect(m_TimerAircraftsMotion, &QTimer::timeout, this, &Model::notifyAircraftTimerObservers);

    m_TimerAircraftsCreation = new QTimer();
    //QObject::connect(m_TimerAircraftsCreation, &QTimer::timeout, this, &Model::createAircraft);
}


void Model::initPoints() {
    initZonePoints();
    initPathPoints();
    initPathIntersectionPoints();
}

// Во всей программе, кроме места ввода координат из числовых данных (то есть три метода ниже), все координаты переведены
// в программную систему координат, ось вправо — это X, ось сверху вниз — это Y (не забываем, что он перевернут),
// ось Z — это высота (смотрит на нас).

// Координаты из числового материала вводятся так: сначала значение по оси справа налево (которая в программной с. к. есть X,
// потом значение по оси снизу вверх (которая в программной с. к. есть Y).
// Например: даны координты точки в с. к. летчиков: Z = 95000, X = -25000; мы так и записываем: 95000, -25000.

void Model::initZonePoints() {

    m_ZonePoints.push_back(CDPoint(95000, -25000));
    m_ZonePoints.push_back(CDPoint(50000, -60000));
    m_ZonePoints.push_back(CDPoint(305000, -183000));
    m_ZonePoints.push_back(CDPoint(405000, -50000));
    m_ZonePoints.push_back(CDPoint(190000, -25000));
}

void Model::initPathPoints() {
    m_PathPoints.push_back(CDPoint(70500, -44000));
    m_PathPoints.push_back(CDPoint(66000, -67500));
    m_PathPoints.push_back(CDPoint(150000, -108000));
    m_PathPoints.push_back(CDPoint(300000, -180500));
    m_PathPoints.push_back(CDPoint(397000, -60000));
    m_PathPoints.push_back(CDPoint(300000, -38000));
    m_PathPoints.push_back(CDPoint(220000, -28500));

}

void Model::initPathIntersectionPoints() {
    m_PathIntersectionPoints.push_back(CDPoint(210000, -75000));
}

void Model::initPaths() {
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[0], m_PathPoints[3]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[1], m_PathPoints[5]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[2], m_PathPoints[4]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[5], m_PathPoints[3]}));
    m_AircraftPaths.push_back(AircraftPath({m_PathPoints[6], m_PathIntersectionPoints[0], m_PathPoints[3]}));
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

QString Model::getAircraftId(int pathId) {
    return "A" + QString::number(pathId + 1) + QString("0") + QString::number(m_Aircrafts.size() + 1);
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
    m_AircraftTimerObservers.erase(std::remove(m_AircraftTimerObservers.begin(),
                                               m_AircraftTimerObservers.end(), observer), m_AircraftTimerObservers.end());
}

void Model::notifyAircraftTimerObservers() {
    for (int i = 0; i < m_AircraftTimerObservers.size(); i++) {
        m_AircraftTimerObservers[i]->updateData(m_TimerAircraftsMotionTickValue);
    }

    // В этот метод передается "", поскольку интерфейс, к которому принадлежит данный метод,
    // используется и классом MainWindow (Представлением), и Моделью. В модели нужно принимать значение,
    // в Представлении нет. Такие дела.
    m_AircraftObserver->updateAircraftData("");

    checkPotentiallyDangerousAircrafts();
}

void Model::checkPotentiallyDangerousAircrafts() {
    m_CanRemoveAircraft = false;
    for (int i = 0; i < m_Aircrafts.size() - 1; i++) {
        for (int j = i + 1; j < m_Aircrafts.size(); j++) {
            auto potDangerousAircrafts = m_Aircrafts[i]->getPotentiallyDangerousAircrafts();
            if (m_Aircrafts[i]->isAircraftPotentiallyDangerous(*m_Aircrafts[j]) &&
                    !(m_Aircrafts[i]->contains(potDangerousAircrafts, *m_Aircrafts[j])))
            {
                m_Aircrafts[i]->addPotentiallyDangerousAircraft(*m_Aircrafts[j]);
            } else if (!m_Aircrafts[i]->isAircraftPotentiallyDangerous(*m_Aircrafts[j]) &&
                       (m_Aircrafts[i]->contains(potDangerousAircrafts, *m_Aircrafts[j]))) {
                m_Aircrafts[i]->removePotentiallyDangerousAircraft(*m_Aircrafts[j]);
            }
        }
    }
    m_CanRemoveAircraft = true;
}

void Model::registerAircraftsObserver(IAircraftObserver* observer) {
    m_AircraftObserver = observer;
}

// В конструкторе идет привязка таймера и вызова этого метода
void Model::createAircraft() {
    // Если нужна генерация самолетов через случайное значение в интервале, то раскомментируй в этом методе все,
    // что закомментировано, и закомментируй все, что сейчас раскомментировано.
//    std::random_device rd;
//    std::mt19937 eng(rd());
//    std::uniform_int_distribution<int> pathDistr(0, m_AircraftPaths.size() - 1);
//    std::uniform_int_distribution<int> intervalDistr(m_TimerACTickValueMin, m_TimerACTickValueMax);

//    int pathIndex = pathDistr(eng);
//    m_Aircrafts.push_back(new Aircraft(getAircraftId(pathIndex).toStdString(), m_AircraftPaths[pathIndex], this,
//                                       getStopwatchValue(), (int)m_Aircrafts.size(), m_TimerAircraftsMotionTickValue));

//    registerAircraftTimerObserver(m_Aircrafts[m_Aircrafts.size() - 1]);

    m_Aircrafts.push_back(new Aircraft(getAircraftId(0).toStdString(), m_AircraftPaths[0], this,
                                       getStopwatchValue(),
                                       (int)m_Aircrafts.size(), m_TimerAircraftsMotionTickValue));

    registerAircraftTimerObserver(m_Aircrafts[m_Aircrafts.size() - 1]);

    m_Aircrafts.push_back(new Aircraft(getAircraftId(1).toStdString(), m_AircraftPaths[1], this,
                                        getStopwatchValue(),
                                       (int)m_Aircrafts.size(), m_TimerAircraftsMotionTickValue));

    registerAircraftTimerObserver(m_Aircrafts[m_Aircrafts.size() - 1]);

    m_Aircrafts.push_back(new Aircraft(getAircraftId(2).toStdString(), m_AircraftPaths[2], this,
                                       getStopwatchValue(),
                                       (int)m_Aircrafts.size(), m_TimerAircraftsMotionTickValue));

    registerAircraftTimerObserver(m_Aircrafts[m_Aircrafts.size() - 1]);

    m_Aircrafts.push_back(new Aircraft(getAircraftId(4).toStdString(), m_AircraftPaths[4], this,
                           getStopwatchValue(),
                                       (int)m_Aircrafts.size(), m_TimerAircraftsMotionTickValue));

    registerAircraftTimerObserver(m_Aircrafts[m_Aircrafts.size() - 1]);

//    m_TimerAircraftsCreation->setInterval(intervalDistr(eng));
}

// Этот метод являетя частью интерфейса Наблюдатель
void Model::updateAircraftData(std::string aircraftId) {
    m_AircraftIdsToRemove.push_back(aircraftId);
    if (m_CanRemoveAircraft) {
        std::vector<int> indices;
        for (int i = 0; i < m_AircraftIdsToRemove.size(); i++) {
            removeAircraftTimerObserver(getAircraftById(m_AircraftIdsToRemove[i]));
            m_Aircrafts.erase(std::remove(m_Aircrafts.begin(), m_Aircrafts.end(), getAircraftById(m_AircraftIdsToRemove[i])), m_Aircrafts.end());

            indices.push_back(i);
        }

        for (int i = 0; i < indices.size(); i++) {
            m_AircraftIdsToRemove.erase(m_AircraftIdsToRemove.begin() + i);
        }
    }
}

Aircraft* Model::getAircraftById(std::string aircraftId) {
    for (int i = 0; i < m_Aircrafts.size(); i++) {
        if (m_Aircrafts[i]->getId() == aircraftId) {
            return m_Aircrafts[i];
        }
    }

    throw std::invalid_argument("The aicraftId is not contained in the list of aircrafts");
}

void Model::start() {
    m_TimerAircraftsMotion->start(m_TimerAircraftsMotionTickValue);
    m_TimerAircraftsCreation->start(m_TimerAircraftsCreationTickValue);

    createAircraft();
}

void Model::stop() {
    m_TimerAircraftsMotion->stop();
    m_TimerAircraftsCreation->stop();

    m_Aircrafts.clear();
}

void Model::pause() {
    m_TimerAircraftsMotion->stop();
    m_TimerAircraftsCreation->stop();
}

void Model::continueWork() {
    m_TimerAircraftsMotion->start();
    m_TimerAircraftsCreation->start();
}
