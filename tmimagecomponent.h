#ifndef TMIMAGECOMPONENT_H
#define TMIMAGECOMPONENT_H

#include "drawablecomponent.h"

class TMImageComponent: public DrawableComponent
{
public:
    TMImageComponent();
    TMImageComponent(TMImageComponent *image);
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
    void changeColor();

    QPixmap *image;
    QString path;
    int x,y;
    int end_x,end_y;
    int height,width;
    int res_x,res_y;
    int sel_x,sel_y;
    double proportion;
    QString name;
    QColor *color;
    bool selected;
    bool resize;
};

#endif // TMIMAGECOMPONENT_H
