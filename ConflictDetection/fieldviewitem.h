#ifndef FIELDVIEWITEM_H
#define FIELDVIEWITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QPolygon>

#include "cdpoint.h"
#include "fieldpoints.h"
#include "aircraft.h"

class FieldViewItem : public QGraphicsItem
{
public:
    FieldViewItem(FieldPoints &fieldPoints, std::vector<AircraftPath>& paths,
                  std::vector<Aircraft*>& aircrafts);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setGeometry(int aWidth, int aHeight);

    void updateGraphics();

    //void drawZonePoints(std::vector<QPoint> points);

private:
    void drawZonePoints(QPainter *painter);
    void drawZoneLines(QPainter *painter);

    void drawPathPoints(QPainter *painter);
    void drawPathLines(QPainter *painter);

    void drawPathIntersectionPoints(QPainter *painter);

    void drawFieldGrid(QPainter *painter);

    void drawAircrafts(QPainter* painter);

private:
    int m_Width = 100;
    int m_Height = 100;

    FieldPoints &m_FieldPoints;

    std::vector<AircraftPath>& m_AircraftPaths;

    std::vector<Aircraft*>& m_Aircrafts;
};

#endif // FIELDVIEWITEM_H
