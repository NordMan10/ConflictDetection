#include "fieldviewitem.h"

FieldViewItem::FieldViewItem(FieldPoints &fieldPoints, std::vector<std::vector<CDPoint>>& paths) :
    m_FieldPoints(fieldPoints),
    m_Paths(paths)
{
    QGraphicsItem::update();
}

QRectF FieldViewItem::boundingRect() const {
    return QRectF(0, 0, m_Width, m_Height);
}

void FieldViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/) {
    //painter->setPen(QPen(Qt::black, 3));

    //painter->drawRect(0, 0, m_Width, m_Height);

//    QPixmap aircraftPicture(":/resources/img/aircraft.png");

//    painter->save();
//    painter->translate(50, 50);
//    painter->rotate(45);
//    painter->drawPixmap(-20, -20, 40, 40, aircraftPicture);
//    painter->restore();

    drawZoneLines(painter);
    drawZonePoints(painter);

    drawPathLines(painter);
    drawPathPoints(painter);

    drawPathIntersectionPoints(painter);
}

void FieldViewItem::drawZonePoints(QPainter *painter) {
    painter->setPen(QPen(Qt::black, 4));

    for (auto i = 0; i < m_FieldPoints.zonePoints.size(); i++)
    {
        QRect rect(m_FieldPoints.zonePoints[i].x() - 5, m_FieldPoints.zonePoints[i].y() - 5, 10, 10);
        painter->drawRect(rect);
        painter->fillRect(rect, QBrush(Qt::white));

//        std::string label = "";
//        for (int j = 0; j < i + 1; j++) label += "I";
        painter->drawText(QPoint(m_FieldPoints.zonePoints[i].x() + 10, m_FieldPoints.zonePoints[i].y() + 25), QString::number(i + 1));
    }
}

void FieldViewItem::drawZoneLines(QPainter *painter) {
    painter->setPen(QPen(Qt::red, 3));

    for (size_t i = 0, j = m_FieldPoints.zonePoints.size() - 1; i < m_FieldPoints.zonePoints.size(); j = i, i++) {
        painter->drawLine(m_FieldPoints.zonePoints[j].x(), m_FieldPoints.zonePoints[j].y(), m_FieldPoints.zonePoints[i].x(), m_FieldPoints.zonePoints[i].y());
    }
}

void FieldViewItem::drawPathPoints(QPainter *painter) {
    painter->setPen(QPen(Qt::black, 4));
    painter->setBrush(Qt::black);

    for (auto i = 0; i < m_FieldPoints.pathPoints.size(); i++)
    {
        QRect rect(m_FieldPoints.pathPoints[i].x() - 5, m_FieldPoints.pathPoints[i].y() - 5, 10, 10);
        painter->drawEllipse(rect);
        painter->drawText(QPoint(m_FieldPoints.pathPoints[i].x() + 10, m_FieldPoints.pathPoints[i].y()), QString::number(i + 1));
    }
}

void FieldViewItem::drawPathLines(QPainter *painter) {
    //painter->setPen(QPen(Qt::green, 2));

    for (size_t i = 0; i < m_Paths.size(); i++) {
        painter->setPen(QPen(Qt::green, 2));
        for (size_t j = 0; j < m_Paths[i].size() - 1; j++) {
            painter->drawLine(m_Paths[i][j].x(), m_Paths[i][j].y(), m_Paths[i][j + 1].x(), m_Paths[i][j + 1].y());
        }
        painter->setPen(QPen(Qt::black, 2));
        painter->drawText(QPoint(m_Paths[i][0].x() + 10, m_Paths[i][0].y() + 25), "M" + QString::number(i + 1));
    }
}

void FieldViewItem::drawPathIntersectionPoints(QPainter *painter) {
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::yellow);

    for (auto i = 0; i < m_FieldPoints.pathIntersectionPoints.size(); i++)
    {
        QRect rect(m_FieldPoints.pathIntersectionPoints[i].x() - 5, m_FieldPoints.pathIntersectionPoints[i].y() - 5, 10, 10);
        painter->drawEllipse(rect);
        painter->drawText(QPoint(m_FieldPoints.pathIntersectionPoints[i].x() + 10, m_FieldPoints.pathIntersectionPoints[i].y()), QString::number(i + m_FieldPoints.pathPoints.size() + 1));
    }
}

void FieldViewItem::setGeometry(int aWidth, int aHeight) {
    m_Width = aWidth;
    m_Height = aHeight;
}

