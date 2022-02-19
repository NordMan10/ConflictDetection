#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QTimer>

#include "IModel.h"
#include "cdpoint.h"
#include "fieldpoints.h"
#include "IAircraftObserver.h"
#include "aircraft.h"

class Model : public IModel//, public QWidget
{

public:
    Model();

public:
    std::vector<CDPoint>& getZonePoints() override;
    std::vector<CDPoint>& getPathPoints() override;
    std::vector<CDPoint>& getPathIntersectionPoints() override;

    FieldPoints& getFieldPoints() override;

    std::vector<std::vector<CDPoint>>& getPaths() override;

    std::vector<Aircraft*>& getAircrafts() override;

    long long getStopwatchValue() override;
    void updateStopwatchValue(int value) override;
    void setStopwatchValue(int value) override;

    void registerAircraftTimerObserver(IAircraftTimerObserver* observer) override;
    void removeAircraftTimerObserver(IAircraftTimerObserver* observer) override;
    //void notifyAircraftTimerObservers() override;

    void addAircraftsObserver(IAircraftObserver* observer) override;

    void createAircraft();

protected slots:
    //void timerAircraftsMotionTimeout();
    //void notifyAircraftTimerObservers() override;

private:
    void initPoints();

    void initZonePoints();
    void initPathPoints();
    void initPathIntersectionPoints();

    void initPaths();

    void start() override;
    void stop() override;
    void pause() override;
    // Не названа как "continue", потому что слово зарезервировано.
    void continueWork() override;

    void notifyAircraftTimerObservers();

private:
    std::vector<CDPoint> m_ZonePoints;
    std::vector<CDPoint> m_PathPoints;
    std::vector<CDPoint> m_PathIntersectionPoints;

    FieldPoints m_FieldPoints;

    std::vector<std::vector<CDPoint>> m_Paths;

    long long m_StopwatchValue = 0;

    std::vector<IAircraftTimerObserver*> m_AircraftTimerObservers;

    IAircraftObserver* m_AircraftObserver;

    std::vector<Aircraft*> m_Aircrafts;

    QTimer* m_TimerAircraftsMotion;
    int m_TimerAircraftsMotionTickValue = 50;
};

#endif // MODEL_H
