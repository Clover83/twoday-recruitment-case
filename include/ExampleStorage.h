#pragma once

#include <unordered_map>
#include "IParkingStorage.h"

class ExampleStorage : public IParkingStorage
{
public:
    bool store(ParkingData data) override;
    std::optional<ParkingData> retrieve(ParkingData dataToSearchFor) override;

private:
    std::unordered_map<int, ParkingData> spots;
};