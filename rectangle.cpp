#include "rectangle.h"

Rectangle::Rectangle(const QPen &p, QPoint start, QPoint end):
    Shape(p,start,end)
{}

void Rectangle::draw(QPainter &painter) const {
    painter.setPen(pen);
    painter.drawRect(QRect(startPoint, endPoint));
}
bool Rectangle::contains(const QPoint& point) const  {
    return QRect(startPoint, endPoint).normalized().contains(point);
}

void Rectangle::resize(const QPoint &newPos, int handleIndex)  {
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



void Rectangle::createSelectionHandles(QPainter &painter)  {
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
