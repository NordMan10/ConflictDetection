#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <QPixmap>
#include <QVector>
#include <QDebug>
#include <QPolygon>
#include <QLabel>

#include "IAircraftTimerObserver.h"
#include "cdpoint.h"
#include "aircraftpath.h"
#include "IAircraftObserver.h"

#define PI 3.14159265

class Aircraft : public IAircraftTimerObserver
{
public:
    Aircraft(std::string id, AircraftPath path, IAircraftObserver* observer, long long entryMoment,
             int aircraftListIndex, int timerTickValue);

    std::string getId() const;

    QPixmap& getImage();

    double x() const;
    double y() const;
    double z() const;

    int x_inMeters() const;
    int y_inMeters() const;
    int z_inMeters() const;

    AircraftPath& getPath();

    double getHorizontalAngle() const;

    void updateData(int timerTickValue) override;

    int getDangerRadius() const;

    int getImageWidth() const;
    int getImageHeight() const;

    int getISZ_Width() const;
    int getISZ_Length() const;

    int get_IPSZ_Length() const;

    double getVelocityX() const;
    double getVelocityY() const;
    double getVelocityZ() const;

    const QString& getTextForDataCard();
    const QRectF& getDataCardRect();

    bool isAircraftPotentiallyDangerous(const Aircraft& aircraft);

    std::vector<std::reference_wrapper<Aircraft>>& getPotentiallyDangerousAircrafts();
    void addPotentiallyDangerousAircraft(Aircraft& aircraft);
    void removePotentiallyDangerousAircraft(const Aircraft& aircraft);

    friend bool operator==(const Aircraft& a1, const Aircraft& a2);
    friend bool operator!=(const Aircraft& a1, const Aircraft& a2);

    bool contains(std::vector<std::reference_wrapper<Aircraft>> vec, const Aircraft& elem);

    QPolygon& get_ISZ_Rectangle();
//    QRect& get_IPSZ_Rectangle();

    QPolygon& get_IPSZ_Rectangle();
    QPolygon& getShifted_IPSZ_Rectangle();

    bool isInConflict() const;
    void setInConflict(bool value);


    bool isZoneIntersects() const;
    void setIsZoneIntersects(bool value);

    void set_R_min(double value);

private:
    void initGraphicsItems();

    void calculateHorAngle();

    void handleArrivalToEndPoint();

    void handleArrivalToMiddlePoint();
    void changeMotionDirection();

    void calculateShifts(int timerTickValue);

    bool isAircraftAtPoint(CDPoint point);

    CDPoint getNextPathPoint(CDPoint point);

    void conflictDetection();

    bool isSeparationStandardsViolated(double delta_X, double delta_Y, double delta_Z);

    double getDistanceDerivative(double delta_X, double delta_Y, double delta_Z,
                                 double delta_Vx, double delta_Vy, double delta_Vz);

    bool isLinesIntersect(QLine line1, QLine line2);
    bool isRectanglesIntersect(QRect rect1, QRect rect2);

    void create_ISZ_Rectangle();
    void create_IPSZ_Rectangle();

    double getHorDistBtwAircrafts(double delta_X, double delta_Y);

private:
    std::vector<IAircraftObserver*> m_AircraftObservers;
    int m_AircraftListIndex;

    // Условный идентификатор ВС, который будет выводится в формуляр
    std::string m_Id;

    QPixmap m_Image;

    double m_AngleHor;

    // Координаты в программной системе координат, в метрах
    double m_X;
    double m_Y;
    double m_Z = Convert::ConvertMetersToPixels(3000);

    double m_X_inMeters;
    double m_Y_inMeters;
    double m_Z_inMeters = 3000;

    // Момент входа в зону (момент создания ВС) в значении счетчика секундомера (мсек).
    // Для вывода нужно конвертировать с помощью QTime::fromMSecsSinceStartOfDay
    long long m_EntryMoment;

    // Скорость в м/с
    double m_Velocity = 275;

    // Размеры ИЗБ по высоте, ширине и длине, в метрах (это +-).
    int m_ISZ_Height = 300;
    int m_ISZ_Width = 1500;
    int m_ISZ_Length = 1500;

    QPolygon m_ISZ_Rectangle;

//    QRect m_IPSZ_Rectangle; // Если пересекаются, то оранжевым, если фактический конфликт, то красным

    QPolygon m_IPSZ_Rectangle;
    QPolygon m_Shifted_IPSZ_Rectangle;

    // Интервал времени прогнозирования, с. Для БПЛА: 30 с., для самолетов: 90 с.
    int m_PredictingInterval = 40;

    // Допуски на вертикальное и горизонтальное эшелонировавние соответственно, в метрах.
    int m_SeparationStandardV = 300;
    int m_SeparationStandardHor = 2000;

    // Радиус в метрах
    int m_DangerRadius = 10000;

    AircraftPath m_Path;

    CDPoint m_ActivePathStartPoint;
    CDPoint m_ActivePathEndPoint;

    double m_XShift;
    double m_YShift;

    double m_XShift_inMeters;
    double m_YShift_inMeters;

    double m_VelocityX;
    double m_VelocityY;
    double m_VelocityZ = 0;

    int m_TimerTickValue;

    int m_ImageWidth = 5;
    int m_ImageHeight = 5;

    std::vector<std::reference_wrapper<Aircraft>> m_PotentiallyDangerousAircrafts {};

    double m_Tau_min = -1;
    double m_R_min = -1;

    bool m_IsZoneIntersects = false;
    bool m_IsInConflict = false;

    QString m_TextForDataCard;
    QRectF m_DataCardRect;
};

#endif // AIRCRAFT_H
