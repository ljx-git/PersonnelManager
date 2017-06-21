#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);

    init();

    QTimer* timer = new QTimer(this);//用于时间显示
    connect(timer, SIGNAL(timeout()), this, SLOT(time_slot()));
    timer->start(1000);

    //为菜单栏的Action设置响应函数，可以将该QAction与QstackedWidget的相关页连接起来
    connect(ui->menubar,SIGNAL(triggered(QAction *)),this,SLOT(dothis(QAction *)));
    //menubar是定义的菜单栏，MainWindow是主界面
    connect(this,SIGNAL(tt(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    //stackedWidget是堆栈窗体，tt(int)是自定义信号

    //添加背景图且不会覆盖控件
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/new/prefix/stackedWidget.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);

    //创建model实现与数据库交互
    model = new QSqlTableModel(this);
    model->setTable("personinfo");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model1 = new QSqlTableModel(this);
    model1->setTable("user");
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model2 = new QSqlTableModel(this);
    model2->setTable("checkin");
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model3 = new QSqlTableModel(this);
    model3->setTable("checkin");
    model3->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->lineEdit_29->setEchoMode(QLineEdit::Password);
    ui->newLineEdit->setEchoMode(QLineEdit::Password);
    ui->affirmLineEdit->setEchoMode(QLineEdit::Password);
}

user::~user()
{
    delete ui;
}

void user::display()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void user::time()
{
    ui->timeLabel->setText((new QDateTime)->currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
}

void user::time_slot()
{
    ui->nowTimeLabel->setText((new QDateTime)->currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
}

void user::init()
{
    QIcon icon;
    icon.addPixmap(QPixmap(":/new/prefix/open.png"),QIcon::Normal, QIcon::On);   //节点打开状态图标
    icon.addPixmap(QPixmap(":/new/prefix/close.png"),QIcon::Normal, QIcon::Off); //节点关闭状态图标
    ui->treeWidget->clear();

    QTreeWidgetItem* selete = new QTreeWidgetItem(ui->treeWidget, QStringList(QStringLiteral("信息查询")));
    selete->setIcon(0, icon);
    ui->treeWidget->addTopLevelItem(selete);
    QTreeWidgetItem* seleteInfo = new QTreeWidgetItem(selete, QStringList(QStringLiteral("员工信息查询")));
    selete->addChild(seleteInfo);
    QTreeWidgetItem* seleteSala = new QTreeWidgetItem(selete, QStringList(QStringLiteral("薪资查询")));
    selete->addChild(seleteSala);
    QTreeWidgetItem* seleteCheck = new QTreeWidgetItem(selete, QStringList(QStringLiteral("考勤查询")));
    selete->addChild(seleteCheck);

    QTreeWidgetItem* lea = new QTreeWidgetItem(ui->treeWidget, QStringList(QStringLiteral("员工请假")));
    lea->setIcon(0, icon);
    ui->treeWidget->addTopLevelItem(lea);
    QTreeWidgetItem* meLea = new QTreeWidgetItem(lea, QStringList(QStringLiteral("我要请假")));
    lea->addChild(meLea);
}

void user::on_treeWidget_clicked(const QModelIndex &index)
{
    int nTopIndex = index.parent().row();     //获取父节点的值
    if (-1 == nTopIndex)     //根节点应该是
    {
        //QTreeWidgetItem *item = ui->treeWidget->currentItem();
        //item->setExpanded(!item->isExpanded());
        //这儿设置为当点击父节点时显示首页
        ui->stackedWidget->setCurrentIndex(0);
        return ;
    }

    // //因为user用户只有一个列选项，所以不用考虑节点值会和别的列重复
    int nCurrenIndex = index.row();
    int nIndex = nTopIndex<<3|nCurrenIndex;    //跟据父节点和子节点的值确定
    this->setWindowTitle(index.data().toString());
    this->setWindowTitle(index.data().toString());
    switch (nIndex)
    {
    case 0:
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case 1:
        ui->dateEdit_14->setDate(QDate::currentDate());
        model2->select();
        int j;

        for(j=0;j<model2->rowCount();j++)
        {
            if((model2->data(model2->index(j,0)) == jobNum) || (model2->data(model2->index(j, 1)) == nameStr))
            {
                break;
            }
        }

        ui->lineEdit_2->setText(model2->data(model2->index(j,4)).toString());
        ui->lineEdit_3->setText(model2->data(model2->index(j,5)).toString());


        model->select();
        int k;

        for(k=0;k<model->rowCount();k++)
        {
            if((model->data(model->index(j,0)) == jobNum) || (model->data(model->index(j, 1)) == nameStr))
            {
                break;
            }
        }
        ui->lineEdit_4->setText(model->data(model->index(k,5)).toString());
        int money;
        money=ui->lineEdit_4->text().toInt()-(ui->lineEdit_2->text().toInt()+ui->lineEdit_3->text().toInt())*100;
        ui->lineEdit_5->setText(QString::number(money,10));

        ui->stackedWidget->setCurrentIndex(2);
        break;
    case 2:
        ui->dateEdit_15->setDate((QDate::currentDate()));
        model2->select();
        int i;

        for(i=0;i<model2->rowCount();i++)
        {
            if((model2->data(model2->index(i,0)) == jobNum) || (model2->data(model2->index(i, 1)) == nameStr))
            {
                break;
            }
        }
        ui->lineEdit_9->setText(model2->data(model2->index(i,4)).toString());
        ui->lineEdit_10->setText(model2->data(model2->index(i,5)).toString());

        ui->stackedWidget->setCurrentIndex(3);
        break;
    case 8:
        ui->stackedWidget->setCurrentIndex(4);
        break;
    default:
        break;
    }
}

void user::dothis(QAction *action)
{
    //因为QAction的类型不能用swicth，所以这儿用if else实现
    if(action==ui->action_4)//UserInfoAction是定义的QAction，这里判断触发的QAction是否为UserInfoAction，是则发送信号
    {
        emit tt(5);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->action)//UserInfoAction是定义的QAction，这里判断触发的QAction是否为UserInfoAction，是则发送信号
    {
        emit tt(6);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->action_2)//UserInfoAction是定义的QAction，这里判断触发的QAction是否为UserInfoAction，是则发送信号
    {
        emit tt(7);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->action_3)//UserInfoAction是定义的QAction，这里判断触发的QAction是否为UserInfoAction，是则发送信号
    {
        //emit tt(4);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->action_5)//UserInfoAction是定义的QAction，这里判断触发的QAction是否为UserInfoAction，是则发送信号
    {
        model->select();
        int i;
        for(i=0;i<model->rowCount();i++)
        {
            if((model->data(model->index(i,0)) == jobNum) || (model->data(model->index(i, 1)) == nameStr))
            {
                break;
            }
        }

        ui->jobNumLineEdit_18->setText(model->data(model->index(i,0)).toString());
        ui->nameLineEdit_18->setText(model->data(model->index(i,1)).toString());
        ui->connLineEdit_18->setText(model->data(model->index(i,2)).toString());
        ui->posiLineEdit_13->setText(model->data(model->index(i,3)).toString());
        ui->departLineEdit_13->setText(model->data(model->index(i,4)).toString());
        ui->dateEdit_25->setDate(model->data(model->index(i,5)).toDate());
        emit tt(8);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->action_6)//UserInfoAction是定义的QAction，这里判断触发的QAction是否为UserInfoAction，是则发送信号
    {
        model->select();
        int i;
        for(i=0;i<model->rowCount();i++)
        {
            if((model->data(model->index(i,0)) == jobNum) || (model->data(model->index(i, 1)) == nameStr))
            {
                break;
            }
        }
        ui->jobNumLineEdit_19->setText(model->data(model->index(i,0)).toString());
        ui->nameLineEdit_19->setText(model->data(model->index(i,1)).toString());
        ui->connLineEdit_19->setText(model->data(model->index(i,2)).toString());
        ui->posiLineEdit_14->setText(model->data(model->index(i,3)).toString());
        ui->departLineEdit_14->setText(model->data(model->index(i,4)).toString());
        ui->dateEdit_26->setDate(model->data(model->index(i,5)).toDate());
        emit tt(9);//发射信号，这里需要使用emit关键字
    }
    else
    {
        return;
    }
}

void user::on_selectBtn_clicked()
{
    //当查询一次，不返回时，想查询另一个人的信息，那么当输入员工号，点击查询后，先清空原来的查询信息，再显示本次的查询信息
    ui->jobNumLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->connLineEdit->clear();
    ui->posiLineEdit->clear();
    ui->departLineEdit->clear();

    if(ui->selectLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请输入员工工号"),QMessageBox::Yes);
        return;
    }

    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)) == ui->selectLineEdit->text().toInt())
        {
            break;
        }
    }

    if(i!=model->rowCount())
    {
        ui->jobNumLineEdit->setText(model->data(model->index(i,0)).toString());
        ui->nameLineEdit->setText(model->data(model->index(i,1)).toString());
        ui->connLineEdit->setText(model->data(model->index(i,2)).toString());
        ui->posiLineEdit->setText(model->data(model->index(i,3)).toString());
        ui->departLineEdit->setText(model->data(model->index(i,4)).toString());
        ui->dateEdit_2->setDate(model->data(model->index(i,6)).toDate());
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void user::on_okBtn_11_clicked()
{
    model1->select();
    int i;
    for(i=0;i<model1->rowCount();i++)
    {
        if((model1->data(model1->index(i,0)) == jobNum) || (model1->data(model1->index(i, 1)) == nameStr))
        {
            break;
        }
    }

    if(ui->lineEdit_29->text()!=model1->data(model1->index(i,2)))
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("原密码输入错误"),QMessageBox::Yes);
        return;
    }

    if(ui->newLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请输入要修改的密码"),QMessageBox::Yes);
        return;
    }

    if(ui->newLineEdit->text() != ui->affirmLineEdit->text())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("两次输入的密码不一致"),QMessageBox::Yes);
        return;
    }

    //能登录成功，则说明用户存在于数据库表项中，所以不用判断i是否小于model->rowCount()
    model1->setData(model1->index(i, 2), ui->newLineEdit->text());
    if(model1->submitAll())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("密码修改成功"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("密码修改失败"),QMessageBox::Yes);
    }
    ui->lineEdit_29->clear();
    ui->newLineEdit->clear();
    ui->affirmLineEdit->clear();
}

