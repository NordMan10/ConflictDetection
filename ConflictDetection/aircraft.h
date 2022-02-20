#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <QPixmap>

#include "IAircraftTimerObserver.h"
#include "cdpoint.h"
#include "aircraftpath.h"
#include "IAircraftObserver.h"

#define PI 3.14159265

class Aircraft : public IAircraftTimerObserver
{
public:
    Aircraft(std::string id, AircraftPath path, IAircraftObserver* observer, int aircraftListIndex, int timerTickValue);

    std::string getId() const;

    double x() const;
    double y() const;
    double z() const;

    QPixmap image;

    AircraftPath& getPath();

    double getHorizontalAngle();

    void updateData(int timerTickValue) override;

    int getDangerRadius();

    int getImageWidth();
    int getImageHeight();

    int getISZ_Width();
    int getISZ_Length();

private:
    void handleArrivalToEndPoint();

    void handleArrivalToMiddlePoint();
    void changeMotionDirection();

    void calculateShifts(int timerTickValue);

    bool isAircraftAtPoint(CDPoint point);

    CDPoint getNextPathPoint(CDPoint point);

    int get_IPSZ_Length();

private:
    std::vector<IAircraftObserver*> m_AircraftObservers;
    int m_AircraftListIndex;

    // Условный идентификатор ВС, который будет выводится в формуляр
    std::string m_Id;

    // Координаты в программной системе координат, в пикселях
    double m_X;
    double m_Y;
    double m_Z = 3000;

    // Момент входа в зону (момент создания ВС) в значении счетчика секундомера.
    // Для вывода нужно конвертировать с помощью QTime::fromMSecsSinceStartOfDay
    int m_EntryMoment;

    // Скорость в м/с
    int m_Velocity = 275;

    // Размеры ИЗБ по высоте, ширине и длине, в метрах (пока не ясно, это +- или в сумме).
    int m_ISZ_Height = 300;
    int m_ISZ_Width = 1500;
    int m_ISZ_Length = 1500;

    // Интервал времени прогнозирования, с.
    int m_PredictingInterval = 30;

    // Допуски на вертикальное и горизонтальное эшелонировавние соответственно, в метрах.
    int m_SecurityVertical = 300;
    int m_SecurityHorizontal = 2000;

    // Радиус в метрах
    int m_DangerRadius = 5000;

    AircraftPath m_Path;

    CDPoint m_ActivePathStartPoint;
    CDPoint m_ActivePathEndPoint;

    double m_XShift;
    double m_YShift;

    int m_TimerTickValue;

    int m_ImageWidth = 10;
    int m_ImageHeight = 10;
};

#endif // AIRCRAFT_H
