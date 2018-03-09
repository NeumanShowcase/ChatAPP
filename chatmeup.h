#ifndef CHATMEUP_H
#define CHATMEUP_H

#include <QErrorMessage>
#include <QMainWindow>
#include "msgclient.h"
#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
class ChatMeUp;
}

class ChatMeUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatMeUp(QWidget *parent = 0);
    ~ChatMeUp();
    bool makeConnection(QString ipAdress, QString portNumberString);
    virtual void keyPressEvent(QKeyEvent *event);
    void toggleChatUI();
    void toggleConnectUI();

private slots:

    void exitApp();
    void on_btn_connect_clicked();
    void readyRead();
    void on_btn_sendMsg_clicked();
    void userTyping();
    void disconnectedFromServer(void);
    void disconnect(void);

private:

    Ui::ChatMeUp *ui;
    QTcpSocket* mySocketConnection;
    QString myRecievedMsgs;
    void closeEvent(QCloseEvent *bar);
};

#endif // CHATMEUP_H
