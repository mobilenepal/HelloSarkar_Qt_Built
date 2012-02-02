#include "hellosarkar.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDesktopWidget *qD=new QDesktopWidget();
    QString splImg = "";
    if(qD->width()>qD->height())//landscape
    {
        splImg = ":/splash_landscape.jpg";
    }
    else
    {
        splImg = ":/splash_portrait.jpg";
    }
    QPixmap pixmap(splImg);
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Loading...");
    qApp->processEvents();//This is used to accept a click on the screen so that user can cancel the screen

    hellosarkar appGui;
    appGui.setOrientation(hellosarkar::ScreenOrientationAuto);
    appGui.showExpanded();
    splash.finish(&appGui);
    return app.exec();
}
