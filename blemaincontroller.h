#ifndef BLEMAINCONTROLLER_H
#define BLEMAINCONTROLLER_H

#include <advertisingdelegate.h>

class BLEMainController: public AdvertisingDelegate
{
public:
    BLEMainController();
    ~BLEMainController();

    void startAdvertisingSession(AdvertisingDelegate advertisingDelegate);

private:
    QT_AdvertisingDelegate* qt_advertisingDelegate;

    // AdvertisingDelegate interface
public:
    void connected();
    void disconnected();
    void stateChanged(QLowEnergyController::ControllerState newState);
    void errorOccurred(QLowEnergyController::Error newError);
};

#endif // BLEMAINCONTROLLER_H
