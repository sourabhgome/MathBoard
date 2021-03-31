#ifndef TMCIRCLECOMPONENT_H
#define TMCIRCLECOMPONENT_H

#include "drawablecomponent.h"
#include <QPointF>

class TMCircleComponent: public DrawableComponent
{
public:
    TMCircleComponent();
    TMCircleComponent(TMCircleComponent *circle);
    void draw(QPainter *paint) override;
    bool isYourCoordinate(int x, int y) override;
    void beSelected(QPainter *) override;
    bool getSelected() override;
    void setSelected(bool value) override;
    void dragged(int x, int y,bool proportional) override;
    QString toString() override;
    QJsonObject toJson() override;
    void fromJson(QJsonObject &json) override;
    void setName(QString name) override;
    QString getName() override;

    QPointF center;
    qreal radius_x;
    qreal radius_y;
    int res_x,res_y;
    QColor *color;
    int pen_size;
    QString name;
    bool selected;
    bool resize;
};

#endif // TMCIRCLECOMPONENT_H
