#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

//Q_DECLARE_METATYPE(GLuint)


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_renderer(0),
    m_renderThread(0),
    animationTimer(0)
{
    ui->setupUi(this);
    qDebug() << "Main GUI thread ... " << this->thread();
    QApplication::instance()->thread();
}

MainWindow::~MainWindow()
{
    qDebug() << "Main window destructor called";
    if(animationTimer)
    {
        animationTimer->stop();
        delete animationTimer;
        qDebug() << "Timer deleted";
    }
    //
    if(m_renderer)
    {
        emit onCleanRenderer();
        qDebug() << "Renderer deleted";
    }
    //
    if(m_renderThread)
    {
        m_renderThread->quit();
        m_renderThread->deleteLater();
        m_renderThread->wait();
        delete m_renderThread;
        qDebug() << "RenderThread deleted";
    }
    //
    delete ui;
}

void MainWindow::setUpPlots()
{
    QCPScatterStyle myScatter;
    myScatter.setShape(QCPScatterStyle::ssCircle);
    myScatter.setPen(QPen(Qt::blue));
    myScatter.setBrush(Qt::red);
    myScatter.setSize(10);

    // add two new graphs and set their look:
    ui->customPlot1->addGraph();
    ui->customPlot1->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->customPlot1->addGraph();
    ui->customPlot1->graph(1)->setPen(QPen(Qt::blue)); // line color red for second graph
    ui->customPlot1->graph(1)->setScatterStyle(myScatter);
    ui->customPlot1->xAxis->setLabel(QString("time (s)"));
    ui->customPlot1->yAxis->setLabel(QString("x-position (m)"));

    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(250), y0(250);
    for (int i=0; i<250; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->customPlot1->xAxis2->setVisible(true);
    ui->customPlot1->xAxis2->setTickLabels(false);
    ui->customPlot1->yAxis2->setVisible(true);
    ui->customPlot1->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot1->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot1->graph(0)->setData(x, y0);
    QVector<double> tmpX, tmpY;
    if(!x.isEmpty())
    {
        tmpX.push_back(x[0]);
        tmpY.push_back(y0[0]);
    }
    ui->customPlot1->graph(1)->setData(tmpX,tmpY);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->customPlot1->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->customPlot1->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // Update the UI
    ui->customPlot1->replot();
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(m_renderer->timer, &QTimer::timeout, this, &MainWindow::onUpdateCustomPlot);
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_pushButton_clicked()
{
    m_renderer = new Renderer();
    m_renderThread = new QThread;
    m_renderer->createSharedContext(ui->openGLWidget);
    m_renderer->initializeRenderer(ui->openGLWidget->size());
    m_renderer->m_context->moveToThread(m_renderThread);
    m_renderer->moveToThread(m_renderThread);

    connect(m_renderer, &Renderer::onTextureReady, ui->openGLWidget, &MyOpenGLWidget::onTextureChanged);
    connect(ui->openGLWidget, &MyOpenGLWidget::onOpenGLWidgetResize, m_renderer, &Renderer::openGLWidgetSizeChange,Qt::QueuedConnection);
    connect(ui->openGLWidget, &MyOpenGLWidget::requestUpdate, this, &MainWindow::onUpdaterequest);
    connect(this, &MainWindow::onCleanRenderer, m_renderer, &Renderer::cleanUpRenderer, Qt::QueuedConnection);
    m_renderThread->start();

    QMetaObject::invokeMethod(m_renderer, "renderScene", Qt::QueuedConnection);
    ui->openGLWidget->update();
}

void MainWindow::on_pushButtonAnimate_clicked()
{
    connect(this, &MainWindow::onAnimationStart, m_renderer, &Renderer::animateScene,Qt::QueuedConnection);
    emit onAnimationStart();
    this->setUpPlots();
}

void MainWindow::onUpdaterequest()
{
    ui->openGLWidget->update();
}

static int count = 0;
void MainWindow::onUpdateCustomPlot()
{
    QVector<double> x(250), y0(250);
    for (int i=0; i<250; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
    }
    QVector<double> tmpX, tmpY;
    if(!x.isEmpty())
    {
        tmpX.push_back(x[count]);
        tmpY.push_back(y0[count]);
    }
    ui->customPlot1->graph(1)->setData(tmpX,tmpY);
    ui->customPlot1->replot();
    tmpX.clear();
    tmpY.clear();
    if(count < x.size()-1)
    {
        count++;
    }
}
