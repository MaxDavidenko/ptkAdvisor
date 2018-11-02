#include "gui/ptkAdvisorMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ptkAdvisorMainWindow w;
    w.show();

    return a.exec();

}

