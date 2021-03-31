#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include "tmview.h"
#include "mainwindow.h"
#include "tmfreehandcomponent.h"
#include "tmlinecomponent.h"
#include "tmcirclecomponent.h"
#include "tmrectanglecomponent.h"
#include <QMainWindow>
#include <QColor>

class Canvas : public QFrame
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void add(DrawableComponent *component);
    void draw(QPainter *paint);
    void update();
    void update(bool);
    void enterEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void leaveEvent(QEvent *) override;
    void keyPressed(QKeyEvent *event);
    void keyReleased(QKeyEvent *event);
    void setFlag(int value);
    int getFlag();
    void insertImageButton_clicked(QString fileName);
    void insertIcon(QString fileName);
    void setColor(QColor *value);

    TMView *tmView;
    bool lined_page;
    QList<DrawableComponent *> *copiedComponents;

    void setPen_size(int value);

signals:
    void component_added();


private:
    int flag,k,pen_size;
    int start_x,start_y;
    QPointF point1;
    QPointF point2;
    TMFreeHandComponent *freeHand;
    TMLineComponent *line;
    TMCircleComponent *circle;
    TMRectangleComponent *rectangle;
    QColor *color;
    DrawableComponent *selectedComponent;
    QPixmap *canvas_background;
    QPixmap *canvas_frame;
    bool shift_pressed;
};

#endif // CANVAS_H
