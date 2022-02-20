#ifndef IAIRCRAFTOBSERVER_H
#define IAIRCRAFTOBSERVER_H

//#ifndef AIRCRAFT_H
//#include "aircraft.h"
//#endif

class IAircraftObserver
{
public:
    virtual ~IAircraftObserver(){};

    virtual void updateAircraftData(int aircraftListIndex) = 0;
};

#endif // IAIRCRAFTOBSERVER_H
