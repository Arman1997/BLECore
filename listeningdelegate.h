#ifndef LISTENINGDELEGATE_H
#define LISTENINGDELEGATE_H

#include<servicedata.h>
#include<QObject>

class ConnectionDataSource
{
public:
    virtual void serviceUpdated(ServiceData  serviceData) = 0;
    virtual void serviceAdded(ServiceData serviceData) = 0;
    virtual void serviceRemoved(ServiceData serviceData) = 0;

    virtual ~ConnectionDataSource();

};

class QT_ConnectionDataSource: public QObject
{
 Q_OBJECT
public:

    QT_ConnectionDataSource(ConnectionDataSource* dataSource) {
        this->connectionDataSource = dataSource;
    }

private slots:

void serviceUpdated(ServiceData  serviceData)
{
    connectionDataSource->serviceUpdated(serviceData);
}

void serviceAdded(ServiceData serviceData)
{
    connectionDataSource->serviceAdded(serviceData);
}

void serviceRemoved(ServiceData serviceData)
{
    connectionDataSource->serviceRemoved(serviceData);
}

private:
    ConnectionDataSource* connectionDataSource;
};

#endif // LISTENINGDELEGATE_H
