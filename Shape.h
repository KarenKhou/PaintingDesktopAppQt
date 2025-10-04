//  Karen EL KHOURY

#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QMouseEvent>
#include <QAction>
#include <QColor>
#include <QPen>
#include <iostream>
#include <vector>
using namespace std;

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
    void move(const QPoint &delta) {
        startPoint += delta;
        endPoint   += delta;
    }

    virtual void resize(const QPoint &newPos, int handleIndex)=0;
    virtual void createSelectionHandles(QPainter &painter) = 0;
    int handleSelected(const QPoint &p)const{
        int i=0;
        for (auto handle : selectionHandle){
            QRectF bigger = handle.adjusted(-4, -4, 4, 4); // 4 px de tolérance
            if (bigger.contains(p)) {
                return i;
            }
            i++;

        }
        return -1;
    }


protected:
    QPen pen{};
    QPoint startPoint{};
    QPoint endPoint{};
    vector<QRectF> selectionHandle{};

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

    bool contains(const QPoint &point) const override {
        QPointF intersectPnt;
        QLineF l(point.x()-10, point.y()-10, point.x()+10, point.y()+10);
        QLineF l2(startPoint,endPoint);
        return (l2.intersects(l, &intersectPnt)==QLineF::BoundedIntersection);
    }


    void resize(const QPoint &newPos, int handleIndex) override {
        if (handleIndex == 0) {
            startPoint = newPos;
        } else if (handleIndex == 1) {
            endPoint = newPos;
        }
    }

    void createSelectionHandles(QPainter &painter) override{
        selectionHandle.clear();
        QPen p;
        //p.setColor(QColor::Black)

        const int size = 16;

        QRectF r1(startPoint.x()-size/2, startPoint.y()-size/2, size, size);
        QRectF r2(endPoint.x()-size/2,   endPoint.y()-size/2,   size, size);
        selectionHandle.push_back(r1);
        selectionHandle.push_back(r2);

        painter.setPen(p);
        painter.drawRect(r1);
        painter.drawRect(r2);

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
        return QRect(startPoint, endPoint).normalized().contains(point);
    }

    void resize(const QPoint &newPos, int handleIndex) override {
        switch (handleIndex) {
        case 0: // top-left
            startPoint = newPos;
            break;
        case 1: // top-right
            startPoint.setY(newPos.y());
            endPoint.setX(newPos.x());
            break;
        case 2: // bottom-left
            startPoint.setX(newPos.x());
            endPoint.setY(newPos.y());
            break;
        case 3: // bottom-right
            endPoint = newPos;
            break;
        }
    }



    void createSelectionHandles(QPainter &painter) override {
        selectionHandle.clear();

        const int size = 16;
        QRectF b(startPoint, endPoint);
        b = b.normalized();

        QRectF r1(b.topLeft().x()     - size/2, b.topLeft().y()     - size/2, size, size);
        QRectF r2(b.topRight().x()    - size/2, b.topRight().y()    - size/2, size, size);
        QRectF r3(b.bottomLeft().x()  - size/2, b.bottomLeft().y()  - size/2, size, size);
        QRectF r4(b.bottomRight().x() - size/2, b.bottomRight().y() - size/2, size, size);

        selectionHandle.push_back(r1);
        selectionHandle.push_back(r2);
        selectionHandle.push_back(r3);
        selectionHandle.push_back(r4);

        painter.setPen(Qt::black);
        painter.drawRect(r1); painter.drawRect(r2);
        painter.drawRect(r3); painter.drawRect(r4);
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

    bool contains(const QPoint& point) const override {
        return QRect(startPoint, endPoint).normalized().contains(point);
    }

        void resize(const QPoint &newPos, int handleIndex) override{
            switch (handleIndex) {
            case 0: // top-left
                startPoint = newPos;
                break;
            case 1: // top-right
                startPoint.setY(newPos.y());
                endPoint.setX(newPos.x());
                break;
            case 2: // bottom-left
                startPoint.setX(newPos.x());
                endPoint.setY(newPos.y());
                break;
            case 3: // bottom-right
                endPoint = newPos;
                break;
            }
        }

    void createSelectionHandles(QPainter &painter) override {
        selectionHandle.clear();

        const int size = 16;
        QRectF b(startPoint, endPoint);
        b = b.normalized();

        QRectF r1(b.topLeft().x()     - size/2, b.topLeft().y()     - size/2, size, size);
        QRectF r2(b.topRight().x()    - size/2, b.topRight().y()    - size/2, size, size);
        QRectF r3(b.bottomLeft().x()  - size/2, b.bottomLeft().y()  - size/2, size, size);
        QRectF r4(b.bottomRight().x() - size/2, b.bottomRight().y() - size/2, size, size);

        selectionHandle.push_back(r1);
        selectionHandle.push_back(r2);
        selectionHandle.push_back(r3);
        selectionHandle.push_back(r4);

        painter.setPen(Qt::black);
        painter.drawRect(r1); painter.drawRect(r2);
        painter.drawRect(r3); painter.drawRect(r4);
    }

};

#endif // SHAPE_H
