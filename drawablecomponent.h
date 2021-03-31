#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include <QJsonObject>
#include<QPainter>

class DrawableComponent
{
public:
    virtual void draw(QPainter *paint)=0;
    virtual bool isYourCoordinate(int x,int y)=0;
    virtual void beSelected(QPainter *)=0;
    virtual void setSelected(bool selected)=0;
    virtual bool getSelected()=0;
    virtual void dragged(int x,int y,bool proportional)=0;
    virtual QString toString()=0;
    virtual void setName(QString name)=0;
    virtual QString getName()=0;
    virtual QJsonObject toJson()=0;
    virtual void fromJson(QJsonObject &json)=0;
};

#endif // DRAWABLECOMPONENT_H
