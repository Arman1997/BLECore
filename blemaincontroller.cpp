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
    delete qt_connectionDelegate;
    delete qt_connectionDataSource;
    delete deviceDiscoveryAgent;
}

void BLEMainController::establishConnectionSignals(QLowEnergyController *periperal)
{
    if(qt_connectionDelegate)
    {
        QObject::connect(periperal,SIGNAL(QLowEnergyController::stateChanged),
                         qt_connectionDelegate,SLOT(QT_ConnectionDelegate::stateChanged));

        QObject::connect(periperal,SIGNAL(QLowEnergyController::error),
                         qt_connectionDelegate,SLOT(QT_ConnectionDelegate::errorOccurred));
    }
}

void BLEMainController::establishDataSourceSignals(QBluetoothDeviceDiscoveryAgent *deviceDiscoveryAgent)
{
    if(qt_connectionDelegate) {
        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::finished,qt_connectionDelegate,
                         &QT_ConnectionDelegate::finished);

        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::canceled,
                         qt_connectionDelegate, &QT_ConnectionDelegate::canceled);

        QObject::connect(deviceDiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
                    qt_connectionDelegate, SLOT(deviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));

        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                         qt_connectionDelegate, &QT_ConnectionDelegate::deviceDiscovered);
    }

    if(qt_connectionDataSource) {
        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                         qt_connectionDataSource,&QT_ConnectionDataSource::deviceAdded);

        QObject::connect(deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceUpdated,
                         qt_connectionDataSource,&QT_ConnectionDataSource::deviceUpdated);
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
    qt_connectionDelegate = new QT_ConnectionDelegate(&connectionDelegate);
}

void BLEMainController::setConnectionDataSource(ConnectionDataSource connectionDateSource)
{
    qt_connectionDataSource = new QT_ConnectionDataSource(&connectionDateSource);
}