void user::on_pushButton_28_clicked()
{
    model->select();
    int i;
    for(i=0;i<model->rowCount();i++)
    {
        if((model->data(model->index(i,0)) == jobNum) || (model->data(model->index(i, 1)) == nameStr))
        {
            break;
        }
    }

    model->setData(model->index(i, 1), ui->nameLineEdit_19->text());
    model->setData(model->index(i, 2), ui->connLineEdit_19->text());
    if(model->submitAll())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("信息修改成功"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("信息修改失败"),QMessageBox::Yes);
    }
}

void user::on_pushButton_27_clicked()
{
    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,1)).toString() == ui->lineEdit_28->text())
        {
            break;
        }
    }
    if(i!=model->rowCount())
    {
        model3->select();
        int j=model3->rowCount();
        model3->insertRow(j);
        model3->setData(model3->index(j,0),model->data(model->index(i,0)).toInt());
        model3->setData(model3->index(j,1),ui->lineEdit_28->text());
        model3->setData(model3->index(j,2),ui->textEdit_9->toPlainText());
        model3->setData(model3->index(j,3),ui->dateEdit_23->dateTime());
        model3->setData(model3->index(j,4),ui->dateEdit_24->dateTime());
        model3->setData(model3->index(j,5),0);

        if(model3->submitAll())
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请假信息提交成功"),QMessageBox::Yes);
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请假信息提交失败"),QMessageBox::Yes);
            return;
        }
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("您为什么不在员工表呢？what's your name?"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

