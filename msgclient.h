#ifndef MSGCLIENT_H
#define MSGCLIENT_H
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QException>

class MsgClient
{
public:
    MsgClient();
    bool makeConnection(QString ipAdress, QString portNumberString);
    QTcpSocket& getSocket(void);
private:
    QTcpSocket* mySocketConnection;
};

#endif // MSGCLIENT_H
