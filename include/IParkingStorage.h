#pragma once

#include <optional>
#include "ParkingData.h"

class IParkingStorage
{
public:
    virtual ~IParkingStorage() {}
    virtual bool Store(ParkingData data);
    virtual std::optional<ParkingData> Retrieve(int spotID);
};