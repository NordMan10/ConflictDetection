#include "controller.h"

Controller::Controller(IModel &model) : m_Model(model)
{

}

Controller::~Controller() {
    //delete m_Model;
}

std::vector<CDPoint> Controller::getZonePoints() const {
    return m_Model.getZonePoints();
}

std::vector<CDPoint> Controller::getPathPoints() const {
    return m_Model.getPathPoints();
}

std::vector<CDPoint> Controller::getPathIntersectionPoints() const {
    return m_Model.getPathIntersectionPoints();
}

void Controller::start() {

}

void Controller::stop() {

}

void Controller::pause() {

}

void Controller::continueWork() {

}
