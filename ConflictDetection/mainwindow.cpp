#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fw = new FieldView();

    standardOptions();
    initViewElements();


}

void MainWindow::standardOptions() {
    setWindowState(Qt::WindowMaximized);

    resize(QDesktopWidget().availableGeometry(this).size());
}

void MainWindow::initViewElements() {
    qDebug() << width() << ", " << height();
    ui->mainGrid->setGeometry(QRect(0, 0, width(), height()));



    ui->topGrid->setColumnStretch(0, 3);
    ui->topGrid->setColumnStretch(1, 0);
    ui->topGrid->setColumnStretch(2, 3);
    ui->topGrid->setColumnStretch(3, 5);
    ui->topGrid->setColumnStretch(4, 2);

    m_StartStopBtn = new QPushButton("Start");
    ui->topGrid->addWidget(m_StartStopBtn, 0, 0);

//    m_PauseContinueBtn = new QPushButton("Pause");
//    ui->gridLayout->addWidget(m_PauseContinueBtn, 0, 1);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete fw;
}

