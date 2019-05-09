#include <QCoreApplication>

#include "ui.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UI* app = new UI;

    app->run();

    return a.exec();
}
