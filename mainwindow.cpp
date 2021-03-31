#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QIcon>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QtWidgets>
#include <QFileDialog>
#include <QtCore>
#include <QTimer>
#include <QAbstractItemView>
#include "tmgroupcomponent.h"
#include "tmimagecomponent.h"

#include "canvas.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initView();
    this->setWindowTitle("Math Board");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.8);
    connect(ui->frame, SIGNAL(component_added()), this, SLOT(component_added()));
    this->flag=0;
    this->backgroundColor=*new QColor("white");
    this->foregroundColor=*new QColor("black");
    buttons=new QList<QPushButton *>();
    buttons->append(this->ui->drawLineButton);
    buttons->append(this->ui->drawCircleButton);
    buttons->append(this->ui->drawRectangleButton);
    buttons->append(this->ui->drawFreeHandButton);
    buttons->append(this->ui->pickComponentButton);
    buttons->append(this->ui->iconsPanelButton);
    slides=new QList<TMView *>();
    slides->append(this->ui->frame->tmView);
    this->selectedSlide=slides->at(0);
    initialiseSlidesList();
    initialiseIconsList();
    this->ui->slidesList->setParent(this);
    this->ui->iconsPanel->setParent(this);
    this->ui->slidesList->setGeometry(1223,50,20,688);
    this->ui->iconsPanel->setGeometry(105,30,this->ui->iconsPanel->rect().width(),this->ui->iconsPanel->rect().height());
    this->ui->stopRecordingButton->setDisabled(true);
    this->ui->stopRecordingButton->hide();
    this->ui->stopRecordingButton->setGeometry(this->ui->startRecordingButton->geometry());
    process=new QProcess();
    /*buttons->append(this->ui->saveButton);
    buttons->append(this->ui->openButton);
    buttons->append(this->ui->deleteButton);
    buttons->append(this->ui->redoButton);
    buttons->append(this->ui->undoButton);
    buttons->append(this->ui->groupComponentsButton);
    buttons->append(this->ui->ungroupComponentsButton);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initView()
{
    QPixmap *icon;
    QIcon *qIcon;
    this->ui->iconsPanel->hide();
    icon=new QPixmap("c:\\qteg\\Painter\\images\\circle_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->drawCircleButton->setIcon(*qIcon);
    this->ui->drawCircleButton->setIconSize(QSize(20,20));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\line_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->drawLineButton->setIcon(*qIcon);
    this->ui->drawLineButton->setIconSize(QSize(20,20));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\pencil_cursor.png");
    qIcon=new QIcon(*icon);
    this->ui->drawFreeHandButton->setIcon(*qIcon);
    this->ui->drawFreeHandButton->setIconSize(QSize(20,20));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\square_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->drawRectangleButton->setIcon(*qIcon);
    this->ui->drawRectangleButton->setIconSize(QSize(20,20));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\pick_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->pickComponentButton->setIcon(*qIcon);
    this->ui->pickComponentButton->setIconSize(QSize(20,20));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\save_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->saveButton->setIcon(*qIcon);
    this->ui->saveButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\open_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->openButton->setIcon(*qIcon);
    this->ui->openButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\delete_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->deleteButton->setIcon(*qIcon);
    this->ui->deleteButton->setIconSize(QSize(40,40));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\undo_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->undoButton->setIcon(*qIcon);
    this->ui->undoButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\redo_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->redoButton->setIcon(*qIcon);
    this->ui->redoButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\group_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->groupComponentsButton->setIcon(*qIcon);
    this->ui->groupComponentsButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\ungroup_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->ungroupComponentsButton->setIcon(*qIcon);
    this->ui->ungroupComponentsButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\plane_page_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->clearPageButton->setIcon(*qIcon);
    this->ui->clearPageButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\lined_page_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->linedPageButton->setIcon(*qIcon);
    this->ui->linedPageButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\new_slide_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->addNewSlideButton->setIcon(*qIcon);
    this->ui->addNewSlideButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\delete_slide_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->deleteCurrentSlideButton->setIcon(*qIcon);
    this->ui->deleteCurrentSlideButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\copy_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->copyComponentsButton->setIcon(*qIcon);
    this->ui->copyComponentsButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\paste_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->pasteComponentsButton->setIcon(*qIcon);
    this->ui->pasteComponentsButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\insert_image_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->insertImageButton->setIcon(*qIcon);
    this->ui->insertImageButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\insert_icon_icon.png");
    qIcon=new QIcon(*icon);
    this->ui->iconsPanelButton->setIcon(*qIcon);
    this->ui->iconsPanelButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\startRecording.png");
    qIcon=new QIcon(*icon);
    this->ui->startRecordingButton->setIcon(*qIcon);
    this->ui->startRecordingButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\stopRecording.png");
    qIcon=new QIcon(*icon);
    this->ui->stopRecordingButton->setIcon(*qIcon);
    this->ui->stopRecordingButton->setIconSize(QSize(25,25));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\png\\80.png");
    qIcon=new QIcon(*icon);
    this->ui->minimizeButton->setIcon(*qIcon);
    this->ui->minimizeButton->setIconSize(QSize(20,20));
    icon=new QPixmap("c:\\qteg\\Painter\\images\\png\\81.png");
    qIcon=new QIcon(*icon);
    this->ui->closeButton->setIcon(*qIcon);
    this->ui->closeButton->setIconSize(QSize(20,20));
}

void MainWindow::on_drawCircleButton_clicked()
{
    this->ui->frame->setFlag(1);
    for(auto k:*buttons) k->setStyleSheet("QPushButton#"+k->objectName()+":hover{background-color:#282828;color:white;}QPushButton#"+k->objectName()+"{background:transparent;color:white;border:none;}QToolTip{background:#282828;color:#dddddd;}");
    this->ui->drawCircleButton->setStyleSheet("background:#282828;color:#dddddd;");
    this->ui->frame->tmView->deselectAll();
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_drawLineButton_clicked()
{
    this->ui->frame->setFlag(2);
    for(auto k:*buttons) k->setStyleSheet("QPushButton#"+k->objectName()+":hover{background-color:#282828;color:white;}QPushButton#"+k->objectName()+"{background:transparent;color:white;border:none;}QToolTip{background:#282828;color:#dddddd;}");
    this->ui->drawLineButton->setStyleSheet("background:#282828;color:#dddddd;");
    this->ui->frame->tmView->deselectAll();
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_drawFreeHandButton_clicked()
{
    this->ui->frame->setFlag(3);
    for(auto k:*buttons) k->setStyleSheet("QPushButton#"+k->objectName()+":hover{background-color:#282828;color:white;}QPushButton#"+k->objectName()+"{background:transparent;color:white;border:none;}QToolTip{background:#282828;color:#dddddd;}");
    this->ui->drawFreeHandButton->setStyleSheet("background:#282828;color:#dddddd;");
    this->ui->frame->tmView->deselectAll();
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_drawRectangleButton_clicked()
{
    this->ui->frame->setFlag(4);
    for(auto k:*buttons) k->setStyleSheet("QPushButton#"+k->objectName()+":hover{background-color:#282828;color:white;}QPushButton#"+k->objectName()+"{background:transparent;color:white;border:none;}QToolTip{background:#282828;color:#dddddd;}");
    this->ui->drawRectangleButton->setStyleSheet("background:#282828;color:#dddddd;");
    this->ui->frame->tmView->deselectAll();
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_pickComponentButton_clicked()
{
    this->ui->frame->setFlag(5);
    for(auto k:*buttons) k->setStyleSheet("QPushButton#"+k->objectName()+":hover{background-color:#282828;color:white;}QPushButton#"+k->objectName()+"{background:transparent;color:white;border:none;}QToolTip{background:#282828;color:#dddddd;}");
    this->ui->pickComponentButton->setStyleSheet("background:#282828;color:#dddddd;");
    this->ui->iconsPanel->hide();
}


void MainWindow::component_added()
{
    while(this->ui->listWidget->count()>0)
    {
      this->ui->listWidget->takeItem(0);
    }
    int list_length=this->ui->frame->tmView->list->length();
    int index=list_length-1;
    int i=0;
    for(;index>=0;index--,i++)
    {
        this->flag=1;
        QListWidgetItem *item=new QListWidgetItem(this->ui->frame->tmView->list->at(index)->getName());
        this->ui->listWidget->addItem(item);
        if(this->ui->frame->tmView->list->at(index)->getSelected())
        {
            this->ui->listWidget->setCurrentRow(i);
        }
    }
}

void MainWindow::on_listWidget_itemSelectionChanged()
{

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    this->ui->pickComponentButton->click();
    //this->ui->frame->tmView->deselectAll();
    int selectedIndex=this->ui->listWidget->currentRow();
    //this->ui->label->setText(QString::number(selectedIndex)+" "+QString::number(this->ui->frame->tmView->list->length()-1)+" "+QString::number((this->ui->frame->tmView->list->length()-1)-selectedIndex));
    if(selectedIndex!=-1)
    this->ui->frame->tmView->setSelectedComponent(this->ui->frame->tmView->list->at((this->ui->frame->tmView->list->length()-1)-selectedIndex));
    this->ui->iconsPanel->hide();
    this->ui->frame->update(true);
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    this->ui->pickComponentButton->click();
    //this->ui->frame->tmView->deselectAll();
    int selectedIndex=this->ui->listWidget->currentRow();
    //this->ui->label->setText(QString::number(selectedIndex)+" "+QString::number(this->ui->frame->tmView->list->length()-1)+" "+QString::number((this->ui->frame->tmView->list->length()-1)-selectedIndex));
    if(selectedIndex!=-1)
    this->ui->frame->tmView->setSelectedComponent(this->ui->frame->tmView->list->at((this->ui->frame->tmView->list->length()-1)-selectedIndex));
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "KeyPress Chala";
    this->ui->frame->keyPressed(event);
    if(event->key()==16777223)
    {
        DrawableComponent *comp=this->ui->frame->tmView->getSelectedComponent();
        if(comp!=nullptr)
        {
            this->ui->frame->tmView->list->removeOne(comp);
            this->ui->frame->tmView->deletedElementList->append(comp);
        }
        this->ui->frame->update();
    }
    if(event->matches(QKeySequence::SelectAll))
    {
        qDebug() << "Select All chala";
        for(auto k: *this->ui->frame->tmView->list)
            k->setSelected(true);
        on_pickComponentButton_clicked();
        this->ui->frame->update();
    }
    else if(event->matches(QKeySequence::Undo))
    {
        if(this->ui->frame->tmView->deletedElementList->size()>0)
        {
            DrawableComponent *comp=this->ui->frame->tmView->deletedElementList->takeLast();
            this->ui->frame->tmView->list->append(comp);
            this->ui->frame->tmView->redoList->append(comp);
        }
        this->ui->frame->update();
    }
    else if(event->matches(QKeySequence::Redo))
    {
        if(this->ui->frame->tmView->redoList->size()>0)
        {
            DrawableComponent *comp=this->ui->frame->tmView->redoList->takeLast();
            this->ui->frame->tmView->list->removeOne(comp);
            this->ui->frame->tmView->deletedElementList->append(comp);
        }
        this->ui->frame->update();
    }
    else if(event->matches(QKeySequence::Copy))
    {
        this->on_copyComponentsButton_clicked();
    }
    else if(event->matches(QKeySequence::Paste))
    {
        this->on_pasteComponentsButton_clicked();
    }
    else if(event->matches(QKeySequence::Save))
    {
        this->on_saveButton_clicked();
    }
    else if(event->matches(QKeySequence::Open))
    {
        this->on_openButton_clicked();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    this->ui->frame->keyReleased(event);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    //this->ui->label->setText(QString::number(position));
    if(position<20) this->ui->frame->setPen_size(1);
    else if(position<40) this->ui->frame->setPen_size(2);
    else if(position<60) this->ui->frame->setPen_size(3);
    else if(position<80) this->ui->frame->setPen_size(4);
    else this->ui->frame->setPen_size(5);
    this->ui->iconsPanel->hide();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //this->ui->label->setText(QString::number(value));
    if(value<20) this->ui->frame->setPen_size(1);
    else if(value<40) this->ui->frame->setPen_size(2);
    else if(value<60) this->ui->frame->setPen_size(3);
    else if(value<80) this->ui->frame->setPen_size(4);
    else this->ui->frame->setPen_size(5);
    this->ui->iconsPanel->hide();
}

void MainWindow::on_deleteButton_clicked()
{
    DrawableComponent *comp=this->ui->frame->tmView->getSelectedComponent();
    //for(auto comp : *this->ui->frame->tmView->deletedElementList) comp->setSelected(false);
    for(auto comp : *this->ui->frame->tmView->list)
    {
        if(comp->getSelected()==true)
        {
            comp->setSelected(false);
            this->ui->frame->tmView->list->removeOne(comp);
            this->ui->frame->tmView->deletedElementList->append(comp);
        }
    }
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_undoButton_clicked()
{
    if(this->ui->frame->tmView->deletedElementList->size()>0)
    {
        DrawableComponent *comp=this->ui->frame->tmView->deletedElementList->takeLast();
        this->ui->frame->tmView->list->append(comp);
        this->ui->frame->tmView->redoList->append(comp);
    }
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_redoButton_clicked()
{
    if(this->ui->frame->tmView->redoList->size()>0)
    {
        DrawableComponent *comp=this->ui->frame->tmView->redoList->takeLast();
        this->ui->frame->tmView->list->removeOne(comp);
        this->ui->frame->tmView->deletedElementList->append(comp);
    }
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_saveButton_clicked()
{
    QJsonArray arr;
    QJsonArray slideArr=*new QJsonArray();
    for(auto s:*slides)
    {
        arr=*new QJsonArray();
        for(auto k:*s->list)
        {
            arr.append(k->toJson());
        }
        slideArr.append(arr);
    }
    QJsonDocument document=*new QJsonDocument(slideArr);
    //QString fileName = QFileDialog::getOpenFileName(this,tr("Save File"), "c:\\qteg\\Painter\\SavedFiles\\");
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save File"), "c:\\qteg\\Painter\\SavedFiles\\untitled.painter",tr("*.painter"));
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
    this->ui->iconsPanel->hide();
}


void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "c:\\qteg\\Painter\\SavedFiles\\",tr("*.painter"));
    if(fileName.compare("")!=0)
    {
        QFile jsonFile(fileName);
        jsonFile.open(QFile::ReadOnly);
        QString file=jsonFile.readAll();
        QJsonDocument document=QJsonDocument::fromJson(file.toUtf8());
        QJsonArray slidesArr=document.array();
        this->ui->frame->tmView->list->clear();
        slides->clear();
        for(auto s: slidesArr)
        {
            QJsonArray arr=s.toArray();
            QJsonObject temp;
            TMView *tempView;
            tempView=new TMView();
            for(auto k: arr)
            {
                temp=k.toObject();
                if(temp["shape"].toString().compare("Rectangle")==0)
                {
                    TMRectangleComponent *rect=new TMRectangleComponent();
                    rect->fromJson(temp);
                    tempView->list->append(rect);
                    //this->ui->frame->tmView->list->append(rect);
                }
                else if(temp["shape"].toString().compare("Circle")==0)
                {
                    TMCircleComponent *circle=new TMCircleComponent();
                    circle->fromJson(temp);
                    tempView->list->append(circle);
                    //this->ui->frame->tmView->list->append(circle);
                }
                else if(temp["shape"].toString().compare("Line")==0)
                {
                    TMLineComponent *line=new TMLineComponent();
                    line->fromJson(temp);
                    tempView->list->append(line);
                    //this->ui->frame->tmView->list->append(line);
                }
                else if(temp["shape"].toString().compare("Freehand")==0)
                {
                    TMFreeHandComponent *freeHand=new TMFreeHandComponent();
                    freeHand->fromJson(temp);
                    tempView->list->append(freeHand);
                    //this->ui->frame->tmView->list->append(freeHand);
                }
                else if(temp["shape"].toString().compare("Group")==0)
                {
                    TMGroupComponent *group=new TMGroupComponent();
                    group->fromJson(temp);
                    //this->ui->frame->tmView->list->append(group);
                    tempView->list->append(group);
                }
                else if(temp["shape"].toString().compare("Image")==0)
                {
                    TMImageComponent *image=new TMImageComponent();
                    image->fromJson(temp);
                    tempView->list->append(image);
                }
            }
            slides->append(tempView);
        }
        selectedSlide=slides->at(0);
        initialiseSlidesList();
    }
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}


void MainWindow::on_groupComponentsButton_clicked()
{
    TMGroupComponent *g=new TMGroupComponent();
    for(auto k : *this->ui->frame->tmView->list)
    {
        if(k->getSelected()==true)
        {
            g->group->append(k);
            this->ui->frame->tmView->list->removeOne(k);
        }
    }
    this->ui->frame->tmView->list->append(g);
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_ungroupComponentsButton_clicked()
{
    DrawableComponent *comp=this->ui->frame->tmView->selectedComponent;
    if(comp!=nullptr && comp->toString().compare("Group")==0)
    {
        this->ui->frame->tmView->list->removeOne(comp);
        TMGroupComponent *group=(TMGroupComponent*)comp;
        for(auto k : *group->group)
        {
            this->ui->frame->tmView->list->append(k);
        }
    }
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_foregroundColorButton_clicked()
{
    QColor color= QColorDialog::getColor(this->foregroundColor,this,"Choose Color");
    if(color.isValid())
    {
        this->foregroundColor=color;
        this->ui->frame->setColor(new QColor(this->foregroundColor.name()));
        this->ui->foregroundColorButton->setStyleSheet("background:"+this->foregroundColor.name()+";color:black;border:1px solid #dddddd;");
    }
    this->ui->iconsPanel->hide();
}

void MainWindow::on_backgroundColorButton_clicked()
{
    QColor color=QColorDialog::getColor(this->backgroundColor,this,"Choose Color");
    if(color.isValid())
    {
        this->backgroundColor= color;
        this->ui->frame->setStyleSheet("background:"+this->backgroundColor.name());
        this->ui->backgroundColorButton->setStyleSheet("background:"+this->backgroundColor.name()+";color:black;border:1px solid #dddddd;");
    }
    this->ui->iconsPanel->hide();
}

void MainWindow::on_clearPageButton_clicked()
{
    for(auto k: *this->ui->frame->tmView->list)
    {
        this->ui->frame->tmView->list->removeOne(k);
        this->ui->frame->tmView->deletedElementList->append(k);
    }
    this->ui->frame->update();
    this->ui->iconsPanel->hide();
}

void MainWindow::on_linedPageButton_clicked()
{
    if(this->ui->frame->lined_page==true)
    {
        this->ui->frame->lined_page=false;
    }
    else
        this->ui->frame->lined_page=true;
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::radioButtonClicked(bool k)
{
    QObject *object = QObject::sender();
    QRadioButton *btn = qobject_cast<QRadioButton *>(object);
    if (k)
    {
        this->ui->frame->tmView=slides->at(btn->text().toInt());
    }
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::initialiseSlidesList()
{
    while(this->ui->slidesList->count()>0)
    {
      this->ui->slidesList->takeItem(0);
    }
    QRadioButton *radio;
    QListWidgetItem *item;
    int i=0;
    for(auto k : *slides)
    {
        radio=new QRadioButton(QString::number(i),this->ui->slidesList);
        item=new QListWidgetItem("",this->ui->slidesList);
        item->setSizeHint(QSize(item->sizeHint().width(), 23));
        this->ui->slidesList->addItem(item);
        this->ui->slidesList->setItemWidget(item,radio);
        QObject::connect( radio, SIGNAL( toggled( bool ) ), this, SLOT( radioButtonClicked( bool ) ) );
        i++;
        if(selectedSlide==k)
            radio->setChecked(true);
    }
}

void MainWindow::initialiseIconsList()
{
    QPixmap *image;
    QIcon *icon;
    QListWidgetItem *item;
    QDir directory("C:/qteg/Painter/images/png");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    foreach(QString filename, images)
    {
        image=new QPixmap("C:/qteg/Painter/images/png/"+filename);
        icon=new QIcon(*image);
        item=new QListWidgetItem("C:/qteg/Painter/images/png/"+filename,this->ui->iconsList);
        item->setIcon(*icon);
        item->setSizeHint(QSize(35,50));
        this->ui->iconsList->addItem(item);
        //this->ui->iconsList->setItemWidget(item,image);
    }
    this->ui->iconsList->setIconSize(QSize(35,35));
}


void MainWindow::on_addNewSlideButton_clicked()
{
    if(slides->size()<29)
    {
        this->ui->frame->tmView->deselectAll();
        TMView *newSlide=new TMView();
        this->ui->frame->tmView=newSlide;
        slides->append(newSlide);
        selectedSlide=newSlide;
        initialiseSlidesList();
        this->ui->iconsPanel->hide();
        this->ui->frame->update();
    }

}

void MainWindow::on_deleteCurrentSlideButton_clicked()
{
    if(slides->size()>1)
    {
        TMView *k=this->ui->frame->tmView;
        int index=slides->indexOf(k);
        slides->removeOne(k);
        if(index < slides->size())
            selectedSlide=slides->at(index);
        else
            selectedSlide=slides->at(index-1);
        initialiseSlidesList();
        this->ui->iconsPanel->hide();
        this->ui->frame->update();
    }
    else
    {
        TMView *k=this->ui->frame->tmView;
        int index=slides->indexOf(k);
        slides->append(new TMView());
        slides->removeOne(k);
        if(index < slides->size())
            selectedSlide=slides->at(index);
        else
            selectedSlide=slides->at(index-1);
        initialiseSlidesList();
        this->ui->iconsPanel->hide();
        this->ui->frame->update();
    }
}

void MainWindow::on_copyComponentsButton_clicked()
{
    int count=0;
    for(auto k : *this->ui->frame->tmView->list)
    {
        if(k->getSelected()==true)
        {
            if(count==0)
            {
                this->ui->frame->copiedComponents->clear();
                count++;
            }
            if(k->toString().compare("Rectangle")==0)
            {
                TMRectangleComponent *rect=new TMRectangleComponent((TMRectangleComponent*)k);
                rect->dragged(10,10,false);
                this->ui->frame->copiedComponents->append(rect);
            }
            else if(k->toString().compare("Circle")==0)
            {
                TMCircleComponent *circle=new TMCircleComponent((TMCircleComponent*)k);
                circle->dragged(10,10,false);
                this->ui->frame->copiedComponents->append(circle);
            }
            else if(k->toString().compare("Line")==0)
            {
                TMLineComponent *line=new TMLineComponent((TMLineComponent*)k);
                line->dragged(10,10,false);
                this->ui->frame->copiedComponents->append(line);
            }
            else if(k->toString().compare("Freehand")==0)
            {
                TMFreeHandComponent *freeHand=new TMFreeHandComponent((TMFreeHandComponent*)k);
                freeHand->dragged(10,10,false);
                this->ui->frame->copiedComponents->append(freeHand);
            }
            else if(k->toString().compare("Group")==0)
            {
                TMGroupComponent *group=new TMGroupComponent((TMGroupComponent*)k);
                group->dragged(10,10,false);
                this->ui->frame->copiedComponents->append(group);
            }
            else if(k->toString().compare("Image")==0)
            {
                TMImageComponent *image=new TMImageComponent((TMImageComponent*)k);
                image->dragged(10,10,false);
                this->ui->frame->copiedComponents->append(image);
            }
        }
    }
    this->ui->iconsPanel->hide();
}

void MainWindow::on_pasteComponentsButton_clicked()
{
    if(this->ui->frame->copiedComponents->size()>0)
    {
        this->ui->frame->tmView->deselectAll();
        for(auto k : *this->ui->frame->copiedComponents)
        {
            this->ui->frame->tmView->list->append(k);
            if(k->toString().compare("Rectangle")==0)
            {
                TMRectangleComponent *rect=new TMRectangleComponent((TMRectangleComponent*)k);
                rect->dragged(10,10,false);
                this->ui->frame->copiedComponents->replace(this->ui->frame->copiedComponents->indexOf(k),rect);
            }
            else if(k->toString().compare("Circle")==0)
            {
                TMCircleComponent *circle=new TMCircleComponent((TMCircleComponent*)k);
                circle->dragged(10,10,false);
                this->ui->frame->copiedComponents->replace(this->ui->frame->copiedComponents->indexOf(k),circle);
            }
            else if(k->toString().compare("Line")==0)
            {
                TMLineComponent *line=new TMLineComponent((TMLineComponent*)k);
                line->dragged(10,10,false);
                this->ui->frame->copiedComponents->replace(this->ui->frame->copiedComponents->indexOf(k),line);
            }
            else if(k->toString().compare("Freehand")==0)
            {
                TMFreeHandComponent *freeHand=new TMFreeHandComponent((TMFreeHandComponent*)k);
                freeHand->dragged(10,10,false);
                this->ui->frame->copiedComponents->replace(this->ui->frame->copiedComponents->indexOf(k),freeHand);
            }
            else if(k->toString().compare("Group")==0)
            {
                TMGroupComponent *group=new TMGroupComponent((TMGroupComponent*)k);
                group->dragged(10,10,false);
                this->ui->frame->copiedComponents->replace(this->ui->frame->copiedComponents->indexOf(k),group);
            }
            else if(k->toString().compare("Image")==0)
            {
                TMImageComponent *image=new TMImageComponent((TMImageComponent*)k);
                image->dragged(10,10,false);
                this->ui->frame->copiedComponents->replace(this->ui->frame->copiedComponents->indexOf(k),image);
            }
        }
    }
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}


void MainWindow::on_insertImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "c:\\qteg\\Painter\\SavedFiles\\","Images (*.png *.jpg)");
    if(fileName.compare("")!=0) this->ui->frame->insertImageButton_clicked(fileName);
    this->ui->iconsPanel->hide();
    this->ui->frame->update();
}

void MainWindow::on_iconsPanelButton_clicked()
{
    this->prev_flag=this->ui->frame->getFlag();
    this->ui->iconsPanel->show();
    this->ui->frame->setFlag(0);
    for(auto k:*buttons) k->setStyleSheet("QPushButton#"+k->objectName()+":hover{background-color:#282828;color:white;}QPushButton#"+k->objectName()+"{background:transparent;color:white;border:none;}QToolTip{background:#282828;color:#dddddd;}");
    this->ui->iconsPanelButton->setStyleSheet("background:#282828;color:#dddddd;");
    this->ui->frame->tmView->deselectAll();
    this->ui->frame->update();
    //this->ui->iconsPanel->setGeometry(90,130,this->ui->iconsPanel->rect().width(),this->ui->iconsPanel->rect().height());
}

void MainWindow::on_iconsPanelCloseButton_clicked()
{
    this->ui->iconsPanel->hide();
    if(prev_flag==1) on_drawCircleButton_clicked();
    else if(prev_flag==2) on_drawLineButton_clicked();
    else if(prev_flag==3) on_drawFreeHandButton_clicked();
    else if(prev_flag==4) on_drawRectangleButton_clicked();
    else if(prev_flag==5) on_pickComponentButton_clicked();
    //this->ui->iconsPanel->setGeometry(1000,1000,this->ui->iconsPanel->rect().width(),this->ui->iconsPanel->rect().height());
}

void MainWindow::on_iconsList_itemClicked(QListWidgetItem *item)
{
    this->ui->iconsPanel->hide();
    this->ui->iconsList->scrollToTop();
    item->setSelected(false);
    this->ui->frame->insertIcon(item->text());
    this->ui->pickComponentButton->click();
    this->ui->frame->enterEvent(nullptr);
    this->ui->frame->update();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString text=item->text();
    //this->ui->listWidget->editItem(item);
    item->setText("");
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    /*bool ok;
    DrawableComponent *comp=nullptr;
    int selectedIndex=this->ui->listWidget->currentRow();
    if(selectedIndex!=-1)
    {
        comp=this->ui->frame->tmView->list->at((this->ui->frame->tmView->list->length()-1)-selectedIndex);
        QString text = QInputDialog::getText(this, tr("Rename"),tr("New name:"), QLineEdit::Normal,item->text(), &ok);
        if (ok && !text.isEmpty())
           comp->setName(text);
    }*/
    //this->ui->frame->update();
}

