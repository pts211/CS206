#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onShowAbout()));
    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(onLogout()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onExit()));

    //TEST Generating GUI
    FingerTabWidget *tabs = new FingerTabWidget();
    QVector<QString> digits = {"Fall 2014", "Spring 2015", "Fall 2015", "Spring 2016", "Fall 2016"};
    int i = 0;
    foreach(QString s, digits) {
        tabs->addTab(new QLabel("Test: " + QString::number(i++)), s);
    }
    ui->fingerTabLayout->addWidget(tabs);

    testTableView();
}


//TODO PAUL - Not working quite yet. Will need to progromatically insert table anyways, should
//just switch to that now.
void MainWindow::testTableView() {
    QStringList tableHeaders = {"Thing 1", "Thing 2"};
    ui->tableWidget->setHorizontalHeaderLabels(tableHeaders);
    ui->tableWidget->setItem(0,1, new QTableWidgetItem("Hello"));
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
}

/* -------------------- SLOTS -------------------- */

//Display an about message. Describe the app, display group members, logo?, and any other
//helpfull information.
void MainWindow::onShowAbout() {
    dialog_about = new QMessageBox(this);
    dialog_about->about(this, "Path-To-Success", "This handy program will tell you how much longer you get to stay here!");
}

//TODO Call methods display the main window, figure out all of the complex stuff for scheduling,
//and any other cool things. Depending on how good our algorithm is a loading spinner might be
//a good thing to have.
void MainWindow::onDisplayStudent(QString un, int majorIndex) {

    //Set the currentMajor and currentStudent variables.
    currentMajor = majors.at(majorIndex);
    foreach(Student student, students) {
        if(un != NULL && un.compare(student.getUsername()) == 0){
            currentStudent = student;
        }
    }
    //Populate the known labels in the main window.
    ui->labelUser->setText(currentStudent.getFirstName() + " " + currentStudent.getLastName());
    ui->labelHoursEarned->setText(QString::number(currentStudent.getHoursTaken()) + " of 128 hours earned.");
    ui->labelDegree->setText(currentMajor.getMajor());
    show();
}

void MainWindow::onLogout() {
    emit ShowLogin();
    hide();
}

void MainWindow::onExit() {
    QCoreApplication::quit();
}
/* -------------------- SLOTS END -------------------- */


/* -------------------- GETTERS & SETTERS -------------------- */
QVector<Major> MainWindow::getMajors() const
{
    return majors;
}

void MainWindow::setMajors(const QVector<Major> &value)
{
    majors = value;
}
QVector<Student> MainWindow::getStudents() const
{
    return students;
}

void MainWindow::setStudents(const QVector<Student> &value)
{
    students = value;
}

/* -------------------- GETTERS & SETTERS END -------------------- */


MainWindow::~MainWindow()
{
    delete ui;
}
