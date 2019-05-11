#ifndef LISTENINGDELEGATE_H
#define LISTENINGDELEGATE_H

#include<servicedata.h>
#include<listenerdata.h>

class ConnectionDataSource
{
public:
    virtual void serviceUpdated(const ServiceData &serviceData) = 0;
    virtual void serviceAdded(const ServiceData &serviceData) = 0;
    virtual void serviceRemoved(const ServiceData &serviceData) = 0;

    virtual void deviceAdded(const BLEUserData &userData) = 0;
    virtual void deviceUpdated(const BLEUserData &userData) = 0;

    virtual ~ConnectionDataSource();

};

#endif // LISTENINGDELEGATE_H
