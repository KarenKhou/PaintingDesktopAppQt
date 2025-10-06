// Karen EL KHOURY

#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "Shape.h"


class Ellipse : public Shape{
public:
    Ellipse(const QPen &p, QPoint start, QPoint end);

    void draw(QPainter &painter) const override;

    bool contains(const QPoint& point) const override ;

    void resize(const QPoint &newPos, int handleIndex) override;

    void createSelectionHandles(QPainter &painter) override ;
};

#endif // ELLIPSE_H
