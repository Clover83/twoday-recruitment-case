#pragma once

#include "IParkingStorage.h"

class ExampleStorage : public IParkingStorage
{
    bool Store(ParkingData data) override;
    std::optional<ParkingData> Retrieve(int spotID) override;
};