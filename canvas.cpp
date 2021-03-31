#include "canvas.h"
#include "tmview.h"
#include "tmfreehandcomponent.h"
#include "tmimagecomponent.h"
#include <QMouseEvent>
#include <QPen>
#include <QPixmap>
#include <QDebug>
#include <QtMath>

Canvas::Canvas(QWidget *parent) : QFrame(parent)
{
    tmView=new TMView();
    circle=nullptr;
    line=nullptr;
    freeHand=nullptr;
    rectangle=nullptr;
    this->k=0;
    color=new QColor("#000000");
    selectedComponent=nullptr;
    flag=0;
    this->start_x=0;
    this->start_y=0;
    this->pen_size=1;
    this->lined_page=true;
    this->canvas_background=new QPixmap("c:/qteg/Painter/images/canvas_background.jpg");
    this->copiedComponents=new QList<DrawableComponent*>();
    //this->canvas_background=new QPixmap("c:/qteg/Painter/images/logo.png");
}
void Canvas::paintEvent(QPaintEvent *e)
{
    QPainter *paint=new QPainter(this);
    //paint->eraseRect(this->rect());
    QPen penHLines(QColor("#dddddd"), 0);
    paint->setPen(penHLines);
    if(lined_page==true)
    {
        //paint->drawPixmap(this->rect(),*canvas_background);
        int i=1;
        while(i<this->rect().height())
        {
            if(i%30==0) paint->drawLine(*new QPoint(30,i),*new QPoint(this->rect().width()-30,i));
            i++;
        }
    }
    //paint->drawLine(*new QPoint(0,50),*new QPoint(this->rect().width(),50));
    //paint->drawPixmap(this->rect().x()+735,this->rect().y()+10,70,70,*canvas_background);
    tmView->setQPainter(paint);
    tmView->draw();
    if(circle!=nullptr) tmView->temporaryDraw(flag,circle);
    else if(line!=nullptr) tmView->temporaryDraw(flag,line);
    else if(freeHand!=nullptr) tmView->temporaryDraw(flag,freeHand);
    else if(rectangle!=nullptr) tmView->temporaryDraw(flag,rectangle);
    /*if(flag==5 and selectedComponent!=nullptr)
    {
        tmView->selectComponent(selectedComponent);
        this->selectedComponent=nullptr;
    }*/
    paint->end();
    delete paint;
    QFrame::paintEvent(e);
}

void Canvas::draw(QPainter *paint)
{
    paint->drawEllipse(10,10,110,110); //Just to test
}

void Canvas::update()
{
    QWidget::update();
    emit component_added();
}

void Canvas::update(bool)
{
    QWidget::update();
}

void Canvas::enterEvent(QEvent *)
{
    QWidget::setCursor(Qt::ForbiddenCursor);
    if(flag!=0)
    {
        QPixmap cursor_pixmap = QPixmap("c:\\qteg\\Painter\\images\\pencil_cursor1.png");
        QCursor cursor_default = QCursor(cursor_pixmap.scaled(32,32), 0, 0);
        QWidget::setCursor(cursor_default);
    }
    if(flag==5) QWidget::setCursor(Qt::PointingHandCursor);
}


