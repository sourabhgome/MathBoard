#include "tmcirclecomponent.h"
#include <QPen>
#include <QtMath>
#include <QDebug>
TMCircleComponent::TMCircleComponent()
{
    this->selected=false;
    this->resize=false;
    this->name="Circle";
}

TMCircleComponent::TMCircleComponent(TMCircleComponent *circle)
{
    this->center=*new QPointF(circle->center);
    this->radius_x=circle->radius_x;
    this->radius_y=circle->radius_y;
    this->color=circle->color;
    this->pen_size=circle->pen_size;
    this->selected=circle->selected;
    this->name=circle->name;
}

void TMCircleComponent::draw(QPainter *paint)
{
    QPen penHLines(*color, this->pen_size);
    paint->setPen(penHLines);
    paint->drawEllipse(this->center,this->radius_x,this->radius_x);
    paint->setPen(*new QColor("#282828"));
    if(this->selected==true)
    {
        paint->drawRect(this->center.rx()+radius_x-2,this->center.ry()+2,4,4);
        paint->drawRect(this->center.rx()-radius_x-2,this->center.ry()+2,4,4);
        paint->drawRect(this->center.rx()-2,this->center.ry()+radius_x-2,4,4);
        paint->drawRect(this->center.rx()-2,this->center.ry()-radius_x-2,4,4);
    }
}

bool TMCircleComponent::isYourCoordinate(int x, int y)
{
    this->resize=false;
    QRectF rect1(this->center.rx()+radius_x-2,this->center.ry()+2,4,4);
    QRectF rect2(this->center.rx()-radius_x-2,this->center.ry()+2,4,4);
    QRectF rect3(this->center.rx()-2,this->center.ry()+radius_x-2,4,4);
    QRectF rect4(this->center.rx()-2,this->center.ry()-radius_x-2,4,4);
    if(rect1.contains(x,y))
    {
        res_x=x;
        res_y=y;
        resize=true;
    }
    else if(rect2.contains(x,y))
    {
        res_x=x;
        res_y=y;
        resize=true;
    }
    else if(rect3.contains(x,y))
    {
        res_x=x;
        res_y=y;
        resize=true;
    }
    else if(rect4.contains(x,y))
    {
        res_x=x;
        res_y=y;
        resize=true;
    }
    if(resize==true) return true;
    int h=this->center.rx();
    int k=this->center.ry();
    int a=this->radius_x;
    int b=this->radius_x;
    int p = (qPow((x - h), 2) / qPow(a, 2)) + (qPow((y - k), 2) / qPow(b, 2));
    if(p<1)
    {
        return true;
    }
    return false;
}

void TMCircleComponent::beSelected(QPainter *paint)
{
    paint->setPen(*new QColor("blue"));
    paint->drawRect(this->center.rx()+radius_x-2,this->center.ry()+2,4,4);
    paint->drawRect(this->center.rx()-radius_x-2,this->center.ry()+2,4,4);
    paint->drawRect(this->center.rx()-2,this->center.ry()+radius_x-2,4,4);
    paint->drawRect(this->center.rx()+2,this->center.ry()-radius_x-2,4,4);
}

bool TMCircleComponent::getSelected()
{
    return selected;
}

void TMCircleComponent::setSelected(bool value)
{
    selected = value;
}

void TMCircleComponent::dragged(int x, int y,bool proportional)
{
    if(resize!=true)
    {
        this->center.setX(this->center.x()+x);
        this->center.setY(this->center.y()+y);
    }
    else
    {
//        if(qFabs(x)<qFabs(y)) this->radius_x+=y;
//        else this->radius_x+=x;
        //qDebug() << this->center.x();
        //qDebug() << res_x;
        if(this->center.x() == res_x)
        {
            if(this->center.y() >= res_y)
            {
                this->radius_x=this->radius_x+y;
                res_y=res_y+y;
            }
            else
            {
                this->radius_x=this->radius_x-y;
                res_y=res_y-y;
            }
        }
        else
        {
            if(this->center.x() >= res_x)
            {
                this->radius_x=this->radius_x+x;
                res_x=res_x+x;
            }
            else
            {
                this->radius_x=this->radius_x-x;
                res_x=res_x-x;
            }
        }
    }
}

QString TMCircleComponent::toString()
{
    return "Circle";
}

QJsonObject TMCircleComponent::toJson()
{
    QJsonObject json=*new QJsonObject();
    json["shape"]="Circle";
    json["center_x"]=center.x();
    json["center_y"]=center.y();
    json["radius_x"]=radius_x;
    json["radius_y"]=radius_y;
    json["color"]=color->name();
    json["pen_size"]=pen_size;
    json["name"]=name;
    return json;
}

void TMCircleComponent::fromJson(QJsonObject &json)
{
    center.setX(json["center_x"].toInt());
    center.setY(json["center_y"].toInt());
    radius_x=json["radius_x"].toInt();
    radius_y=json["radius_y"].toInt();
    color=new QColor(json["color"].toString());
    pen_size=json["pen_size"].toInt();
    name=json["name"].toString();
}

void TMCircleComponent::setName(QString name)
{
    this->name=name;
}

QString TMCircleComponent::getName()
{
    return this->name;
}
