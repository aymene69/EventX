#include <QApplication>
#include "include/MainWindow.hpp"

#ifdef Q_OS_WIN
int WinMain(int argc, char *argv[]) {
#else
int main(int argc, char *argv[]) {
#endif
    QApplication eventX(argc, argv);
    MainWindow mainWindow;
    return QApplication::exec();
}