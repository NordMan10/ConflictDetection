#include "mainwindow.h"

MainWindow::MainWindow()
{
    standardOptions();
    initViewElements();
}

void MainWindow::standardOptions() {
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);

    // try to set "on".
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowTitle("MainWindow");
    setFrameStyle(0);

    setWindowState(Qt::WindowMaximized);

    resize(QDesktopWidget().availableGeometry(this).size());
    setSceneRect(0, 0, this->size().width(), this->size().height());
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    //setFixedSize(this->size().width(), this->size().height());


    m_Scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(&m_Scene);
}

void MainWindow::initViewElements() {

}

