#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "major.h"
#include "student.h"
#include "fingertabbarwidget.h"
#include "fingertabwidget.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void formatTableLayout(QTableWidget *table);
    void setStupidAlignment(QTableWidgetItem *item, int column);


    ~MainWindow();

    QVector<Major> getMajors() const;
    void setMajors(const QVector<Major> &value);
    QVector<Student> getStudents() const;
    void setStudents(const QVector<Student> &value);
    int getCreditMax() const;
    void setCreditMax(const int& max);
    int getCreditMin() const;
    void setCreditMin(const int& min);

    QVector< QVector<Course> > getSchedule();

    QString getSemesterInfo(int semesterCount);


private:
    Ui::MainWindow *ui;
    QMessageBox *dialog_about;

    QVector<Major> majors;
    QVector<Student> students;

    Major currentMajor;
    Student currentStudent;

    int creditMax;
    int creditMin;

public slots:
    void onShowAbout();
    void onLogout();
    void onExit();
    void onDisplayStudent(QString, int);
    void onMinChange();
    void onMaxChange();

signals:
    void ShowLogin();

};

#endif // MAINWINDOW_H
