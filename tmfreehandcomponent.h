#ifndef TMFREEHANDCOMPONENT_H
#define TMFREEHANDCOMPONENT_H

#include <QVector>
#include <QPointF>
#include "drawablecomponent.h"

class TMFreeHandComponent: public DrawableComponent
{
public:
    TMFreeHandComponent();
    TMFreeHandComponent(TMFreeHandComponent *freeHand);
    void draw(QPainter *paint) override;
    bool isYourCoordinate(int x, int y) override;
    void beSelected(QPainter *) override;
    bool getSelected() override;
    int distance(int x1,int y1, int x2, int y2);
    void setSelected(bool value) override;
    void dragged(int x, int y,bool proportional) override;
    QString toString() override;
    QJsonObject toJson() override;
    void fromJson(QJsonObject &json) override;
    void setName(QString name) override;
    QString getName() override;

    QVector<QPointF> *listOfPoints;
    QColor *color;
    QString name;
    int pen_size;
    bool selected;
};

#endif // TMFREEHANDCOMPONENT_H
