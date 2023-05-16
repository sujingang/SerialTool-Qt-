#include "str_model.h"
strThread::strThread(QObject *parent) : QThread(parent)
{
    isStart = false;
    isEnd = true;
    str_source[0] = "";
    str_source[1] = "";
    str_source[2] = "";
    str_source[3] = "";
    type_cnt = 0;
}

void strThread::run()
{
    while(1)
    {
        if(isStart && isEnd)
        {
            isStart = false;
            isEnd = false;
            qDebug("call strCreate\n");
            strCreate();
        }
        usleep(10000);
    }

}

void strThread::getStrSource()
{
    switch (strCreateParam.i_type) {
    case 0:
        str_source[0] = str_number;
        type_cnt = 1;
        break;
    case 1:
        str_source[0] = str_letter_lower;
        type_cnt = 1;
        break;
    case 2:
        str_source[0] = str_letter_upper;
        type_cnt = 1;
        break;
    case 3:
        str_source[0] = str_letter_lower;
        str_source[1] = str_letter_upper;
        type_cnt = 2;
        break;
    case 4:
        str_source[0] = strCreateParam.special;
        type_cnt = 1;
        break;
    case 5:
        str_source[0] = str_number;
        str_source[1] = str_letter_lower;
        type_cnt = 2;
        break;
    case 6:
        str_source[0] = str_number;
        str_source[1] = str_letter_upper;
        type_cnt = 2;
        break;
    case 7:
        str_source[0] = str_number;
        str_source[1] = str_letter_lower;
        str_source[2] = str_letter_upper;
        type_cnt = 3;
        break;
    case 8:
        str_source[0] = str_number;
        str_source[1] = strCreateParam.special;
        type_cnt = 2;
        break;
    case 9:
        str_source[0] = strCreateParam.special;
        str_source[1] = str_letter_lower;
        type_cnt = 2;
        break;
    case 10:
        str_source[0] = strCreateParam.special;
        str_source[1] = str_letter_upper;
        type_cnt = 2;
        break;
    case 11:
        str_source[0] = strCreateParam.special;
        str_source[1] = str_letter_lower;
        str_source[2] = str_letter_upper;
        type_cnt = 3;
        break;
    case 12:
        str_source[0] = str_number;
        str_source[1] = str_letter_lower;
        str_source[2] = strCreateParam.special;
        type_cnt = 3;
        break;
    case 13:
        str_source[0] = str_number;
        str_source[1] = str_letter_upper;
        str_source[2] = strCreateParam.special;
        type_cnt = 3;
        break;
    case 14:
        str_source[0] = str_number;
        str_source[1] = str_letter_lower;
        str_source[2] = str_letter_upper;
        str_source[3] = strCreateParam.special;
        type_cnt = 4;
        break;
    default:
        str_source[0] = "";
        str_source[1] = "";
        str_source[2] = "";
        str_source[3] = "";
        type_cnt = 0;
        break;
    }
}

unsigned int strThread::getRandom(unsigned int min,unsigned int max)
{
    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));

    int num = qrand()%(max-min + 1);

//    qDebug() << "min:" << min << "max:" << max << "num:" << num;

    return num;
}

bool strThread::checkIndex(QList<unsigned int> list, unsigned int index)
{
    bool isNew = true;
    unsigned int i = 0;

    for(i = 0; i < list.size(); i++)
    {
        if(list[i] == index)
        {
            isNew = false;
            break;
        }
    }

    return isNew;
}

QString strThread::getRanString(unsigned int len)
{
    QString s_str;

//    s_str.fill('#', len);

    QList<unsigned int> list_src_index;
    QList<unsigned int> list_char_index;
    QList<unsigned int> list_pos_index;
    unsigned int src_index = 0;
    unsigned int src_loop_cnt = len / type_cnt;
    unsigned int pos_index = 0;
    unsigned int char_index = 0;
    unsigned int i = 0, j = 0;

    for(i = 0; i < len; i++)
    {
        if(type_cnt > 1)
        {
            if(i % type_cnt == 0)
            {
                list_src_index.clear();
            }
            do
            {
//                qDebug() << "src_index:";
                src_index = getRandom(0, type_cnt - 1);
            }while(!checkIndex(list_src_index, src_index));
//            qDebug() << "src_index:" << src_index;
            list_src_index.append(src_index);
        }
        do
        {
//            qDebug() << "char_index:";
            char_index = getRandom(0, str_source[src_index].length() - 1);
        }while(!checkIndex(list_char_index, char_index));
//        qDebug() << "char_index:" << char_index;
        list_char_index.append(char_index);

        do
        {
//            qDebug() << "pos_index:";
            pos_index = getRandom(0, len);
        }while(!checkIndex(list_pos_index, pos_index));
//        qDebug() << "pos_index:" << pos_index;

        list_pos_index.append(pos_index);

        s_str.insert(pos_index, str_source[src_index].mid(char_index,1));
    }

//    sleep(1);

//    qDebug() << "s_str:" << s_str.remove(QRegExp("\\s"));

    return s_str.remove(QRegExp("\\s"));
}

void strThread::strCreate()
{
    QString s_str = "";
    QString s_str_source = "";
    QString s_result = "";

    unsigned long i = 0;
    int index = 0;

    //剔除排除字符串
    str_number = type_number;
    str_letter_lower = type_letter_lower;
    str_letter_upper = type_letter_upper;
    for(i = 0; i < strCreateParam.exclude.length(); i++)
    {
        index = str_number.lastIndexOf(strCreateParam.exclude.mid(i, 1));
        if(index >= 0)
        {
//            qDebug() << "index:" << index << "exclude: " << strCreateParam.exclude.mid(i, 1);
            str_number.remove(index, 1);
        }

        index = str_letter_lower.lastIndexOf(strCreateParam.exclude.mid(i, 1));
        if(index >= 0)
        {
            str_letter_lower.remove(index, 1);
        }
        index = str_letter_upper.lastIndexOf(strCreateParam.exclude.mid(i, 1));
        if(index >= 0)
        {
            str_letter_upper.remove(index, 1);
        }

    }

    qDebug() << "str_number:" << str_number;
    qDebug() << "str_letter_lower:" << str_letter_lower;
    qDebug() << "str_letter_upper:" << str_letter_upper;

    if(str_number.isEmpty() || str_letter_lower.isEmpty() || str_letter_upper.isEmpty())
    {
        return;
    }

    getStrSource();

    qDebug() << "type_cnt:" << type_cnt << "i_quantity:" << strCreateParam.i_quantity << "len:" << strCreateParam.i_len;


    for(i = 0; i < strCreateParam.i_quantity; i++)
    {
//        qDebug() << "count:" << i + 1;
        s_result.append(strCreateParam.prefix + getRanString(strCreateParam.i_len) + strCreateParam.suffix + "\n");
    }

    emit returnStrSignal(s_result);

    isEnd = true;
}

void strThread::createStrSlot(STR_CREATE_PARAM createParam)
{
    strCreateParam.prefix = createParam.prefix;
    strCreateParam.suffix = createParam.suffix;
    strCreateParam.special = createParam.special;
    strCreateParam.exclude = createParam.exclude;
    strCreateParam.i_quantity = createParam.i_quantity;
    strCreateParam.i_len = createParam.i_len;
    strCreateParam.i_type = createParam.i_type;

    isStart = true;
}
