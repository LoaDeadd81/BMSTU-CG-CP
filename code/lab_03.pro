QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    build/Builder.cpp \
    build/Loader.cpp \
    camera/Camera.cpp \
    commands/Commands.cpp \
    creators/BuilderCreators.cpp \
    creators/CommandCreators.cpp \
    creators/DirectorCreators.cpp \
    creators/FabricCreator.cpp \
    creators/LoaderCreators.cpp \
    creators/QtToolCreators.cpp \
    creators/VisitorCreators.cpp \
    draw/Drawer.cpp \
    draw/QtDrawTools.cpp \
    main.cpp \
    managers/Managers.cpp \
    model/Coord.cpp \
    model/Model.cpp \
    model/primitives.cpp \
    objects/CompositeObject.cpp \
    qt_files/mainwindow.cpp \
    scene/Scene.cpp \
    solution/BuilderSolution.cpp \
    solution/DirectorSolution.cpp \
    solution/FabricSolution.cpp \
    solution/LoaderSolution.cpp \
    visitor/DrawVisitor.cpp \
    visitor/TransformVisitor.cpp

HEADERS += \
    build/Builder.h \
    build/Loader.h \
    camera/Camera.h \
    commands/BaseCommand.h \
    commands/Commands.h \
    creators/BuilderCreators.h \
    creators/CommandCreators.h \
    creators/DirectorCreators.h \
    creators/FabricCreator.h \
    creators/LoaderCreators.h \
    creators/QtToolCreators.h \
    creators/VisitorCreators.h \
    draw/DrawTools.h \
    draw/Drawer.h \
    draw/QtDrawTools.h \
    mainwindow.h \
    managers/BaseManager.h \
    managers/Managers.h \
    model/Coord.h \
    model/Model.h \
    model/primitives.h \
    objects/CompositeObject.h \
    objects/SceneObjects.h \
    objects/SimpleObject.h \
    qt_files/mainwindow.h \
    scene/BaseScene.h \
    scene/Scene.h \
    scene/SceneInterface.h \
    solution/BuilderSolution.h \
    solution/DirectorSolution.h \
    solution/FabricSolution.h \
    solution/LoaderSolution.h \
    visitor/DrawVisitor.h \
    visitor/ObjectVisitor.h \
    visitor/TransformVisitor.h

FORMS += \
    qt_files/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/cube.txt

INCLUDEPATH = build/ \
    camera/ \
    commands/ \
    creators/ \
    draw/ \
    managers/ \
    model/ \
    objects/ \
    qt_files/ \
    scene/ \
    solution/ \
    visitor/ \
