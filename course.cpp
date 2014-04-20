#include "course.h"

Course::Course()
{
}
QString Course::getDepartment() const
{
    return department;
}

void Course::setDepartment(const QString &value)
{
    department = value;
}
int Course::getNumber() const
{
    return number;
}

void Course::setNumber(int value)
{
    number = value;
}
QString Course::getName() const
{
    return name;
}

void Course::setName(const QString &value)
{
    name = value;
}
int Course::getHours() const
{
    return hours;
}

void Course::setHours(int value)
{
    hours = value;
}
QString Course::getSemester() const
{
    return semester;
}

void Course::setSemester(const QString &value)
{
    semester = value;
}
bool Course::getIsRequired() const
{
    return isRequired;
}

void Course::setIsRequired(bool value)
{
    isRequired = value;
}
QVector<QString> Course::getPrerequisites() const
{
    return prerequisites;
}

void Course::setPrerequisites(const QVector<QString> &value)
{
    prerequisites = value;
}

void Course::addPrerequisite(QString value)
{
    prerequisites.push_back(value);
}







