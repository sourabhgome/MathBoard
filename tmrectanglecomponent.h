#ifndef TMRECTANGLECOMPONENT_H
#define TMRECTANGLECOMPONENT_H

#include "drawablecomponent.h"

class TMRectangleComponent: public DrawableComponent
{
public:
    TMRectangleComponent();
    TMRectangleComponent(TMRectangleComponent *rect);
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

    int x;
    int y;
    int height;
    int width;
    int end_x;
    int end_y;
    int res_x;
    int res_y;
    int sel_x;
    int sel_y;
    QColor *color;
    int pen_size;
    bool selected;
    QString name;
    double proportion;
    bool resize;
};

#endif // TMRECTANGLECOMPONENT_H
