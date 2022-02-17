#ifndef IAIRCRAFTTIMERTICKOBSERVER_H
#define IAIRCRAFTTIMERTICKOBSERVER_H

class IAircraftTimerObserver
{
public:
    virtual ~IAircraftTimerObserver(){};

    virtual void updateAircraftData() = 0;
};

#endif // IAIRCRAFTTIMERTICKOBSERVER_H
