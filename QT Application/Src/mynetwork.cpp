#include "mynetwork.h"

MyNetwork::MyNetwork(QObject *parent) : QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
    if(!m_udpSocket->bind(udpPort, QUdpSocket::ShareAddress )) //
        qDebug() << "m_udpSocket : " + m_udpSocket->errorString()  ;
    else
        qDebug() <<"UDP bind 127.0.0.1:" +QString::number(udpPort)+" LISTENING." ;

    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(readyReadUDP()));
    m_temperature = 0 ;
    m_humidity = 0 ;
}

void MyNetwork::sendUDP(QString msg)
{

}

void MyNetwork::readyReadUDP()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        QString data = datagram;
        qDebug() << "void MyNetwork::readyReadUDP(): "<< data ;
        if(data.contains("<temperature>"))
        {
            data.replace("<temperature>","");
            temperature(data.toDouble());
        }
        if(data.contains("<humidity>"))
        {
            data.replace("<humidity>","");
            humidity(data.toDouble());

        }



    }
}
