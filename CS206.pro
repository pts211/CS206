#-------------------------------------------------
#
# Project created by QtCreator 2014-04-14T13:33:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS206
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    major.cpp \
    course.cpp \
    student.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    major.h \
    course.h \
    student.h

FORMS    += mainwindow.ui \
    logindialog.ui

OTHER_FILES += \
    Resources.txt \
    majors/* \
    students/*

#SUBDIRS = majors \

#Project
majors.path     = $${OUT_PWD}/majors
majors.files    = majors/*
students.path   = $${OUT_PWD}/students
students.files  = students/*

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
INSTALLS       += majors students majors_d majors_r students_d students_r

#for(FILE, OTHER_FILES){
#    QMAKE_POST_LINK += $$quote(cmd /c copy /y $${PWD_WIN}\\$${FILE} $${DESTDIR_WIN}$$escape_expand(\\n\\t))
#}

# Copy qml files post build
#win32 {}
