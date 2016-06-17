#include "renderer.h"
#include <QDebug>
#include <QMessageBox>

Renderer::Renderer(QObject *parent) : QObject(parent),
    m_context(0),
    m_surface(0)
{

}

Renderer::~Renderer()
{

}

static const char *vertexShaderSource2 =
    "#version 330\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "uniform mat4 matrix;\n"
    "out vec3 col;\n"
    "void main() {\n"
    "   col = color;\n"
    "   gl_Position = matrix * vec4(position, 1.0);\n"
    "}\n";

static const char *fragmentShaderSource2 =
    "#version 330\n"
    "in vec3 col;\n"
    "layout (location = 0) out vec4 fragColor;\n"
    "void main() {\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";


void Renderer::initializeRenderer(QSize widgetSize)
{
    qDebug() << "Initialize renderer thread ... " << this->thread();
    qDebug() << "Context in thread ... " << m_context->thread();
    qDebug() << "Surface in thread ... " << m_surface->thread();

    // Make the context current
    m_context->makeCurrent(m_surface);
    m_widgetSize = widgetSize;

    // Create the framebuffers. We will use two framebuffers, one ot render to
    // and the other to store the information required to display the texture
    // to screen. First, define the framebuffer format
    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setSamples(4);    // Multisampling to ensure antialiasing
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    m_renderBuffer = new QOpenGLFramebufferObject(m_widgetSize,fboFormat);
    m_displayBuffer = new QOpenGLFramebufferObject(m_widgetSize);
    // Initializes OpenGL function resolution for the current context
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_3_Core>();

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource2);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource2);
    m_program->link();
    m_posAttr = m_program->attributeLocation("position");
    m_colAttr = m_program->attributeLocation("color");
    m_program->bind();
    m_matrixUniform = m_program->uniformLocation("matrix");

    // Create and define the buffer terms
    m_vao.create();
    m_vao.bind();
    m_vbo.create();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.bind();
    GLfloat vertices[] = { 0.0f, 0.707f, 0.0f,
                           1.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                           0.0f, 1.0f, 0.0f,
                           0.5f, -0.5f, 0.0f,
                           0.0f, 0.0f, 1.0f
    };
    // Copy the data to the buffer
    m_vbo.allocate(vertices, 18*sizeof(float));
    m_funcs->glEnableVertexAttribArray(0);
    m_funcs->glEnableVertexAttribArray(1);
    m_funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
    m_funcs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));

    // Bind the render framebuffer
    m_renderBuffer->bind();

    m_funcs->glViewport(0, 0, m_widgetSize.width(), m_widgetSize.height());
//    m_retinaScale = openGLWidget->devicePixelRatio();
    m_retinaScale = 1.0;
    frame = 0.0f;

    // Now move the object and context to the renderThread
    m_context->doneCurrent();
}

void Renderer::createSharedContext(QOpenGLWidget *openGLWidget)
{
    m_openGLWidget = openGLWidget;
    // We want to share the context of the OpenGLWidget
    if(!m_context)
    {
        openGLWidget->context()->doneCurrent();
        m_context = new QOpenGLContext();
        m_context->setFormat(openGLWidget->context()->format());
        m_context->setShareContext(openGLWidget->context());
        m_context->create();
        if(!m_context->isValid())
        {
            QMessageBox::warning(nullptr, QObject::tr("OpenGL initialisation Error"),
                                     QObject::tr("Cannot get a shared OpenGL context. Requires version 3.3 minimum"));
            qFatal("Requires OpenGL >= 3.0");
            exit( 1 );
        }

        // Now set the surface format
        m_surface = new QOffscreenSurface();
        m_surface->setFormat(m_context->format());
        m_surface->create();
    }
}


void Renderer::renderScene()
{
    // Make the renderer context current
    m_context->makeCurrent(m_surface);

    // Recall the openGL functions pointer
    m_funcs->initializeOpenGLFunctions();

    // Bind the render framebuffer
    m_renderBuffer->bind();

    // Set-up the draw context
    m_funcs->glViewport(0, 0, m_widgetSize.width() * m_retinaScale, m_widgetSize.height() * m_retinaScale);
    m_funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the scene
    m_program->bind();
    m_vao.bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * frame / 60.0f, 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    m_funcs->glDrawArrays(GL_TRIANGLES, 0, 3);

    // Now flush contents inot the framebuffer
    m_funcs->glFlush();

    // Copy the colormap from the renderBuffer to the displayBuffer
    // (this step is required if multi-sampling)
    m_displayBuffer->bind();
    QOpenGLFramebufferObject::blitFramebuffer(m_displayBuffer,m_renderBuffer);

    emit onTextureReady(m_displayBuffer->texture());


//    qDebug() << "Texture location (GLuint)... " << m_displayBuffer->toImage();
//    QImage tmp(m_displayBuffer->toImage());
//    qDebug() << "Image size..." << tmp.size();
//    QString str = QString("tmpImage%1.png").arg(frame);
//    qDebug() << "image location " << str;
//    tmp.save(str);

    m_renderBuffer->bind();
    m_program->release();
    frame++;
}


void Renderer::cleanUpRenderer()
{
    qDebug() << "Renderer destructor called from thread " << this->thread();
    qDebug() << "Context is in thread " << m_context->thread();
    m_context->makeCurrent(m_surface);
    qDebug() << "context made current";
    m_vao.destroy();
    m_renderBuffer->release();
    delete m_renderBuffer;
    m_displayBuffer->release();
    delete m_displayBuffer;
    delete m_program;
    m_context->doneCurrent();
    delete m_context;
}

void Renderer::openGLWidgetSizeChange(int width, int height)
{
    // Make the renderer context current
    m_context->makeCurrent(m_surface);
    m_widgetSize.setWidth(width);
    m_widgetSize.setHeight(height);
    // Need to delete the current FBO's
    m_renderBuffer->release();
    m_displayBuffer->release();
    delete m_renderBuffer;
    delete m_displayBuffer;
    // Now re-create with the new size.
    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setSamples(4);    // Multisampling to ensure antialiasing
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    m_renderBuffer = new QOpenGLFramebufferObject(m_widgetSize,fboFormat);
    m_displayBuffer = new QOpenGLFramebufferObject(m_widgetSize);
    // Re-draw the scene onto the new framebuffers
    this->renderScene();
}

void Renderer::animateScene()
{
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Renderer::renderScene, Qt::QueuedConnection);
    timer->start(16);
}


