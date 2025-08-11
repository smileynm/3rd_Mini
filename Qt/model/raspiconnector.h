#ifndef RASPICONNECTOR_H
#define RASPICONNECTOR_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class RaspiConnector : public QObject
{
    Q_OBJECT

signals:
    void logMessage(const QString& msg);
    void QRcodeData(const QByteArray& QRdata);

public:
    static RaspiConnector* getInstance();
    void startConnect(qint16 port = 12345);
    void disconnect();~RaspiConnector();
    RaspiConnector(const RaspiConnector&) = delete;
    RaspiConnector& operator=(const RaspiConnector&) = delete;
private:
    explicit RaspiConnector(QObject *parent = nullptr);
    void newConnection();
    void onReadyRead();

    static RaspiConnector* instance;

    QTcpServer *tcpServer;

};

#endif // RASPICONNECTOR_H
