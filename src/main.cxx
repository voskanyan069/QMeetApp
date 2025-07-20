#include "ui/mainwindow.hxx"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFont font;
    font.setFamily("Segoe UI, Ubuntu, Noto Sans, Arial");
    a.setFont(font);
    w.show();
    return a.exec();
}
