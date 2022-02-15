#include "fieldview.h"

FieldView::FieldView()
{
    m_PosX = 240;
    m_PosY = 45;

    m_Width = Convert::s_FieldWidth;
    m_Height = Convert::s_FieldHeight;

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
    m_fvItem->setPos(m_PosX, m_PosY);
    qDebug() << width() << height();
    m_fvItem->setGeometry(m_Width, m_Height);
}

void FieldView::addElementsToScene() {
    m_Scene.addItem(m_fvItem);
}

int FieldView::getWidth() const {
    return m_Width;
}

int FieldView::getHeight() const {
    return m_Height;
}

void FieldView::drawStaticGraphics(std::vector<CDPoint> zonePoints) {

}

FieldView::~FieldView() {
    delete m_fvItem;
}
