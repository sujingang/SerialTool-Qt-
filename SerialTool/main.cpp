#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon = QIcon(":/new/icon/strtoolicon.ico");//使用相对路径
    w.setWindowIcon(icon);
    w.setWindowTitle("SerialTool");//改主窗口名字
    w.show();
    return a.exec();
}
