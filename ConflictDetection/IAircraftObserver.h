#ifndef IAIRCRAFTOBSERVER_H
#define IAIRCRAFTOBSERVER_H

//#include <QWidget>

#include "aircraft.h"

class IAircraftObserver
{
public:
    virtual ~IAircraftObserver(){};

    virtual void updateAircraftData(/*std::vector<Aircraft*>& aircrafts*/) = 0;
};

#endif // IAIRCRAFTOBSERVER_H
