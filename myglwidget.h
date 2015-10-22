#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QVector3D>
#include <QVector>
//#include <QOpenGLFunctions_2_0>
#include <QGLWidget>

class GL_Widget : public QGLWidget
{
Q_OBJECT
public:
    explicit GL_Widget(QWidget *parent = 0);
    QVector3D readGL();
    std::string getterNomFile() const;
    std::string setterNomFile(std::string nom);
    QVector<QVector3D> setterTableau(QVector<QVector3D> vectorT);
    QVector<QVector3D> getterTableau();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    std::string m_nameFile;
    QVector<QVector3D> m_vector;

};

#endif // GL_WIDGET_H
