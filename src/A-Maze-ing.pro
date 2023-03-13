QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VPATH += \
    model \
    model/field \
    model/file_reader \
    model/file_writer \
    controller \
    view

SOURCES += \
    cavetab.cc \
    caveviewport.cc \
    main.cc \
    mainwindow.cc \
    maze.cc \
    mazetab.cc \
    cave_file_reader.cc \
    maze_file_reader.cc \
    cave_file_writer.cc \
    maze_file_writer.cc \
    cave.cc \
    facade.cc \
    mazeviewport.cc \
    scene.cpp

HEADERS += \
    facade.h \
    controller.h \
    field.h \
    maze.h \
    cave.h \
    cave_file_reader.h \
    file_reader.h \
    maze_file_reader.h \
    cave_file_writer.h \
    file_writer.h \
    maze_file_writer.h \
    cavetab.h \
    caveviewport.h \
    mainwindow.h \
    mazetab.h \
    mazeviewport.h \
    scene.h

FORMS += \
    cavetab.ui \
    mainwindow.ui \
    mazetab.ui

ICON = assets/A-Maze-ing.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += model model/field model/file_reader model/file_writer controller view
