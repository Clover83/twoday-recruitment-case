#pragma once

#include <optional>
#include "ParkingData.h"

class IParkingStorage
{
public:
    virtual ~IParkingStorage() {}
    virtual bool store(ParkingData data) = 0;
    virtual std::optional<ParkingData> retrieve(int spotID) = 0;
};