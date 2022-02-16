#include "fieldview.h"

FieldView::FieldView(FieldPoints &fieldPoints, std::vector<std::vector<CDPoint>>& paths) :
    m_FieldPoints(fieldPoints),
    m_Paths(paths)
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
    setSceneRect(0, 0, 1440, 810);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    //setFixedSize(this->size().width(), this->size().height());

    //setBackgroundBrush(QBrush(Qt::red));


    m_Scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(&m_Scene);
}

void FieldView::initViewElements() {
    m_fvItem = new FieldViewItem(m_FieldPoints, m_Paths);
    m_fvItem->setPos(0, 0);
    //qDebug() << width() << height();
    m_fvItem->setGeometry(1440, 810);
}

void FieldView::addElementsToScene() {
    m_Scene.addItem(m_fvItem);
    //m_Scene.
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
