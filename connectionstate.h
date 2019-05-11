#ifndef CONNECTIONSTATE_H
#define CONNECTIONSTATE_H

namespace BLEConnectionState {
typedef enum {
        UnconnectedState = 0,
        ConnectingState,
        ConnectedState,
        DiscoveringState,
        DiscoveredState,
        ClosingState,
        AdvertisingState,
        Finished,
        Canceled
    } ConnectionState;
}

#endif // CONNECTIONSTATE_H