void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    DrawableComponent *comp=nullptr;
    QString newName=item->text();
    int selectedIndex=this->ui->listWidget->currentRow();
    if(selectedIndex!=-1)
    {
        comp=this->ui->frame->tmView->list->at((this->ui->frame->tmView->list->length()-1)-selectedIndex);
        if(newName.compare("")!=0)
        {
            comp->setName(newName);
            this->ui->frame->update();
        }
    }

}

void MainWindow::on_startRecordingButton_clicked()
{
    QStringList arguments { "c:\\qteg\\Painter\\screen.py"};
    process->start("py",arguments);
    process->waitForStarted();
    this->ui->startRecordingButton->setEnabled(false);
    this->ui->stopRecordingButton->setEnabled(true);
    this->ui->stopRecordingButton->show();
    this->ui->startRecordingButton->hide();
}

void MainWindow::on_stopRecordingButton_clicked()
{
    process->kill();
    this->ui->startRecordingButton->setEnabled(true);
    this->ui->stopRecordingButton->setEnabled(false);
    this->ui->stopRecordingButton->hide();
    this->ui->startRecordingButton->show();
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Recording"), "c:\\qteg\\Painter\\Recordings\\recording.avi",tr("*.avi"));
    QFile video(fileName);
    QFile temp("C:\\qteg\\Painter\\Recordings\\temp\\output.avi");
    temp.open( QFile::ReadOnly );
    video.open( QFile::WriteOnly | QFile::Truncate );
    video.write( temp.readAll() ) >= 0;
    video.close();
    temp.close();
}

void MainWindow::on_minimizeButton_clicked()
{
    MainWindow::setWindowState(Qt::WindowMinimized);
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::WindowStateChange)
    {
        if(isMinimized())
        {
            //do nothing
        }
        else
        {
            MainWindow::setWindowState(Qt::WindowFullScreen);
        }
    }
}

void MainWindow::on_closeButton_clicked()
{
    qApp->exit();
}
