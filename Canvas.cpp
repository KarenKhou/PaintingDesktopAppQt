#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>


void Canvas::paintEvent(QPaintEvent * e){
    QWidget::paintEvent(e);
    QPainter painter(this);
    QPen pen = QPen(currentColor, 2);
    painter.setPen(pen);
    if (startPoint != endPoint) {
        painter.drawLine(startPoint, endPoint);
    }
}

void Canvas::mousePressEvent(QMouseEvent* e){
    if (e->button() == Qt::LeftButton) {
        Line * l = new Line;
        l->startPoint = e->pos();
        l->endPoint = e->pos();
        l->color = currentColor;
        savedLines.push_back(l);
        drawing = true;
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *e) {
    if (drawing) {
        l->endPoint = e->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton && drawing) {
        endPoint = e->pos();
        drawing = false;
        update();
    }
}

void Canvas::selectColor(QAction * colorAction) {
    if (colorAction->text() == "Red") {
        currentColor = Qt::red;
    } else if (colorAction->text() == "Blue") {
        currentColor = Qt::blue;
    }
    update();
}
