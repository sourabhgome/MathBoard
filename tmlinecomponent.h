#ifndef TMLINECOMPONENT_H
#define TMLINECOMPONENT_H

#include <QPointF>
#include "drawablecomponent.h"

class TMLineComponent: public DrawableComponent
{
public:
    TMLineComponent();
    TMLineComponent(TMLineComponent *line);
    void draw(QPainter *paint) override;
    bool isYourCoordinate(int x, int y) override;
    void beSelected(QPainter *) override;
    int distance(int x1,int y1, int x2, int y2);
    bool getSelected() override;
    void setSelected(bool value) override;
    void dragged(int x, int y,bool proportional) override;
    QString toString() override;
    QJsonObject toJson() override;
    void fromJson(QJsonObject &json) override;
    void setName(QString name) override;
    QString getName() override;

    QPointF point1;
    QPointF point2;
    QPointF *res;
    QColor *color;
    int pen_size;
    QString name;
    bool selected;
    bool resize;
};

#endif // TMLINECOMPONENT_H
