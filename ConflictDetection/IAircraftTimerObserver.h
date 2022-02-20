#ifndef IAIRCRAFTTIMEROBSERVER_H
#define IAIRCRAFTTIMEROBSERVER_H


class IAircraftTimerObserver
{
public:
    virtual ~IAircraftTimerObserver(){};

    virtual void updateData(int timerTickValue) = 0;
};

#endif // IAIRCRAFTTIMEROBSERVER_H
