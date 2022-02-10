#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class FieldView : public QGraphicsView
{
public:
    FieldView();

private:
    QGraphicsScene m_Scene;

private:
    void initViewElements();
    void addElementsToScene();
    void standardOptions();
};

#endif // FIELDVIEW_H
