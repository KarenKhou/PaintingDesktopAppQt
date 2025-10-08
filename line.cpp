// Karen EL KHOURY

#include "line.h"

Line::Line(const QPen &p, QPoint start, QPoint end):
    Shape(p,start,end)
{}

void Line::draw(QPainter &painter) const {
    painter.setPen(pen);
    painter.drawLine(startPoint, endPoint);
}

bool Line::contains(const QPoint &point) const  {
    QPointF intersectPnt;
    QLineF l(point.x()-10, point.y()-10, point.x()+10, point.y()+10);
    QLineF l2(startPoint,endPoint);
    return (l2.intersects(l, &intersectPnt)==QLineF::BoundedIntersection);
}


void Line::resize(const QPoint &newPos, int handleIndex)  {
    if (handleIndex == 0) {
        startPoint = newPos;
    } else if (handleIndex == 1) {
        endPoint = newPos;
    }
}

void Line::createSelectionHandles(QPainter &painter) {
    selectionHandle.clear();
    QPen p;
    //p.setColor(QColor::Black)

    const int size = 20;

    QRectF r1(startPoint.x()-size/2, startPoint.y()-size/2, size, size);
    QRectF r2(endPoint.x()-size/2,   endPoint.y()-size/2,   size, size);
    selectionHandle.push_back(r1);
    selectionHandle.push_back(r2);

    painter.setPen(p);
    painter.drawRect(r1);
    painter.drawRect(r2);

}
