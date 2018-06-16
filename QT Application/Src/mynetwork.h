#ifndef MYNETWORK_H
#define MYNETWORK_H

#include <QObject>
#include <QUdpSocket>
#include "MyPropertyHelper.h"


class MyNetwork : public QObject
{
    Q_OBJECT
public:
    explicit MyNetwork(QObject *parent = nullptr);
    AUTO_PROPERTY(int, temperature)
    AUTO_PROPERTY(int, humidity)
signals:

public slots:
    void sendUDP(QString msg);

private slots:
    void readyReadUDP();

private:
    int udpPort = 8236 ;
    QUdpSocket *m_udpSocket = nullptr;

};

#endif // MYNETWORK_H
