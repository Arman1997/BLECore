#include "updatenotifier.h"

UpdateNotifier::UpdateNotifier()
{
    listeners = new std::vector<BLEListener>;
}

UpdateNotifier::~UpdateNotifier()
{
    delete listeners;
}

void UpdateNotifier::addListener(BLEListener &listener)
{
    for (std::vector<BLEListener>::iterator it = listeners->begin() ; it != listeners->end() ; it++)
    {
       it->userAdded(listener.getUserData());
    }

    listeners->push_back(listener);
}

void UpdateNotifier::removeListener(const BLEListener &listener)
{
    listeners->erase(std::remove(listeners->begin(), listeners->end(), listener), listeners->end());

    for (std::vector<BLEListener>::iterator it = listeners->begin() ; it != listeners->end() ; it++)
    {
       it->userRemoved(listener.getUserData());
    }
}

void UpdateNotifier::updateListener(const BLEListener &listener)
{
    for (std::vector<BLEListener>::iterator it = listeners->begin() ; it != listeners->end() ; it++)
    {
       it->userUpdated(listener.getUserData());
    }
}

void UpdateNotifier::sendMessage(const BLEMessage &message)
{
    for (std::vector<BLEListener>::iterator it = listeners->begin() ; it != listeners->end() ; it++)
    {
       it->messageReceived(message,it->getUserData());
    }
}

