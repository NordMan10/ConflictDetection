#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(IModel &model, IController &controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Model(model),
    m_Controller(controller)
{
    ui->setupUi(this);

    standardOptions();

    initViewElements();

    drawStaticGraphics(m_Controller.getZonePoints());
}

void MainWindow::standardOptions() {
    setWindowState(Qt::WindowMaximized);

    resize(QDesktopWidget().availableGeometry(this).size());
    //qDebug() << width() << height();
}

void MainWindow::initViewElements() {
    //qDebug() << width() << ", " << height();
    //ui->mainGrid->setGeometry(QRect(0, 0, width(), height()));
    //ui->MainWindow::centralwidget->setWid

    ui->mainGrid->setRowStretch(0, 1);
    ui->mainGrid->setRowStretch(1, 4);


    //qDebug() << ui->mainGrid->geometry().width() << ui->mainGrid->geometry().height();

    ui->topGrid->setMargin(30);
    ui->topGrid->setColumnStretch(0, 1);
    ui->topGrid->setColumnStretch(1, 0);
    ui->topGrid->setColumnStretch(2, 1);
    ui->topGrid->setColumnStretch(3, 10);
    ui->topGrid->setColumnStretch(4, 2);

    m_StartStopBtn = new QPushButton("Start");
    ui->topGrid->addWidget(m_StartStopBtn, 0, 0);

    m_SpacerHorTop1 = new QSpacerItem(100, 5, QSizePolicy::Maximum, QSizePolicy::Maximum);
    ui->topGrid->addItem(m_SpacerHorTop1, 0, 1);

    m_PauseContinueBtn = new QPushButton("Pause");
    ui->topGrid->addWidget(m_PauseContinueBtn, 0, 2);

    m_SpacerHorTop2 = new QSpacerItem(800, 5, QSizePolicy::Maximum, QSizePolicy::Maximum);
    ui->topGrid->addItem(m_SpacerHorTop2, 0, 3);

    m_Stopwatch = new QLabel("00:00:00");
    m_Stopwatch->setFont(QFont("Roboto", 16));
    ui->topGrid->addWidget(m_Stopwatch, 0, 4);

    fv = new FieldView();
    m_FieldWidth = fv->getWidth();
    m_FieldHeight = fv->getHeight();
    ui->bottomGrid->addWidget(fv, 0, 0/*, Qt::AlignJustify*/);
    //qDebug() << ui->bottomGrid->cellRect(0, 0).width() << ui->bottomGrid->cellRect(0, 0).height();
}

void MainWindow::drawStaticGraphics(std::vector<CDPoint> zonePoints) {

}

MainWindow::~MainWindow()
{
    delete ui;
    delete fv;
    delete m_StartStopBtn;
    delete m_PauseContinueBtn;
    delete m_Stopwatch;

    // По идее их нужно удалять, но тогда после закрытия окна программа крашится
    //delete m_SpacerHorTop1;
    //delete m_SpacerHorTop2;
}

