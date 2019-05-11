#ifndef QTCONNECTIONDELEGATEADAPTER_H
#define QTCONNECTIONDELEGATEADAPTER_H

#include <QtBluetooth/qlowenergycontroller.h>
#include<qbluetoothdevicediscoveryagent.h>
#include<advertisingdelegate.h>


class QTConnectionDelegateAdapter: public QObject {
    Q_OBJECT

public:
    QTConnectionDelegateAdapter(ConnectionDelegate* delegate);

public slots:
void deviceDiscovered(const QBluetoothDeviceInfo &info);

void finished();

void canceled();

void stateChanged(QLowEnergyController::ControllerState newState);

void errorOccurred(QLowEnergyController::Error newError);

void errorOccurred(QBluetoothDeviceDiscoveryAgent::Error error);

private:
    ConnectionDelegate* connectionDelegate;
};


#endif // QTCONNECTIONDELEGATEADAPTER_H
