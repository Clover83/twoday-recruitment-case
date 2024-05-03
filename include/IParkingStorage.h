#pragma once

#include <optional>
#include "ParkingData.h"

class IParkingStorage
{
public:
    virtual ~IParkingStorage() {}
    virtual bool store(ParkingData data) = 0;
    virtual std::optional<ParkingData> retrieve(ParkingData dataToSearchFor) = 0;
    virtual void onEntry(ParkingData entry) = 0;
    virtual void onExit(ParkingData exit) = 0;
};