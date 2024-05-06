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

/// @brief User requests to leave or pick up their vehicle (entry/exit) get processed here.
class ParkingHouse
{
public:
    HouseInfo houseInfo;

    ParkingHouse(const HouseInfo& houseInfo, std::shared_ptr<IParkingDataBroker> dataBroker);

    /// @brief User requests to leave their vehicle.
    /// @param entryData Must have valid ID, license plate, and start time.
    /// @return Whether the entry data was valid and sent to the data broker.
    EntryResult processEntry(const ParkingSpotData& entryData);

    /// @brief User requests to pick up their vehicle.
    /// @param exitData Must have valid ID, license plate, and end time.
    /// @return Whether the exit data was valid and sent to the data broker.
    ExitResult processExit(const ParkingSpotData& exitData);

    /// @brief The cost, calculated as per house info costs.
    double getCost(int secondsParked) const;

private:
    std::shared_ptr<IParkingDataBroker> dataBroker;
    RangeCheckResult checkLimits(const ParkingSpotData& spotData) const;
    std::pair<RangeCheckResult, time_t> getSecondsParked(const ParkingSpotData& oldData, const ParkingSpotData& newData);
};