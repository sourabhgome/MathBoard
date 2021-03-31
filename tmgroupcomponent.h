#ifndef TMGROUPCOMPONENT_H
#define TMGROUPCOMPONENT_H

#include "drawablecomponent.h"

class TMGroupComponent : public DrawableComponent
{
public:
    TMGroupComponent();
    TMGroupComponent(TMGroupComponent *group);
    void draw(QPainter *paint) override;
    bool isYourCoordinate(int x,int y) override;
    void beSelected(QPainter *) override;
    void setSelected(bool selected) override;
    bool getSelected() override;
    void dragged(int x,int y,bool proportional) override;
    QString toString() override;
    QJsonObject toJson() override;
    void fromJson(QJsonObject &json) override;
    void setName(QString name) override;
    QString getName() override;

    QList<DrawableComponent *> *group;
    QString name;
    bool selected;
};

#endif // TMGROUPCOMPONENT_H
