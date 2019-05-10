#ifndef LISTENINGDELEGATE_H
#define LISTENINGDELEGATE_H

#include<servicedata.h>
#include<QObject>
#include<listenerdata.h>

class ConnectionDataSource
{
public:
    virtual void serviceUpdated(const ServiceData &serviceData) = 0;
    virtual void serviceAdded(const ServiceData &serviceData) = 0;
    virtual void serviceRemoved(const ServiceData &serviceData) = 0;

    virtual void deviceAdded(const BLEUserData &userData) = 0;
    virtual void deviceRemoved(const BLEUserData &userData) = 0;
    virtual void deviceUpdated(const BLEUserData &userData) = 0;

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

void deviceAdded(const BLEUserData &userData)
{
    connectionDataSource->deviceAdded(userData);
}

void deviceRemoved(const BLEUserData &userData)
{
    connectionDataSource->deviceRemoved(userData);
}

void deviceUpdated(const BLEUserData &userData)
{
    connectionDataSource->deviceUpdated(userData);
}

private:
    ConnectionDataSource* connectionDataSource;
};

#endif // LISTENINGDELEGATE_H
