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
    delete qt_advertisingDelegate;
}

void BLEMainController::startAdvertisingSession(AdvertisingDelegate advertisingDelegate)
{
    qt_advertisingDelegate = new QT_AdvertisingDelegate(&advertisingDelegate);

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

    QObject::connect(periperal,SIGNAL(connected()),this->qt_advertisingDelegate,SLOT(connected()));
    QObject::connect(periperal,SIGNAL(disconnected()),this->qt_advertisingDelegate,SLOT(disconnected()));
    QObject::connect(periperal,SIGNAL(stateChanged()),this->qt_advertisingDelegate,SLOT(stateChanged()));
    QObject::connect(periperal,SIGNAL(error()),this->qt_advertisingDelegate,SLOT(errorOccurred()));


    const QScopedPointer<QLowEnergyController> leController(periperal);
    QScopedPointer<QLowEnergyService> service(leController->addService(serviceData));
    leController->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData,
                                   advertisingData);

}
