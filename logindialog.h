#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>

namespace Ui {
class LoginDialog;
}

/*!
 *Makes class LoginDialog a child to its parent, QDialog
 */
class LoginDialog : public QDialog
{
/*!
 *Turns Login Dialog into a QObject
 */
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    void setUsername( QString& username );

private:
    Ui::LoginDialog *ui;

signals:

    //TODO Looks like auto documenation is possible. Figure it out and use it.
    /*!
      * A signal emitted when the login is performed.
      * \param username the username entered in the dialog
      * \param password the password entered in the dialog
      * \param index the number of the username selected in the combobox
      */
    void acceptLogin( QString& username, QString& password, int& indexNumber );

public slots:
    /*!
      * A lot to adjust the emitting of the signal.
      */
    void slotAcceptLogin();

};

#endif // LOGINDIALOG_H
