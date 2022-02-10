#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    standardOptions();

    fv = new FieldView();

    initViewElements();


}

void MainWindow::standardOptions() {
    setWindowState(Qt::WindowMaximized);

    //resize(QDesktopWidget().availableGeometry(this).size());
}

void MainWindow::initViewElements() {
    //qDebug() << width() << ", " << height();
    //ui->mainGrid->setGeometry(QRect(0, 0, width(), height()));
//    ui->mainGrid->setRowStretch(0, 1);
//    ui->mainGrid->setRowStretch(1, 4);

    ui->topGrid->setMargin(30);
    ui->topGrid->setColumnStretch(0, 2);
    ui->topGrid->setColumnStretch(1, 0);
    ui->topGrid->setColumnStretch(2, 2);
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

    ui->bottomGrid->addWidget(fv, 0, 0, Qt::AlignJustify);

//    m_Frame = new QFrame();
//    ui->bottomGrid->addWidget(m_Frame);
//    m_Frame->setFrameRect(QRect(100, 100, 100, 50));
//    m_Frame->setLineWidth(5);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete fv;
    delete m_StartStopBtn;
    delete m_PauseContinueBtn;
    delete m_Stopwatch;
    delete m_SpacerHorTop1;
    delete m_SpacerHorTop2;
}

