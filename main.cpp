#include "mainwindow.h"
#include "logindialog.h"
#include "mainFunctions.h"

#include <QtCore>
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog ld;

    QObject::connect(&ld, SIGNAL(DisplayStudent(QString, int)), &w, SLOT(onDisplayStudent(QString,int)));
    QObject::connect(&w, SIGNAL(ShowLogin()), &ld, SLOT(onShowLogin()));

    //TODO PAUL - for testing only:
//    for(int i=0; i<10; i++){
//        qDebug() << w.getSemesterInfo(i);
//    }

    if(!QDir("majors").exists() && !QDir("students").exists()) {
        qDebug("Directory not found!");
        return 0;
    }

    qDebug("Directories exist: Scanning");

    //Scan the "majors" directory for .csv's
    QStringList fileFilter("*.csv");
    QDir directory("majors");
    QStringList majorList = directory.entryList(fileFilter);

    //Scan the "students" directory for .csv's
    directory.setPath("students");
    QStringList studentList = directory.entryList(fileFilter);


    //Parse all of the files in the found directories to Major and Student objects.
    QVector<Major> majors = LoadMajors(majorList);
    QVector<Student> students = LoadStudents(studentList);

    //Pass a copy of the vectors to the mainwindow so it can figure things out
    //after the user is selected.
    //Instead of setting students, if it is desired, can change it to a singular student
    //so that not all students are loaded.
    w.setMajors(majors);
    w.setStudents(students);

    if(!majors.isEmpty()) {
        foreach(Major m, majors) {
            ld.addMajor(m.getMajor());
        }
    }else {
        ld.addMajor("No majors found!");
    }

    QVector<QString> studUVec;
    foreach(QString stud, studentList) {
        studUVec.push_back(stud.remove(".csv"));
    }
    ld.setStudentUserVec(studUVec);

    ld.show();

    //w.showLogin();
    //w.show();

    return a.exec();
}
