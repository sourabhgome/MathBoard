#include "tmlinecomponent.h"
#include <QDebug>
#include <QPen>
#include <QtMath>

TMLineComponent::TMLineComponent()
{
    this->selected=false;
    this->name="Line";
}

TMLineComponent::TMLineComponent(TMLineComponent *line)
{
    this->point1=*new QPointF(line->point1);
    this->point2=*new QPointF(line->point2);
    this->color=line->color;
    this->pen_size=line->pen_size;
    this->selected=line->selected;
    this->name=line->name;
}

void TMLineComponent::draw(QPainter *paint)
{
    QPen penHLines(*color, this->pen_size);
    paint->setPen(penHLines);
    paint->drawLine(point1,point2);
    paint->setPen(*new QColor("#282828"));
    if(this->selected)
    {
        paint->drawRect(point1.x()-2,point1.y()-2,4,4);
        paint->drawRect(point2.x()-2,point2.y()-2,4,4);
    }
}

bool TMLineComponent::isYourCoordinate(int x, int y)
{
    resize=false;
    res=nullptr;
    QRectF rect1(point1.x()-2,point1.y()-2,4,4);
    QRectF rect2(point2.x()-2,point2.y()-2,4,4);
    if(rect1.contains(x,y))
    {
        resize=true;
        res=&point1;
    }
    else if(rect2.contains(x,y))
    {
        resize=true;
        res=&point2;
    }
    if(resize==true) return true;
    if(distance(point1.x(),point1.y(),x,y)+distance(x,y,point2.x(),point2.y())==distance(point1.x(),point1.y(),point2.x(),point2.y()))
        return true;
    return false;
}


void TMLineComponent::beSelected(QPainter *paint)
{
    paint->drawRect(point1.x()-2,point1.y()-2,4,4);
    paint->drawRect(point2.x()-2,point2.y()-2,4,4);
}

int TMLineComponent::distance(int x1, int y1, int x2, int y2)
{
    return qSqrt(qPow((x1-x2),2)+qPow((y1-y2),2));
}

bool TMLineComponent::getSelected()
{
    return selected;
}

void TMLineComponent::setSelected(bool value)
{
    selected = value;
}

void TMLineComponent::dragged(int x, int y,bool proportional)
{
    if(!resize)
    {
        this->point1.setX(this->point1.x()+x);
        this->point1.setY(this->point1.y()+y);
        this->point2.setX(this->point2.x()+x);
        this->point2.setY(this->point2.y()+y);
    }
    else
    {
        res->setX(res->x()+x);
        res->setY(res->y()+y);
    }
}

QString TMLineComponent::toString()
{
    return "Line";
}

QJsonObject TMLineComponent::toJson()
{
    QJsonObject json=*new QJsonObject();
    json["shape"]="Line";
    json["point1_x"]=point1.x();
    json["point1_y"]=point1.y();
    json["point2_x"]=point2.x();
    json["point2_y"]=point2.y();
    json["color"]=color->name();
    json["pen_size"]=pen_size;
    json["name"]=name;
    return json;
}

void TMLineComponent::fromJson(QJsonObject &json)
{
    point1.setX(json["point1_x"].toInt());
    point1.setY(json["point1_y"].toInt());
    point2.setX(json["point2_x"].toInt());
    point2.setY(json["point2_y"].toInt());
    color=new QColor(json["color"].toString());
    pen_size=json["pen_size"].toInt();
    name=json["name"].toString();
}

void TMLineComponent::setName(QString name)
{
    this->name=name;
}

QString TMLineComponent::getName()
{
    return this->name;
}
