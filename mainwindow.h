#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include<QListWidgetItem>
#include <QPushButton>
#include "canvas.h"
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initView();

private slots:
    void on_drawCircleButton_clicked();

    void on_drawLineButton_clicked();

    void on_drawFreeHandButton_clicked();

    void on_drawRectangleButton_clicked();

    void component_added();

    void on_pickComponentButton_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_valueChanged(int value);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemActivated(QListWidgetItem *item);

    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

    void on_deleteButton_clicked();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void on_saveButton_clicked();

    void on_openButton_clicked();

    void on_groupComponentsButton_clicked();

    void on_ungroupComponentsButton_clicked();

    void on_foregroundColorButton_clicked();

    void on_backgroundColorButton_clicked();

    void on_clearPageButton_clicked();

    void on_linedPageButton_clicked();

    void radioButtonClicked(bool k);

    void initialiseSlidesList();

    void initialiseIconsList();

    void on_addNewSlideButton_clicked();

    void on_deleteCurrentSlideButton_clicked();

    void on_copyComponentsButton_clicked();

    void on_pasteComponentsButton_clicked();

    void on_insertImageButton_clicked();

    void on_iconsPanelButton_clicked();

    void on_iconsPanelCloseButton_clicked();

    void on_iconsList_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_startRecordingButton_clicked();

    void on_stopRecordingButton_clicked();

    void on_minimizeButton_clicked();

    void changeEvent(QEvent *);

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout;
    int flag;
    QList<QPushButton *> *buttons;
    QColor foregroundColor,backgroundColor;
    QList<TMView *> *slides;
    TMView *selectedSlide;
    int prev_flag;
    QProcess *process;
};
#endif // MAINWINDOW_H
