#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QTime>
#include <QTimer>
#include <random>

#include "IModel.h"
//#include "cdpoint.h"
//#include "fieldpoints.h"
//#include "IAircraftObserver.h"
//#include "aircraft.h"
//#include "aircraftpath.h"

class Model : public IModel, public IAircraftObserver
{

public:
    Model();

public:
    std::vector<CDPoint>& getZonePoints() override;
    std::vector<CDPoint>& getPathPoints() override;
    std::vector<CDPoint>& getPathIntersectionPoints() override;

    FieldPoints& getFieldPoints() override;

    std::vector<AircraftPath>& getPaths() override;

    std::vector<Aircraft*>& getAircrafts() override;

    long long getStopwatchValue() override;
    void updateStopwatchValue(int value) override;
    void setStopwatchValue(int value) override;

    void registerAircraftTimerObserver(IAircraftTimerObserver* observer) override;
    void removeAircraftTimerObserver(IAircraftTimerObserver* observer) override;
    //void notifyAircraftTimerObservers() override;

    void registerAircraftsObserver(IAircraftObserver* observer) override;

    void createAircraft();

    void updateAircraftData(std::string aircraftId) override;

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

    void checkPotentiallyDangerousAircrafts();

    QString getAircraftId(int pathId);

    Aircraft* getAircraftById(std::string aircraftId);

private:
    std::vector<CDPoint> m_ZonePoints;
    std::vector<CDPoint> m_PathPoints;
    std::vector<CDPoint> m_PathIntersectionPoints;

    FieldPoints m_FieldPoints;

    //std::vector<std::vector<CDPoint>> m_Paths;

    long long m_StopwatchValue = 0;

    std::vector<IAircraftTimerObserver*> m_AircraftTimerObservers;

    IAircraftObserver* m_AircraftObserver;

    std::vector<Aircraft*> m_Aircrafts;
    std::vector<AircraftPath> m_AircraftPaths;

    QTimer* m_TimerAircraftsMotion;
    int m_TimerAircraftsMotionTickValue = 100;

    QTimer* m_TimerAircraftsCreation;
    int m_TimerAircraftsCreationTickValue = 15000;
    int m_TimerACTickValueMin = 25000;
    int m_TimerACTickValueMax = 30000;

    std::vector<std::string> m_AircraftIdsToRemove;
    bool m_CanRemoveAircraft = false;

    std::random_device m_rd;
    std::mt19937 m_eng;
};

#endif // MODEL_H
