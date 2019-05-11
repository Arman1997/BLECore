#include "connectionmanager.h"


ConnectionManager::ConnectionManager(ConnectionDataSource *dataSource) {
    this->connectionDataSource = dataSource;
}

void ConnectionManager::serviceUpdated(ServiceData serviceData)
{
    connectionDataSource->serviceUpdated(serviceData);
}

void ConnectionManager::serviceAdded(ServiceData serviceData)
{
    connectionDataSource->serviceAdded(serviceData);
}

void ConnectionManager::serviceRemoved(ServiceData serviceData)
{
    connectionDataSource->serviceRemoved(serviceData);
}

void ConnectionManager::deviceAdded(const QBluetoothDeviceInfo &info)
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        // connectionDataSource->deviceAdded(userData);
    }
}

void ConnectionManager::deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields)
{
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        //connectionDataSource->deviceUpdated(userData);
    }
}
