#include "aircraft.h"

Aircraft::Aircraft(std::string id, int x, int y, int z) :
    m_Id(id), m_X(x), m_Y(y), m_Z(z)
{
    image = QPixmap(":/resources/img/aircraft.png");
    //registerObserver(aircraftObserver);
    //connect(this, SIGNAL(signal_updateAircraftData()), aircraftObserver, SLOT(updateAircraftData));
}

void Aircraft::updateAircraftData() {
    m_X++;
}

//void Aircraft::registerObserver(IAircraftObserver* observer) {
//    m_AircraftObservers.push_back(observer);
//}

//void Aircraft::removeObserver(IAircraftObserver* observer) {
//    m_AircraftObservers.erase(std::remove(m_AircraftObservers.begin(), m_AircraftObservers.end(), observer), m_AircraftObservers.end());
//}

//void Aircraft::notifyObservers() {
//    for (int i = 0; i < m_AircraftObservers.size(); i++) {
//        m_AircraftObservers[i]->updateAircraftData();
//    }
//}

std::string Aircraft::getId() const {
    return m_Id;
}

int Aircraft::x() const {
    return m_X;
}

int Aircraft::y() const {
    return m_Y;
}

int Aircraft::z() const {
    return m_Z;
}