void Canvas::add(DrawableComponent *component)
{
    tmView->add(component);
    QWidget::update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(flag==1)
    {
        circle=new TMCircleComponent();
        circle->center=event->localPos();
        circle->color=color;
        circle->pen_size=this->pen_size;
    }
    else if(flag==2)
    {
        line=new TMLineComponent();
        line->point1=event->localPos();
        line->color=color;
        line->pen_size=this->pen_size;
    }
    else if(flag==3)
    {
        freeHand=new TMFreeHandComponent();
        freeHand->color=color;
        freeHand->pen_size=this->pen_size;
    }
    else if(flag==4)
    {
        rectangle=new TMRectangleComponent();
        rectangle->x=event->localPos().x();
        rectangle->y=event->localPos().y();
        rectangle->color=color;
        rectangle->pen_size=this->pen_size;
    }
    if(flag==5)
    {
        tmView->processClick(event->localPos().x(),event->localPos().y());
        start_x=event->pos().rx();
        start_y=event->pos().ry();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    k++;
    if(flag==1) //for circle
    {
        circle->radius_x=circle->center.rx()-event->pos().rx();
    }
    else if(flag==2) //for line
    {
        line->point2=event->localPos();
        if(shift_pressed)
        {
            if(qFabs(event->localPos().x()-line->point1.x())<qFabs(event->localPos().y()-line->point1.y()))
            {
                line->point2.setX(line->point1.x());
                line->point2.setY(event->localPos().y());
            }
            else if(qFabs(event->localPos().x()-line->point1.x())>qFabs(event->localPos().y()-line->point1.y()))
            {
                line->point2.setX(event->localPos().x());
                line->point2.setY(line->point1.y());
            }
            else
            {
                line->point2=event->localPos();
            }
        }
    }
    else if(flag==3) //for freehand
    {
        QPointF point=event->localPos();
        freeHand->listOfPoints->append(point);
    }
    else if(flag==4)
    {
        int w=rectangle->y-event->localPos().y();
        int h=rectangle->x-event->localPos().x();
        if(shift_pressed==true)
        {
            if(h<w)
            {
                rectangle->height=-h;
                rectangle->width=-h;
            }
            else
            {
                rectangle->height=-w;
                rectangle->width=-w;
            }
        }
        else
        {
            rectangle->height=-h;
            rectangle->width=-w;
        }
    }
    else if(flag==5)
    {
        selectedComponent=tmView->getSelectedComponent();
        int x=event->localPos().x()-start_x;
        int y=event->localPos().y()-start_y;
        if(selectedComponent!=nullptr)
        {
            selectedComponent->dragged(x,y,shift_pressed);
        }
        start_x=event->localPos().x();
        start_y=event->localPos().y();
    }
    QWidget::update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(flag==1)
    {
        tmView->add(circle);
        circle=nullptr;
    }
    else if(flag==2)
    {
        tmView->add(line);
        line=nullptr;
    }
    else if(flag==3)
    {
        if(freeHand->listOfPoints->size()>1)
        tmView->add(freeHand);
        freeHand=nullptr;
    }
    else if(flag==4)
    {
        //rectangle->end_x=event->localPos().x();
        //rectangle->end_y=event->localPos().y();
        rectangle->end_x=rectangle->x+rectangle->height;
        rectangle->end_y=rectangle->y+rectangle->width;
        tmView->add(rectangle);
        rectangle=nullptr;
    }
    else if(flag==5)
    {
        tmView->processClick(event->localPos().x(),event->localPos().y());
    }
    emit component_added();
    QWidget::update();
}

void Canvas::leaveEvent(QEvent *)
{

}

void Canvas::keyPressed(QKeyEvent *event)
{
    if(event->key()==16777249)
        this->tmView->multipleSelection=true;
    if(event->key()==16777248)
        this->shift_pressed=true;
}

void Canvas::keyReleased(QKeyEvent *event)
{
    this->tmView->multipleSelection=false;
    this->shift_pressed=false;
}

void Canvas::setFlag(int value)
{
    flag = value;
}

int Canvas::getFlag()
{
    return this->flag;
}

void Canvas::insertImageButton_clicked(QString fileName)
{
    TMImageComponent *image=new TMImageComponent();
    image->image=new QPixmap(fileName);
    image->path=fileName;
    if(image->image->rect().height()>450 || image->image->rect().width()>790)
    {
        double ratio=image->image->rect().width()/image->image->rect().height();
        if(image->image->rect().width()>790 && image->image->rect().height()<=450)
        {
            image->width=790/ratio;
            image->height=790*ratio;
        }
        else if(image->image->rect().height()>450 && image->image->rect().width()<=790)
        {
            image->width=450/ratio;
            image->height=450*ratio;
        }
        else
        {
            image->width=790/ratio;
            image->height=450*ratio;
        }
    }
    else
    {
        image->width=image->image->rect().width();
        image->height=image->image->rect().height();
    }
    image->end_x=image->x+image->width;
    image->end_y=image->y+image->height;
    this->tmView->list->append(image);
    QWidget::update();
}

void Canvas::insertIcon(QString fileName)
{
    TMImageComponent *image=new TMImageComponent();
    image->x=100;
    image->y=100;
    image->image=new QPixmap(fileName);
    image->path=fileName;
    image->width=40;
    image->height=40;
    //image->image->rect().setHeight(40);
    //image->image->rect().setWidth(40);
    image->end_x=image->x+image->width;
    image->end_y=image->y+image->height;
    image->name="Icon";
    image->color=new QColor(color->name());
    image->changeColor();
    this->tmView->list->append(image);
    QWidget::update();
}

void Canvas::setColor(QColor *value)
{
    color = value;
}

void Canvas::setPen_size(int value)
{
    pen_size = value;
}
