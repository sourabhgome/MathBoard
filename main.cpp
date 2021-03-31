#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("c:\\qteg\\Painter\\images\\math_splash_screen1.png");
    QSplashScreen splash(pixmap.scaled(600,600,Qt::KeepAspectRatio));
    splash.show();
    a.processEvents();
    MainWindow w;
    //QThread::msleep(8000);
    a.setWindowIcon(QIcon("c:\\qteg\\Painter\\images\\math_splash_screen1.png"));
    w.setWindowState(Qt::WindowFullScreen);
    //w.showFullScreen();
    w.show();
    splash.finish(&w);
    return a.exec();

}
