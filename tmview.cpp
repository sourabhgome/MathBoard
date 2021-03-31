#include "tmview.h"
#include "tmfreehandcomponent.h"

#include <QVector>
#include <QPointF>

TMView::TMView()
{
    list=new QList<DrawableComponent *>();
    deletedElementList=new QList<DrawableComponent *>();
    redoList=new QList<DrawableComponent *>();
    selectedComponent=nullptr;
    multipleSelection=false;
}
void TMView::add(DrawableComponent *component)
{
    list->append(component);
    draw();
}

void TMView::setQPainter(QPainter *paint)
{
    this->paint=paint;
}

void TMView::draw()
{
    for(auto k:*list)
    {
        k->draw(this->paint);
    }
}

void TMView::temporaryDraw(int flag, DrawableComponent *component)
{
    component->draw(paint);
}

void TMView::selectComponent(DrawableComponent *component)
{
    component->beSelected(paint);
}

void TMView::processClick(int x, int y)
{
    if(multipleSelection==false) deselectAll();
    int i=list->size()-1;
    for(;i>=0;i--)
    {
        auto element=list->at(i);
        bool ans=element->isYourCoordinate(x,y);
        if(ans)
        {
            element->setSelected(true);
            this->selectedComponent=element;
            if(multipleSelection==false)
            {
                break;
            }
        }
    }
}

void TMView::deselectAll()
{
    if(selectedComponent!=nullptr)
    {
        selectedComponent->setSelected(false);
        selectedComponent=nullptr;
    }
    for(auto element: *(list)) element->setSelected(false);
}

void TMView::setSelectedComponent(DrawableComponent *value)
{
    if(multipleSelection==false) deselectAll();
    selectedComponent = value;
    selectedComponent->setSelected(true);
}

DrawableComponent* TMView::getSelectedComponent()
{
    return this->selectedComponent;
}
