#include "manager.h"
#include "ui_manager.h"
#include <QDebug>

int flag=0;
int flag1=0;
int flag2=0;
int flag3=0;
int flag4=0;

manager::manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);

    //初始化导航栏
    init();

    QTimer* timer = new QTimer(this);//用于时间显示
    connect(timer, SIGNAL(timeout()), this, SLOT(time_slot()));
    timer->start(1000);

    this->setStyleSheet(0);
    //为菜单栏的Action设置响应函数，可以将该QAction与QstackedWidget的相关页连接起来
    connect(ui->menuBar,SIGNAL(triggered(QAction *)),this,SLOT(dothis(QAction *)));
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
    model2->setTable("depart");
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model3 = new QSqlTableModel(this);
    model3->setTable("checkin");
    model3->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model4 = new QSqlTableModel(this);
    model4->setTable("leav");
    model4->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), ui->comboBox_2, SLOT(process(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(process(int)));
    connect(ui->comboBox_5, SIGNAL(currentIndexChanged(int)), this, SLOT(process1(int)));

    ui->lineEdit_29->setEchoMode(QLineEdit::Password);
    ui->newLineEdit->setEchoMode(QLineEdit::Password);
    ui->affirmLineEdit->setEchoMode(QLineEdit::Password);
}

manager::~manager()
{
    delete ui;
}

