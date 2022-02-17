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
    m_Model.start();
}

void Controller::stop() {
    m_Model.stop();
}

void Controller::pause() {
    m_Model.pause();
}

void Controller::continueWork() {
    m_Model.continueWork();
}

long long Controller::getStopwatchValue() {
    return m_Model.getStopwatchValue();
}

void Controller::updateStopwatchValue(int value) {
    m_Model.updateStopwatchValue(value);
}

void Controller::setStopwatchValue(int value) {
    m_Model.setStopwatchValue(value);
}
