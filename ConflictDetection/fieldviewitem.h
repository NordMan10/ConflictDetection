#ifndef FIELDVIEWITEM_H
#define FIELDVIEWITEM_H

#include <QGraphicsItem>
#include <QPainter>

class FieldViewItem : public QGraphicsItem
{
public:
    FieldViewItem();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setGeometry(int aWidth, int aHeight);

private:
    int m_Width = 100;
    int m_Height = 100;
};

#endif // FIELDVIEWITEM_H
