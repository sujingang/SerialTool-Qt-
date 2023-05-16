#ifndef STR_MODEL_H
#define STR_MODEL_H

//1.继承QOject
#include <QObject>
#include <QThread>
#include <QtDebug>
#include <QTime>

#define type_number "0123456789"
#define type_letter_lower "abcdefghijklmnopqrstuvwxyz"
#define type_letter_upper "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct
{
    QString prefix;
    QString suffix;
    QString special;
    QString exclude;
    unsigned int i_quantity;
    unsigned int i_len;
    unsigned int i_type;
}STR_CREATE_PARAM, *P_STR_CREATE_PARAM;

//2.改为public QThread
class strThread : public QThread
{
    Q_OBJECT
public:
    void strCreate();
    void getStrSource();
    unsigned int getRandom(unsigned int min, unsigned int max);
    QString getRanString(unsigned int len);
    bool checkIndex(QList<unsigned int> list, unsigned int index);
    explicit strThread(QObject *parent = nullptr);

public slots:
    void createStrSlot(STR_CREATE_PARAM createParam);

signals:
    //自定义信号
    void  returnStrSignal(QString result);
//3.重写run函数
protected:
    void run() override;//线程入口函数

private:
    bool isStart;
    bool isEnd;
    QString str_number;
    QString str_letter_lower;
    QString str_letter_upper;

    QString str_source[5];
    unsigned int type_cnt;
    STR_CREATE_PARAM strCreateParam;
};

#endif // STR_MODEL_H
