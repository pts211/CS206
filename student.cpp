#include "student.h"

Student::Student()
{
}

int Student::getId() const
{
    return id;
}

void Student::setId(int value)
{
    id = value;
}
QString Student::getUsername() const
{
    return username;
}

void Student::setUsername(const QString &value)
{
    username = value;
}
QString Student::getFirstName() const
{
    return firstName;
}

void Student::setFirstName(const QString &value)
{
    firstName = value;
}
QString Student::getLastName() const
{
    return lastName;
}

void Student::setLastName(const QString &value)
{
    lastName = value;
}
QString Student::getMajor() const
{
    return major;
}

void Student::setMajor(const QString &value)
{
    major = value;
}
QVector<Course> Student::getCourses() const
{
    return courses;
}

void Student::setCourses(const QVector<Course> &value)
{
    courses = value;
}

void Student::addCourse(Course value)
{
    courses.push_back(value);
}










