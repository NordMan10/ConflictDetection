#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "IModel.h"
#include "cdpoint.h"
#include "fieldpoints.h"


class Model : public IModel
{
public:
    Model();

public:
    std::vector<CDPoint>& getZonePoints() override;
    std::vector<CDPoint>& getPathPoints() override;
    std::vector<CDPoint>& getPathIntersectionPoints() override;

    FieldPoints& getFieldPoints() override;

    std::vector<std::vector<CDPoint>>& getPaths() override;

    long long getStopwatchValue() override;
    void updateStopwatchValue(int value) override;
    void setStopwatchValue(int value) override;

private:
    void initPoints();

    void initZonePoints();
    void initPathPoints();
    void initPathIntersectionPoints();

    void initPaths();

private:
    std::vector<CDPoint> m_ZonePoints;
    std::vector<CDPoint> m_PathPoints;
    std::vector<CDPoint> m_PathIntersectionPoints;

    FieldPoints m_FieldPoints;

    std::vector<std::vector<CDPoint>> m_Paths;

    long long m_StopwatchValue = 0;

};

#endif // MODEL_H
