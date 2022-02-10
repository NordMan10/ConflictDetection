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

#include "fieldview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FieldView *fv;

    QFrame *m_Frame;

    QPushButton *m_StartStopBtn;
    QPushButton *m_PauseContinueBtn;

    QSpacerItem *m_SpacerHorTop1;
    QSpacerItem *m_SpacerHorTop2;

    QLabel *m_Stopwatch;

private:
    void initViewElements();
    void standardOptions();
};

#endif // MAINWINDOW_H
