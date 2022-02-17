#ifndef IAIRCRAFTTIMEROBSERVER_H
#define IAIRCRAFTTIMEROBSERVER_H

#include <QWidget>

class IAircraftTimerObserver : public QWidget
{
public:
    virtual ~IAircraftTimerObserver(){};

private slots:
    virtual void updateAircraftData() = 0;
};

#endif // IAIRCRAFTTIMEROBSERVER_H
