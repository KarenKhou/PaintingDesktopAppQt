#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVector>
#include <QPen>
#include <QColor>

//docu pr le pen stle https://doc.qt.io/qt-6/qt.html#PenStyle-enum
using namespace std;



class Canvas: public QWidget {
    Q_OBJECT
public:
    Canvas(QWidget *parent);
    struct Line{
        QPoint startPoint;
        QPoint endPoint;
        QPen pen;
    };

    QAction * pinkAction{};
    QAction * blueAction{};
    QAction * solidLine{};
    QAction * dashLine{};
    QAction * dotLine{};

protected:
    virtual void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    Line * currentLine;
    QVector<Line * > savedLines;
    bool isDrawing;
    QColor currentColor;
    Qt::PenStyle currentStyle;
    int currentWidth;

public slots:
    void selectColor(QAction * colorAction);
    void selectStyle(QAction * colorAction);
    void selectWidth(int width);
};
#endif // CANVAS_H
