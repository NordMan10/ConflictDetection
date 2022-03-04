#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(IModel &model, IController &controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Model(model),
    m_Controller(controller)
{
    ui->setupUi(this);

    m_Model.registerAircraftsObserver(this);

    standardOptions();
    initViewElements();

    m_ViewZoom = new Graphics_view_zoom(m_FieldView);
    m_ViewZoom->set_modifiers(Qt::NoModifier);

    connect(m_TimerStopwatch, SIGNAL(timeout()), this, SLOT(slotTimerStopwatchTick()));

    connect(m_StartStopBtn, SIGNAL(clicked()), this, SLOT(start()));
    connect(m_PauseContinueBtn, SIGNAL(clicked()), this, SLOT(pause()));
}

void MainWindow::standardOptions() {
    setWindowState(Qt::WindowMaximized);

    resize(QDesktopWidget().availableGeometry(this).size());
    //qDebug() << width() << height();
}

void MainWindow::initViewElements() {
    ui->mainGrid->setRowStretch(0, 1);
    ui->mainGrid->setRowStretch(1, 4);

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

    m_FieldView = new FieldView(m_Model.getFieldPoints(), m_Model.getPaths(), m_Model.getAircrafts());
    m_FieldWidth = m_FieldView->getWidth();
    m_FieldHeight = m_FieldView->getHeight();
    ui->bottomGrid->addWidget(m_FieldView, 0, 0/*, Qt::AlignJustify*/);

    m_TimerStopwatch = new QTimer();
}

void MainWindow::slotTimerStopwatchTick() {
    m_Controller.updateStopwatchValue(m_StopwatchTickValue);
    m_Stopwatch->setText(QTime::fromMSecsSinceStartOfDay(m_Controller.getStopwatchValue()).toString());
    //m_Stopwatch->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void MainWindow::start() {
    m_TimerStopwatch->start(m_StopwatchTickValue);
    m_StartStopBtn->setText("Stop");
    disconnect(m_StartStopBtn, SIGNAL(clicked()), this, SLOT(start()));
    connect(m_StartStopBtn, SIGNAL(clicked()), this, SLOT(stop()));

    m_Controller.start();
}

void MainWindow::stop() {
    m_TimerStopwatch->stop();
    m_StartStopBtn->setText("Start");
    disconnect(m_StartStopBtn, SIGNAL(clicked()), this, SLOT(stop()));
    connect(m_StartStopBtn, SIGNAL(clicked()), this, SLOT(start()));

    m_Controller.setStopwatchValue(0);
    m_Stopwatch->setText("00:00:00");

    if (!m_TimerStopwatch->isActive()) {
        m_PauseContinueBtn->setText("Pause");
        disconnect(m_PauseContinueBtn, SIGNAL(clicked()), this, SLOT(continueWork()));
        connect(m_PauseContinueBtn, SIGNAL(clicked()), this, SLOT(pause()));
    }

    m_Controller.stop();
}

void MainWindow::pause() {
    if (m_TimerStopwatch->isActive()) {
        m_TimerStopwatch->stop();
        m_PauseContinueBtn->setText("Continue");
        disconnect(m_PauseContinueBtn, SIGNAL(clicked()), this, SLOT(pause()));
        connect(m_PauseContinueBtn, SIGNAL(clicked()), this, SLOT(continueWork()));

        m_Controller.pause();
    }
}

void MainWindow::continueWork() {
    m_TimerStopwatch->start();
    m_PauseContinueBtn->setText("Pause");
    disconnect(m_PauseContinueBtn, SIGNAL(clicked()), this, SLOT(continueWork()));
    connect(m_PauseContinueBtn, SIGNAL(clicked()), this, SLOT(pause()));

    m_Controller.continueWork();
}

void MainWindow::updateAircraftData(std::string aircraftId) {
    m_FieldView->updateGraphics();
}

MainWindow::~MainWindow()
{
    // В теории этого делать не нужно, поскольку с закрытием главного окна завершается работа
    // приложения, а значит и освобождается вся память.
    delete ui;
    delete m_FieldView;
    delete m_StartStopBtn;
    delete m_PauseContinueBtn;
    delete m_Stopwatch;

    delete m_TimerStopwatch;
    // По идее их нужно удалять, но тогда после закрытия окна программа крашится
    //delete m_SpacerHorTop1;
    //delete m_SpacerHorTop2;
}

