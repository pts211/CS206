#ifndef STUDENT_H
#define STUDENT_H

#include <QtCore>

#include "course.h"

class Student
{
public:
    Student();

    int getId() const;
    void setId(int value);

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

    QString getMajor() const;
    void setMajor(const QString &value);

    QVector<Course> getCourses() const;
    void setCourses(const QVector<Course> &value);
    void addCourse(Course value);

    int getHoursTaken();

private:
    int id;
    QString username;
    QString firstName;
    QString lastName;
    QString major;
    QVector<Course> courses;
};

#endif // STUDENT_H
