#include "GetFit.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {

    QApplication a(argc, argv);
    GetFit w;
    w.show();
    return a.exec();
}