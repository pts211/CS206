#ifndef MAJOR_H
#define MAJOR_H

#include <QtCore>

#include "course.h"

class Major
{
public:
    Major();

    QString getMajor() const;
    void setMajor(const QString &value);

    QVector<Course> getCourses() const;
    void setCourses(const QVector<Course> &value);
    void addCourse(Course value);
    int getTotalHours();

private:
    QString major;
    QVector<Course> courses;
};

#endif // MAJOR_H
