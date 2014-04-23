#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    creditMax(17),
    creditMin(12)
{
    ui->setupUi(this);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onShowAbout()));
    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(onLogout()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onExit()));
    connect(ui->maxBox, SIGNAL(valueChanged(int)), this, SLOT(onMaxChange()));
    connect(ui->minBox, SIGNAL(valueChanged(int)), this, SLOT(onMinChange()));

    ui->minBox->setValue(creditMin);
    ui->maxBox->setValue(creditMax);
    ui->minBox->setMaximum(ui->maxBox->value());
    ui->maxBox->setMinimum(ui->minBox->value());

    //TEST Generating GUI

    //TODO PAUL - make this function generate a bunch of QTableWidgets that
    //are tables of semesters to display.
    //Vector<QTableWidget> = generateSemesterTables();

    FingerTabWidget *tabs = new FingerTabWidget();
    QVector<QString> digits = {"Fall 2014", "Spring 2015", "Fall 2015", "Spring 2016", "Fall 2016"};
    int i = 0;
    foreach(QString s, digits) {
        tabs->addTab(new QLabel("Test: " + QString::number(i++)), s);
    }
//    ui->fingerTabLayout->addWidget(tabs);

    testTableView();
}


//TODO PAUL - Not working quite yet. Will need to progromatically insert table anyways, should
//just switch to that now.
void MainWindow::testTableView() {
    QTableWidget *tempTable = new QTableWidget(5, 5);
    QStringList tableHeaders = {"Thing 1", "Thing 2", "Thing 3", "Thing 4", "Thing 5"};

    tempTable->setHorizontalHeaderLabels(tableHeaders);
    tempTable->setItem(0,1, new QTableWidgetItem("Hello"));
    ui->fingerTabLayout->addWidget(tempTable);

//    ui->tableWidget->setHorizontalHeaderLabels(tableHeaders);
//    ui->tableWidget->setItem(0,1, new QTableWidgetItem("Hello"));
//    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
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

void MainWindow::onMaxChange()
{
    setCreditMax(ui->maxBox->value());
    ui->minBox->setMaximum(ui->maxBox->value());
}

void MainWindow::onMinChange()
{
    setCreditMin(ui->minBox->value());
    ui->maxBox->setMinimum(ui->minBox->value());
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

int MainWindow::getCreditMax() const
{
    return creditMax;
}

void MainWindow::setCreditMax(const int& max)
{
    creditMax = max;
}

int MainWindow::getCreditMin() const
{
    return creditMin;
}

void MainWindow::setCreditMin(const int &min)
{
    creditMin = min;
}

/* -------------------- GETTERS & SETTERS END -------------------- */


MainWindow::~MainWindow()
{
    delete ui;
}

QVector< QVector<Course> > MainWindow::getSchedule(QString nextSem)
{
    QVector<Course> student = currentStudent.getCourses();
    QVector<Course> major = currentMajor.getCourses();
    QVector<Course> taken;//list of all "taken" courses
    for(int i = 0; i < student.size(); i++)
    {
        for(int j = 0; j< major.size(); j++)
        {
            if(student[i].getNumber() == major[i].getNumber() && student[i].getDepartment().compare(major[i].getDepartment()) == 0)
            {
                taken.push_back(major[j]);
                major.remove(j);
                j--;
            }
        }
    }

    //Semesters
    QVector< QVector<Course> > semesters;
    bool isFall = (nextSem.compare("F")==0);
    while(major.size() > 0 )//runs until all classes are "taken")
    {
        int curCredits = 0;
        QVector<Course> thisSem;
        for(int i = 0; i < major.size(); i++)
        {
            if(major[i].getHours() + curCredits <= creditMax)
            {
                if(major[i].getSemester().contains("F") && isFall ||
                        major[i].getSemester().contains("S") && !isFall)
                {
                    bool canTake = true;
                    for(int j = 0; j < major[i].getPrerequisites().size(); j++)
                    {
                        bool completed = false;
                        for(int k = 0; k < taken.size(); k++)
                        {
                            QString course = taken[k].getDepartment();
                            course.append(taken[k].getNumber());
                            if( course.compare(major[i].getPrerequisites()[j]))
                            {
                                completed = true;
                            }
                        }
                        if(!completed)
                        {
                            canTake = false;
                        }
                    }
                    if(canTake)
                    {
                        thisSem.push_back(major[i]);
                        taken.push_back(major[i]);
                        curCredits += major[i].getHours();

                        major.remove(i);
                        i--;
                    }
                }
            }
            else
            {
                break;
            }
        }
        semesters.push_back(thisSem);
        isFall = !isFall;
    }
    return semesters;
}
