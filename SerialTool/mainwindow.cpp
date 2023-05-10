#include "mainwindow.h"
#include "serialtool.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sn_create_clicked()
{
    QString s_result = "";
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
    unsigned long i_sn_start = s_sn_start.mid(i_prefix_len, i_mid_len).toULong();
    unsigned long i_sn_quantity = s_sn_quantity.toULong();
    unsigned int i_sn_step = s_sn_step.toUInt();
    unsigned long i = 0;
    unsigned long i_sn = 0;
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

//    s_result.sprintf("i_sn_start=%.*d\ni_sn_quantity=%d\ni_sn_step=%d\ni_sn_base=%d\n", i_sn_len - (i_prefix_len + i_suffix_len), i_sn_start, i_sn_quantity, i_sn_step, i_sn_base);

    for(i = 0; i < i_sn_quantity; i++)
    {
        i_sn = i_sn_start + i*i_sn_step;
        s_sn_tmp = QString::number(i_sn, i_sn_base);
        if(s_sn_tmp.length() > i_mid_len)
        {
            ui->sn_result->append("已超出范围！！\n");
            return;
        }
        if(i_sn_base == 10)
        {
            s_sn.sprintf("%.*d", i_mid_len, i_sn);
        }
        else if(i_sn_base == 16)
        {
            s_sn.sprintf("%.*X", i_mid_len, i_sn);
        }

        s_result.append(s_sn_prefix + s_sn + s_sn_suffix + "\n");
    }

    ui->sn_result->append(s_result);
}

void MainWindow::on_mac_create_clicked()
{
    QString s_result = "";
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
    unsigned long i_sn_start = s_sn_start.mid(i_prefix_len, i_mid_len).toULong();
    unsigned long i_sn_quantity = s_sn_quantity.toULong();
    unsigned int i_sn_step = s_sn_step.toUInt();
    unsigned long i = 0;
    unsigned long i_sn = 0;
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

    s_result.sprintf("i_sn_start=%.*d\ni_sn_quantity=%d\ni_sn_step=%d\ni_sn_base=%d\n", i_sn_len - (i_prefix_len + i_suffix_len), i_sn_start, i_sn_quantity, i_sn_step, i_sn_base);

    for(i = 0; i < i_sn_quantity; i++)
    {
        i_sn = i_sn_start + i*i_sn_step;
        s_sn_tmp = QString::number(i_sn, i_sn_base);
        if(s_sn_tmp.length() > i_mid_len)
        {
            ui->sn_result->append("已超出范围！！\n");
            return;
        }
        if(i_sn_base == 10)
        {
            s_sn.sprintf("%.*d", i_mid_len, i_sn);
        }
        else if(i_sn_base == 16)
        {
            s_sn.sprintf("%.*X", i_mid_len, i_sn);
        }

        s_result.append(s_sn_prefix + s_sn + s_sn_suffix + "\n");
    }

    ui->sn_result->append(s_result);
}

void MainWindow::on_str_create_clicked()
{

}
