#include <QApplication>
#include "include/MainWindow.hpp"
#define
#ifdef Q_OS_WIN
int WinMain(int argc, char *argv[]) {
#else
int main(int argc, char *argv[]) {
#endif
    QApplication eventX(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("EventX 1.0");
    mainWindow.show();
    return QApplication::exec();
}