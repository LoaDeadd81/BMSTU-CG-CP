#include "qt_files/mainwindow.h"
#include "Solution.h"
#include "Creator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    ModelBuilderSolution mb_sol;
    ModelDirectorSolution md_sol;
    LoaderSolution load_sol;
    FabricSolution fab_sol;

    mb_sol.registeraation("frame", make_shared<ModelBuilderCreator>());
    mb_sol.configure("frame");

    md_sol.registeraation("frame", make_shared<ModelDirectorCreator>());
    md_sol.configure("frame");

    load_sol.registeraation("txt", make_shared<TXTLoaderCreator>());
    load_sol.configure("txt");

    fab_sol.registeraation("qt", make_shared<QtFabricCreator>());
    fab_sol.configure("qt");

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    w.show();
    return a.exec();
}
