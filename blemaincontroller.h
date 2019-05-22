#ifndef BLEMAINCONTROLLER_H
#define BLEMAINCONTROLLER_H

#include "qtconnectiondelegateadapter.h"
#include <connectiondatasource.h>
#include <qbluetoothdevicediscoveryagent.h>
#include "connectionmanager.h"
#include "blemessage.h"


class BLEMainController: public ConnectionDelegate
{
public:
    BLEMainController();
    ~BLEMainController();

    void startAdvertisingSession();
    void startListeningSession();
    void sendMessageForService(ServiceData serviceData, BLEMessage message);

private:
    QTConnectionDelegateAdapter *m_connectionDelegateAdapter = nullptr;
    ConnectionManager *m_connectionManager = nullptr;

    QBluetoothDeviceDiscoveryAgent* m_deviceDiscoveryAgent;

    void establishConnectionSignals(QLowEnergyController *periperal);
    void establishDataSourceSignals(QBluetoothDeviceDiscoveryAgent *deviceDiscoveryAgent);

public:
    void setConnectionDelegate(ConnectionDelegate connectionDelegate);
    void setConnectionDataSource(ConnectionDataSource connectionDateSource);
};

#endif // BLEMAINCONTROLLER_H
