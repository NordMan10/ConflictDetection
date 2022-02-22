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

    m_X_inMeters = m_Path.getPath()[0].x_inMeters();
    m_Y_inMeters = m_Path.getPath()[0].y_inMeters();
    m_Z_inMeters = m_Path.getPath()[0].z_inMeters();

    image = QPixmap(":/resources/img/aircraft2.png");

    m_TimerTickValue = timerTickValue;
    calculateShifts(timerTickValue);


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

int Aircraft::x_inMeters() const {
    return m_X_inMeters;
}

int Aircraft::y_inMeters() const {
    return m_Y_inMeters;
}

int Aircraft::z_inMeters() const {
    return m_Z_inMeters;
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
    return m_Velocity * m_PredictingInterval;
}

double Aircraft::getHorizontalAngle() {
    // Попробуй поменять на метры
    int dx = (m_ActivePathStartPoint.x() - m_ActivePathEndPoint.x()) * (-1);
    int dy = m_ActivePathStartPoint.y() - m_ActivePathEndPoint.y();

    double angle = std::atan2(dy, dx) * 180 / PI;

    return angle;
}

void Aircraft::calculateShifts(int timerTickValue) {
    auto angle = getHorizontalAngle();

    m_VelocityX = m_Velocity * std::sin(angle * PI / 180);
    m_VelocityY = m_Velocity * std::cos(angle * PI / 180);

    double pathShift = m_Velocity / (double)(1000 / timerTickValue);

    double xShift_inMeters = (pathShift * std::cos(angle * PI / 180));
    double yShift_inMeters = (-1) * (pathShift * std::sin(angle * PI / 180));

    m_XShift_inMeters = xShift_inMeters;
    m_YShift_inMeters = yShift_inMeters;

    m_XShift = xShift_inMeters / Convert::s_MetersInPixel;
    m_YShift = yShift_inMeters / Convert::s_MetersInPixel;
}

void Aircraft::updateData(int timerTickValue) {
    m_X += m_XShift;
    m_Y += m_YShift;

    auto temp = m_XShift_inMeters;
    auto temp2 = m_X;
    auto temp3 = m_X_inMeters;

    m_X_inMeters += m_XShift_inMeters;
    m_Y_inMeters += m_YShift_inMeters;

    handleArrivalToMiddlePoint();
    handleArrivalToEndPoint();

    // checkBoundsIntersection(); or smth like that
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

void Aircraft::handleArrivalToEndPoint() {
    CDPoint endPoint = m_Path.getPath()[m_Path.getPath().size() - 1];
    if (isAircraftAtPoint(endPoint)) {
        for (int i = 0; i < m_AircraftObservers.size(); i++) {
            m_AircraftObservers[i]->updateAircraftData(m_AircraftListIndex);
        }
        m_AircraftObservers.clear();
    }
}

bool Aircraft::isAircraftAtPoint(CDPoint point) {
    return (std::abs(m_X_inMeters - point.x_inMeters()) < 30 && std::abs(m_Y_inMeters - point.y_inMeters()) < 30);
}

CDPoint Aircraft::getNextPathPoint(CDPoint point) {
    for (int i = 0; i < m_Path.getPath().size(); i++) {
        if (m_Path.getPath()[i] == point)
            return m_Path.getPath()[i + 1];
    }

    throw std::invalid_argument("The argument point is not contained in the aircraft path");
}

// Попробуй поменять на метры (расчет в пикселях может давать сильные неточности)
bool Aircraft::isAircraftPotentiallyDangerous(const Aircraft& aircraft) {
    return std::pow(aircraft.x() - x(), 2) + std::pow(aircraft.y() - y(), 2) <= std::pow(m_DangerRadius, 2);
}

std::vector<std::reference_wrapper<Aircraft>>& Aircraft::getPotentiallyDangerousAircrafts() {
    return m_PotentiallyDangerousAircrafts;
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

//template <typename T>
bool Aircraft::contains(std::vector<std::reference_wrapper<Aircraft>> vec, const Aircraft& elem)
{
    bool result = false;
    for (auto& x : vec)
    {
        if (x.get() == elem)
        {
            result = true;
            break;
        }
    }
    return result;
}







