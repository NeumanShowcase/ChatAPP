#include "chatmeup.h"
#include "ui_chatmeup.h"

ChatMeUp::ChatMeUp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatMeUp)
{
    ui->setupUi(this);
    toggleConnectUI();
    ui->lbl_connectionStatus->setAlignment(Qt::AlignCenter);
    ui->actionDisconnect->setDisabled(true);
    // make the socket //
    mySocketConnection = new QTcpSocket;
    // connect socket event signal to corresponding functions //
    connect(mySocketConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(mySocketConnection,SIGNAL(disconnected()),this,SLOT(disconnectedFromServer()));

    connect(ui->inpt_msg, SIGNAL(textChanged()), this, SLOT(userTyping()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(exitApp()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(disconnect()));



    // fix for qt style bug //
    QColor col = QColor::fromRgb(30, 215, 96);
    if(col.isValid()) {
        QString qss = QString("background-color: %1").arg(col.name());
        ui->btn_connect->setStyleSheet(qss);
        ui->btn_sendMsg->setStyleSheet(qss);
    }

}


ChatMeUp::~ChatMeUp()
{
    delete mySocketConnection;
    delete ui;
}

bool ChatMeUp::makeConnection(QString ipAdress, QString portNumberString)
{

    mySocketConnection->connectToHost(ipAdress,portNumberString.toInt());
    ui->lbl_connectionStatus->setPixmap(QPixmap(":/resources/conn_makeConnect.png"));
    if(mySocketConnection->waitForConnected(2000))
    {
        qDebug() << "Connection was successfull!";
        toggleChatUI();

        ui->lbl_connectionStatus->setPixmap(QPixmap(":/resources/conn_connected.png"));
        return true;
    }
    else
    {
        ui->lbl_connectionStatus->setPixmap(QPixmap(":/resources/conn_disConnected.png"));
        throw QString("Could not connect to " + ipAdress);

    }
}

void ChatMeUp::keyPressEvent(QKeyEvent *event)
{
    qDebug () << event->key();
    if (event->key() == Qt::Key_Enter)
    {
        if (mySocketConnection->state() == QTcpSocket::ConnectedState)
            on_btn_sendMsg_clicked();
    }
}

void ChatMeUp::on_btn_connect_clicked()
{
    try
    {

        QString inputtedIp = ui->input_ip->toPlainText();
        QString choosenPort = ui->input_port->toPlainText();
        qDebug() << inputtedIp << choosenPort;

        makeConnection(inputtedIp, choosenPort);
        QString userName = ui->inpt_username->toPlainText();
        QByteArray sendUserName;
        sendUserName = "NAMECHANGEME:" + userName.toUtf8();
        mySocketConnection->write(sendUserName);


    }
    catch(QString ErrorCode)
    {
        QErrorMessage myException;
        myException.showMessage(ErrorCode);
        myException.exec();
    }



}

void ChatMeUp::readyRead()
{
    ui->lbl_messages->ensureCursorVisible();
    qDebug() << "Data to read";
    QString justRec = mySocketConnection->readLine();
    myRecievedMsgs += justRec + "\n";

    ui->lbl_messages->setText(myRecievedMsgs);

    // scroll down textwindow //

    QTextCursor cursor = ui->lbl_messages->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->lbl_messages->setTextCursor(cursor);
}

void ChatMeUp::on_btn_sendMsg_clicked()
{
    QString msgFromInput = ui->inpt_msg->toPlainText();
    ui->inpt_msg->clear();
    QByteArray sendMsg;
    sendMsg = msgFromInput.toUtf8();
    mySocketConnection->write(sendMsg);
}

void ChatMeUp::userTyping()
{
    if (ui->inpt_msg->toPlainText().length() > 1)
    {
        QString lookForNewRow = ui->inpt_msg->toPlainText();
        if (lookForNewRow[lookForNewRow.length()-1] == '\xa')
            on_btn_sendMsg_clicked();
    }

}
// if signal from socket "disconnected" //
void ChatMeUp::disconnectedFromServer()
{
    ui->lbl_connectionStatus->setPixmap(QPixmap(":/resources/conn_disConnected.png"));
    toggleConnectUI();
    QErrorMessage hostShutDown;
    hostShutDown.showMessage("Lost connection to server!");
    hostShutDown.exec();
}

void ChatMeUp::disconnect()
{
    qDebug () << "user choose to disconnect";
    ui->lbl_messages->clear();
    myRecievedMsgs.clear();
    mySocketConnection->disconnectFromHost();
}
// Handles user pushing exit button on window (make nice disconnect) //
void ChatMeUp::closeEvent(QCloseEvent *userQuit)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "ChatApp",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        userQuit->ignore();
    } else {
        userQuit->accept();
    }
}
void ChatMeUp::toggleChatUI(void)
{
    // hide connect ui related //
    ui->btn_connect->setVisible(false);
    ui->lbl_serverIp->setVisible(false);
    ui->lbl_serverport->setVisible(false);
    ui->input_ip->setVisible(false);
    ui->input_port->setVisible(false);
    ui->inpt_username->setVisible(false);
    ui->lbl_connectionStatus->setVisible(false);
    ui->lbl_nickname->setVisible(false);
    ui->actionDisconnect->setDisabled(false);

    // show chat ui related //
    ui->btn_sendMsg->setVisible(true);
    ui->lbl_messages->setVisible(true);
    ui->inpt_msg->setVisible(true);

}

void ChatMeUp::toggleConnectUI()
{
    // show connect ui related //
    ui->btn_connect->setVisible(true);
    ui->lbl_serverIp->setVisible(true);
    ui->lbl_serverport->setVisible(true);
    ui->input_ip->setVisible(true);
    ui->input_port->setVisible(true);
    ui->inpt_username->setVisible(true);
    ui->lbl_connectionStatus->setVisible(true);
    ui->lbl_nickname->setVisible(true);
    ui->actionDisconnect->setDisabled(true);
    // hide chat ui related //
    ui->btn_sendMsg->setVisible(false);
    ui->lbl_messages->setVisible(false);
    ui->inpt_msg->setVisible(false);

}

void ChatMeUp::exitApp()
{
    mySocketConnection->disconnectFromHost();
    QCoreApplication::quit();
}

