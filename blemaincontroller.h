#ifndef BLEMAINCONTROLLER_H
#define BLEMAINCONTROLLER_H

#include <advertisingdelegate.h>
#include <listeningdelegate.h>

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

    void establishConnectionSignals(QLowEnergyController* periperal);

public:
    void connected();
    void disconnected();
    void connectionStateUpdated(QLowEnergyController::ControllerState newState);
    void errorOccurred(QLowEnergyController::Error newError);

    void setConnectionDelegate(ConnectionDelegate connectionDelegate);
    void setConnectionDataSource(ConnectionDataSource connectionDateSource);
};

#endif // BLEMAINCONTROLLER_H
