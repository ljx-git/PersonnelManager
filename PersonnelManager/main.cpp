#include "login.h"
#include <QApplication>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ManagerSystem");
    db.setUserName("root");
    db.setPassword("llll");
    if(db.open())
    {
        login l;
        l.show();
        return a.exec();
    }
    else
    {
        QMessageBox::information(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("系统载入数据库失败，无法运行"),QMessageBox::Yes);
    }

    return 0;
}
