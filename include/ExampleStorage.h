#pragma once

#include <unordered_map>
#include <vector>
#include "IParkingStorage.h"

class ExampleStorage : public IParkingStorage
{
public:
    bool store(ParkingData data) override;
    std::optional<ParkingData> retrieve(ParkingData dataToSearchFor) override;
    void onEntry(ParkingData entryData);
    void onExit(ParkingData exitData);

private:
    std::unordered_map<int, ParkingData> activeSpots;
    std::vector<ParkingData> oldSpots;
};