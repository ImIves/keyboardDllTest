#include "mainwindow.h"
#include <QApplication>
#include <QLibrary>
#include "keyboard.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QLibrary keyboardLib("keyboard");
//    keyboardLib.load();
    Keyboard objKeyboard;
    objKeyboard.showDigital();
    MainWindow w;
    w.show();

    return a.exec();
}
