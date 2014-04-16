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
//    setUpGUI();


}


//TODO Can modify this method to check for valid username when the username box loses focus and display neat message if
//the user is not found.
void LoginDialog::setUsername(QString &username){
//    bool found = false;
//    for( int i = 0; i < comboUsername->count() && ! found ; i++ )
//        if( comboUsername->itemText( i ) == username  ){
//            comboUsername->setCurrentIndex( i );
//            found = true;
//        }

//    if( ! found ){
//        int index = comboUsername->count();
//        qDebug() << "Select username " << index;
//        comboUsername->addItem( username );

//        comboUsername->setCurrentIndex( index );
//    }

//    // place the focus on the password field
//    editPassword->setFocus();
}

void LoginDialog::slotAcceptLogin(){
//    QString username = comboUsername->currentText();
//    QString password = editPassword->text();
//    int     index    = comboUsername->currentIndex();

//    emit acceptLogin( username,  // current username
//                      password,  // current password
//                      index      // index in the username list
//                      );

    // close this dialog
    close();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
