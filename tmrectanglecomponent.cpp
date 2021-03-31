#include "tmrectanglecomponent.h"
#include <QPen>
#include <QRectF>
#include <QDebug>
TMRectangleComponent::TMRectangleComponent()
{
    this->selected=false;
    this->resize=false;
    this->name="Rectangle";
}

TMRectangleComponent::TMRectangleComponent(TMRectangleComponent *rect)
{
    this->x=rect->x;
    this->y=rect->y;
    this->height=rect->height;
    this->width=rect->width;
    this->end_x=rect->end_x;
    this->end_y=rect->end_y;
    this->color=rect->color;
    this->pen_size=rect->pen_size;
    this->selected=rect->selected;
    this->name=rect->name;
}

void TMRectangleComponent::draw(QPainter *paint)
{
    QPen penHLines(*color, this->pen_size);
    paint->setPen(penHLines);
    paint->drawRect(x,y,height,width);
    paint->setPen(*new QColor("#282828"));
    if(selected==true)
    {
        int x1,x2,x3,x4,y1,y2,y3,y4;
        if(this->x<=this->end_x)
        {
            x1=this->x;
            x2=this->end_x;
            x3=this->end_x;
            x4=this->x;
        }
        else
        {
            x1=this->end_x;
            x2=this->x;
            x3=this->x;
            x4=this->end_x;
        }
        if(this->y<=this->end_y)
        {
            y1=this->y;
            y2=this->y;
            y3=this->end_y;
            y4=this->end_y;
        }
        else
        {
            y1=this->end_y;
            y2=this->end_y;
            y4=this->y;
            y3=this->y;
        }
        paint->drawRect(x1-2,y1-2,4,4);
        paint->drawRect(x2-2,y2-2,4,4);
        paint->drawRect(x3-2,y3-2,4,4);
        paint->drawRect(x4-2,y4-2,4,4);
    }
}

bool TMRectangleComponent::isYourCoordinate(int x, int y)
{
    this->resize=false;
    int x1,x2,x3,x4,y1,y2,y3,y4;
    if(this->x<=this->end_x)
    {
        x1=this->x;
        x3=this->end_x;
    }
    else
    {
        x1=this->end_x;
        x3=this->x;
    }
    if(this->y<=this->end_y)
    {
        y1=this->y;
        y3=this->end_y;
    }
    else
    {
        y1=this->end_y;
        y3=this->y;
    }
    QRectF rect(this->x,this->y,this->height,this->width);
    if(this->x<=this->end_x)
    {
        x1=this->x;
        x2=this->end_x;
        x3=this->end_x;
        x4=this->x;
    }
    else
    {
        x1=this->end_x;
        x2=this->x;
        x3=this->x;
        x4=this->end_x;
    }
    if(this->y<=this->end_y)
    {
        y1=this->y;
        y2=this->y;
        y3=this->end_y;
        y4=this->end_y;
    }
    else
    {
        y1=this->end_y;
        y2=this->end_y;
        y4=this->y;
        y3=this->y;
    }
    QRectF rect1(x1-2,y1-2,4,4);
    QRectF rect2(x2-2,y2-2,4,4);
    QRectF rect3(x3-2,y3-2,4,4);
    QRectF rect4(x4-2,y4-2,4,4);
    if(rect1.contains(x,y))
    {
        resize=true;
        res_x=x1;
        res_y=y1;
        sel_x=x1;
        sel_y=y1;
    }
    else if(rect2.contains(x,y))
    {
        resize=true;
        res_x=x2;
        res_y=y2;
        sel_x=x2;
        sel_y=y2;
    }
    else if(rect3.contains(x,y))
    {
        resize=true;
        res_x=x3;
        res_y=y3;
        sel_x=x3;
        sel_y=y3;
    }
    else if(rect4.contains(x,y))
    {
        resize=true;
        res_x=x4;
        res_y=y4;
        sel_x=x4;
        sel_y=y4;
    }
    if(resize==true) return true;
    return rect.contains(x,y);
}

