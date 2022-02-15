#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "IModel.h"
#include "cdpoint.h"



class Model : public IModel
{
public:
    Model();

public:
    std::vector<CDPoint> getZonePoints() const override;
    std::vector<CDPoint> getPathPoints() const override;
    std::vector<CDPoint> getPathIntersectionPoints() const override;

private:
    void initPoints();

    void initZonePoints();
    void initPathPoints();
    void initPathIntersectionPoints();

private:
    std::vector<CDPoint> m_ZonePoints;
    std::vector<CDPoint> m_PathPoints;
    std::vector<CDPoint> m_PathIntersectionPoints;
};

#endif // MODEL_H
