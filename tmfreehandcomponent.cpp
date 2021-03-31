#include "tmfreehandcomponent.h"
#include <QPointF>
#include <QVector>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QJsonArray>
#include <QDebug>

TMFreeHandComponent::TMFreeHandComponent()
{
    listOfPoints=new QVector<QPointF>();
    this->selected=false;
    this->name="Freehand";
}

TMFreeHandComponent::TMFreeHandComponent(TMFreeHandComponent *freeHand)
{
    this->listOfPoints=new QVector<QPointF>(*freeHand->listOfPoints);
    this->color=freeHand->color;
    this->pen_size=freeHand->pen_size;
    this->selected=freeHand->selected;
    this->name=freeHand->name;
}

void TMFreeHandComponent::draw(QPainter *paint)
{
    QPen penHLines(*color, this->pen_size);
    paint->setPen(penHLines);
    int i=0;
    for(i=0;i<listOfPoints->length()-1;i++)
        paint->drawLine(listOfPoints->at(i),listOfPoints->at(i+1));
    paint->setPen(*new QColor("#282828"));
    if(selected==true)
    {
        i=0;
        for(i=0;i<listOfPoints->length();i=i+5)
            paint->drawRect(listOfPoints->at(i).x()-2,listOfPoints->at(i).y()-2,4,4);
        paint->drawRect(listOfPoints->at(listOfPoints->length()-1).x()-2,listOfPoints->at(listOfPoints->length()-1).y()-2,4,4);
    }
}

bool TMFreeHandComponent::isYourCoordinate(int x, int y)
{
    /*for(auto p:*listOfPoints)
    {
        if(( p.x()-x >=-5 && p.x()-x<=5 ) && ( p.y()-y >=-5 && p.y()-y<=5 ))
            return true;
    }*/
    int i=0;
    for(i=0;i<listOfPoints->length()-1;i++)
        if(distance(listOfPoints->at(i).x(),listOfPoints->at(i).y(),x,y)+distance(x,y,listOfPoints->at(i+1).x(),listOfPoints->at(i+1).y())==distance(listOfPoints->at(i).x(),listOfPoints->at(i).y(),listOfPoints->at(i+1).x(),listOfPoints->at(i+1).y()))
            return true;
    return false;
}

void TMFreeHandComponent::beSelected(QPainter *)
{

}

bool TMFreeHandComponent::getSelected()
{
    return selected;
}

int TMFreeHandComponent::distance(int x1, int y1, int x2, int y2)
{
    return qSqrt(qPow((x1-x2),2)+qPow((y1-y2),2));
}

void TMFreeHandComponent::setSelected(bool value)
{
    selected = value;
}

void TMFreeHandComponent::dragged(int x, int y,bool proportional)
{
    int i=0;
    QPointF p;
    for(i=0;i<listOfPoints->length();i++)
    {
        p=listOfPoints->at(i);
        p.setX(p.x()+x);
        p.setY(p.y()+y);
        listOfPoints->replace(i,p);
    }
}

QString TMFreeHandComponent::toString()
{
    return "Freehand";
}

QJsonObject TMFreeHandComponent::toJson()
{
    QJsonObject json=*new QJsonObject();
    json["shape"]="Freehand";
    int i=0;
    QJsonArray arr=*new QJsonArray();
    for(auto k:*listOfPoints)
    {
        arr.append(k.x());
        arr.append(k.y());
        //json[QString::number(i)+"x_point"]=k.x();
        //json[QString::number(i)+"x_point"]=k.x();
        i++;
    }
    json["points"]=arr;
    json["color"]=color->name();
    json["pen_size"]=pen_size;
    json["name"]=name;
    return json;
}

void TMFreeHandComponent::fromJson(QJsonObject &json)
{
    QJsonArray arr=*new QJsonArray(json["points"].toArray());
    QPointF *point;
    int i=0;
    while(i<arr.size())
    {
        point=new QPointF();
        point->setX(arr[i].toInt());
        point->setY(arr[i+1].toInt());
        listOfPoints->append(*point);
        i=i+2;
    }
    color=new QColor(json["color"].toString());
    pen_size=json["pen_size"].toInt();
    name=json["name"].toString();
}

void TMFreeHandComponent::setName(QString name)
{
    this->name=name;
}

QString TMFreeHandComponent::getName()
{
    return this->name;
}
