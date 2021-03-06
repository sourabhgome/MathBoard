#include "tmimagecomponent.h"
#include <QDebug>

TMImageComponent::TMImageComponent()
{
    selected=false;
    resize=false;
    x=10;
    y=10;
    width=0;
    height=0;
    this->name="Image";
    this->color=nullptr;
}

TMImageComponent::TMImageComponent(TMImageComponent *image)
{
    this->image=new QPixmap(image->path);
    this->path=image->path;
    this->x=image->x;
    this->y=image->y;
    this->height=image->height;
    this->width=image->width;
    this->end_x=image->end_x;
    this->end_y=image->end_y;
    this->selected=image->selected;
    this->name=image->name;
    if(image->color!=nullptr)
    {
        this->color=new QColor(image->color->name());
        changeColor();
    }
    else
        this->color=nullptr;
}

void TMImageComponent::draw(QPainter *paint)
{
    paint->drawPixmap(x,y,width,height,*image);
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

bool TMImageComponent::isYourCoordinate(int x, int y)
{
    resize=false;
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
    QRectF rect(this->x,this->y,width,height);
    return rect.contains(x,y);
}

void TMImageComponent::beSelected(QPainter *)
{

}

void TMImageComponent::setSelected(bool selected)
{
    this->proportion=(double)((double)this->width/(double)this->height);
    this->selected=selected;
}

bool TMImageComponent::getSelected()
{
    return selected;
}

void TMImageComponent::dragged(int x, int y, bool proportional)
{
    int temp_x=res_x;
    int temp_y=res_y;
    if(!resize)
    {
        this->x=this->x+x;
        this->y=this->y+y;
        this->end_x=this->end_x+x;
        this->end_y=this->end_y+y;
    }
    else
    {
        if(this->end_x > this->x+5 && this->end_y > this->y+5)
        {
        if(sel_x==this->x && sel_y==this->y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->width=this->end_x-temp_x;
            this->height=this->end_y-temp_y;
            if(proportional)
            {
                this->width=this->height*this->proportion;
                this->height=this->width/this->proportion;
            }
            this->x=this->end_x-this->width;
            this->y=this->end_y-this->height;
            this->sel_x=this->x;
            this->sel_y=this->y;
        }
        else if(sel_x==this->end_x && sel_y==this->y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->width=temp_x-this->x;
            this->height=this->end_y-temp_y;
            if(proportional)
            {
                this->width=this->height*this->proportion;
                this->height=this->width/this->proportion;
            }
            this->end_x=this->x+this->width;
            this->y=this->end_y-this->height;
            this->sel_x=this->end_x;
            this->sel_y=this->y;
        }
        else if(sel_x==this->end_x && sel_y==this->end_y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->width=temp_x-this->x;
            this->height=temp_y-this->y;
            if(proportional)
            {
                this->width=this->height*this->proportion;
                this->height=this->width/this->proportion;
            }
            this->end_x=this->x+this->width;
            this->end_y=this->y+this->height;
            this->sel_x=this->end_x;
            this->sel_y=this->end_y;
        }
        else if(sel_x==this->x && sel_y==this->end_y)
        {
            temp_x+=x;
            temp_y+=y;
            res_x=temp_x;
            res_y=temp_y;
            this->width=this->end_x-temp_x;
            this->height=temp_y-this->y;
            if(proportional)
            {
                this->width=this->height*this->proportion;
                this->height=this->width/this->proportion;
            }
            this->x=this->end_x-width;
            this->end_y=this->y+height;
            this->sel_x=this->x;
            this->sel_y=this->end_y;
        }
        }
    }
}

QString TMImageComponent::toString()
{
    return "Image";
}

QJsonObject TMImageComponent::toJson()
{
    QJsonObject &json=*new QJsonObject();
    json["shape"]="Image";
    json["image"]=path;
    json["x"]=x;
    json["y"]=y;
    json["height"]=height;
    json["width"]=width;
    json["end_x"]=end_x;
    json["end_y"]=end_y;
    if(color!=nullptr)
    json["color"]=color->name();
    json["name"]=name;
    return json;
}

void TMImageComponent::fromJson(QJsonObject &json)
{
    image=new QPixmap(json["image"].toString());
    x=json["x"].toInt();
    y=json["y"].toInt();
    height=json["height"].toInt();
    width=json["width"].toInt();
    end_x=json["end_x"].toInt();
    end_y=json["end_y"].toInt();
    name=json["name"].toString();
    if(json["color"].isNull()==false)
    color=new QColor(json["color"].toString());
    changeColor();
}

void TMImageComponent::setName(QString name)
{
    this->name=name;
}

QString TMImageComponent::getName()
{
    return this->name;
}

void TMImageComponent::changeColor()
{
    QImage tmp = image->toImage();
    QPixmap *temp=nullptr;
    if(name.compare("Icon")==0)
    {
        for(int y = 0; y < tmp.height(); y++)
            for(int x= 0; x < tmp.width(); x++)
            {
                color->setAlpha(tmp.pixelColor(x,y).alpha());
                tmp.setPixelColor(x,y,*color);
            }
    temp=new QPixmap(QPixmap::fromImage(tmp));
    }
    if(temp!=nullptr)
        this->image=temp;
}
