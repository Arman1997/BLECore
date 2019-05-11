#ifndef ADVERTISINGDELEGATE_H
#define ADVERTISINGDELEGATE_H

#include<connectionerror.h>
#include<connectionstate.h>

class ConnectionDelegate {
public:
    virtual void connectionStateUpdated(BLEConnectionState::ConnectionState newState) const = 0;
    virtual void errorOccurred(BLEConnectionError::Error newError) const = 0;

    virtual ~ConnectionDelegate();
};

#endif // ADVERTISINGDELEGATE_H
