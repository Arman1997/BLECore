#ifndef UPDATENOTIFIER_H
#define UPDATENOTIFIER_H

#include<vector>
#include<listener.h>

class UpdateNotifier
{
private:
    std::vector<BLEListener> *listeners;
public:
    UpdateNotifier();
    ~UpdateNotifier();

    void addListener(BLEListener &listener);
    void removeListener(const BLEListener& listener);
    void updateListener(const BLEListener& listener);
    void sendMessage(const BLEMessage& message);
};

#endif // UPDATENOTIFIER_H
