#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVector>
#include <QPen>
#include <QColor>

//docu pr le pen stle https://doc.qt.io/qt-6/qt.html#PenStyle-enum
using namespace std;



class Canvas: public QWidget {
    Q_OBJECT
public:

    struct Shape {
        enum Type { Line, Rectangle, Ellipse } type;
        QPoint startPoint;
        QPoint endPoint;
        QPen pen;
    };

    Canvas(QWidget *parent);

    QAction * pinkAction{};
    QAction * blueAction{};
    QAction * solidLine{};
    QAction * dashLine{};
    QAction * dotLine{};
    QAction * lineAction{};
    QAction * rectAction{};
    QAction * ellipseAction{};

protected:
    virtual void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    Shape * currentShape;
    QVector<Shape * > savedLines;
    bool isDrawing;
    QColor currentColor;
    Qt::PenStyle currentStyle;
    int currentWidth;
    Shape::Type currentShapeType;

public slots:
    void selectColor(QAction * colorAction);
    void selectStyle(QAction * colorAction);
    void selectWidth(int width);
    void selectShape(QAction * shapeSelected);
};
#endif // CANVAS_H
