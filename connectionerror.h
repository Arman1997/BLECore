#ifndef CONNECTIONERROR_H
#define CONNECTIONERROR_H

namespace BLEConnectionError {
typedef enum {
        NoError,
        UnknownRemoteDeviceError,
        NetworkError,
        InvalidBluetoothAdapterError,
        ConnectionError,
        AdvertisingError,
        RemoteHostClosedError,
        InputOutputError,
        PoweredOffError,
        UnsupportedPlatformError,
        UnsupportedDiscoveryMethod,
        UnknownError = 100
    } Error;
}

#endif // CONNECTIONERROR_H
