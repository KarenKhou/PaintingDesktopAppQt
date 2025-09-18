#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>


void Canvas::paintEvent(QPaintEvent * e){
    QWidget::paintEvent(e);
    QPainter painter(this);
    QPen pen = QPen(currentColor, 2);
    painter.setPen(pen);
    for (auto line :savedLines){
        painter.drawLine(line->startPoint, line->endPoint);

    }
}

void Canvas::mousePressEvent(QMouseEvent* e){
    if (e->button() == Qt::LeftButton) {
        currentLine = new Line();
        currentLine->startPoint = e->pos();
        currentLine->endPoint = e->pos();
        currentLine->startPoint = e->pos();
        currentLine->color = currentColor;
        drawing = true;
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *e) {
    if (drawing) {
        currentLine->endPoint = e->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton && drawing) {
        currentLine->endPoint = e->pos();
        drawing = false;
        update();
        savedLines.push_back(currentLine);
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
