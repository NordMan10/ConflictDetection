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
#include "aircraft.h"

class FieldView : public QGraphicsView
{
public:
    FieldView(FieldPoints &fieldPoints, std::vector<AircraftPath>& paths,
              std::vector<Aircraft*>& aircrafts);
    //FieldView(int width, int height);
    ~FieldView();

    int getWidth() const;
    int getHeight() const;

    void updateGraphics();

private:
    QGraphicsScene m_Scene;

    int m_PosX;
    int m_PosY;

    int m_Width;
    int m_Height;

    FieldViewItem* m_fvItem;

    FieldPoints& m_FieldPoints;

    std::vector<AircraftPath>& m_AircraftPaths;

    std::vector<Aircraft*>& m_Aircrafts;

private:
    void initViewElements();
    void addElementsToScene();
    void standardOptions();
};

#endif // FIELDVIEW_H
