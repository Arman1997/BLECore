#include "updatenotifier.h"

UpdateNotifier::UpdateNotifier()
{
    listeners = new std::vector<BLEListener*>;
}

UpdateNotifier::~UpdateNotifier()
{
    delete listeners;
}

void UpdateNotifier::addListener(const BLEListener &listener)
{
    for (std::vector<BLEListener*>::iterator it = listeners->begin() ; it != listeners->end() ; it++)
    {

    }

}

void UpdateNotifier::removeListener(const BLEListener &listener)
{
}

