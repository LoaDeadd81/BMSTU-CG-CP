cmake_minimum_required(VERSION 3.21)
project(lab_03_oop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.2.4/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )

include_directories(objects
        model
        scene
        camera
        visitor
        commands
        managers
        creators
        draw
        build
        solution
        errors
        )

add_executable(lab_03_oop
        main.cpp
        qt_files/mainwindow.h
        qt_files/mainwindow.cpp
        qt_files/mainwindow.ui
        objects/SceneObjects.h
        model/Model.cpp
        model/Model.h
        model/primitives.cpp
        model/primitives.h
        model/Coord.cpp
        model/Coord.h
        camera/Camera.cpp
        camera/Camera.h
        visitor/ObjectVisitor.h
        objects/SimpleObject.h
        objects/CompositeObject.cpp
        objects/CompositeObject.h
        visitor/TransformVisitor.cpp
        visitor/TransformVisitor.h
        scene/Scene.cpp
        scene/Scene.h
        scene/BaseScene.h
        scene/SceneInterface.h
        commands/BaseCommand.h
        commands/Commands.cpp
        commands/Commands.h
        managers/BaseManager.h
        managers/Managers.cpp
        managers/Managers.h
        creators/CommandCreators.h
        creators/CommandCreators.cpp
        creators/VisitorCreators.cpp
        creators/VisitorCreators.h
        draw/Drawer.cpp
        draw/Drawer.h
        draw/DrawTools.h
        draw/QtDrawTools.cpp
        draw/QtDrawTools.h
        creators/QtToolCreators.cpp
        creators/QtToolCreators.h
        visitor/DrawVisitor.cpp
        visitor/DrawVisitor.h
        build/Loader.cpp
        build/Loader.h
        build/Builder.cpp
        build/Builder.h
        creators/FabricCreator.cpp
        creators/FabricCreator.h
        solution/FabricSolution.cpp
        solution/FabricSolution.h
        creators/DirectorCreators.cpp
        creators/DirectorCreators.h
        creators/BuilderCreators.cpp
        creators/BuilderCreators.h
        creators/LoaderCreators.cpp
        creators/LoaderCreators.h
        solution/DirectorSolution.cpp
        solution/DirectorSolution.h
        solution/BuilderSolution.cpp
        solution/BuilderSolution.h
        solution/LoaderSolution.cpp
        solution/LoaderSolution.h
        solution/Solution.h
        creators/Creator.h errors/Error.cpp errors/Error.h scene/SceneInterface.cpp)

target_link_libraries(lab_03_oop
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
