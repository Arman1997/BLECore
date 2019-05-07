#ifndef ADVERTISINGDELEGATE_H
#define ADVERTISINGDELEGATE_H

#include <QtBluetooth/qlowenergycontroller.h>


class ConnectionDelegate {
public:
    virtual void connectionStateUpdated(QLowEnergyController::ControllerState newState) = 0;
    virtual void errorOccurred(QLowEnergyController::Error newError) = 0;

    virtual ~ConnectionDelegate();
};

class QT_ConnectionDelegate: public QObject {
    Q_OBJECT

public:
    QT_ConnectionDelegate(ConnectionDelegate* delegate) {
        this->connectionDelegate = delegate;
    }

private slots:
    void stateChanged(QLowEnergyController::ControllerState newState) {
        connectionDelegate->connectionStateUpdated(newState);
    }

    void errorOccurred(QLowEnergyController::Error newError) {
        connectionDelegate->errorOccurred(newError);
    }

private:
    ConnectionDelegate* connectionDelegate;
};

#endif // ADVERTISINGDELEGATE_H
