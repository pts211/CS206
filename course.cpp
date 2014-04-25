#include "course.h"

Course::Course()
{
}

bool Course::operator==(const Course &other) const {
    return (this->getNumber() == other.getNumber()) &&
           (this->getDepartment().compare(other.getDepartment()) == 0);
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

QStringList Course::getRowItems()
{
    //X99 is the number used for an elective >= X00 level.
    //Below we translate that identifier to be more user friendly.
    QString modifiedNumberStr = "";
    if(QString::number(this->number).contains("99")){
        QString tempStr = QString::number(this->number).replace("99", "");
        modifiedNumberStr = "> " + tempStr + "00";
    }else{
        modifiedNumberStr = QString::number(this->number);
    }

    //{"Department", "Number", "Name", "Hours"};
    return QStringList({
                        this->department,
                        modifiedNumberStr,
                        this->name,
                        QString::number(this->hours)
                       });
}







