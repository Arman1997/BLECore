#ifndef LISTENER_H
#define LISTENER_H

#include<listenerdata.h>
#include<blemessage.h>

class BLEListener {
public:

    virtual ~BLEListener();

    //Users
    virtual void userAdded(const BLEUserData &userData) = 0;
    virtual void userUpdated(const BLEUserData &userData) const = 0;
    virtual void userRemoved(const BLEUserData &userData) const = 0;
    virtual void messageReceived(const BLEMessage &message, const BLEUserData &userData) const = 0;
    virtual const BLEUserData& getUserData() const = 0;
};

#endif // LISTENER_H