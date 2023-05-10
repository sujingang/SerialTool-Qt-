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

}

void MainWindow::on_mac_create_clicked()
{

}

void MainWindow::on_str_create_clicked()
{

}
