#include <Forms/ui_wordspelling.h>
#include <QApplication>

#include "Headers/mainwindow.h"
#include "Headers/worddictation.h"
#include "Headers/wordspelling.h"
#include "Headers/wordreview.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    // MainWindow w;
    // WordDictation w;
    // WordSpelling w;
    WordReview w;
    w.show();
    return QApplication::exec();
}
