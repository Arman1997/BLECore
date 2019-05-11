#include "blemaincontroller.h"
#include <QtBluetooth/qlowenergyadvertisingdata.h>
#include <QtBluetooth/qlowenergyadvertisingparameters.h>
#include <QtBluetooth/qlowenergycharacteristic.h>
#include <QtBluetooth/qlowenergycharacteristicdata.h>
#include <QtBluetooth/qlowenergydescriptordata.h>
#include <QtBluetooth/qlowenergycontroller.h>
#include <QtBluetooth/qlowenergyservice.h>
#include <QtBluetooth/qlowenergyservicedata.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qloggingcategory.h>
#include <QtCore/qscopedpointer.h>


BLEMainController::BLEMainController()
{

}

BLEMainController::~BLEMainController()
{
    delete m_connectionDelegateAdapter;
    delete m_connectionManager;
    delete deviceDiscoveryAgent;
}

void BLEMainController::establishConnectionSignals(QLowEnergyController *periperal)
{
    if(m_connectionDelegateAdapter)
    {
        QObject::connect(periperal,SIGNAL(QLowEnergyController::stateChanged),
                         m_connectionDelegateAdapter,SLOT(QTConnectionDelegateAdapter::stateChanged));

        QObject::connect(periperal,SIGNAL(QLowEnergyController::error),
                         m_connectionDelegateAdapter,SLOT(QTConnectionDelegateAdapter::errorOccurred));
    }
}

void BLEMainController::establishDataSourceSignals(QBluetoothDeviceDiscoveryAgent *deviceDiscoveryAgent)
{
    if(m_connectionDelegateAdapter) {
        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::finished,m_connectionDelegateAdapter,
                         &QTConnectionDelegateAdapter::finished);

        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::canceled,
                         m_connectionDelegateAdapter, &QTConnectionDelegateAdapter::canceled);

        QObject::connect(deviceDiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
                    m_connectionDelegateAdapter, SLOT(deviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));

        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                         m_connectionDelegateAdapter, &QTConnectionDelegateAdapter::deviceDiscovered);
    }

    if(m_connectionManager) {
        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                         m_connectionManager,&ConnectionManager::deviceAdded);

        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceUpdated,
                         m_connectionManager,&ConnectionManager::deviceUpdated);
    }

}

void BLEMainController::startAdvertisingSession()
{
    QLowEnergyAdvertisingData advertisingData;
    advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
    advertisingData.setIncludePowerLevel(true);
    advertisingData.setLocalName("BLECore_Server");
    advertisingData.setServices(QList<QBluetoothUuid>() << QBluetoothUuid::PublicBrowseGroup);

    QLowEnergyCharacteristicData charData;
    charData.setUuid(QBluetoothUuid::PublicBrowseGroup);
    charData.setValue(QByteArray(2, 0));
    charData.setProperties(QLowEnergyCharacteristic::Notify);

    const QLowEnergyDescriptorData clientConfig(QBluetoothUuid::ClientCharacteristicConfiguration,
                                                QByteArray(2, 0));
    charData.addDescriptor(clientConfig);

    QLowEnergyServiceData serviceData;
    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceData.setUuid(QBluetoothUuid::PublicBrowseGroup);
    serviceData.addCharacteristic(charData);

    QLowEnergyController* periperal = QLowEnergyController::createPeripheral();

    establishConnectionSignals(periperal);
    const QScopedPointer<QLowEnergyController> leController(periperal);
    QScopedPointer<QLowEnergyService> service(leController->addService(serviceData));
    leController->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData,
                                   advertisingData);

}

void BLEMainController::startListeningSession()
{
    deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(nullptr);
    deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);
    establishDataSourceSignals(deviceDiscoveryAgent);
    deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BLEMainController::setConnectionDelegate(ConnectionDelegate connectionDelegate)
{
    m_connectionDelegateAdapter = new QTConnectionDelegateAdapter(&connectionDelegate);
}

void BLEMainController::setConnectionDataSource(ConnectionDataSource connectionDateSource)
{
    m_connectionManager = new ConnectionManager(&connectionDateSource);
}
