#ifndef QTCONNECTIONDELEGATEADAPTER_H
#define QTCONNECTIONDELEGATEADAPTER_H

#include <QtBluetooth/qlowenergycontroller.h>
#include<qbluetoothdevicediscoveryagent.h>
#include<connectiondelegate.h>


class QTConnectionDelegateAdapter: public QObject {
    Q_OBJECT

public:
    QTConnectionDelegateAdapter(ConnectionDelegate* delegate);

public slots:
void deviceDiscovered(const QBluetoothDeviceInfo &info);

void finished() const;

void canceled() const;

void stateChanged(QLowEnergyController::ControllerState newState) const;

void errorOccurred(QLowEnergyController::Error newError) const;

void errorOccurred(QBluetoothDeviceDiscoveryAgent::Error error) const;

private:
    ConnectionDelegate* connectionDelegate;
};


#endif // QTCONNECTIONDELEGATEADAPTER_H
