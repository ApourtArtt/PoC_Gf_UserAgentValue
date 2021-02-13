#ifndef NETWORKREQUESTER_H
#define NETWORKREQUESTER_H

#include <QObject>
#include <QtNetwork>

class NetworkRequester : public QObject
{
    Q_OBJECT
public:
    explicit NetworkRequester(QObject *parent = nullptr) : QObject(parent) {}

    QByteArray post(QByteArray jsonRequest, QNetworkRequest header)
    {
        QSharedPointer<QNetworkReply> reply = QSharedPointer<QNetworkReply>(nam.post(header, jsonRequest));
        while (!reply->isFinished())
            qApp->processEvents();
        return reply->readAll();
    }

    QByteArray get(QNetworkRequest header)
    {
        QSharedPointer<QNetworkReply> reply = QSharedPointer<QNetworkReply>(nam.get(header));
        while(!reply->isFinished())
            qApp->processEvents();
        return reply->readAll();
    }

private:
    QNetworkAccessManager nam;
};

#endif // NETWORKREQUESTER_H
