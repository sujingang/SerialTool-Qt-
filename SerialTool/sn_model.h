#ifndef SERIALTOOL_H
#define SERIALTOOL_H

//1.继承QOject
#include <QObject>
#include<QThread>

//2.改为public QThread
class snThread : public QThread
{
    Q_OBJECT
public:
    void snCreate();
    explicit snThread(QObject *parent = nullptr);

public slots:
    void createSnSlot(QString prefix, QString suffix, unsigned long mid, unsigned long i_mid_len, unsigned int i_quantity, unsigned int i_step, unsigned int i_base);

signals:
    //自定义信号
    void  returnSnSignal(QString result);
//3.重写run函数
protected:
    void run();//线程入口函数

private:
    bool isStart;
};

#endif // SERIALTOOL_H
