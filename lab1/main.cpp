#include <QApplication>
#include "AuthWindow.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    AuthWindow::AuthWindow authWindow;
//    authWindow.show();
    Controller controller;
    controller.showAuth();
    return QApplication::exec();
}
