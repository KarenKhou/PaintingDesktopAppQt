#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QMouseEvent>
#include <QAction>
#include <QColor>
#include <QPen>
#include <iostream>

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

    void setColor(QColor color){
        pen.setColor(color);
    }
    void setStyle(Qt::PenStyle style){
        pen.setStyle(style);
    }
    void setWidth(int w){
        pen.setWidth(w);
    }

    virtual ~Shape() = default;

    virtual void draw(QPainter &painter) const = 0;
    virtual bool contains(const QPoint &pt) const = 0;
    virtual void move(QPoint pos) =0;
    virtual void resize()=0;


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

    bool contains(const QPoint &p) const override {
        return false;
    }

    void move(QPoint pos) override{
        startPoint= pos;

    }

    void resize() override{

    }


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
    bool contains(const QPoint& point) const override {
        std::cout<<"hi"<<QRect(startPoint, endPoint).normalized().contains(point);
        return QRect(startPoint, endPoint).normalized().contains(point);
    }

    void move(QPoint pos) override{
        QPoint dist = pos - startPoint;
        startPoint += dist;
        endPoint   += dist;
    }

    void resize() override{

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

    bool contains(const QPoint &p) const override {
        return false;
    }

    void move(QPoint pos) override{
        startPoint= pos;

    }

    void resize() override{

    }
};

#endif // SHAPE_H
