#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QAction>
#include <QColor>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    isDrawing(false),
    currentColor(Qt::black),
    currentStyle(Qt::SolidLine),
    currentWidth(5)
{}

void Canvas::paintEvent(QPaintEvent * paintEvent){
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);

    if (isDrawing && currentLine) {
        painter.setPen(currentLine->pen);
        painter.drawLine(currentLine->startPoint, currentLine->endPoint);
    }

    for (auto line :savedLines){
        painter.setPen(line->pen);
        painter.drawLine(line->startPoint, line->endPoint);
    }
}

void Canvas::mousePressEvent(QMouseEvent* mouseEvent){
    if (mouseEvent->button() == Qt::LeftButton) {
        currentLine = new Line();
        QPen pen;
        pen.setColor(currentColor);
        pen.setStyle(currentStyle);
        pen.setWidth(currentWidth);
        currentLine->startPoint = mouseEvent->pos();
        currentLine->endPoint = mouseEvent->pos();
        currentLine->pen = pen;
        isDrawing = true;
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (isDrawing) {
        currentLine->endPoint = mouseEvent->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton && isDrawing) {
        currentLine->endPoint = mouseEvent->pos();
        isDrawing = false;
        update();
        savedLines.push_back(currentLine);
    }
}

void Canvas::selectColor(QAction * colorAction) {
    if (colorAction == pinkAction) {
        currentColor = QColor(254, 1, 154);
    } else if (colorAction == blueAction) {
        currentColor = Qt::blue;
    }
}

void Canvas::selectStyle(QAction * styleSelected) {
    if (styleSelected == solidLine) {
        currentStyle = Qt::SolidLine;
    } else if (styleSelected == dashLine) {
        currentStyle = Qt::DashLine;
    } else if (styleSelected == dotLine) {
    currentStyle = Qt::DotLine;
    }
}

void Canvas::selectWidth(int width) {
    currentWidth = width;
}

