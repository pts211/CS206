#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //dialog_about.about(this, "About", "TEST WINDOW");
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onShowAbout()));

    loginDialog = new LoginDialog( this );
//    loginDialog->setUsername( "Luca" );  // optional
//    connect( loginDialog, SIGNAL(acceptLogin(QString&,QString&,int&)), this, SLOT(slotAcceptUserLogin(QString&,QString&)));
    loginDialog->exec();
}

void MainWindow::onShowAbout() {
    dialog_about = new QMessageBox(this);
    dialog_about->about(this, "TEST", "TEST");
//    dialog_about->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
