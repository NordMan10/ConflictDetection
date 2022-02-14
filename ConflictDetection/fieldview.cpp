#include "fieldview.h"

FieldView::FieldView()
{
    standardOptions();
    initViewElements();

    addElementsToScene();
}

void FieldView::standardOptions() {
    m_Width = 1920;
    m_Height = 900;

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);

    // try to set "on".
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowTitle("FieldView");
    setFrameStyle(3);

    //setWindowState(Qt::WindowMaximized);

    //resize(QDesktopWidget().availableGeometry(this).size());
    //qDebug() << width() << ", " << height();
    setSceneRect(0, 0, m_Width, m_Height);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    //setFixedSize(this->size().width(), this->size().height());

    //setBackgroundBrush(QBrush(Qt::red));


    m_Scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(&m_Scene);
}

void FieldView::initViewElements() {
    m_fvItem = new FieldViewItem();
    m_fvItem->setPos(240, 45);
    qDebug() << width() << height();
    m_fvItem->setGeometry(1440, 810);
}

void FieldView::addElementsToScene() {
    m_Scene.addItem(m_fvItem);
}

FieldView::~FieldView() {
    //delete m_fvItem;
}
