#include "fieldviewitem.h"

FieldViewItem::FieldViewItem(FieldPoints &fieldPoints, std::vector<AircraftPath>& paths,
                             std::vector<Aircraft*>& aircrafts) :
    m_FieldPoints(fieldPoints),
    m_AircraftPaths(paths),
    m_Aircrafts(aircrafts)
{
    QGraphicsItem::update();
}

QRectF FieldViewItem::boundingRect() const {
    return QRectF(0, 0, m_Width, m_Height);
}

void FieldViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/) {
    drawFieldGrid(painter);

    drawZoneLines(painter);
    drawZonePoints(painter);

    drawPathLines(painter);
    drawPathPoints(painter);

    drawPathIntersectionPoints(painter);

    drawAircrafts(painter);
}

void FieldViewItem::drawZonePoints(QPainter *painter) {
    painter->setPen(QPen(Qt::black, 2));

    for (auto i = 0; i < m_FieldPoints.zonePoints.size(); i++)
    {
        QRect rect(m_FieldPoints.zonePoints[i].x() - 2,
                   m_FieldPoints.zonePoints[i].y() - 2, 4, 4);
        painter->drawRect(rect);
        painter->fillRect(rect, QBrush(Qt::white));

        painter->setFont(QFont("Roboto", 5));
        painter->drawText(QPoint(m_FieldPoints.zonePoints[i].x() + 10,
                                 m_FieldPoints.zonePoints[i].y() + 20),
                          QString::number(i + 1));
    }
}

void FieldViewItem::drawZoneLines(QPainter *painter) {
    painter->setPen(QPen(Qt::red, 1));

    for (size_t i = 0, j = m_FieldPoints.zonePoints.size() - 1; i < m_FieldPoints.zonePoints.size(); j = i, i++) {
        painter->drawLine(m_FieldPoints.zonePoints[j].x(),
                          m_FieldPoints.zonePoints[j].y(),
                          m_FieldPoints.zonePoints[i].x(),
                          m_FieldPoints.zonePoints[i].y());
    }
}

void FieldViewItem::drawPathPoints(QPainter *painter) {
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::black);

    for (auto i = 0; i < m_FieldPoints.pathPoints.size(); i++)
    {
        QRect rect(m_FieldPoints.pathPoints[i].x() - 2, m_FieldPoints.pathPoints[i].y() - 2, 4, 4);
        painter->drawEllipse(rect);
        painter->drawText(QPoint(m_FieldPoints.pathPoints[i].x() + 10,
                                 m_FieldPoints.pathPoints[i].y()),
                          QString::number(i + 1));
    }
}

void FieldViewItem::drawPathLines(QPainter *painter) {
    //painter->setPen(QPen(Qt::green, 2));

    for (size_t i = 0; i < m_AircraftPaths.size(); i++) {
        painter->setPen(QPen(Qt::green, 1));
        for (size_t j = 0; j < m_AircraftPaths[i].getPath().size() - 1; j++) {
            painter->drawLine(m_AircraftPaths[i].getPath()[j].x(),
                              m_AircraftPaths[i].getPath()[j].y(),
                              m_AircraftPaths[i].getPath()[j + 1].x(),
                              m_AircraftPaths[i].getPath()[j + 1].y());
        }
        painter->setPen(QPen(Qt::black, 1));
        painter->setFont(QFont("Roboto", 5));
        painter->drawText(QPoint(m_AircraftPaths[i].getPath()[0].x() + 10,
                          m_AircraftPaths[i].getPath()[0].y() + 25),
                "M" + QString::number(i + 1));
    }
}

void FieldViewItem::drawPathIntersectionPoints(QPainter *painter) {
    painter->setPen(QPen(Qt::black, 0.5));
    painter->setBrush(Qt::yellow);

    for (auto i = 0; i < m_FieldPoints.pathIntersectionPoints.size(); i++)
    {
        QRect rect(m_FieldPoints.pathIntersectionPoints[i].x() - 2,
                   m_FieldPoints.pathIntersectionPoints[i].y() - 2, 4, 4);
        painter->drawEllipse(rect);
        painter->setFont(QFont("Roboto", 5));
        painter->drawText(QPoint(m_FieldPoints.pathIntersectionPoints[i].x() + 10,
                                 m_FieldPoints.pathIntersectionPoints[i].y()),
                          QString::number(i + m_FieldPoints.pathPoints.size() + 1));
    }
}