void manager::display()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void manager::time()
{
     ui->timeLabel->setText((new QDateTime)->currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
}

void manager::time_slot()
{
     ui->nowTimeLabel->setText((new QDateTime)->currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
}

void manager::init()
{
    QIcon icon;
    icon.addPixmap(QPixmap(":/new/prefix/open.png"),QIcon::Normal, QIcon::On);   //节点打开状态图标
    icon.addPixmap(QPixmap(":/new/prefix/close.png"),QIcon::Normal, QIcon::Off); //节点关闭状态图标
    ui->treeWidget->clear();

    QTreeWidgetItem* manager = new QTreeWidgetItem(ui->treeWidget, QStringList(QStringLiteral("基本信息管理")));
    manager->setIcon(0, icon);
    ui->treeWidget->addTopLevelItem(manager);
    QTreeWidgetItem* seleteInfo = new QTreeWidgetItem(manager, QStringList(QStringLiteral("查询信息")));
    manager->addChild(seleteInfo);
    QTreeWidgetItem* addInfo = new QTreeWidgetItem(manager, QStringList(QStringLiteral("添加信息")));
    manager->addChild(addInfo);
    QTreeWidgetItem* alterInfo = new QTreeWidgetItem(manager, QStringList(QStringLiteral("修改信息")));
    manager->addChild(alterInfo);
    QTreeWidgetItem* eraseInfo = new QTreeWidgetItem(manager, QStringList(QStringLiteral("删除信息")));
    manager->addChild(eraseInfo);

    QTreeWidgetItem* salary = new QTreeWidgetItem(ui->treeWidget, QStringList(QStringLiteral("薪资管理")));
    salary->setIcon(0, icon);
    ui->treeWidget->addTopLevelItem(salary);
    QTreeWidgetItem* seleteSala = new QTreeWidgetItem(salary, QStringList(QStringLiteral("查询薪资")));
    salary->addChild(seleteSala);
    QTreeWidgetItem* alterSala = new QTreeWidgetItem(salary, QStringList(QStringLiteral("修改薪资")));
    salary->addChild(alterSala);

    QTreeWidgetItem* checkIn = new QTreeWidgetItem(ui->treeWidget, QStringList(QStringLiteral("考勤管理")));
    checkIn->setIcon(0, icon);
    ui->treeWidget->addTopLevelItem(checkIn);
    QTreeWidgetItem* seleteChe = new QTreeWidgetItem(checkIn, QStringList(QStringLiteral("查询考勤")));
    checkIn->addChild(seleteChe);
    QTreeWidgetItem* alterChe = new QTreeWidgetItem(checkIn, QStringList(QStringLiteral("修改考勤")));
    checkIn->addChild(alterChe);

    QTreeWidgetItem* depart = new QTreeWidgetItem(ui->treeWidget, QStringList(QStringLiteral("部门管理")));
    depart->setIcon(0, icon);
    ui->treeWidget->addTopLevelItem(depart);
    QTreeWidgetItem* seleteDepa = new QTreeWidgetItem(depart, QStringList(QStringLiteral("查询部门")));
    depart->addChild(seleteDepa);
    QTreeWidgetItem* addDepa = new QTreeWidgetItem(depart, QStringList(QStringLiteral("添加部门")));
    depart->addChild(addDepa);
    QTreeWidgetItem* alterDepa = new QTreeWidgetItem(depart, QStringList(QStringLiteral("修改部门")));
    depart->addChild(alterDepa);
    QTreeWidgetItem* eraseDepa = new QTreeWidgetItem(depart, QStringList(QStringLiteral("删除部门")));
    depart->addChild(eraseDepa);

    QTreeWidgetItem* leave = new QTreeWidgetItem(ui->treeWidget, QStringList(QStringLiteral("请假管理")));
    leave->setIcon(0, icon);
    ui->treeWidget->addTopLevelItem(leave);
    QTreeWidgetItem* leaveMe = new QTreeWidgetItem(leave, QStringList(QStringLiteral("我要请假")));
    leave->addChild(leaveMe);
    QTreeWidgetItem* approve = new QTreeWidgetItem(leave, QStringList(QStringLiteral("假条审批")));
    leave->addChild(approve);
}

void manager::on_treeWidget_clicked(const QModelIndex &index)
{
    int nTopIndex = index.parent().row();     //获取父节点的值
    if (-1 == nTopIndex)     //根节点应该是
    {
        //QTreeWidgetItem *item = ui->treeWidget->currentItem();
        // item->setExpanded(!item->isExpanded());
        //这儿设置为当点击父节点时显示首页
        ui->stackedWidget->setCurrentIndex(0);
        return ;
    }

    int nCurrenIndex = index.row();
    int nIndex = nTopIndex<<3|nCurrenIndex;    //跟据父节点和子节点的值确定
    this->setWindowTitle(index.data().toString());
    switch (nIndex)
    {
    //第0页是首页
    case 0:
        ui->selectLineEdit->clear();
        ui->jobNumLineEdit->clear();
        ui->nameLineEdit->clear();
        ui->connLineEdit->clear();
        ui->posiLineEdit->clear();
        ui->departLineEdit->clear();
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case 1:
    {   //为了避免case语句可能没有被执行到（执行其他case了）导致变量没有初始化而导致接下来的错误，加上大括号
        //设置下拉框内容
        if(flag==0)
        {
            setComboBox();
        }
        //设置lineEdit提示字段
        ui->nameLineEdit_7->setPlaceholderText(QString::fromLocal8Bit("请输入职工姓名"));
        setJobNum();
        ui->connLineEdit_7->setPlaceholderText(QString::fromLocal8Bit("请输入联系方式"));
        ui->salaLineEdit_3->setPlaceholderText(QString::fromLocal8Bit("请输入员工薪资"));
        ui->dateEdit_7->setDate((new QDate)->currentDate());
        ui->stackedWidget->setCurrentIndex(2);
        break;
    }
    case 2:
        ui->stackedWidget->setCurrentIndex(3);
        clearAllSea();
        break;
    case 3:
        ui->stackedWidget->setCurrentIndex(4);
        break;
    case 8:
        ui->stackedWidget->setCurrentIndex(5);
        break;
    case 9:
        ui->stackedWidget->setCurrentIndex(6);
        break;
    case 16:
        ui->stackedWidget->setCurrentIndex(7);
        break;
    case 17:
        ui->stackedWidget->setCurrentIndex(8);
        break;
    case 24:
        setComboBox_11();
        ui->stackedWidget->setCurrentIndex(9);
        break;
    case 25:
        //设置提示字段
        ui->lineEdit_25->setPlaceholderText(QString::fromLocal8Bit("请输入部门名称"));
        ui->lineEdit_11->setPlaceholderText(QString("0"));
        setDepartNum();
        ui->textEdit_4->setPlaceholderText(QString::fromLocal8Bit("请输入每行输入一个职位"));
        ui->textEdit_3->setPlaceholderText(QString::fromLocal8Bit("请输入部门职位信息"));
        ui->stackedWidget->setCurrentIndex(10);
        break;
    case 26:
        setComboBox_12();
        ui->stackedWidget->setCurrentIndex(11);
        break;
    case 27:
        setComboBox_13();
        ui->stackedWidget->setCurrentIndex(12);
        break;
    case 32:
        ui->dateEdit_23->setDate(QDate::currentDate());
        ui->dateEdit_24->setDate(QDate::currentDate());
        ui->stackedWidget->setCurrentIndex(13);
        break;
    case 33:
        ui->stackedWidget->setCurrentIndex(14);
        break;
    default:
        break;
    }
}

void manager::dothis(QAction *action)
{
    //因为QAction的类型不能用swicth，所以这儿用if else实现
    if(action==ui->about)//about是定义的QAction，这里判断触发的QAction是否为about，是则发送信号
    {
        emit tt(15);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->help)//help是定义的QAction，这里判断触发的QAction是否为help，是则发送信号
    {
        emit tt(16);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->alter)//alter是定义的QAction，这里判断触发的QAction是否为alter，是则发送信号
    {
        emit tt(17);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->exit)//exit是定义的QAction，这里判断触发的QAction是否为exit，是则发送信号
    {
        //emit tt(4);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->selete)//selete是定义的QAction，这里判断触发的QAction是否为selete，是则发送信号
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
        ui->dateEdit_25->setDate(model->data(model->index(i,6)).toDate());
        emit tt(18);//发射信号，这里需要使用emit关键字
    }
    else if(action==ui->alterme)//UserInfoAction是定义的QAction，这里判断触发的QAction是否为UserInfoAction，是则发送信号
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
        emit tt(19);//发射信号，这里需要使用emit关键字
    }
    else
    {
        return;
    }
}

//设置下拉框的显示内容
void manager::setComboBox()
{
    model2->select();
    int i=0;
    for(;i<model2->rowCount();++i)
    {
        ui->comboBox->insertItem(i,model2->data(model2->index(i,0)).toString());
    }
    flag=1;
}

void manager::setComboBox_11()
{
    if(flag2==0)
    {
        model2->select();
        int i=0;
        for(;i<model2->rowCount();++i)
        {
            ui->comboBox_11->insertItem(i,model2->data(model2->index(i,0)).toString());
        }
        flag2=1;
    }
}

void manager::setComboBox_12()
{
    if(flag3==0)
    {
        model2->select();
        int i=0;
        for(;i<model2->rowCount();++i)
        {
            ui->comboBox_11->insertItem(i,model2->data(model2->index(i,0)).toString());
        }
        flag2=1;
    }
}


void manager::setComboBox_13()
{
    if(flag4==0)
    {
        model2->select();
        int i=0;
        for(;i<model2->rowCount();++i)
        {
            ui->comboBox_11->insertItem(i,model2->data(model2->index(i,0)).toString());
        }
        flag2=1;
    }
}

//员工基本信息添加成功后，清空输入栏
void manager::clearAll()
{
    //QString::number() 将int转换为QString类型，括号里填int型数据
    //int num = ui->jobNumLineEdit->text().toInt() + 1;
    //ui->jobNumLineEdit->setText(QString::number(num));
    ui->jobNumLineEdit_7->clear();
    ui->nameLineEdit_7->clear();
    ui->connLineEdit_7->clear();
    ui->salaLineEdit_3->clear();
}

//判断添加员工时信息是否输入完整
bool manager::judgeEmpty()
{
    if(ui->nameLineEdit_7->text().isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("职工姓名不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->connLineEdit_7->text().isEmpty())
    {
        //设置只能输入数字
        if((ui->connLineEdit_7->text().toDouble()/10000000000)!=1)
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("请输入以1开口的11位数字"),QMessageBox::Yes);
            return false;
        }
        QRegExp regx("[0-9]+$");
        QValidator *validator = new QRegExpValidator(regx, ui->connLineEdit_7 );
        ui->connLineEdit_7->setValidator( validator);
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("职工联系方式不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->salaLineEdit_3->text().isEmpty())
    {
        //设置只能输入数字
        ui->salaLineEdit_3->setValidator(new QIntValidator(0, 1000000, this)); //0, 1000为输入的数字值范围
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("职工薪资不能为空"),QMessageBox::Yes);
        return false;
    }
    else
        return true;
}

void manager::setJobNum()
{
    model->select();
    int rowNum = model->rowCount(); //获得表的行数
    QString str = (new QDate)->currentDate().toString("yyyy");
    int num = str.toInt();
    int n;

    if(rowNum == 0)
    {
        n=num*10000+1;//model->setData(model->index(rowNum,0),num*10000+1);
    }
    else
    {
        n=model->data(model->index(rowNum - 1, 0)).toInt()+1;  //减一是因为数据表中行号是从1开始的
    }

    str=QString::number(n,10);
    //这儿要设置为settext方法，否则会因为文本框设置为enabled而获取不到文本框数据
    ui->jobNumLineEdit_7->setText(str);
    //ui->jobNumLineEdit_7->setPlaceholderText(str);
}

//添加员工基本信息
void manager::on_okBtn_5_clicked()
{
    if(!this->judgeEmpty())
        return;
    model->select();
    int i;
    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)) == ui->jobNumLineEdit_7->text().toInt())
        {
            break;
        }
    }
    if(i!=model->rowCount())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("职工工号已经存在"),QMessageBox::Yes);
        //this->clearAll();
        return;
    }

    //若是出现同名情况，进行处理：在名字后面加上字符做以区分
    QString str = ui->nameLineEdit_7->text();
    model->setFilter(QObject::tr("name = '%1'").arg(str)); //根据姓名进行筛选
    model->select();
    int count = model->rowCount();

    int rowNum = model->rowCount(); //获得表的行数
    model->insertRow(rowNum); //添加一行

    //设置添加的对应信息
    QChar c = 'a' + count - 1;
    if(count == 0)
    {
        model->setData(model->index(rowNum,1),ui->nameLineEdit_7->text());
    }
    else
    {
        model->setData(model->index(rowNum,1),ui->nameLineEdit_7->text()+QString(c));
    }

    model->setData(model->index(rowNum,0),ui->jobNumLineEdit_7->text().toInt());
    model->setData(model->index(rowNum,2),ui->connLineEdit_7->text());
    model->setData(model->index(rowNum,5),ui->salaLineEdit_3->text().toInt());
    model->setData(model->index(rowNum,3),ui->comboBox->currentText());
    model->setData(model->index(rowNum,4),ui->comboBox_2->currentText());
    model->setData(model->index(rowNum,6),ui->dateEdit_7->dateTime());

    //submitAll()->提交对表的修改
    if(model->submitAll())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("职工信息添加成功"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("职工信息添加失败"),QMessageBox::Yes);
        return;
    }

    int rowNum1 = model1->rowCount(); //获得表的行数
    model1->insertRow(rowNum1); //添加一行

    if(count == 0)
    {
        model1->setData(model1->index(rowNum1,1),ui->nameLineEdit_7->text());
    }
    else
    {
        model1->setData(model1->index(rowNum1,1),ui->nameLineEdit_7->text()+QString(c));
    }
    model1->setData(model1->index(rowNum1,0),ui->jobNumLineEdit_7->text().toInt());
    model1->setData(model1->index(rowNum1,2),"123456");

    if(ui->managerRB_3->isChecked())
    {
         model1->setData(model1->index(rowNum1,3),1);
    }
    else
    {
         model1->setData(model1->index(rowNum1,3),0);
    }
    model1->submitAll();   //只有提交了修改，添加才生效

    //更新部门人数
    model2->select();
    for(i=0;i<model2->rowCount();i++)
    {
        if(ui->comboBox->currentText()==model2->data(model2->index(i,0)))
        {
            break;
        }
    }
    model2->setData(model2->index(i,3),model2->data(model2->index(i,3)).toInt()+1);
    model2->submitAll();   //只有提交了修改，添加才生效

     //更新考勤表，加入新员工考勤信息
    model3->select();
    int rowNum2 = model3->rowCount(); //获得表的行数
    model3->insertRow(rowNum2); //添加一行

    if(count == 0)
    {
        model3->setData(model3->index(rowNum2,1),ui->nameLineEdit_7->text());
    }
    else
    {
        model3->setData(model3->index(rowNum2,1),ui->nameLineEdit_7->text()+QString(c));
    }
    model3->setData(model3->index(rowNum2,0),ui->jobNumLineEdit_7->text().toInt());

    model3->setData(model3->index(rowNum2,2),ui->dateEdit_7->dateTime().toString("yyyy").toInt());
    model3->setData(model3->index(rowNum2,3),ui->dateEdit_7->dateTime().toString("MM").toInt());
    model3->setData(model3->index(rowNum2,4),"0");
    model3->setData(model3->index(rowNum2,5),"0");

    model3->submitAll();   //只有提交了修改，添加才生效

    //只有等user也添加了信息才能清空输入框，不然清空了后user表添加不了信息
    this->clearAll();
    setJobNum();
}

