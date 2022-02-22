#include "aircraft.h"

Aircraft::Aircraft(std::string id, AircraftPath path, IAircraftObserver* observer, int aircraftListIndex, int timerTickValue) :
    m_Id(id),
    m_Path(path),
    m_ActivePathStartPoint(path.getPath()[0]),
    m_ActivePathEndPoint(path.getPath()[1])
{
    m_AircraftObservers.push_back(observer);
    m_AircraftListIndex = aircraftListIndex;

    m_X = m_Path.getPath()[0].x();
    m_Y = m_Path.getPath()[0].y();
    m_Z = m_Path.getPath()[0].z();

    image = QPixmap(":/resources/img/aircraft2.png");

    m_TimerTickValue = timerTickValue;
    calculateShifts(timerTickValue);


}

void Aircraft::updateData(int timerTickValue) {
    m_X += m_XShift;
    m_Y += m_YShift;

    handleArrivalToMiddlePoint();
    handleArrivalToEndPoint();
}

std::string Aircraft::getId() const {
    return m_Id;
}

double Aircraft::x() const {
    return m_X;
}

double Aircraft::y() const {
    return m_Y;
}

double Aircraft::z() const {
    return m_Z;
}

AircraftPath& Aircraft::getPath() {
    return m_Path;
}

int Aircraft::getDangerRadius() {
    return m_DangerRadius;
}

int Aircraft::getImageWidth() {
    return m_ImageWidth;
}

int Aircraft::getImageHeight() {
    return m_ImageHeight;
}

int Aircraft::getISZ_Width() {
    return m_ISZ_Width;
}

int Aircraft::getISZ_Length() {
    return m_ISZ_Length;
}

int Aircraft::get_IPSZ_Length() {
    return Convert::ConvertMetersToPixels(m_Velocity * m_PredictingInterval);
}

double Aircraft::getHorizontalAngle() {
    int dx = (m_ActivePathStartPoint.x() - m_ActivePathEndPoint.x()) * -1;
    int dy = m_ActivePathStartPoint.y() - m_ActivePathEndPoint.y();

    double angle = std::atan2(dy, dx) * 180 / PI;

    return angle;
}

void Aircraft::handleArrivalToEndPoint() {
    CDPoint endPoint = m_Path.getPath()[m_Path.getPath().size() - 1];
    if (isAircraftAtPoint(endPoint)) {
        for (int i = 0; i < m_AircraftObservers.size(); i++) {
            m_AircraftObservers[i]->updateAircraftData(m_AircraftListIndex);
        }
        m_AircraftObservers.clear();
    }
}

void Aircraft::handleArrivalToMiddlePoint() {
    if (isAircraftAtPoint(m_ActivePathEndPoint)) {
        if (m_ActivePathEndPoint != m_Path.getPath().back()) {
            m_ActivePathStartPoint = m_ActivePathEndPoint;
            m_ActivePathEndPoint = getNextPathPoint(m_ActivePathStartPoint);

            calculateShifts(m_TimerTickValue);
        }
    }
}

void Aircraft::calculateShifts(int timerTickValue) {
    auto angle = getHorizontalAngle();

    double pathShift = m_Velocity / (1000 / timerTickValue);

    double xShift = (pathShift * std::cos(angle * PI / 180)) / Convert::s_MetersInPixel;
    double yShift = (-1) * (pathShift * std::sin(angle * PI / 180)) / Convert::s_MetersInPixel;

    m_XShift = xShift;
    m_YShift = yShift;
}

bool Aircraft::isAircraftAtPoint(CDPoint point) {
    return (std::abs(m_X - point.x()) < 2 && std::abs(m_Y - point.y()) < 2);
}

CDPoint Aircraft::getNextPathPoint(CDPoint point) {
    for (int i = 0; i < m_Path.getPath().size(); i++) {
        if (m_Path.getPath()[i] == point)
            return m_Path.getPath()[i + 1];
    }

    throw std::invalid_argument("The argument point is not contained in the aircraft path");
}

bool Aircraft::isAircraftPotentiallyDangerous(const Aircraft& aircraft) {
    return std::pow(aircraft.x() - x(), 2) + std::pow(aircraft.y() - y(), 2) <= std::pow(m_DangerRadius, 2);
}

void Aircraft::addPotentiallyDangerousAircraft(Aircraft& aircraft) {
    m_PotentiallyDangerousAircrafts.push_back(aircraft);
}

void Aircraft::removePotentiallyDangerousAircraft(const Aircraft& aircraft) {
    auto it = std::remove(m_PotentiallyDangerousAircrafts.begin(), m_PotentiallyDangerousAircrafts.end(), aircraft);
}

bool operator==(const Aircraft& a1, const Aircraft& a2) {
    return a1.getId() == a2.getId();
}

bool operator!=(const Aircraft& a1, const Aircraft& a2) {
    return !(a1 == a2);
}





