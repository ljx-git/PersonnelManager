#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "manager.h"
#include "user.h"
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QPalette>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_loginBtn_clicked();

    void on_exitBtm_clicked();

    void on_CommRaBt_clicked();

    void on_ManaRaBt_clicked();

private:
    Ui::login *ui;
    manager m;
    user u;
    QSqlTableModel *model;
    QSqlTableModel *model1;
};

#endif // LOGIN_H
