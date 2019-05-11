#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include<servicedata.h>
#include<QObject>
#include<listenerdata.h>
#include<qbluetoothdevicediscoveryagent.h>
#include<listeningdelegate.h>

class QT_ConnectionDataSource: public QObject
{
 Q_OBJECT
public:

    QT_ConnectionDataSource(ConnectionDataSource* dataSource) {
        this->connectionDataSource = dataSource;
    }

public slots:

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

void deviceAdded(const QBluetoothDeviceInfo &info)
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        // connectionDataSource->deviceAdded(userData);
    }
}

void deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields)
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        //connectionDataSource->deviceUpdated(userData);
    }
}

private:
    ConnectionDataSource* connectionDataSource;
};


#endif // CONNECTIONMANAGER_H
