#include "aircraft.h"

Aircraft::Aircraft(std::string id, AircraftPath path) :
    m_Id(id),
    m_Path(path),
    m_ActivePathStartPoint(path.getPath()[0]),
    m_ActivePathEndPoint(path.getPath()[1])
{
    m_X = m_Path.getPath()[0].x();
    m_Y = m_Path.getPath()[0].y();
    m_Z = m_Path.getPath()[0].z();

    image = QPixmap(":/resources/img/aircraft.png");
}

void Aircraft::updateAircraftData(int timerTickValue) {
    auto angle = getHorizontalAngle();

    double pathShift = m_Velocity / (1000 / timerTickValue);

    double xShift = (pathShift * std::cos(angle * PI / 180)) /*/ Convert::s_MetersInPixel*/;
    double yShift = (-1) * (pathShift * std::sin(angle * PI / 180)) /*/ Convert::s_MetersInPixel*/;

    m_X += xShift;
    m_Y += yShift;
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

double Aircraft::getHorizontalAngle() {
    int dx = (m_ActivePathStartPoint.x() - m_ActivePathEndPoint.x()) * -1;
    int dy = m_ActivePathStartPoint.y() - m_ActivePathEndPoint.y();

    double angle = std::atan2(dy, dx) * 180 / PI;

    return angle;
}
