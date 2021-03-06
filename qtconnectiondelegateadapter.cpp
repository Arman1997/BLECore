#include "qtconnectiondelegateadapter.h"

QTConnectionDelegateAdapter::QTConnectionDelegateAdapter(ConnectionDelegate *delegate) {
    this->connectionDelegate = delegate;
}

void QTConnectionDelegateAdapter::deviceDiscovered(const QBluetoothDeviceInfo &info) {
    connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::DiscoveredState);
}

void QTConnectionDelegateAdapter::finished() const
{
    connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::Finished);
}

void QTConnectionDelegateAdapter::canceled() const
{
    connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::Canceled);
}

void QTConnectionDelegateAdapter::stateChanged(QLowEnergyController::ControllerState newState) const
{
    switch (newState) {
    case QLowEnergyController::ControllerState::UnconnectedState:
        connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::UnconnectedState);
        break;
    case QLowEnergyController::ControllerState::ConnectingState:
        connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::ConnectingState);
        break;
    case QLowEnergyController::ControllerState::ConnectedState:
        connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::ConnectedState);
        break;
    case QLowEnergyController::ControllerState::DiscoveredState:
        connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::DiscoveredState);
        break;
    case QLowEnergyController::ControllerState::DiscoveringState:
        connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::DiscoveringState);
        break;
    case QLowEnergyController::ControllerState::ClosingState:
        connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::ClosingState);
        break;
    case QLowEnergyController::ControllerState::AdvertisingState:
        connectionDelegate->connectionStateUpdated(BLEConnectionState::ConnectionState::AdvertisingState);
        break;
    }
}

void QTConnectionDelegateAdapter::errorOccurred(QLowEnergyController::Error newError) const
{
    switch (newError) {

    case QLowEnergyController::Error::NoError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::NoError);
        break;

    case QLowEnergyController::Error::UnknownError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::UnknownError);
        break;

    case QLowEnergyController::Error::UnknownRemoteDeviceError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::UnknownRemoteDeviceError);
        break;

    case QLowEnergyController::Error::NetworkError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::NetworkError);
        break;

    case QLowEnergyController::Error::InvalidBluetoothAdapterError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::InvalidBluetoothAdapterError);
        break;

    case QLowEnergyController::Error::ConnectionError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::ConnectionError);
        break;

    case QLowEnergyController::Error::AdvertisingError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::AdvertisingError);
        break;

    case QLowEnergyController::Error::RemoteHostClosedError:
        connectionDelegate->errorOccurred(BLEConnectionError::Error::RemoteHostClosedError);
        break;
    }
}

void QTConnectionDelegateAdapter::errorOccurred(QBluetoothDeviceDiscoveryAgent::Error error) const
{
    switch (error) {
    case QBluetoothDeviceDiscoveryAgent::Error::NoError:
        connectionDelegate->errorOccurred(BLEConnectionError::NoError);
        break;
    case QBluetoothDeviceDiscoveryAgent::Error::InputOutputError:
        connectionDelegate->errorOccurred(BLEConnectionError::InputOutputError);
        break;
    case QBluetoothDeviceDiscoveryAgent::Error::PoweredOffError:
        connectionDelegate->errorOccurred(BLEConnectionError::PoweredOffError);
        break;
    case QBluetoothDeviceDiscoveryAgent::Error::InvalidBluetoothAdapterError:
        connectionDelegate->errorOccurred(BLEConnectionError::InvalidBluetoothAdapterError);
        break;
    case QBluetoothDeviceDiscoveryAgent::Error::UnsupportedPlatformError:
        connectionDelegate->errorOccurred(BLEConnectionError::UnsupportedPlatformError);
        break;
    case QBluetoothDeviceDiscoveryAgent::Error::UnsupportedDiscoveryMethod:
        connectionDelegate->errorOccurred(BLEConnectionError::UnsupportedDiscoveryMethod);
        break;
    case QBluetoothDeviceDiscoveryAgent::Error::UnknownError:
        connectionDelegate->errorOccurred(BLEConnectionError::UnknownError);
        break;
    }
}
