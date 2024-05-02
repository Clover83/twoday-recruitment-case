#pragma once

#include "IParkingStorage.h"

class ExampleStorage : public IParkingStorage
{
public:
    bool store(ParkingData data) override;
    std::optional<ParkingData> retrieve(int spotID) override;
};