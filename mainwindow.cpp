#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    creditMax(17),
    creditMin(12)
{
    ui->setupUi(this);

    this->setFixedSize(this->geometry().width(),this->geometry().height());

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onShowAbout()));
    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(onLogout()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onExit()));
    connect(ui->maxBox, SIGNAL(valueChanged(int)), this, SLOT(onMaxChange()));
    connect(ui->minBox, SIGNAL(valueChanged(int)), this, SLOT(onMinChange()));

    ui->minBox->setValue(creditMin);
    ui->maxBox->setValue(creditMax);
    ui->minBox->setMaximum(ui->maxBox->value());
    ui->maxBox->setMinimum(ui->minBox->value());
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

    updateDisplay();
    show();
}

//Performs all of the table formatting the semesters.
void MainWindow::updateDisplay()
{
    //Refresh checkboxes and buttons
    while(ui->fingerTabLayout->count() > 0) {
                QWidget* widget = ui->fingerTabLayout->itemAt(0)->widget();
                ui->fingerTabLayout->removeWidget(widget);
                delete widget;
        }

    QVector<QVector<Course>> semesters = getSchedule();

    //Populate the known labels in the main window.
    ui->labelUser->setText(currentStudent.getFirstName() + " " + currentStudent.getLastName());
    ui->labelHoursEarned->setText(
                QString::number(currentStudent.getHoursTowards(currentMajor.getCourses())) +
                " of " +
                QString::number(currentMajor.getTotalHours()) +
                " hours earned."
                );
    ui->labelDegree->setText(currentMajor.getMajor());
    ui->labelExpGrad->setText( getSemesterInfo(semesters.size() - 1) );


    FingerTabWidget *tabs = new FingerTabWidget();
    QStringList tableHeaders = {"Department", "Number", "Name", "Hours"};

    foreach(QVector<Course> semester, semesters) {
        QTableWidget *tempTable = new QTableWidget(semester.size(), tableHeaders.size());
        tempTable->setHorizontalHeaderLabels(tableHeaders);

        int semHours = 0;
        int i = 0;
        foreach(Course c, semester) {
            for(int j = 0; j<tempTable->columnCount(); j++) {
                QString itemText = c.getRowItems()[j];
                QTableWidgetItem *temp = new QTableWidgetItem(itemText);
                //Makes table items read only.
                temp->setFlags(temp->flags() ^ Qt::ItemIsEditable);
                setStupidAlignment(temp, j);
                tempTable->setItem(i, j, temp);
            }
            i++;
            semHours += c.getHours();
        }

        formatTableLayout(tempTable);

        //Sets the tab name as well as displays the hours for the semester in the tab.
        QString tabString = getSemesterInfo(semesters.indexOf(semester)) + " \t(" + QString::number(semHours) + ")";
        tabs->addTab(tempTable, tabString);
    }
    ui->fingerTabLayout->addWidget(tabs);
}

//Performs all of the table formatting the semesters.
void MainWindow::formatTableLayout(QTableWidget *table)
{
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->verticalHeader()->setVisible(false);

    //Set the column widths to a percent.
    //TODO PAUL - Will eventually need to call this when resizing the window so it always looks great!
    int w = table->width();
    table->setColumnWidth(0, w*.2);
    table->setColumnWidth(1, w*.1);
    table->setColumnWidth(2, w*.6);
    table->setColumnWidth(3, w*.1);
}

//PAUL - I'm not very proud of this, but I couldn't get any other way to work... So
//just live with it.
void MainWindow::setStupidAlignment(QTableWidgetItem *item, int column)
{
    switch(column)
    {
        case 0:
            item->setTextAlignment(Qt::AlignCenter);
            break;
        case 1:
            item->setTextAlignment(Qt::AlignCenter);
            break;
        case 2:
            item->setTextAlignment(Qt::AlignVCenter);
            break;
        case 3:
            item->setTextAlignment(Qt::AlignCenter);
            break;
        default:
            item->setTextAlignment(Qt::AlignLeft);
            break;
    }
}

void MainWindow::onMaxChange()
{
    setCreditMax(ui->maxBox->value());
    ui->minBox->setMaximum(ui->maxBox->value());
    updateDisplay();
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

QVector< QVector<Course> > MainWindow::getSchedule()
{
    QVector<Course> coursesNeeded = currentMajor.getCourses();
    QVector<Course> coursesTaken;//list of all "taken" courses

    foreach(Course sC, currentStudent.getCourses()) {
        foreach(Course mC, currentMajor.getCourses()) {
            if((sC.getNumber() == mC.getNumber()) && (sC.getDepartment().compare(mC.getDepartment()) == 0)){
                coursesTaken.push_back(mC);
                coursesNeeded.remove(coursesNeeded.indexOf(mC));
            }
        }
    }

    QString nextSem = getSemesterInfo(0);

    //Semesters
    QVector< QVector<Course> > semesters;
    bool isFall = (nextSem.contains("F", Qt::CaseInsensitive));
    while(!coursesNeeded.isEmpty())//runs until all classes are "taken")
    {
        int curCredits = 0;
        QVector<Course> thisSem;

        foreach(Course needed, coursesNeeded) {
            //PAUL - I see this accounts for creditMax, somewhere we need to handle the minimum too.
            //I think we might end up needing to have "filler" classes to pad the semesters if the hours are short.
            if(needed.getHours() + curCredits <=creditMax) {
                if((needed.getSemester().contains("F") && isFall) ||
                   (needed.getSemester().contains("S") && !isFall)) {

                    //So the student needs that class? Well, has he done all the prereqs? Lets check.
                    bool hasCompletedPrereqs = false;
                    foreach(QString prereq, needed.getPrerequisites()) {
                        hasCompletedPrereqs = false;
                        //PAUL - I don't think this is going to work for multiple prerequsites. Maybe reversing the loops and
                        //changing the variables is an option?
                        //PAUL - Fixed it.
                        foreach(Course taken, coursesTaken) {
                            QString course = taken.getDepartment() + QString::number(taken.getNumber());
                            if(course.compare(prereq) == 0) {
                                hasCompletedPrereqs = true;
                                break;
                            }
                        }
                        if(!hasCompletedPrereqs){
                            break;
                        }
                    }
                    //You can take the class if you have completed the prerequsites!
                    if(hasCompletedPrereqs || needed.getPrerequisites().isEmpty()) {
                        thisSem.push_back(needed);
                        //PAUL - This seems risky, it could schedule a course while student is taking the prereq.
                        coursesTaken.push_back(needed);
                        curCredits += needed.getHours();
                        coursesNeeded.remove(coursesNeeded.indexOf(needed));
                    }
                }
            }
        }
        semesters.push_back(thisSem);
        isFall = !isFall;
    }
    return semesters;
}

QString MainWindow::getSemesterInfo(int semesterCount){
    QDate date; // = QDate();
    int year = date.currentDate().year();

    bool isFall = true;

    if(date.currentDate().month() > 6){
        year++;
        isFall = false;
    }
    for(int i=0; i<semesterCount; i++){
        if(isFall){ year++; }
        isFall = !isFall;
    }

    if(isFall){
        return "Fall " + QString::number(year) + "   \t";
    }else{
        return "Spring " + QString::number(year);
    }
}