void manager::on_selectBtn_clicked()
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
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_cancleBtn_3_clicked()
{
    clearAll();
    ui->stackedWidget->setCurrentIndex(0);
}

bool manager::isDepartEmpty()
{
    if(ui->lineEdit_25->text().isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("部门名不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->textEdit_4->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("部门职位列表不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->textEdit_3->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("部门职责不能为空"),QMessageBox::Yes);
        return false;
    }
    return true;
}

void manager::setDepartNum()
{
    model2->select();
    int rowCount=model2->rowCount();
    int newRow=rowCount+1;
    int bit=0;
    while(newRow>0)
    {
        newRow/=10;
        bit++;
    }

    //设置部门编号为4位数，不够的前面补0
    int i=4;
    QString number;
    while((i-bit)>0)
    {
        number+="0";
        i--;
    }

    newRow=rowCount+1;
    number+=QString::number(newRow,10);
    //ui->lineEdit_26->setPlaceholderText(number);
    ui->lineEdit_26->setText(number);
}

void manager::clearAllDepart()
{
    ui->lineEdit_25->clear();
    ui->lineEdit_26->clear();
    ui->textEdit_4->clear();
    ui->textEdit_3->clear();
}

void manager::on_pushButton_18_clicked()
{
    if(!isDepartEmpty())
    {
        return;
    }
    model2->select();
    int i = 0;
    for(i=0;i<model2->rowCount();i++)
    {
        if(model2->data(model2->index(i,0)) == ui->lineEdit_25->text())
        {
            break;
        }
    }
    if(i!=model2->rowCount())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("部门名已经存在"),QMessageBox::Yes);
        return;
    }

    int rowNum=model2->rowCount();
    model2->insertRow(rowNum); //添加一行
    model2->setData(model2->index(rowNum,0),ui->lineEdit_25->text());
    model2->setData(model2->index(rowNum,4),ui->lineEdit_26->text().toInt());
    model2->setData(model2->index(rowNum,1),ui->textEdit_4->toPlainText());
    model2->setData(model2->index(rowNum,2),ui->textEdit_3->toPlainText());
    model2->setData(model2->index(rowNum,3),ui->lineEdit_11->text().toInt());

    //submitAll()->提交对表的修改
    if(model2->submitAll())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("部门信息添加成功"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("部门信息添加失败"),QMessageBox::Yes);
        return;
    }
    clearAllDepart();
    setDepartNum();
}

