#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginDialog* loginDialog;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMessageBox *dialog_about;

public slots:
    void onShowAbout();
};

#endif // MAINWINDOW_H
