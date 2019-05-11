#include "connectionmanager.h"


ConnectionManager::ConnectionManager(ConnectionDataSource *dataSource,
                                     QTConnectionDelegateAdapter *connectionDelegateAdapter):
    m_connectionDataSource(dataSource),
    m_currentDevice(nullptr),
    m_controller(nullptr),
    m_connectionDelegateAdapter(connectionDelegateAdapter)
{

}

ConnectionManager::~ConnectionManager()
{
    delete m_currentDevice;
    delete m_controller;
}

void ConnectionManager::serviceUpdated(ServiceData serviceData)
{
   // m_connectionDataSource->serviceUpdated(serviceData);
}

void ConnectionManager::serviceAdded(const QBluetoothUuid &newService)
{
    if (newService == QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup)) {
        // m_connectionDataSource->serviceAdded(serviceData);
      }
}

void ConnectionManager::serviceRemoved(ServiceData serviceData)
{
   // m_connectionDataSource->serviceRemoved(serviceData);
}

void ConnectionManager::deviceAdded(const QBluetoothDeviceInfo &info)
{
    setNewDevice(info);
    clearCurrentConnection();
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {

        // connectionDataSource->deviceAdded(userData);


        if (m_currentDevice) {

            m_controller = QLowEnergyController::createCentral(m_currentDevice->getDevice(), this);
            m_controller->setRemoteAddressType(QLowEnergyController::PublicAddress);

            connect(m_controller, &QLowEnergyController::serviceDiscovered,
                                this, &ConnectionManager::serviceAdded);

            if (m_connectionDelegateAdapter) {
                connect(m_controller, &QLowEnergyController::disconnected, this, [this]() {
                    m_connectionDelegateAdapter->errorOccurred(QLowEnergyController::Error::ConnectionError);
                });

                connect(m_controller, &QLowEnergyController::discoveryFinished,
                        this->m_connectionDelegateAdapter, &QTConnectionDelegateAdapter::finished);

                connect(m_controller,
                        static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
                        m_connectionDelegateAdapter,
                        static_cast<void (QTConnectionDelegateAdapter::*)(QLowEnergyController::Error) const>(&QTConnectionDelegateAdapter::errorOccurred));


            }

            connect(m_controller, &QLowEnergyController::connected, this, [this]() {
                if (m_connectionDelegateAdapter) {
                    m_connectionDelegateAdapter->stateChanged(QLowEnergyController::ControllerState::ConnectedState);
                    m_controller->discoverServices();
                }
            });

            m_controller->connectToDevice();
        }
    }
}

void ConnectionManager::deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields)
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        //...
    }
}

void ConnectionManager::clearCurrentConnection()
{
    if (m_controller) {
        m_controller->disconnectFromDevice();
        delete m_controller;
        m_controller = nullptr;
    }
}

void ConnectionManager::setNewDevice(const QBluetoothDeviceInfo &info)
{
    delete m_currentDevice;
    m_currentDevice = nullptr;
    m_currentDevice = new DeviceInfo(info);
}


