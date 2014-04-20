#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setModal( true );
    setFixedSize(size());
    setWindowTitle( tr("Path-To-Success: Login") );
    ui->editUsername->setStyleSheet("QLineEdit {}");
}

void LoginDialog::setStudentUserVec( QVector<QString> sUVec) {
    studentUserVec = sUVec;
}

void LoginDialog::addMajor(QString major) {
    ui->comboMajor->addItem(major);
}


/* -------------------- SLOTS -------------------- */

void LoginDialog::onShowLogin() {
    ui->editUsername->setText("");
    show();
}

/* -------------------- SLOTS END -------------------- */


/* -------------------- FUNCTIONS -------------------- */
//Validate that the username that is trying to be used exists in the file directory.
//If the username is not valid then outline the username input and wait for user to
//try again.
bool LoginDialog::validateUser() {
    if(studentUserVec.contains(ui->editUsername->text())) {
         ui->editUsername->setStyleSheet("QLineEdit {}");
        return true;
    }else{
        ui->editUsername->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        ui->editUsername->setFocus();
        return false;
    }
}
/* -------------------- FUNCTIONS END -------------------- */

/* -------------------- BUTTONS -------------------- */

//Check to see if the username is valid, if it is emit a signal to the mainwindow to
//start processing everything. Close the login dialog.
void LoginDialog::on_btnLogin_clicked()
{
    if(validateUser()){
        //TODO Display might not be the best word choice. (Should emit signal to open main window with schedule stuff).
        emit DisplayStudent(ui->editUsername->text(), ui->comboMajor->currentIndex());
        hide();
    }

}

void LoginDialog::on_btnExit_clicked()
{
    QCoreApplication::quit();
}

/* -------------------- BUTTONS END-------------------- */

LoginDialog::~LoginDialog()
{
    delete ui;
}
