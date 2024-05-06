#pragma once
#include "ParkingResults.h"
#include "ParkingSpotData.h"

struct HouseInfo;

class IParkingDataBroker
{
public:
    virtual ~IParkingDataBroker() {}
    virtual std::pair<BrokerResult, ParkingSpotData> findSpot(const ParkingSpotData& dataToSearchFor) const = 0;
    virtual void onValidEntry(const ParkingSpotData& entryData) = 0;
    virtual void onValidExit(const ParkingSpotData& exitData) = 0;
};