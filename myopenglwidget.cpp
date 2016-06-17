#include <QMessageBox>
#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_vboMain(QOpenGLBuffer::VertexBuffer)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    this->m_texture = 0;
}

MyOpenGLWidget::~MyOpenGLWidget()
{

}

static const char *vertexShaderSource =
    "#version 330\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec2 textureUV;\n"
    "out vec2 texcoord;\n"
    "void main() {\n"
    "   texcoord = textureUV;\n"
    "   gl_Position = vec4(position, 1.0);\n"
    "}\n";

static const char *fragmentShaderSource =
    "#version 330\n"
    "in vec2 texcoord;\n"
    "layout (location = 0) out vec4 fragColor;\n"
    "uniform sampler2D Texture;\n"
    "void main() {\n"
    "   vec4 color = texture(Texture, texcoord);\n"
    "   fragColor = color;\n"
    "}\n";


void MyOpenGLWidget::initializeGL()
{
    // Initializes OpenGL function resolution for the current context
    m_funcs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    if ( !m_funcs )
    {
        QMessageBox::warning(nullptr, QObject::tr("OpenGL initialisation Error"),
                                 QObject::tr("Cannot get an OpenGL context. Requires version 3.3 minimum"));
        qFatal("Requires OpenGL >= 3.0");
        exit( 1 );
    }
    m_funcs->initializeOpenGLFunctions();

    // Create the shader program
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_program->bindAttributeLocation("position", 0);
    m_program->bindAttributeLocation("textureUV", 1);
    m_program->bind();
    m_positionLoc = m_program->uniformLocation("position");
    m_textureLoc = m_program->uniformLocation("textureUV");

    // Create and define the buffer terms
    m_vaoMain.create();
    m_vaoMain.bind();
    m_vboMain.create();
    m_vboMain.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboMain.bind();
    float verts[]={  -1.0f, -1.0f, 0.0f,
                      0.0f, 0.0f,
                      -1.0f, 1.0f, 0.0f,
                      0.0f, 1.0f,
                      1.0f, 1.0f, 0.0f,
                      1.0f, 1.0f,
                      1.0f, 1.0f, 0.0f,
                      1.0f, 1.0f,
                      1.0f, -1.0f, 0.0f,
                      1.0f, 0.0f,
                     -1.0f, -1.0f, 0.0f,
                      0.0f, 0.0f
    };
    // Copy the data to the buffer
    m_vboMain.allocate(verts, 30*sizeof(float));
    m_funcs->glEnableVertexAttribArray(0);
    m_funcs->glEnableVertexAttribArray(1);
    m_funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
    m_funcs->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    m_vaoMain.release();

    // Now the camera frame
    m_vaoCamera.create();
    m_vaoCamera.bind();
    m_vboCamera.create();
    m_vboCamera.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vboCamera.bind();
    float vertsCam[]={  -1.0f, 0.5f, 0.0f,
                      0.0f, 0.0f,
                      -1.0f, 1.0f, 0.0f,
                      0.0f, 1.0f,
                      -0.5f, 1.0f, 0.0f,
                      1.0f, 1.0f,
                      -0.5f, 1.0f, 0.0f,
                      1.0f, 1.0f,
                      -0.5f, 0.5f, 0.0f,
                      1.0f, 0.0f,
                     -1.0f, 0.5f, 0.0f,
                      0.0f, 0.0f
    };
    // Copy the data to the buffer
    m_vboCamera.allocate(vertsCam, 30*sizeof(float));
    m_funcs->glEnableVertexAttribArray(0);
    m_funcs->glEnableVertexAttribArray(1);
    m_funcs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
    m_funcs->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    m_vaoCamera.release();
}

void MyOpenGLWidget::paintGL()
{
//    qDebug() << "PaintGL called... ";
    m_funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Bind the shader program
    m_program->bind();
    m_funcs->glActiveTexture(GL_TEXTURE0);
    m_funcs->glBindTexture(GL_TEXTURE_2D, this->m_texture);
    // Bind the main vertex buffer
    m_vaoMain.bind();
    m_funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
    // Bind the camera vertex buffer
    m_vaoCamera.bind();
    m_funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
    m_funcs->glBindTexture(GL_TEXTURE_2D, 0);
    m_program->release();
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, GLfloat(width) / height, 0.5f, 100000.0f);
    emit onOpenGLWidgetResize(width, height);
}


void MyOpenGLWidget::onTextureChanged(unsigned int texture)
{
    m_texture = static_cast<GLuint>(texture);
//    qDebug() << "Texture location (trans)... " << m_texture;
//    this->paintGL();
//    QMetaObject::invokeMethod(this, "Update", Qt::QueuedConnection);
    emit requestUpdate();
}



