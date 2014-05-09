#include <QtTest/QtTest>
#include <QtCore>
#include <iostream>
#include "../mainFunctions.h"
using namespace std;

class UnitTests: public QObject
{
    Q_OBJECT
private slots:
    void TestID_1();
    void TestID_2();
    void TestID_3();
    void TestID_4();
    void TestID_5();
};

void UnitTests::TestID_1()
{
    // OK Test
    QStringList fileFilter("*.csv");
    QDir directory = QDir::current();
    directory.cd("majors");
    QStringList majorList = directory.entryList(fileFilter);
    QVector<Major> majors = LoadMajors(majorList);
    QCOMPARE(majors.size(), 2);

    // ERROR Test
    QStringList fileFilter2("*.csv");
    QDir directory2 = QDir::current();
    directory2.cd("students");
    QStringList majorList2 = directory2.entryList(fileFilter2);
    QVector<Major> majors2 = LoadMajors(majorList2);
    QCOMPARE(majors2.size(), 0);
}

void UnitTests::TestID_2()
{
    // OK Test
    QStringList fileFilter("*.csv");
    QDir directory = QDir::current();
    directory.cd("students");
    QStringList studentList = directory.entryList(fileFilter);
    QVector<Student> students = LoadStudents(studentList);
    QCOMPARE(students.size(), 3);

    // ERROR Test
    QStringList fileFilter2("*.csv");
    QDir directory2 = QDir::current();
    directory.cd("major");
    QStringList studentList2 = directory2.entryList(fileFilter2);
    QVector<Student> students2 = LoadStudents(studentList2);
    QCOMPARE(students2.size(), 0);
}

void UnitTests::TestID_3()
{
    // OK Test
    Course c;
    QFile f("course/datastructures.csv");
    if(f.open(QIODevice::ReadOnly)){
        while(!f.atEnd()){
            QString line = f.readLine();
            //cout << line.toStdString() << endl;
            c = LoadCourse(line);
        }
    }
    f.close();

    QVector<QString> prereqs = c.getPrerequisites();

    QCOMPARE(c.getDepartment(),QString("CS"));
    QCOMPARE(c.getNumber(),153);
    QCOMPARE(c.getName(),QString("Data Structures"));
    QCOMPARE(c.getHours(),3);
    QCOMPARE(c.getSemester(),QString("FS"));
    QCOMPARE(c.getIsRequired(),true);
    QCOMPARE(prereqs.size(),1);
    QCOMPARE(prereqs.at(0),QString("CS53"));

}

void UnitTests::TestID_4()
{
    // OK Test
    Major m;
    QFile f("majors/Computer_Science.csv");
    if(f.open(QIODevice::ReadOnly)){
        QString line = f.readLine();
        //cout << line.toStdString() << endl;
        m = LoadMajorHeader(line);
    }
    f.close();

    QCOMPARE(m.getMajor(),QString("Computer Science"));
}

void UnitTests::TestID_5()
{
    // OK Test
    Student s;
    QFile f("students/ptsx9d.csv");
    if(f.open(QIODevice::ReadOnly)){
        QString line = f.readLine();
        //cout << line.toStdString() << endl;
        s = LoadStudentHeader(line);
    }
    f.close();

    QCOMPARE(s.getMajor(),QString("Computer Science"));
    QCOMPARE(s.getId(),12345678);
    QCOMPARE(s.getFirstName(),QString("Paul"));
    QCOMPARE(s.getLastName(),QString("Sites\n"));
}

QTEST_MAIN(UnitTests)
#include "unittests.moc"
