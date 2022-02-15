#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "IController.h"
#include "IModel.h"

class Controller : public IController
{
private:
    IModel &m_Model;
    //MainWindow &m_View;

public:
    Controller(IModel &model);
    ~Controller();

    std::vector<CDPoint> getZonePoints() const override;
    std::vector<CDPoint> getPathPoints() const override;
    std::vector<CDPoint> getPathIntersectionPoints() const override;

    void start() override;
    void stop() override;

    void pause() override;
    // Не названа как "continue", потому что слово зарезервировано.
    void continueWork() override;
};

#endif // CONTROLLER_H
