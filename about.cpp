#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());

    ui->logo->setStyleSheet("border-image: url(images/logo.png)");
}

About::~About()
{
    delete ui;
}
