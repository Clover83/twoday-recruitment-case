#pragma once
#include <unordered_map>
#include <string>
#include "IParkingDataBroker.h"

class ExampleDataBroker : public IParkingDataBroker
{ 
public:
    std::pair<BrokerResult, ParkingSpotData> findSpot(const ParkingSpotData& dataToSearchFor) const override;
    void onValidEntry(const ParkingSpotData& entryData) override;
    void onValidExit(const ParkingSpotData& entryData) override;

private:
    std::unordered_map<SpotID, ParkingSpotData> activeSpots;
    std::unordered_map<std::string, SpotID> licenceToID;
    std::unordered_map<SpotID, ParkingSpotData> archivedSpots;
};