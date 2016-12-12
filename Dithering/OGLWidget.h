#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QString>
#include <QWidget>
#include <memory>
class Vertex2D {
public:
    Vertex2D() {}
    Vertex2D(const QPointF& p, const QPointF& c)
        : position(p)
        , coords(c)
    {
    }
    QVector2D position; // position of the vertex
    QVector2D coords; // texture coordinates of the vertex
};
class OGLWidget : public QOpenGLWidget {
public:
    OGLWidget(QWidget* parent = 0);
    ~OGLWidget();
    void setFilename(QString _filename);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    QString filename;
    QTransform m_transform;
    int _width;
    int _height;
    QVector<QOpenGLTexture*> m_tiles;
    QOpenGLBuffer* m_vertexBuffer;
    QOpenGLShaderProgram* m_program;
    void drawGL();
    int tileIndex(int row, int col);
    QRect tileRect(int row, int col);
};

#endif // OGLWIDGET_H
