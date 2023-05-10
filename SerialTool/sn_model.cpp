#include "sn_model.h"

snThread::snThread(QObject *parent) : QThread(parent)
{

}

void snThread::run()
{
    while(1)
    {
        ;
    }

}

void snThread::snCreate()
{
    ;
}

void snThread::createSnSlot(
        QString prefix, QString suffix,
        unsigned long mid, unsigned long i_mid_len,
        unsigned int i_quantity, unsigned int i_step,
        unsigned int i_base)
{
    QString s_sn = "";
    QString s_sn_tmp = "";
    QString s_result = "";

    unsigned long i = 0;
    unsigned long i_sn = mid;

    for(i = 0; i < i_quantity; i++)
    {
        i_sn = mid + i*i_step;
        s_sn_tmp = QString::number(i_sn, i_base);
        if(s_sn_tmp.length() > i_mid_len)
        {
            s_result.append("已超出范围！！\n");
            emit returnSnSignal(s_result);
            return;
        }

        if(i_base == 10)
        {
            s_sn.sprintf("%.*d", i_mid_len, i_sn);
        }
        else if(i_base == 16)
        {
            s_sn.sprintf("%.*X", i_mid_len, i_sn);
        }

        s_result.append(prefix + s_sn + suffix + "\n");
    }

    emit returnSnSignal(s_result);
}
