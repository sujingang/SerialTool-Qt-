#ifndef SERIALTOOL_H
#define SERIALTOOL_H

//1.继承QOject
#include <QObject>
#include <QThread>
#include <QtDebug>

typedef struct
{
    QString prefix;
    QString suffix;
    unsigned long i_mid_start;
    unsigned long i_mid_len;
    unsigned int i_quantity;
    unsigned int i_step;
    unsigned int i_base;
}SN_CREATE_PARAM, *P_SN_CREATE_PARAM;

//2.改为public QThread
class snThread : public QThread
{
    Q_OBJECT
public:
    void snCreate();
    explicit snThread(QObject *parent = nullptr);

public slots:
    void createSnSlot(SN_CREATE_PARAM createParam);

signals:
    //自定义信号
    void  returnSnSignal(QString result);
//3.重写run函数
protected:
    void run() override;//线程入口函数

private:
    bool isStart;
    bool isEnd;
    SN_CREATE_PARAM snCreateParam;
};

#endif // SERIALTOOL_H
