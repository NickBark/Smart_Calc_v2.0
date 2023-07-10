#include <QApplication>
#include <QDebug>
#include <QFile>

#include "mainwindow.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "en-US");
    setlocale(LC_NUMERIC, "C");
    QApplication a(argc, argv);
    MainWindow w;

    // Set GUI style
    QFile styleFile(":/style/DarkGrey.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
    } else
        qDebug() << "Style can't be loaded.";

    w.show();
    return a.exec();
}
