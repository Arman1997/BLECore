#ifndef BLEMAINCONTROLLER_H
#define BLEMAINCONTROLLER_H

#include <advertisingdelegate.h>
#include <listeningdelegate.h>
#include <qbluetoothdevicediscoveryagent.h>
#include "connectionmanager.h"

class BLEMainController: public ConnectionDelegate
{
public:
    BLEMainController();
    ~BLEMainController();

    void startAdvertisingSession();
    void startListeningSession();

private:
    QT_ConnectionDelegate* qt_connectionDelegate = nullptr;
    QT_ConnectionDataSource* qt_connectionDataSource = nullptr;

    QBluetoothDeviceDiscoveryAgent* deviceDiscoveryAgent;

    void establishConnectionSignals(QLowEnergyController* periperal);
    void establishDataSourceSignals(QBluetoothDeviceDiscoveryAgent* deviceDiscoveryAgent);

public:
    void connected();
    void disconnected();
    void connectionStateUpdated(BLEConnectionState::ConnectionState newState);
    void errorOccurred(BLEConnectionError::Error newError);

    void setConnectionDelegate(ConnectionDelegate connectionDelegate);
    void setConnectionDataSource(ConnectionDataSource connectionDateSource);
};

#endif // BLEMAINCONTROLLER_H
