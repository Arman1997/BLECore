#ifndef BLEMAINCONTROLLER_H
#define BLEMAINCONTROLLER_H

#include <advertisingdelegate.h>

class BLEMainController: public ConnectionDelegate
{
public:
    BLEMainController();
    ~BLEMainController();

    void startAdvertisingSession(ConnectionDelegate advertisingDelegate);
    void startListeningSession();

private:
    QT_ConnectionDelegate* qt_advertisingDelegate;

public:
    void connected();
    void disconnected();
    void connectionStateUpdated(QLowEnergyController::ControllerState newState);
    void errorOccurred(QLowEnergyController::Error newError);
};

#endif // BLEMAINCONTROLLER_H
