#include "major.h"

Major::Major()
{
}

QString Major::getMajor() const
{
    return major;
}

void Major::setMajor(const QString &value)
{
    major = value;
}
QVector<Course> Major::getCourses() const
{
    return courses;
}

void Major::setCourses(const QVector<Course> &value)
{
    courses = value;
}

void Major::addCourse(Course value)
{
    courses.push_back(value);
}


