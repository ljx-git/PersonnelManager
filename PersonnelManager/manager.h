#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include "QDateTime"
#include <qtimer.h>
#include <QSqlTableModel>
#include <QMessageBox>

extern int jobNum;
extern QString nameStr;

namespace Ui {
class manager;
}

class manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = 0);
    ~manager();

    void display();

    void init();

    void time();

    void clearAll();

    bool judgeEmpty();

    void setJobNum();

    bool isDepartEmpty();

    void clearAllDepart();

    void setDepartNum();

    void setComboBox();

    void setComboBox_11();

    void setComboBox_12();

    void setComboBox_13();


    void clearAllSea();

private:
signals:
    void tt(int index);//自定义信号

public slots:
   void time_slot();

   //void process(int index);

private slots:
    void on_treeWidget_clicked(const QModelIndex &index);

    void dothis(QAction *action);

    void on_okBtn_5_clicked();

    void on_selectBtn_clicked();

    void on_cancleBtn_3_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void process(int index);

    void process1(int index);

    void on_searchBtn_3_clicked();

    void on_okBtn_2_clicked();

    void on_selectBtn_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_okBtn_11_clicked();

    void on_pushButton_28_clicked();

private:
    Ui::manager *ui;
    QSqlTableModel *model;
    QSqlTableModel *model1;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlTableModel *model4;
};

#endif // MANAGER_H
