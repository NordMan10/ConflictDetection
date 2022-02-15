#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include <QGraphicsItem>
#include <QDebug>

#include "fieldviewitem.h"
#include "convert.h"
#include "cdpoint.h"
#include "fieldpoints.h"

class FieldView : public QGraphicsView
{
public:
    FieldView(FieldPoints &fieldPoints);
    //FieldView(int width, int height);
    ~FieldView();

    int getWidth() const;
    int getHeight() const;

    void drawStaticGraphics(std::vector<CDPoint> zonePoints);

private:
    QGraphicsScene m_Scene;

    int m_PosX;
    int m_PosY;

    int m_Width;
    int m_Height;

    FieldViewItem *m_fvItem;

    FieldPoints &m_FieldPoints;

private:
    void initViewElements();
    void addElementsToScene();
    void standardOptions();
};

#endif // FIELDVIEW_H
