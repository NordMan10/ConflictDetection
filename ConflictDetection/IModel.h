#ifndef IMODEL_H
#define IMODEL_H

//#include <vector>
#include <QWidget>

#include "cdpoint.h"
#include "fieldpoints.h"
#include "IAircraftTimerObserver.h"
#include "IAircraftObserver.h"


class IModel : public QWidget
{
    Q_OBJECT
public:
    virtual ~IModel(){};

    virtual std::vector<CDPoint>& getZonePoints() = 0;
    virtual std::vector<CDPoint>& getPathPoints() = 0;
    virtual std::vector<CDPoint>& getPathIntersectionPoints() = 0;

    virtual FieldPoints& getFieldPoints() = 0;

    virtual std::vector<std::vector<CDPoint>>& getPaths() = 0;

    virtual std::vector<Aircraft*>& getAircrafts() = 0;

    virtual long long getStopwatchValue() = 0;
    virtual void updateStopwatchValue(int value) = 0;
    virtual void setStopwatchValue(int value) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    // Не названа как "continue", потому что слово зарезервировано.
    virtual void continueWork() = 0;

    // Observer pattern methods
    virtual void registerAircraftTimerObserver(IAircraftTimerObserver* observer) = 0;
    virtual void removeAircraftTimerObserver(IAircraftTimerObserver* observer) = 0;
    //virtual void notifyAircraftTimerObservers() = 0;

    virtual void addAircraftsObserver(IAircraftObserver* observer) = 0;

//protected slots:
//    virtual void notifyAircraftTimerObservers();
};

#endif // IMODEL_H
