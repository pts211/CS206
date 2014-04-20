#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "major.h"
#include "student.h"

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

    QVector<Major> getMajors() const;
    void setMajors(const QVector<Major> &value);
    QVector<Student> getStudents() const;
    void setStudents(const QVector<Student> &value);

private:
    Ui::MainWindow *ui;
    QMessageBox *dialog_about;

    QVector<Major> majors;
    QVector<Student> students;


public slots:
    void onShowAbout();
    void onDisplayStudent(QString, int);
};

#endif // MAINWINDOW_H