void manager::on_pushButton_19_clicked()
{
    clearAllDepart();
    ui->stackedWidget->setCurrentIndex(0);
}

void manager::process(int index)
{
    ui->comboBox_2->clear();
    ui->textEdit_10->setPlainText(model2->data(model2->index(index,1)).toString());

    int n;
    int Number=ui->textEdit_10->document()->lineCount(); //读取TextEdit里的行数
    QStringList list;
    for(n=0;n<Number;n++)
    {
        QString str=ui->textEdit_10->toPlainText().section('\n',n-Number,n-Number,QString::SectionSkipEmpty); //取得每行（以换行符进行换行）
        list<<str;
    }
    ui->comboBox_2->insertItems(0,list);
}

void manager::clearAllSea()
{
    //当查询一次，不返回时，想查询另一个人的信息，那么当输入员工号，点击查询后，先清空原来的查询信息，再显示本次的查询信息
    ui->jobNumLineEdit_3->clear();
    ui->nameLineEdit_3->clear();
    ui->connLineEdit_3->clear();
    ui->comboBox_5->clear();
    ui->comboBox_6->clear();
    ui->dateEdit_3->clear();
    ui->searchLineEdit_3->clear();
}

void manager::on_searchBtn_3_clicked()
{
    if(ui->searchLineEdit_3->text().isEmpty())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请输入员工工号"),QMessageBox::Yes);
        return;
    }

    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)) == ui->searchLineEdit_3->text().toInt())
        {
            break;
        }
    }

    if(i!=model->rowCount())
    {
        if(flag1==0)
        {
            model2->select();
            int i=0;
            for(;i<model2->rowCount();++i)
            {
                ui->comboBox_5->insertItem(i,model2->data(model2->index(i,0)).toString());
            }
            flag1=1;
        }
        ui->jobNumLineEdit_3->setText(model->data(model->index(i,0)).toString());
        ui->nameLineEdit_3->setText(model->data(model->index(i,1)).toString());
        ui->connLineEdit_3->setText(model->data(model->index(i,2)).toString());
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::process1(int index)
{
    ui->comboBox_6->clear();
    ui->textEdit_10->setPlainText(model2->data(model2->index(index,1)).toString());

    int n;
    int Number=ui->textEdit_10->document()->lineCount(); //读取TextEdit里的行数
    QStringList list;
    for(n=0;n<Number;n++)
    {
        QString str=ui->textEdit_10->toPlainText().section('\n',n-Number,n-Number,QString::SectionSkipEmpty); //取得每行（以换行符进行换行）
        list<<str;
    }
    ui->comboBox_6->insertItems(0,list);
}

void manager::on_okBtn_2_clicked()
{
    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)) == ui->searchLineEdit_3->text().toInt())
        {
            break;
        }
    }

    if(i!=model->rowCount())
    {
        model2->select();
        int rowNum1=model2->rowCount();
        int n;
        for(n=0;n<rowNum1;n++)
        {
            if(model2->data(model2->index(n,0))==model->data(model->index(i,3)))
            {
                    break;
            }
        }
        model2->setData(model2->index(n,3),model2->data(model2->index(n,3)).toInt()-1);
        model2->submitAll();

        model->select();
        int rowNum=model->rowCount();
        model->setData(model->index(i,1),ui->nameLineEdit_3->text());
        model->setData(model->index(i,2),ui->connLineEdit_3->text());
        model->setData(model->index(i,3),ui->comboBox_5->currentText());
        model->setData(model->index(i,4),ui->comboBox_6->currentText());
        //submitAll()->提交对表的修改
        if(model->submitAll())
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("职工信息修改成功"),QMessageBox::Yes);
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("职工信息修改失败"),QMessageBox::Yes);
            return;
        }


        model2->select();
        rowNum1=model2->rowCount();
        for(n=0;n<rowNum1;n++)
        {
            if(model2->data(model2->index(n,0))==model->data(model->index(i,3)))
            {
                    break;
            }
        }
        model2->setData(model2->index(n,3),model2->data(model2->index(n,3)).toInt()+1);
        model2->submitAll();
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_selectBtn_5_clicked()
{
    if(ui->selectLineEdit_5->text().isEmpty())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("请输入员工工号"),QMessageBox::Yes);
        return;
    }

    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)) == ui->selectLineEdit_5->text().toInt())
        {
            break;
        }
    }

    if(i!=model->rowCount())
    {
        ui->jobNumLineEdit_13->setText(model->data(model->index(i,0)).toString());
        ui->nameLineEdit_13->setText(model->data(model->index(i,1)).toString());
        ui->connLineEdit_13->setText(model->data(model->index(i,2)).toString());
        ui->posiLineEdit_9->setText(model->data(model->index(i,3)).toString());
        ui->departLineEdit_9->setText(model->data(model->index(i,4)).toString());
        ui->dateEdit_13->setDate(model->data(model->index(i,5)).toDate());
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_pushButton_clicked()
{
    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)) == ui->selectLineEdit_5->text().toInt())
        {
            break;
        }
    }

    if(i!=model->rowCount())
    {
        model1->select();
        int n;

        for(n=0;n<model1->rowCount();n++)
        {
            if(model1->data(model1->index(n,0)) == ui->selectLineEdit_5->text().toInt())
            {
                break;
            }
        }
        model1->removeRow(n);
        model1->submitAll();

        model3->select();
        int j;

        for(j=0;j<model3->rowCount();j++)
        {
            if(model3->data(model3->index(j,0)) == ui->selectLineEdit_5->text().toInt())
            {
                break;
            }
        }
        model3->removeRow(j);
        model3->submitAll();

        model->removeRow(i);
        //submitAll()->提交对表的修改
        if(model->submitAll())
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("职工信息删除成功"),QMessageBox::Yes);
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("职工信息删除失败"),QMessageBox::Yes);
            return;
        }
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_pushButton_13_clicked()
{
    ui->dateEdit_22->setDate((new QDate)->currentDate());
    model3->select();
    int i;

    for(i=0;i<model3->rowCount();i++)
    {
        if(model3->data(model3->index(i,0)) == ui->lineEdit_21->text().toInt())
        {
            break;
        }
    }
    if(i!=model3->rowCount())
    {
        ui->lineEdit_9->setText(model3->data(model3->index(i,4)).toString());
        ui->lineEdit_10->setText(model3->data(model3->index(i,5)).toString());
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_pushButton_14_clicked()
{
    ui->dateEdit_22->setDate((new QDate)->currentDate());
    model3->select();
    int i;

    for(i=0;i<model3->rowCount();i++)
    {
        if(model3->data(model3->index(i,0)).toInt() == ui->lineEdit_22->text().toInt())
        {
            break;
        }
    }
    if(i!=model3->rowCount())
    {
        ui->lineEdit_24->setText(model3->data(model3->index(i,4)).toString());
        ui->lineEdit_23->setText(model3->data(model3->index(i,5)).toString());
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_pushButton_15_clicked()
{
    ui->dateEdit_22->setDate((new QDate)->currentDate());
    model3->select();
    int i;

    for(i=0;i<model3->rowCount();i++)
    {
        if(model3->data(model3->index(i,0)).toInt() == ui->lineEdit_22->text().toInt())
        {
            break;
        }
    }
    model3->setData(model3->index(i,4),ui->lineEdit_24->text().toInt());
    model3->setData(model3->index(i,5),ui->lineEdit_23->text().toInt());
    if(model3->submitAll())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("考勤信息修改成功"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("考勤信息修改失败"),QMessageBox::Yes);
        return;
    }
}

void manager::on_pushButton_3_clicked()
{
    model3->select();
    int i;

    int n=0;
    QString str="";
    for(i=0;i<model3->rowCount();i++)
    {
        if(model3->data(model3->index(i,0)).toInt() == ui->lineEdit->text().toInt())
        {
            n=ui->lineEdit->text().toInt();
            break;
        }
        else if(model3->data(model3->index(i,1)).toString() == ui->lineEdit->text())
        {
            str=ui->lineEdit->text();
            break;
        }
        else
            ;
    }

    if(i!=model3->rowCount())
    {
        ui->lineEdit_2->setText(model3->data(model3->index(i,4)).toString());
        ui->lineEdit_3->setText(model3->data(model3->index(i,5)).toString());


        model->select();
        int j;

        for(j=0;j<model->rowCount();j++)
        {
            if(n == 0)
            {
                if(model->data(model->index(j,1)).toString() == ui->lineEdit->text())
                {
                    break;
                }
            }
            else
            {
                if(model->data(model->index(j,0)).toInt() == ui->lineEdit->text().toInt())
                {
                    break;
                }
            }
        }
        ui->lineEdit_4->setText(model->data(model->index(j,5)).toString());
        int money=ui->lineEdit_4->text().toInt()-(ui->lineEdit_2->text().toInt()+ui->lineEdit_3->text().toInt())*100;
        ui->lineEdit_5->setText(QString::number(money,10));
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_pushButton_4_clicked()
{
    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)).toInt() == ui->lineEdit_6->text().toInt())
        {
            break;
        }
    }
    if(i!=model->rowCount())
    {
       ui->lineEdit_7->setText(model->data(model->index(i,5)).toString());
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("该工号无对应的职工"),QMessageBox::Yes);
        ui->selectLineEdit->clear();
        return;
    }
}

