#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "major.h"
#include "course.h"
#include "student.h"

#include <QtCore>
#include <QDir>

QVector<Major> LoadMajors(QStringList);
Major LoadMajorHeader(QString line);

QVector<Student> LoadStudents(QStringList);
Student LoadStudent(QString filename);
Student LoadStudentHeader(QString line);

Course LoadCourse(QString line);

#endif // MAINFUNCTIONS_H
