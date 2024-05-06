#pragma once
#include <memory>
#include "IParkingDataBroker.h"
#include "ParkingSpotData.h"


struct HouseInfo
{
    int floorCount = 3;
    int spotsPerFloor = 15;
    double costPerHour = 15.0;
    double costPerDay = 50.0;
};

class ParkingHouse
{
public:
    HouseInfo houseInfo;

    ParkingHouse(const HouseInfo& houseInfo, std::shared_ptr<IParkingDataBroker> dataBroker);

    EntryResult processEntry(const ParkingSpotData& entryData);
    ExitResult processExit(const ParkingSpotData& exitData);
    double getCost(int secondsParked) const;

private:
    std::shared_ptr<IParkingDataBroker> dataBroker;
    RangeCheckResult checkLimits(const ParkingSpotData& spotData) const;
    std::pair<RangeCheckResult, time_t> getSecondsParked(const ParkingSpotData& oldData, const ParkingSpotData& newData);
};