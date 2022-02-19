#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
//#include <QWidget>
#include <QPixmap>

#include "IAircraftTimerObserver.h"
#include "cdpoint.h"

class Aircraft : public IAircraftTimerObserver//, public IAircraftObservable
{
public:
    Aircraft(std::string id, int x, int y, int z);

//    void registerObserver(IAircraftObserver* observer) override;
//    void removeObserver(IAircraftObserver* observer) override;
//    void notifyObservers() override;

    std::string getId() const;

    int x() const;
    int y() const;
    int z() const;

    QPixmap image;

//signals:
//    void signal_updateAircraftData();

public slots:
    void updateAircraftData() override;

private:
//    std::vector<IAircraftObserver*> m_AircraftObservers;

    // Условный идентификатор ВС, который будет выводится в формуляр
    std::string m_Id;

    // Координаты в программной системе координат, в пикселях
    int m_X;
    int m_Y;
    int m_Z = 3000;

    // Момент входа в зону (момент создания ВС) в значении счетчика секундомера.
    // Для вывода нужно конвертировать с помощью QTime::fromMSecsSinceStartOfDay
    int m_EntryMoment;

    // Скорость в м/с
    int m_Velocity = 275;

    // Размеры ИЗБ по высоте, ширине и длине, в метрах (пока не ясно, это +- или в сумме).
    int m_ISZ_Height = 300;
    int m_ISZ_Width = 1500;
    int m_ISZ_Length = 1500;

    // Допуски на вертикальное и горизонтальное эшелонировавние соответственно, в метрах.
    int m_SecurityVertical = 300;
    int m_SecurityHorizontal = 2000;

    // Радиус в метрах
    int m_DangerRadius = 5000;

    std::vector<CDPoint> path;
};

#endif // AIRCRAFT_H
