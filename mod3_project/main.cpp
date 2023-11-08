#include <QtWidgets>
#include "processing.h"
#include "mainwidget.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    MainWidget mainWidget;
    mainWidget.resize(400, 300);
    mainWidget.show();

    return a.exec();
}
