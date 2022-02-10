#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDesktopWidget>

#include "fieldviewitem.h"

class FieldView : public QGraphicsView
{
public:
    FieldView();
    //FieldView(int width, int height);
    ~FieldView();

private:
    QGraphicsScene m_Scene;

    int m_Width;
    int m_Height;

    FieldViewItem *m_fvItem;

private:
    void initViewElements();
    void addElementsToScene();
    void standardOptions();
};

#endif // FIELDVIEW_H
