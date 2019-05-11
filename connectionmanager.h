#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include<servicedata.h>
#include<QObject>
#include<listenerdata.h>
#include<qbluetoothdevicediscoveryagent.h>
#include<listeningdelegate.h>

class ConnectionManager: public QObject
{
 Q_OBJECT
public:

    ConnectionManager(ConnectionDataSource* dataSource);

public slots:

void serviceUpdated(ServiceData  serviceData);

void serviceAdded(ServiceData serviceData);

void serviceRemoved(ServiceData serviceData);

void deviceAdded(const QBluetoothDeviceInfo &info);

void deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields);

private:
    ConnectionDataSource* connectionDataSource;
};


#endif // CONNECTIONMANAGER_H
