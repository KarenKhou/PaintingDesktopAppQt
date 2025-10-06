// Karen EL KHOURY
#ifndef LINE_H
#define LINE_H
#include "Shape.h"


class Line : public Shape{
public:
    Line(const QPen &p, QPoint start, QPoint end);

    void draw(QPainter &painter) const override;
    bool contains(const QPoint &point) const override;
    void resize(const QPoint &newPos, int handleIndex) override;
    void createSelectionHandles(QPainter &painter) override;
};


#endif // LINE_H
