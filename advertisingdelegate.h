#ifndef ADVERTISINGDELEGATE_H
#define ADVERTISINGDELEGATE_H

#include<connectionerror.h>
#include<connectionstate.h>

class ConnectionDelegate {
public:
    virtual void connectionStateUpdated(BLEConnectionState::ConnectionState newState) = 0;
    virtual void errorOccurred(BLEConnectionError::Error newError) = 0;

    virtual ~ConnectionDelegate();
};

#endif // ADVERTISINGDELEGATE_H
