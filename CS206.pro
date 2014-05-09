#-------------------------------------------------
#
# Project created by QtCreator 2014-04-14T13:33:35
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS206
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    major.cpp \
    course.cpp \
    student.cpp \
    fingertabbarwidget.cpp \
    fingertabwidget.cpp \
    about.cpp \
    mainFunctions.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    major.h \
    course.h \
    student.h \
    fingertabbarwidget.h \
    fingertabwidget.h \
    about.h \
    mainFunctions.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    about.ui

OTHER_FILES += \
    Resources.txt \
    images/* \
    majors/* \
    students/*

#SUBDIRS = majors \

#Project
majors.path     = $${OUT_PWD}/majors
majors.files    = majors/*
students.path   = $${OUT_PWD}/students
students.files  = students/*
images.path   = $${OUT_PWD}/images
images.files  = images/*

#Debug
majors_d.path     = $${OUT_PWD}/debug/majors
majors_d.files    = majors/*
students_d.path   = $${OUT_PWD}/debug/students
students_d.files  = students/*

#Release
majors_r.path     = $${OUT_PWD}/release/majors
majors_r.files    = majors/*
students_r.path   = $${OUT_PWD}/release/students
students_r.files  = students/*
INSTALLS       += majors students majors_d majors_r students_d students_r images

#for(FILE, OTHER_FILES){
#    QMAKE_POST_LINK += $$quote(cmd /c copy /y $${PWD_WIN}\\$${FILE} $${DESTDIR_WIN}$$escape_expand(\\n\\t))
#}

# Copy qml files post build
#win32 {}
