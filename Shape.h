#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QMouseEvent>
#include <QAction>
#include <QColor>
#include <QPen>

enum class ShapeType{
    Rectangle,
    Ellipse,
    Line
};


class Shape {
public:
    Shape(const QPen &p, QPoint start, QPoint end) :
        pen(p),
        startPoint(start),
        endPoint(end)
    {}

    void setEndPoint(QPoint end){
        endPoint = end;
    }

    virtual ~Shape() = default;

    virtual void draw(QPainter &painter) const = 0;
    //virtual bool contains(const QPoint &pt) const = 0;

protected:
    QPen pen;
    QPoint startPoint;
    QPoint endPoint;

};
class Line : public Shape{
public:
    Line(const QPen &p, QPoint start, QPoint end):
        Shape(p,start,end)
    {}

    void draw(QPainter &painter) const override{
        painter.setPen(pen);
        painter.drawLine(startPoint, endPoint);
    }

    // bool contains(const QPoint &pt) const override{

    // }
};

class Rectangle : public Shape{
public:
    Rectangle(const QPen &p, QPoint start, QPoint end):
        Shape(p,start,end)
    {}

    void draw(QPainter &painter) const override{
        painter.setPen(pen);
        painter.drawRect(QRect(startPoint, endPoint));
    }
};

class Ellipse : public Shape{
    public:
        Ellipse(const QPen &p, QPoint start, QPoint end):
            Shape(p,start,end)
    {}

    void draw(QPainter &painter) const override{
        painter.setPen(pen);
        painter.drawEllipse(QRect(startPoint, endPoint).normalized());    }
};

#endif // SHAPE_H
