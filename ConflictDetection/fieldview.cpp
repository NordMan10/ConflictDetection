#include "fieldview.h"

FieldView::FieldView()
{
    standardOptions();
    initViewElements();

    addElementsToScene();
}

void FieldView::standardOptions() {
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);

    // try to set "on".
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowTitle("FieldView");
    setFrameStyle(3);

    //setWindowState(Qt::WindowMaximized);

    resize(QDesktopWidget().availableGeometry(this).size());
    setSceneRect(0, 0, width(), height());
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    //setFixedSize(this->size().width(), this->size().height());

    //setBackgroundBrush(QBrush(Qt::red));


    m_Scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(&m_Scene);
}

void FieldView::initViewElements() {
    m_fvItem = new FieldViewItem();
    m_fvItem->setPos(50, 50);
    m_fvItem->setGeometry(100, 100);
}

void FieldView::addElementsToScene() {
    m_Scene.addItem(m_fvItem);
}

FieldView::~FieldView() {
    delete m_fvItem;
}
