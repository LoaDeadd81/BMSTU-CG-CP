cmake_minimum_required(VERSION 3.5)

project(cg_course VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        UI/mainwindow.cpp
        UI/mainwindow.h
        UI/mainwindow.ui
        Math/Matrix.h Math/Vec.h Errors/Errors.cpp Errors/Errors.h Math/Transformation.cpp Math/Transformation.h Math/GeometryPrimitives.cpp Math/GeometryPrimitives.h Objects/Model.cpp Objects/Model.h Objects/Camera.cpp Objects/Camera.h Objects/Light.cpp Objects/Light.h Manager/SceneManager.h Scene/Scene.cpp Scene/Scene.h Commands/Commands.cpp Commands/Commands.h Objects/Properies.h Drawer/Drawer.cpp Drawer/Drawer.h Render/Render.cpp Render/Render.h Objects/OBJ_Loader.h Objects/loader.cpp Objects/Textures.cpp Objects/Textures.h)

include_directories(Math Errors UI Objects Scene Manager Commands Manager Drawer Render)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cg_course
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET cg_course APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(cg_course SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(cg_course
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(cg_course PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(cg_course PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

install(TARGETS cg_course
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cg_course)
endif ()