void manager::on_pushButton_5_clicked()
{
    model->select();
    int i;

    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)).toInt() == ui->lineEdit_6->text().toInt())
        {
            break;
        }
    }
    model->setData(model->index(i,5),ui->lineEdit_8->text().toInt());
    if(model->submitAll())
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("薪资信息修改成功"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("薪资信息修改失败"),QMessageBox::Yes);
        return;
    }

}

void manager::on_pushButton_27_clicked()
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
        model4->select();
        int j=model4->rowCount();
        model4->insertRow(j);
        model4->setData(model4->index(j,0),model->data(model->index(i,0)).toInt());
        model4->setData(model4->index(j,1),ui->lineEdit_28->text());
        model4->setData(model4->index(j,2),ui->textEdit_9->toPlainText());
        model4->setData(model4->index(j,3),ui->dateEdit_23->date());
        model4->setData(model4->index(j,4),ui->dateEdit_24->date());
        model4->setData(model4->index(j,5),0);

        if(model4->submitAll())
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

void manager::on_pushButton_26_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void manager::on_pushButton_17_clicked()
{
    model2->select();
    int i;

    for(i=0;i<model2->rowCount();i++)
    {
        if(model2->data(model2->index(i,0)).toString() == ui->comboBox_11->currentText())
        {
            break;
        }
    }
    ui->lineEdit_12->setText(model2->data(model2->index(i,3)).toString());
    ui->textEdit->setPlainText(model2->data(model2->index(i,1)).toString());
    ui->textEdit_2->setPlainText(model2->data(model2->index(i,2)).toString());
}

