#include "mainwindow.h"
#include "sn_model.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("SerialTool");

    //....创建线程对象.......
    pSnThread = new snThread(this);
    pMacThread = new macThread(this);
    pStrThread = new strThread(this);

    //...调用run函数
    pSnThread->start();
    pMacThread->start();
    pStrThread->start();

    connect(pSnThread,SIGNAL(returnSnSignal(QString)), this,SLOT(getSnSlot(QString)));
    connect(this,SIGNAL(createSnSignal(SN_CREATE_PARAM)), pSnThread,SLOT(createSnSlot(SN_CREATE_PARAM)));

    connect(pMacThread,SIGNAL(returnMacSignal(QString)), this,SLOT(getMacSlot(QString)));
    connect(this,SIGNAL(createMacSignal(MAC_CREATE_PARAM)), pMacThread,SLOT(createMacSlot(MAC_CREATE_PARAM)));

    connect(pStrThread,SIGNAL(returnStrSignal(QString)), this,SLOT(getStrSlot(QString)));
    connect(this,SIGNAL(createStrSignal(STR_CREATE_PARAM)), pStrThread,SLOT(createStrSlot(STR_CREATE_PARAM)));

    //关闭窗口的时候结束线程
    connect(this,SIGNAL(destroyed()),this,SLOT(quitThreadSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSnSlot(QString result)
{
    ui->sn_result->setText(result);
    ui->sn_result->moveCursor(QTextCursor::End);
    ui->sn_create->setEnabled(true);
}

//线程结束函数
void MainWindow::quitThreadSlot()
{
    pSnThread->quit();
    pSnThread->wait();
    pSnThread->deleteLater();
}

void MainWindow::on_sn_create_clicked()
{
    ui->sn_result->clear();

    bool isError = false;

    QString s_sn_start = ui->sn_start->text().remove(QRegExp("\\s"));
    QString s_sn_prefix = ui->sn_prefix->text().remove(QRegExp("\\s"));
    QString s_sn_suffix = ui->sn_suffix->text().remove(QRegExp("\\s"));
    QString s_sn_quantity = ui->sn_quantity->text().remove(QRegExp("\\s"));
    QString s_sn_step = ui->sn_step->text().remove(QRegExp("\\s"));
    QString s_sn = "";
    QString s_sn_tmp = "";

    int i_sn_len = s_sn_start.length();
    int i_prefix_len = s_sn_prefix.length();
    int i_suffix_len = s_sn_suffix.length();

    if(i_sn_len == 0 || s_sn_start == "" || s_sn_start.isEmpty())
    {
        ui->sn_result->append("起始SN不能为空！！\n");
        isError = true;
    }

    if(s_sn_prefix != s_sn_start.mid(0, i_prefix_len))
    {
        ui->sn_result->append("前缀不一致！！\n");
        isError = true;
    }

    if(s_sn_suffix != s_sn_start.mid(i_sn_len - i_suffix_len, i_suffix_len))
    {
        ui->sn_result->append("后缀不一致！！\n");
        isError = true;
    }

    unsigned long i_mid_len = i_sn_len - (i_prefix_len + i_suffix_len);
    unsigned long i_mid_start = s_sn_start.mid(i_prefix_len, i_mid_len).toULong();
    unsigned long i_sn_quantity = s_sn_quantity.toULong();
    unsigned int i_sn_step = s_sn_step.toUInt();
    unsigned long i = 0;
    unsigned long i_sn = i_mid_start;
    unsigned long i_sn_base = 10;

    if(ui->sn_base->currentIndex() == 0)
    {
        i_sn_base = 10;
    }
    else if(ui->sn_base->currentIndex() == 1)
    {
        i_sn_base = 16;
    }

    if(i_sn_quantity == 0)
    {
        ui->sn_result->append("数量为0！！\n");
        isError = true;
    }

    if(isError == true)
    {
        return;
    }

    snCreateParam.prefix = s_sn_prefix;
    snCreateParam.suffix = s_sn_suffix;
    snCreateParam.i_mid_start = i_mid_start;
    snCreateParam.i_mid_len = i_mid_len;
    snCreateParam.i_quantity = i_sn_quantity;
    snCreateParam.i_step = i_sn_step;
    snCreateParam.i_base = i_sn_base;

    emit createSnSignal(snCreateParam);

    ui->sn_create->setEnabled(false);

//    s_result.sprintf("i_mid_start=%.*d\ni_sn_quantity=%d\ni_sn_step=%d\ni_sn_base=%d\n", i_sn_len - (i_prefix_len + i_suffix_len), i_mid_start, i_sn_quantity, i_sn_step, i_sn_base);
}

void MainWindow::getMacSlot(QString result)
{
    ui->mac_result->setText(result);
    ui->mac_result->moveCursor(QTextCursor::End);
    ui->mac_create->setEnabled(true);
}

void MainWindow::on_mac_create_clicked()
{
    QString mac_result = "";
    ui->mac_result->clear();

    bool isError = false;

    QString s_mac_start = ui->mac_start->text().remove(QRegExp("\\s"));
    QString s_mac_separator = ui->mac_separator->text().remove(QRegExp("\\s"));
    QString s_mac_quantity = ui->mac_quantity->text().remove(QRegExp("\\s"));
    QString s_mac_step = ui->mac_step->text().remove(QRegExp("\\s"));
    QString s_mac_real_start = "";
    QString s_mac_tmp = "";

    if(s_mac_start == "" || s_mac_start.isEmpty())
    {
        ui->mac_result->append("起始MAC不能为空！！\n");
        isError = true;
    }

    unsigned long i_mac_quantity = s_mac_quantity.toULong();
    unsigned int i_mac_len = s_mac_start.length();
    unsigned int i_mac_real_len = s_mac_start.length();
    unsigned int i_mac_separator_len = 1;
    unsigned int i_mac_step = s_mac_step.toUInt();
    unsigned long i = 0;

    if((i_mac_len > 12 && ((i_mac_len - 12) % 5 != 0)) || i_mac_len < 12)
    {
        ui->mac_result->append("MAC 长度不正确！！\n");
        isError = true;
    }
    else if(i_mac_len > 12)
    {
        i_mac_separator_len = (i_mac_len - 12) / 5;
        for(i = 0; i < 6; i++)
        {
            i_mac_real_len = s_mac_real_start.length();
            s_mac_real_start.append(s_mac_start.mid( i_mac_real_len + i * i_mac_separator_len, 2));
        }
    }
    else if(i_mac_len == 12)
    {
        s_mac_real_start = s_mac_start;
    }

    if(i_mac_quantity == 0)
    {
        ui->mac_result->append("数量为0！！\n");
        isError = true;
    }

    if(isError == true)
    {
        return;
    }

    qDebug() << "rel start:" << s_mac_start;
    qDebug() << "rel mac start:" << s_mac_real_start;

    macCreateParam.start = s_mac_real_start;
    macCreateParam.separator = s_mac_separator;
    macCreateParam.i_quantity = i_mac_quantity;
    macCreateParam.i_step = i_mac_step;

    emit createMacSignal(macCreateParam);

    ui->mac_create->setEnabled(false);

}

void MainWindow::getStrSlot(QString result)
{
//    qDebug() << "str:" << result;
    ui->str_result->setText(result);
    ui->str_result->moveCursor(QTextCursor::End);
    ui->str_create->setEnabled(true);
}

void MainWindow::on_str_create_clicked()
{
    ui->str_result->clear();

    bool isError = false;

    QString s_str_prefix = ui->str_prefix->text().remove(QRegExp("\\s"));
    QString s_str_suffix = ui->str_suffix->text().remove(QRegExp("\\s"));
    QString s_str_special = ui->str_special->text().remove(QRegExp("\\s"));
    QString s_str_exclude = ui->str_exclude->text().remove(QRegExp("\\s"));
    QString s_str_quantity = ui->str_quantity->text().remove(QRegExp("\\s"));
    QString s_str_len = ui->str_length->text().remove(QRegExp("\\s"));
    unsigned int i_str_type = ui->str_type->currentIndex();


    if((i_str_type == 4 || i_str_type == 8 ||
        i_str_type == 9 || i_str_type == 10 ||
        i_str_type == 11 || i_str_type == 12 ||
        i_str_type == 13 || i_str_type == 14) &&
        s_str_special.isEmpty())
    {
        ui->str_result->append("请填充特殊字符！！");
        isError = true;
    }

    if(s_str_quantity == "0")
    {
        ui->str_result->append("数量为0！！");
        isError = true;
    }

    if(s_str_len == "0")
    {
        ui->str_result->append("长度为0！！");
        isError = true;
    }

    if(isError == true)
    {
        return;
    }


    strCreateParam.prefix = s_str_prefix;
    strCreateParam.suffix = s_str_suffix;
    strCreateParam.special = s_str_special;
    strCreateParam.exclude = s_str_exclude;
    strCreateParam.i_quantity = s_str_quantity.toUInt();
    strCreateParam.i_len = s_str_len.toUInt();
    strCreateParam.i_type = i_str_type;

    emit createStrSignal(strCreateParam);

    ui->str_create->setEnabled(false);


}
