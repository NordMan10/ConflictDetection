#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDesktopWidget>

class MainWindow : public QGraphicsView
{
public:
    MainWindow();

private:
    QGraphicsScene m_Scene;

private:
    void initViewElements();
    void standardOptions();
};

#endif // MAINWINDOW_H
