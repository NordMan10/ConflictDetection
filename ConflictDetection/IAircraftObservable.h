#ifndef IAIRCRAFTOBSERVABLE_H
#define IAIRCRAFTOBSERVABLE_H

#include "IAircraftObserver.h"

class IAircraftObservable
{
public:
    virtual ~IAircraftObservable(){};

    virtual void registerObserver(IAircraftObserver* observer) = 0;
    virtual void removeObserver(IAircraftObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

#endif // IAIRCRAFTOBSERVABLE_H
