#ifndef TMVIEW_H
#define TMVIEW_H

#include <QList>
#include <QPainter>
#include "drawablecomponent.h"
class TMView
{
public:
    TMView();
    void add(DrawableComponent *component);
    void draw();
    void setQPainter(QPainter *paint);
    void temporaryDraw(int, DrawableComponent *);
    void selectComponent(DrawableComponent *);
    void processClick(int x,int y);
    void deselectAll();
    void setSelectedComponent(DrawableComponent *value);
    DrawableComponent* getSelectedComponent();

public:
    QList<DrawableComponent *> *list;
    QList<DrawableComponent *> *deletedElementList;
    QList<DrawableComponent *> *redoList;
    QPainter *paint;
    DrawableComponent *selectedComponent;
    bool multipleSelection;
};

#endif // TMVIEW_H