void FieldViewItem::drawFieldGrid(QPainter *painter) {
     painter->setPen(QPen(QColor(215, 215, 215), 0.5));

     for (int i = 0; i <= Convert::s_RightFieldBorder; i += 5000) {
         painter->drawLine(QPoint(0, Convert::ConvertMetersToPixels(i)), QPoint(Convert::ConvertMetersToPixels(Convert::s_RightFieldBorder), Convert::ConvertMetersToPixels(i)));
         painter->drawLine(QPoint(Convert::ConvertMetersToPixels(i), 0), QPoint(Convert::ConvertMetersToPixels(i), Convert::ConvertMetersToPixels(Convert::s_RightFieldBorder)));
     }
}

void FieldViewItem::drawAircrafts(QPainter* painter) {
    for (int i = 0; i < m_Aircrafts.size(); i++) {
        // Image drawing
        painter->save();
        painter->translate(m_Aircrafts[i]->x(), m_Aircrafts[i]->y());
        // Домножаем на -1, поскольку функция rotate() поворачивает программную с.к. по часовой
        // стрелке, тогда как пользовательская функция getHorizontalAngle() возвращает значение
        // угла в соответствии с правилами тригонометрии (положительный угол приводит к вращению
        // против часовой стрелки.
        painter->rotate((-1) * (m_Aircrafts[i]->getHorizontalAngle()));
        painter->drawPixmap((-1) * m_Aircrafts[i]->getImageWidth() / 2,
                            (-1) * m_Aircrafts[i]->getImageHeight() / 2,
                            m_Aircrafts[i]->getImageWidth(), m_Aircrafts[i]->getImageHeight(),
                            m_Aircrafts[i]->getImage());
        painter->restore();


        QPen pen(Qt::black, 0.3, Qt::SolidLine);
        // Circle drawing
        pen.setStyle(Qt::DotLine);
        painter->setPen(pen);
        painter->setBrush(Qt::transparent);

        int radiusInPixels = Convert::ConvertMetersToPixels(m_Aircrafts[i]->getDangerRadius());

        painter->save();
        painter->translate(m_Aircrafts[i]->x(), m_Aircrafts[i]->y());
        painter->drawEllipse(-radiusInPixels, -radiusInPixels, radiusInPixels * 2, radiusInPixels * 2);

        // ISZ and IPSZ drawing
        pen.setStyle(Qt::SolidLine);

        if (m_Aircrafts[i]->isInConflict()) {
            pen.setColor(Qt::red);
            painter->setPen(pen);
        } else if (m_Aircrafts[i]->isZoneIntersects()) {
            pen.setColor(QColor("orange"));
            painter->setPen(pen);
        } else {
            pen.setColor(Qt::black);
            painter->setPen(pen);
        }

        painter->drawPolygon(m_Aircrafts[i]->get_ISZ_Rectangle());

        pen.setWidthF(0.5);
        painter->setPen(pen);
        painter->drawPolygon(m_Aircrafts[i]->get_IPSZ_Rectangle());

        //painter->drawPolygon(m_Aircrafts[i]->getShifted_IPSZ_Rectangle());

        // Data card drawing
        pen.setColor(Qt::black);
        pen.setWidthF(0.2);
        painter->setPen(pen);
        painter->setBrush(QColor(255, 255, 255, 200));


        painter->drawRect(m_Aircrafts[i]->getDataCardRect());

        painter->setFont(QFont("Roboto", 1));
        painter->drawText(m_Aircrafts[i]->getDataCardRect(), 0, m_Aircrafts[i]->getTextForDataCard());
        //painter->drawText(7, -23, m_Aircrafts[i]->getTextForDataCard());

        painter->restore();
    }
}

void FieldViewItem::setGeometry(int aWidth, int aHeight) {
    m_Width = aWidth;
    m_Height = aHeight;
}

void FieldViewItem::updateGraphics() {
    QGraphicsItem::update();
}
