#ifndef COURSE_H
#define COURSE_H

#include <QtCore>

class Course
{
public:
    Course();
    bool operator==(const Course &other) const;

    QString getDepartment() const;
    void setDepartment(const QString &value);

    int getNumber() const;
    void setNumber(int value);

    QString getName() const;
    void setName(const QString &value);

    int getHours() const;
    void setHours(int value);

    QString getSemester() const;
    void setSemester(const QString &value);

    bool getIsRequired() const;
    void setIsRequired(bool value);

    QVector<QString> getPrerequisites() const;
    void setPrerequisites(const QVector<QString> &value);
    void addPrerequisite(QString value);

    QStringList getRowItems();

private:
    QString department;
    int number;
    QString name;
    int hours;
    QString semester;
    bool isRequired;
    QVector<QString> prerequisites;

};

#endif // COURSE_H
