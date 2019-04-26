#ifndef ADVERTISINGDELEGATE_H
#define ADVERTISINGDELEGATE_H

#include <QtBluetooth/qlowenergycontroller.h>


class AdvertisingDelegate {
public:
    virtual void connected() = 0;
    virtual void disconnected() = 0;
    virtual void stateChanged(QLowEnergyController::ControllerState newState) = 0;
    virtual void errorOccurred(QLowEnergyController::Error newError) = 0;

    virtual ~AdvertisingDelegate();
};

class QT_AdvertisingDelegate: public QObject {
    Q_OBJECT

public:
    QT_AdvertisingDelegate(AdvertisingDelegate* delegate) {
        this->advertisingDelegate = delegate;
    }

private slots:
    void connected() {
        advertisingDelegate->connected();
    }

    void disconnected() {
        advertisingDelegate->disconnected();
    }
    void stateChanged(QLowEnergyController::ControllerState newState) {
        advertisingDelegate->stateChanged(newState);
    }

    void errorOccurred(QLowEnergyController::Error newError) {
        advertisingDelegate->errorOccurred(newError);
    }

private:
    AdvertisingDelegate* advertisingDelegate;
};

#endif // ADVERTISINGDELEGATE_H
