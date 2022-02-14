#include "fieldviewitem.h"

FieldViewItem::FieldViewItem()
{

}

QRectF FieldViewItem::boundingRect() const {
    return QRectF(0, 0, m_Width, m_Height);
}

void FieldViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/) {
    painter->setPen(QPen(Qt::black, 3));

    QRect rect(0, 0, m_Width, m_Height);
    painter->drawRoundedRect(rect, 5, 5);
}

void FieldViewItem::setGeometry(int aWidth, int aHeight) {
    m_Width = aWidth;
    m_Height = aHeight;
}

