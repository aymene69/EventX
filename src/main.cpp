#include <QApplication>
#include "include/MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication eventX(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("EventX 1.0");
    mainWindow.show();
    return QApplication::exec();
}
