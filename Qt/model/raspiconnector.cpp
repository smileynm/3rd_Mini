#include "raspiconnector.h"

RaspiConnector* RaspiConnector::instance = nullptr;
RaspiConnector* RaspiConnector::getInstance(){
    if (!instance)
        instance = new RaspiConnector();

    return instance;
}



RaspiConnector::RaspiConnector(QObject *parent) : QObject (parent)
{
    tcpServer = new QTcpServer(this);
    connect (tcpServer, &QTcpServer::newConnection, this, &RaspiConnector::newConnection);
}


void RaspiConnector::startConnect(qint16 port)
{
    if (tcpServer->isListening()){ //이미 열려있으면 알려주는 용도
        qDebug() << "RaspiConnector is already running on port" << tcpServer->serverPort();
        return;
    }
    if (tcpServer->listen(QHostAddress::Any, port)){
        qDebug() << "[RaspiConnector] ▶️ Server started on port " << port; // 수신대기
    } else{
        qDebug() << "[RaspiConnector] ❌ Server failed " << tcpServer->errorString(); //연결 실패
    }
}

void RaspiConnector::disconnect(){
    if (tcpServer->isListening()) {
        tcpServer->close();
        qDebug() << "[RaspiConnector]️ Server stopped.";
    } else {
        qDebug() << "[RaspiConnector] Server was not running.";
    }
}

void RaspiConnector::newConnection(){

    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    qDebug() << "[Server] 🔌 클라이언트 접속:" << clientSocket->peerAddress().toString() << ":" << clientSocket->peerPort();
    qDebug().noquote() << QString("[RaspiConnector] 🔌 새 연결 수신 - IP: %1, Port: %2")
                              .arg(clientSocket->peerAddress().toString())
                              .arg(clientSocket->peerPort());
    emit logMessage(QString("🔌 클라이언트 접속: %1:%2")
                        .arg(clientSocket->peerAddress().toString())
                        .arg(clientSocket->peerPort()));

    connect (clientSocket, &QTcpSocket::readyRead, this, &RaspiConnector::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
        clientSocket->deleteLater();     // 메모리 정리
        qDebug() << "[RaspiConnector] Client disconnected.";
    });
}




void RaspiConnector::onReadyRead() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray QRdata = socket->readAll();
    emit logMessage(QString("[Server] 📥 수신 데이터: [ProductID: %1]")
                        .arg(QString::fromUtf8(QRdata)));

    emit QRcodeData(QRdata);
}




RaspiConnector::~RaspiConnector()
{
    if (tcpServer) {
        if (tcpServer->isListening())
            tcpServer->close();
        tcpServer->deleteLater();
        tcpServer = nullptr;
    }
    qDebug() << "[RaspiConnector] ✅ 소멸자 호출됨 (리소스 정리 완료)";
}
