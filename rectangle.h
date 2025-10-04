#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape{
public:
    Rectangle(const QPen &p, QPoint start, QPoint end);

    void draw(QPainter &painter) const override;
    bool contains(const QPoint& point) const override;
    void resize(const QPoint &newPos, int handleIndex) override;
    void createSelectionHandles(QPainter &painter) override;

};


#endif // RECTANGLE_H
