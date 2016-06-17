#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "renderer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUpPlots();

signals:
    void onAnimationStart();
    void onCleanRenderer();

private slots:
    void on_actionNew_triggered();

    void on_pushButton_clicked();

    void on_pushButtonAnimate_clicked();

    void onUpdaterequest();
    void onUpdateCustomPlot();

private:
    Ui::MainWindow *ui;
    Renderer *m_renderer;
    QThread *m_renderThread;
    QTimer *animationTimer;
};

#endif // MAINWINDOW_H
