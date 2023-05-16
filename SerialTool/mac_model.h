#ifndef MAC_MODEL_H
#define MAC_MODEL_H

//1.继承QOject
#include <QObject>
#include <QThread>
#include <QtDebug>

typedef struct
{
    QString start;
    QString separator;
    unsigned long i_quantity;
    unsigned int i_step;
}MAC_CREATE_PARAM, *P_MAC_CREATE_PARAM;

//2.改为public QThread
class macThread : public QThread
{
    Q_OBJECT
public:
    void macCreate();
    explicit macThread(QObject *parent = nullptr);

public slots:
    void createMacSlot(MAC_CREATE_PARAM createParam);

signals:
    //自定义信号
    void  returnMacSignal(QString result);

//3.重写run函数
protected:
    void run() override;//线程入口函数

private:
    bool isStart;
    bool isEnd;
    MAC_CREATE_PARAM macCreateParam;
};

#endif // MAC_MODEL_H
