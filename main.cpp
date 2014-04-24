#include "mainwindow.h"
#include "logindialog.h"
#include "major.h"
#include "course.h"
#include "student.h"

#include <QtCore>
#include <QApplication>
#include <QDir>

QVector<Major> LoadMajors(QStringList);
Major LoadMajorHeader(QString line);

QVector<Student> LoadStudents(QStringList);
Student LoadStudent(QString filename);
Student LoadStudentHeader(QString line);

Course LoadCourse(QString line);

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

//Load in all of the majors given a list of files in the "majors" directory.
QVector<Major> LoadMajors(QStringList majorList) {
    QVector<Major> tempMajorList;
    foreach(QString filename, majorList) {
        QFile f("majors/" + filename);
        if(f.open(QIODevice::ReadOnly)) {
            Major tempMajor;
            int i = 0;
            while(!f.atEnd()) {
                QString line = f.readLine();
                if(i==0){
                    tempMajor = LoadMajorHeader(line);
                }else if(i >= 2){
                    tempMajor.addCourse(LoadCourse(line));
                }
                i++;
            }
            tempMajorList.push_back(tempMajor);
        }
        f.close();
    }
    return tempMajorList;
}

//Not much for the major, but get the header element. (See student for a better example)
Major LoadMajorHeader(QString line) {
    Major tM;
    QStringList items = line.split(",");
    tM.setMajor(items.value(1));

    return tM;
}

//Load in all of the students given a list of files in the "students" directory.
//Note: Since some might complain that it's not efficent to parse an array of potentially
//thousands of students there is another method (LoadStudent) to faciliate loading just
//the student that is desired.
QVector<Student> LoadStudents(QStringList studentList) {
    QVector<Student> tStudentVec;
    foreach(QString filename, studentList) {
        tStudentVec.push_back(LoadStudent(filename));
    }
    return tStudentVec;
}

//To be more efficient I suppose we could just load the student we need.
//PRE: Wants a *.csv string where the * is the username of the student.
Student LoadStudent(QString filename) {
    Student tStudent;
    QFile f("students/" + filename);
    if(f.open(QIODevice::ReadOnly)) {
        int i = 0;
        while(!f.atEnd()) {
            QString line = f.readLine();
            if(i==0){
                tStudent = LoadStudentHeader(line);
                tStudent.setUsername(filename.remove(".csv"));
            }else if(i >= 2){
                tStudent.addCourse(LoadCourse(line));
            }
            i++;
        }
    }else{
        return Student();
    }
    f.close();
    return tStudent;
}

//Get the student header information, name, id, major, etc.
Student LoadStudentHeader(QString line) {
    Student tS;
    QStringList items = line.split(",");
    tS.setMajor(items.value(1));
    tS.setId(items.value(3).toInt());
    tS.setFirstName(items.value(5));
    tS.setLastName(items.value(7));

    return tS;
}

//Load a course given a line of the csv course segment.
Course LoadCourse(QString line) {
    Course tC;
    QStringList items = line.split(",");

    tC.setDepartment(items.takeFirst());
    tC.setNumber(items.takeFirst().toInt());
    tC.setName(items.takeFirst());
    tC.setHours(items.takeFirst().toInt());
    tC.setSemester(items.takeFirst());
    tC.setIsRequired(items.takeFirst().toInt());

    int numPreReq = items.takeFirst().toInt();
    for(int i=0; i<numPreReq; i++) {
        if(!items.isEmpty()) {
            tC.addPrerequisite(items.takeFirst().trimmed());
        }
    }
    return tC;
}
