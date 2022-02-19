#ifndef IAIRCRAFTTIMEROBSERVER_H
#define IAIRCRAFTTIMEROBSERVER_H

#include <QWidget>

class IAircraftTimerObserver : public QWidget
{
public:
    virtual ~IAircraftTimerObserver(){};

public slots:
    virtual void updateAircraftData() = 0;
};

#endif // IAIRCRAFTTIMEROBSERVER_H
