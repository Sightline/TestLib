#ifndef RENDERER_H
#define RENDERER_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOffscreenSurface>
#include <QTimer>

class Renderer : public QObject
{
    Q_OBJECT
public:
    explicit Renderer(QObject *parent = 0);
    ~Renderer();
    void initializeRenderer(QSize widgetSize);
    void createSharedContext(QOpenGLWidget *openGLWidget);

signals:
    void onRenderingComplete(double timeToRenderFrame);
    void onTextureReady(unsigned int texture);

public slots:
    void renderScene();
    void cleanUpRenderer();
    void openGLWidgetSizeChange(int width, int height);
    void animateScene();

public:
    QOpenGLWidget *m_openGLWidget;
    QOpenGLContext *m_context;
    QOffscreenSurface *m_surface;
    QSurfaceFormat *m_surfaceFormat;
    QOpenGLFramebufferObject *m_renderBuffer;
    QOpenGLFramebufferObject *m_displayBuffer;
    QOpenGLShaderProgram m_shader;
    QOpenGLFunctions_3_3_Core *m_funcs;
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;
    QMatrix4x4 m_projection;
    QSize m_widgetSize;
    QTimer *timer;
    float frame;
    qreal m_retinaScale;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
    QOpenGLShaderProgram *m_program;
};

#endif // RENDERER_H
