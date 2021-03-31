#include "tmgroupcomponent.h"

#include <QJsonArray>
#include "tmcirclecomponent.h"
#include "tmrectanglecomponent.h"
#include "tmlinecomponent.h"
#include "tmfreehandcomponent.h"

TMGroupComponent::TMGroupComponent()
{
    group=new QList<DrawableComponent *>();
    selected=false;
    this->name="Group";
}

TMGroupComponent::TMGroupComponent(TMGroupComponent *group)
{
    this->group=new QList<DrawableComponent *>();
    for(auto k : *group->group)
    {
        if(k->toString().compare("Rectangle")==0)
        {
            TMRectangleComponent *rect=new TMRectangleComponent((TMRectangleComponent*)k);
            rect->dragged(10,10,false);
            this->group->append(rect);
        }
        else if(k->toString().compare("Circle")==0)
        {
            TMCircleComponent *circle=new TMCircleComponent((TMCircleComponent*)k);
            circle->dragged(10,10,false);
            this->group->append(circle);
        }
        else if(k->toString().compare("Line")==0)
        {
            TMLineComponent *line=new TMLineComponent((TMLineComponent*)k);
            line->dragged(10,10,false);
            this->group->append(line);
        }
        else if(k->toString().compare("Freehand")==0)
        {
            TMFreeHandComponent *freeHand=new TMFreeHandComponent((TMFreeHandComponent*)k);
            freeHand->dragged(10,10,false);
            this->group->append(freeHand);
        }
        else if(k->toString().compare("Group")==0)
        {
            TMGroupComponent *group=new TMGroupComponent((TMGroupComponent*)k);
            group->dragged(10,10,false);
            this->group->append(group);
        }
    }
    this->name=group->name;
    this->selected=group->selected;
}

void TMGroupComponent::draw(QPainter *paint)
{
    for(auto k:*group)
    {
        k->draw(paint);
    }
}

bool TMGroupComponent::isYourCoordinate(int x, int y)
{
    bool flag=false;
    for(auto k: *group)
    {
        flag=k->isYourCoordinate(x,y);
        if(flag==true)
            break;
    }
    return flag;
}

void TMGroupComponent::beSelected(QPainter *)
{

}

void TMGroupComponent::setSelected(bool selected)
{
    this->selected=selected;
    for(auto k : *group)
        k->setSelected(selected);
}

bool TMGroupComponent::getSelected()
{
    return selected;
}

void TMGroupComponent::dragged(int x, int y,bool proportional)
{
    for(auto k : *group)
        k->dragged(x,y,proportional);
}

QString TMGroupComponent::toString()
{
    return "Group";
}

QJsonObject TMGroupComponent::toJson()
{
    QJsonObject json;
    json["shape"]="Group";
    QJsonArray arr;
    for(auto k : *group)
        arr.append(k->toJson());
    json["group"]=arr;
    json["name"]=name;
    return json;
}

void TMGroupComponent::fromJson(QJsonObject &json)
{
    QJsonArray arr=json["group"].toArray();
    QJsonObject temp;
    for(auto k : arr)
    {
        temp=k.toObject();
        if(temp["shape"].toString().compare("Rectangle")==0)
        {
            TMRectangleComponent *rect=new TMRectangleComponent();
            rect->fromJson(temp);
            group->append(rect);
        }
        else if(temp["shape"].toString().compare("Circle")==0)
        {
            TMCircleComponent *circle=new TMCircleComponent();
            circle->fromJson(temp);
            group->append(circle);
        }
        else if(temp["shape"].toString().compare("Line")==0)
        {
            TMLineComponent *line=new TMLineComponent();
            line->fromJson(temp);
            group->append(line);
        }
        else if(temp["shape"].toString().compare("Freehand")==0)
        {
            TMFreeHandComponent *freeHand=new TMFreeHandComponent();
            freeHand->fromJson(temp);
            group->append(freeHand);
        }
        else if(temp["shape"].toString().compare("Group")==0)
        {
            TMGroupComponent *g=new TMGroupComponent();
            g->fromJson(temp);
            group->append(g);
        }
    }
    name=json["name"].toString();
}

void TMGroupComponent::setName(QString name)
{
    this->name=name;
}

QString TMGroupComponent::getName()
{
    return this->name;
}
