// Karen EL KHOURY

#include "ellipse.h"

Ellipse::Ellipse(const QPen &p, QPoint start, QPoint end):
    Shape(p,start,end)
{}

void Ellipse::draw(QPainter &painter) const{
    painter.setPen(pen);
    painter.drawEllipse(QRect(startPoint, endPoint).normalized());    }

bool Ellipse::contains(const QPoint& point) const {
    QRectF rect(startPoint, endPoint);
    rect = rect.normalized();

    // ellipse center
    double cx = rect.center().x();
    double cy = rect.center().y();

    // half width and half height
    double a = rect.width() / 2.0;
    double b = rect.height() / 2.0;

    // point coordinates
    double x = point.x();
    double y = point.y();

    // ellipse equation
    double value = ((x - cx) * (x - cx)) / (a * a)
                   + ((y - cy) * (y - cy)) / (b * b);

    return value <= 1.0; // inside ellipse
}

void Ellipse::resize(const QPoint &newPos, int handleIndex){
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

void Ellipse::createSelectionHandles(QPainter &painter) {
    selectionHandle.clear();

    const int size = 20;
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

