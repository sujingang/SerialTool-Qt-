#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include "sn_model.h"
#include "mac_model.h"
#include "str_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getSnSlot(QString result);
    void getMacSlot(QString result);
    void getStrSlot(QString result);
    //线程结束函数
    void quitThreadSlot();

private slots:
    void on_sn_create_clicked();

    void on_mac_create_clicked();

    void on_str_create_clicked();
signals:
    //自定义信号
    void  createSnSignal(SN_CREATE_PARAM createParamr);
    void  createMacSignal(MAC_CREATE_PARAM createParamr);
    void  createStrSignal(STR_CREATE_PARAM createParamr);

private:
    Ui::MainWindow *ui;

    //...线程对象....
    snThread *pSnThread;
    macThread *pMacThread;
    strThread *pStrThread;
    SN_CREATE_PARAM snCreateParam;
    MAC_CREATE_PARAM macCreateParam;
    STR_CREATE_PARAM strCreateParam;
};
#endif // MAINWINDOW_H