void TMRectangleComponent::beSelected(QPainter *paint)
{
    int x1,x2,x3,x4,y1,y2,y3,y4;
    if(this->x<=this->end_x)
    {
        x1=this->x;
        x2=this->end_x;
        x3=this->end_x;
        x4=this->x;
    }
    else
    {
        x1=this->end_x;
        x2=this->x;
        x3=this->x;
        x4=this->end_x;
    }
    if(this->y<=this->end_y)
    {
        y1=this->y;
        y2=this->y;
        y3=this->end_y;
        y4=this->end_y;
    }
    else
    {
        y1=this->end_y;
        y2=this->end_y;
        y4=this->y;
        y3=this->y;
    }
    paint->drawRect(x1-2,y1-2,4,4);
    paint->drawRect(x2-2,y2-2,4,4);
    paint->drawRect(x3-2,y3-2,4,4);
    paint->drawRect(x4-2,y4-2,4,4);
}

bool TMRectangleComponent::getSelected()
{
    return selected;
}

void TMRectangleComponent::setSelected(bool value)
{
    this->proportion=(double)((double)this->width/(double)this->height);
    selected = value;
}

void TMRectangleComponent::dragged(int x, int y,bool proportional)
{
    int temp_x=this->res_x;
    int temp_y=this->res_y;
    if(resize!=true)
    {
        this->x=this->x+x;
        this->y=this->y+y;
        this->end_x=this->end_x+x;
        this->end_y=this->end_y+y;
    }
    else
    {
        //qDebug() << this->proportion;
        if(sel_x==this->x && sel_y==this->y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->height=this->end_x-temp_x;
            this->width=this->end_y-temp_y;
            if(proportional)
            {
                this->height=this->width/this->proportion;
                this->width=this->height*this->proportion;
            }
            this->x=this->end_x-this->height;
            this->y=this->end_y-this->width;
            this->sel_x=this->x;
            this->sel_y=this->y;
        }
        else if(sel_x==this->end_x && sel_y==this->y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->height=temp_x-this->x;
            this->width=this->end_y-temp_y;
            if(proportional)
            {
                this->height=this->width/this->proportion;
                this->width=this->height*this->proportion;
            }
            this->end_x=this->x+this->height;
            this->y=this->end_y-this->width;
            this->sel_x=this->end_x;
            this->sel_y=this->y;
        }
        else if(sel_x==this->end_x && sel_y==this->end_y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->height=temp_x-this->x;
            this->width=temp_y-this->y;
            if(proportional)
            {
                this->height=this->width/this->proportion;
                this->width=this->height*this->proportion;
            }
            this->end_x=this->x+this->height;
            this->end_y=this->y+this->width;
            this->sel_x=this->end_x;
            this->sel_y=this->end_y;
        }
        else if(sel_x==this->x && sel_y==this->end_y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->height=this->end_x-temp_x;
            this->width=temp_y-this->y;
            if(proportional)
            {
                this->height=this->width/this->proportion;
                this->width=this->height*this->proportion;
            }
            this->x=this->end_x-height;
            this->end_y=this->y+width;
            this->sel_x=this->x;
            this->sel_y=this->end_y;
        }
    }
}

QString TMRectangleComponent::toString()
{
    return "Rectangle";
}

QJsonObject TMRectangleComponent::toJson()
{
    QJsonObject &json=*new QJsonObject();
    json["shape"]="Rectangle";
    json["x"]=x;
    json["y"]=y;
    json["height"]=height;
    json["width"]=width;
    json["end_x"]=end_x;
    json["end_y"]=end_y;
    json["color"]=color->name();
    json["pen_size"]=pen_size;
    json["name"]=name;
    return json;
}

void TMRectangleComponent::fromJson(QJsonObject &json)
{
    x=json["x"].toInt();
    y=json["y"].toInt();
    height=json["height"].toInt();
    width=json["width"].toInt();
    end_x=json["end_x"].toInt();
    end_y=json["end_y"].toInt();
    color=new QColor(json["color"].toString());
    pen_size=json["pen_size"].toInt();
    name=json["name"].toString();
}

void TMRectangleComponent::setName(QString name)
{
    this->name=name;
}

QString TMRectangleComponent::getName()
{
    return this->name;
}
