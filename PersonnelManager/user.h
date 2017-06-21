#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "QDateTime"
#include <qtimer.h>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>

extern int jobNum;
extern QString nameStr;

namespace Ui {
class user;
}

class user : public QMainWindow
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

    void display();

    void init();

    void time();

private:
signals:
    void tt(int index);//自定义信号

public slots:
    void time_slot();

private slots:
    void on_treeWidget_clicked(const QModelIndex &index);

    void dothis(QAction *action);

    void on_selectBtn_clicked();

    void on_okBtn_11_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::user *ui;
    QSqlTableModel *model;
    QSqlTableModel *model1;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
};

#endif // USER_H
