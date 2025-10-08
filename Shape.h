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
    void move(const QPoint &delta) {
        startPoint += delta;
        endPoint   += delta;
    }
    int handleSelected(const QPoint &p)const{
        int i=0;
        for (auto handle : selectionHandle){
            if (handle.contains(p)) {
                return i;
            }
            i++;
        }
        return -1;
    }

    virtual ~Shape() = default;

    virtual void draw(QPainter &painter) const = 0;
    virtual bool contains(const QPoint &pt) const = 0;


    virtual void resize(const QPoint &newPos, int handleIndex)=0;
    virtual void createSelectionHandles(QPainter &painter) = 0;



protected:
    QPen pen{};
    QPoint startPoint{};
    QPoint endPoint{};
    vector<QRectF> selectionHandle{};

};


#endif // SHAPE_H
