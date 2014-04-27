#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "major.h"
#include "student.h"
#include "fingertabbarwidget.h"
#include "fingertabwidget.h"
#include "about.h"

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

    //Does all of the heavy lifting, recalculates everything and updates UI with new data.
    //Naturally it's called everytime the user changes the max hours spinner. (Good thing computers are fast!)
    void updateDisplay();

    //Sets various table formatting stuff. Bundled in a method for quick access if needed.
    void formatTableLayout(QTableWidget *table);

    //A method to set the alignment of the columns in the tables.
    void setStupidAlignment(QTableWidgetItem *item, int column);


    ~MainWindow();

    QVector<Major> getMajors() const;
    void setMajors(const QVector<Major> &value);
    QVector<Student> getStudents() const;
    void setStudents(const QVector<Student> &value);
    int getCreditMax() const;
    void setCreditMax(const int& max);


    QVector< QVector<Course> > getSchedule();

    //Given a semester returns a string with the seaons and year.
    //If it is past June it assumes that this will be fore the Spring semester.
    //ex. semester 0: Fall 2014
    //    semester 2: Fall 2015
    QString getSemesterInfo(int semesterCount);


private:
    Ui::MainWindow *ui;
    //QMessageBox *dialog_about;
    About *dialog_about;

    QVector<Major> majors;
    QVector<Student> students;

    Major currentMajor;
    Student currentStudent;

    int creditMax;

public slots:
    void onShowAbout();
    void onLogout();
    void onExit();
    void onDisplayStudent(QString, int);
    void onMaxChange();

signals:
    void ShowLogin();

};

#endif // MAINWINDOW_H
