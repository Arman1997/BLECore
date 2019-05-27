#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <servicedata.h>
#include <QObject>
#include <listenerdata.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <connectiondatasource.h>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include "deviceinfo.h"
#include "qtconnectiondelegateadapter.h"
#include <optional>

class ConnectionManager: public QObject
{
 Q_OBJECT
public:

    ConnectionManager(ConnectionDataSource *dataSource,
                      QTConnectionDelegateAdapter *connectionDelegateAdapter);

    ~ConnectionManager();

public slots:

//void serviceUpdated(ServiceData  serviceData);

void serviceAdded(const QBluetoothUuid &newService);

//void serviceRemoved(ServiceData serviceData);

void deviceAdded(const QBluetoothDeviceInfo &info);

void deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields);

private:

void setNewDevice(const QBluetoothDeviceInfo &info);

void clearCurrentConnection();

private:
    ConnectionDataSource *m_connectionDataSource;
    DeviceInfo *m_currentDevice;
    QLowEnergyController *m_controller;
    QTConnectionDelegateAdapter *m_connectionDelegateAdapter;
};


#endif // CONNECTIONMANAGER_H
