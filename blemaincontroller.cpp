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
}

void BLEMainController::establishConnectionSignals(QLowEnergyController *periperal)
{
    if(!this->qt_connectionDelegate)
    {
        QObject::connect(periperal,SIGNAL(QLowEnergyController::stateChanged),this->qt_connectionDelegate,SLOT(QT_ConnectionDelegate::stateChanged));
        QObject::connect(periperal,SIGNAL(QLowEnergyController::error),this->qt_connectionDelegate,SLOT(QT_ConnectionDelegate::errorOccurred));
    }
}

void BLEMainController::startAdvertisingSession()
{
    QLowEnergyAdvertisingData advertisingData;
    advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
    advertisingData.setIncludePowerLevel(true);
    advertisingData.setLocalName("HeartRateServer");
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

void BLEMainController::setConnectionDelegate(ConnectionDelegate connectionDelegate)
{
    qt_connectionDelegate = new QT_ConnectionDelegate(&connectionDelegate);
}

void BLEMainController::setConnectionDataSource(ConnectionDataSource connectionDateSource)
{
    qt_connectionDataSource = new QT_ConnectionDataSource(&connectionDateSource);
}
