#include "mac_model.h"

macThread::macThread(QObject *parent) : QThread(parent)
{
    isStart = false;
    isEnd = true;
}

void macThread::run()
{
    while(1)
    {
        if(isStart && isEnd)
        {
            isStart = false;
            isEnd = false;
            qDebug("call macCreate\n");
            macCreate();
        }
        usleep(10000);
    }

}

void macThread::macCreate()
{
    QString s_mac = "";
    QString s_result = "";

    unsigned long i = 0;
    unsigned long long i_mac_start = macCreateParam.start.toLongLong(NULL, 16);
    unsigned long long i_mac = macCreateParam.start.toLongLong();

//    qDebug() << "start:" << macCreateParam.start;
//    qDebug() << "i_mac_start:" << i_mac_start;

    for(i = 0; i < macCreateParam.i_quantity; i++)
    {
        i_mac = i_mac_start + i * macCreateParam.i_step;

//        qDebug() << "mac:" << i_mac;

        s_mac.sprintf("%012llX", i_mac);

//        qDebug() << "s_mac:" << s_mac;

        if(!macCreateParam.separator.isEmpty())
        {
            s_mac.insert(2, macCreateParam.separator);
            s_mac.insert(5, macCreateParam.separator);
            s_mac.insert(8, macCreateParam.separator);
            s_mac.insert(11, macCreateParam.separator);
            s_mac.insert(14, macCreateParam.separator);
        }

        s_result.append(s_mac + "\n");
    }

    emit returnMacSignal(s_result);

    isEnd = true;
}

void macThread::createMacSlot(MAC_CREATE_PARAM createParam)
{
    macCreateParam.start = createParam.start;
    macCreateParam.separator = createParam.separator;
    macCreateParam.i_quantity = createParam.i_quantity;
    macCreateParam.i_step = createParam.i_step;

    isStart = true;
}
