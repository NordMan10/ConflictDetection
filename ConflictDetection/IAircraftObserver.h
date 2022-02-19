#ifndef IAIRCRAFTOBSERVER_H
#define IAIRCRAFTOBSERVER_H

#include <QWidget>

class IAircraftObserver
{
public:
    virtual ~IAircraftObserver(){};

    virtual void updateAircraftData() = 0;
};

#endif // IAIRCRAFTOBSERVER_H
