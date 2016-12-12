#include "OGLWidget.h"
#include <QPainter>
#include <iostream>
OGLWidget::OGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)

    , m_vertexBuffer(new QOpenGLBuffer)
    , m_program(new QOpenGLShaderProgram(this))
{
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::setFilename(QString _filename)
{
    //    filename = _filename;
    //   // texture.reset(new QOpenGLTexture(QImage(filename).mirrored()));

    //    std::cout << "FILENAME CREATED" << std::endl;
    //    QImage image(filename);
    //    if (image.format() != QImage::Format_ARGB32_Premultiplied)
    //           image = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    //    paintGL();
}

void OGLWidget::initializeGL()
{

    // tiles creation based on a 256x256 image
    QImage image("../build-Dithering-Desktop_Qt_5_7_0_GCC_64bit-Release/start_image.bmp"); //максимально грустный момент
    if (image.format() != QImage::Format_ARGB32_Premultiplied)
        image = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    _width = image.width();
    _height = image.height();
    QOpenGLTexture* tile = new QOpenGLTexture(QOpenGLTexture::Target2D);
    if (!tile) {
        qDebug() << "error!";
    }
    if (!tile->create()) {
        qDebug() << "error again!";
    }

    tile->setSize(_width, _height);
    tile->setFormat(QOpenGLTexture::R8U);
    // you can manage the number of mimap you desire...
    // by default 256x256 => 9 mipmap levels will be allocated:
    // 256, 128, 64, 32, 16, 8, 4, 2 and 1px
    // to modify this use tile->setMipLevels(n);
    tile->setMinificationFilter(QOpenGLTexture::Nearest);
    tile->setMagnificationFilter(QOpenGLTexture::Nearest);
    tile->setData(image, QOpenGLTexture::GenerateMipMaps);
    m_tiles << tile;

    // vertex buffer initialisation
    if (!m_vertexBuffer->create()) {
        qDebug() << "error!";
        return;
    }
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vertexBuffer->bind();
    // room for 2 triangles of 3 vertices
    m_vertexBuffer->allocate(2 * 3 * sizeof(Vertex2D));
    m_vertexBuffer->release();

    // shader program initialisation
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../Dithering/basic_vert.glsl")) {
        qDebug() << "error!";
        return;
    }
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../Dithering/basic_frag.glsl")) {
        qDebug() << "error!";
        return;
    }
    if (!m_program->link()) {
        qDebug() << "error!";
        return;
    }
}
void OGLWidget::resizeGL(int w, int h)
{
}

void OGLWidget::paintGL()
{
}

void OGLWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    // native draw
    painter.beginNativePainting();
    drawGL();
    painter.endNativePainting();
}

void OGLWidget::drawGL()
{
    // always a good thing to make current
    makeCurrent();
    // enable texturing
    context()->functions()->glEnable(GL_TEXTURE_2D);
    // enable blending
    context()->functions()->glEnable(GL_BLEND);
    // blending equation (remember OpenGL textures are premultiplied)
    context()->functions()->glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    // clear
    context()->functions()->glClearColor(0.8, 0.8, 0.8, 1);
    context()->functions()->glClear(GL_COLOR_BUFFER_BIT);
    context()->functions()->glClear(GL_DEPTH_BUFFER_BIT);

    // viewport and matrices setup for a 2D tile system
    context()->functions()->glViewport(0, 0, width(), height());
    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    projectionMatrix.ortho(0, width(), height(), 0, -1, 1);
    QMatrix4x4 viewProjectionMatrix;
    // use a QTransform to scale, translate, rotate your view
    viewProjectionMatrix = projectionMatrix * QMatrix4x4(m_transform);

    // program setup
    m_program->bind();
    // a good practice if you have to manage multiple shared context
    // with shared resources: the link is context dependant.
    if (!m_program->isLinked())
        m_program->link();

    // binding the buffer
    m_vertexBuffer->bind();

    // setup of the program attributes
    int pos = 0, count;
    // positions : 2 floats
    count = 2;
    m_program->enableAttributeArray("vertexPosition");
    m_program->setAttributeBuffer("vertexPosition", GL_FLOAT, pos, count, sizeof(Vertex2D));
    pos += count * sizeof(float);

    // texture coordinates : 2 floats
    count = 2;
    m_program->enableAttributeArray("textureCoordinates");
    m_program->setAttributeBuffer("textureCoordinates", GL_FLOAT, pos, count, sizeof(Vertex2D));
    pos += count * sizeof(float);

    m_program->setUniformValue("viewProjectionMatrix", viewProjectionMatrix);
    m_program->setUniformValue("f_opacity", (float)0.5);

    // draw each tile

    QRect rect = QRect(0, 0, _width, _height);
    // write vertices in the buffer
    // note : better perf if you precreate this buffer

    Vertex2D v0;
    v0.position = QVector2D(rect.bottomLeft());
    v0.coords = QVector2D(0, 1);

    Vertex2D v1;
    v1.position = QVector2D(rect.topLeft());
    v1.coords = QVector2D(0, 0);

    Vertex2D v2;
    v2.position = QVector2D(rect.bottomRight());
    v2.coords = QVector2D(1, 1);

    Vertex2D v3;
    v3.position = QVector2D(rect.topRight());
    v3.coords = QVector2D(1, 0);

    int vCount = 0;
    // first triangle v0, v1, v2
    m_vertexBuffer->write(vCount * sizeof(Vertex2D), &v0, sizeof(Vertex2D));
    vCount++;
    m_vertexBuffer->write(vCount * sizeof(Vertex2D), &v1, sizeof(Vertex2D));
    vCount++;
    m_vertexBuffer->write(vCount * sizeof(Vertex2D), &v2, sizeof(Vertex2D));
    vCount++;

    // second triangle v1, v3, v2
    m_vertexBuffer->write(vCount * sizeof(Vertex2D), &v1, sizeof(Vertex2D));
    vCount++;
    m_vertexBuffer->write(vCount * sizeof(Vertex2D), &v3, sizeof(Vertex2D));
    vCount++;
    m_vertexBuffer->write(vCount * sizeof(Vertex2D), &v2, sizeof(Vertex2D));
    vCount++;

    // bind the tile texture on texture unit 0
    // you can add other textures binding them in texture units 1, 2...
    QOpenGLTexture* tile = m_tiles.at(0);
    // activate texture unit 0
    context()->functions()->glActiveTexture(GL_TEXTURE0);
    // setup texture options here if needed...
    // set sampler2D on texture unit 0
    m_program->setUniformValue("f_tileTexture", 0);
    // bind texture
    tile->bind();
    // draw 2 triangles = 6 vertices starting at offset 0 in the buffer
    context()->functions()->glDrawArrays(GL_TRIANGLES, 0, 6);
    // release texture
    tile->release();

    m_vertexBuffer->release();
    m_program->release();
}



QRect OGLWidget::tileRect(int row, int col)
{

    //return QRect(x, y, _width, _height);
}
