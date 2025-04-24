#include "activemsg.h"

activeMsg::activeMsg(QObject *parent) : QObject(parent)
{
    isStop = false;
    mHandle = XL_INVALID_PORTHANDLE;
}

void activeMsg::setactiveMsg(VCANMsg MessageBuffer)
{
    m_MessageBuffer = MessageBuffer;
}
void activeMsg::setactiveMsg_channle(VCANMsg MessageBuffer,XLportHandle handle)
{
    m_MessageBuffer = MessageBuffer;
    mHandle = handle;
}
void activeMsg::thread()
{
    qDebug() << "⼦线程号：";
    while (!isStop)
    {
        QThread::msleep(500);

        if(CAN_TransmitFD(&m_MessageBuffer,1) != 0)
            isStop = true;
        if(isStop)
        {
            break;
        }
    }
}

void activeMsg::thread_channel()
{
    qDebug() << "⼦线程号：";
    while (!isStop)
    {
        QThread::msleep(500);
        qDebug() << "handle" <<mHandle;
        if(CAN_TransmitFD_Send(&m_MessageBuffer,mHandle) != 0)
            isStop = true;
        if(isStop)
        {
            break;
        }
    }
}