void manager::on_pushButton_20_clicked()
{
    model2->select();
    int i;

    for(i=0;i<model2->rowCount();i++)
    {
        if(model2->data(model2->index(i,0)).toString() == ui->comboBox_12->currentText())
        {
            break;
        }
    }
    ui->lineEdit_13->setText(model2->data(model2->index(i,3)).toString());
    ui->textEdit_6->setPlainText(model2->data(model2->index(i,1)).toString());
    ui->textEdit_5->setPlainText(model2->data(model2->index(i,2)).toString());
}

void manager::on_pushButton_21_clicked()
{
    model2->select();
    int i;

    for(i=0;i<model2->rowCount();i++)
    {
        if(model2->data(model2->index(i,0)).toString() == ui->comboBox_13->currentText())
        {
            break;
        }
    }
    //model4->setData(model4->index(i,5),0);

    //if(model4->submitAll())
   // {
   //     QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("部门信息修改成功"),QMessageBox::Yes);
   // }
  //  else
   // {
    //    QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("部门信息修改失败"),QMessageBox::Yes);
    //    return;
  //  }
    //这儿修改的话员工信息表也要修改
}

void manager::on_pushButton_23_clicked()
{

}

void manager::on_pushButton_24_clicked()
{

}


void manager::on_okBtn_11_clicked()
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

void manager::on_pushButton_28_clicked()
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
