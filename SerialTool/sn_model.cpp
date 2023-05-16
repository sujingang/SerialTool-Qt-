#include "sn_model.h"

snThread::snThread(QObject *parent) : QThread(parent)
{
    isStart = false;
    isEnd = true;
}

void snThread::run()
{
    while(1)
    {
        if(isStart && isEnd)
        {
            isStart = false;
            isEnd = false;
            qDebug("call snCreate\n");
            snCreate();
        }
        usleep(10000);
    }

}

void snThread::snCreate()
{
    QString s_sn = "";
    QString s_sn_tmp = "";
    QString s_result = "";

    unsigned long i = 0;
    unsigned long i_sn = snCreateParam.i_mid_start;

    for(i = 0; i < snCreateParam.i_quantity; i++)
    {
        i_sn = snCreateParam.i_mid_start + i*snCreateParam.i_step;
        s_sn_tmp = QString::number(i_sn, snCreateParam.i_base);
        if(s_sn_tmp.length() > snCreateParam.i_mid_len)
        {
            s_result.append("已超出范围！！\n");
            emit returnSnSignal(s_result);
            return;
        }

        if(snCreateParam.i_base == 10)
        {
            s_sn.sprintf("%.*d", snCreateParam.i_mid_len, i_sn);
        }
        else if(snCreateParam.i_base == 16)
        {
            s_sn.sprintf("%.*X", snCreateParam.i_mid_len, i_sn);
        }

        s_result.append(snCreateParam.prefix + s_sn + snCreateParam.suffix + "\n");
    }

    emit returnSnSignal(s_result);

    isEnd = true;
}

void snThread::createSnSlot(SN_CREATE_PARAM createParam)
{
    snCreateParam.prefix = createParam.prefix;
    snCreateParam.suffix = createParam.suffix;
    snCreateParam.i_mid_start = createParam.i_mid_start;
    snCreateParam.i_mid_len = createParam.i_mid_len;
    snCreateParam.i_quantity = createParam.i_quantity;
    snCreateParam.i_step = createParam.i_step;
    snCreateParam.i_base = createParam.i_base;

    isStart = true;
}
