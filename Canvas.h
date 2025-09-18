#ifndef CANVAS_H
#define CANVAS_H

#endif // CANVAS_H
#include <QWidget>
#include <QVector>
using namespace std;



class Canvas: public QWidget {
public:
    Canvas(QWidget* parent): QWidget(parent), drawing(false){}

    struct Line{
        QPoint startPoint;
        QPoint endPoint;
        QColor color;
    };


protected:
    virtual void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QVector<Line * > savedLines;
    bool drawing;
    QColor currentColor;


//attention il faut faire une display list

public slots:
    void selectColor(QAction * colorAction);

};
