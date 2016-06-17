#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QtCore>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QSurface>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>

class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    MyOpenGLWidget(QWidget *parent=0);
    ~MyOpenGLWidget();


signals:
    void onOpenGLWidgetResize(int width, int height);
    void onTextureReady(GLint texture);
    void requestUpdate();

public slots:
    void onTextureChanged(unsigned int texture);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

private:
    GLuint m_texture;
    QOpenGLFunctions_3_3_Core *m_funcs;
    QOpenGLShaderProgram *m_program;
    QOpenGLBuffer m_vboMain;
    QOpenGLVertexArrayObject m_vaoMain;
    QMatrix4x4 m_projection;
    GLuint m_positionLoc;
    GLuint m_textureLoc;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
    QOpenGLShaderProgram *m_program2;
    QOpenGLFramebufferObject *m_renderBuffer;
    QOpenGLFramebufferObject *m_displayBuffer;
    QOpenGLVertexArrayObject m_vaoCamera;
    QOpenGLBuffer m_vboCamera;
};

#endif // MYOPENGLWIDGET_H
