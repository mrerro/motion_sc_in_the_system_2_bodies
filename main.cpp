#include "form.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    form w;
    w.setWindowTitle("System 2 bodies");
    w.show();

    return a.exec();
}
