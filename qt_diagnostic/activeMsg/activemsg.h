#ifndef ACTIVEMSG_H
#define ACTIVEMSG_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "diagTP/vectorCan.h"

class activeMsg : public QObject
{
    Q_OBJECT
public:
    explicit activeMsg(QObject *parent = nullptr);

    void setactiveMsg(VCANMsg MessageBuffer);

    void setactiveMsg_channle(VCANMsg MessageBuffer,XLportHandle handle);

    void thread();

    void thread_channel();
private:
    bool isStop;

    VCANMsg m_MessageBuffer;

    XLportHandle mHandle;

signals:

};

#endif // ACTIVEMSG_H
