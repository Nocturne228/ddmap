#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget windows;
    windows.setMinimumSize(1431, 800);
    windows.show();

    return app.exec();
}
