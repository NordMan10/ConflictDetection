#include "fieldviewitem.h"

FieldViewItem::FieldViewItem()
{
    QGraphicsItem::update();
}

QRectF FieldViewItem::boundingRect() const {
    return QRectF(0, 0, m_Width, m_Height);
}

void FieldViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/) {
    painter->setPen(QPen(Qt::black, 3));

//    QRect rect(0, 0, m_Width, m_Height);
//    painter->drawRoundedRect(rect, 5, 5);

    QPixmap aircraftPicture(":/resources/img/aircraft.png");

    painter->save();
    painter->translate(50, 50);
    painter->rotate(45);
    painter->drawPixmap(-20, -20, 40, 40, aircraftPicture);
    painter->restore();

    painter->drawPolygon(QPolygon({QPoint(500, 300), QPoint(505, 290), QPoint(510, 300)}));

    QPoint points[3] {QPoint(200, 700), QPoint(300, 750), QPoint(350, 100)};
//    for (int i = 0; i < (sizeof(points) / sizeof(QPoint)) - 1; i++)
//        painter->drawLine(points[i].x(), points[i].y(), points[i + 1].x(), points[i + 1].y());

    QVector<QPoint> pointsV = {QPoint(200, 700), QPoint(300, 750), QPoint(300, 750), QPoint(350, 100)};
    painter->drawLines(pointsV);
}

void FieldViewItem::setGeometry(int aWidth, int aHeight) {
    m_Width = aWidth;
    m_Height = aHeight;
}

