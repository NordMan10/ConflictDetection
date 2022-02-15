#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLabel>
#include <QRect>
#include <QGridLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QFont>
#include <QFrame>

#include "model.h"
#include "controller.h"
#include "fieldview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(IModel &model, IController &controller, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FieldView *fv;

    IModel &m_Model;
    IController &m_Controller;

    QPushButton *m_StartStopBtn;
    QPushButton *m_PauseContinueBtn;

    QSpacerItem *m_SpacerHorTop1;
    QSpacerItem *m_SpacerHorTop2;

    QLabel *m_Stopwatch;

private:
    void initViewElements();
    void standardOptions();

    void drawStaticGraphics(std::vector<CDPoint> zonePoints);

private:
    int m_FieldWidth;
    int m_FieldHeight;
};

#endif // MAINWINDOW_H
