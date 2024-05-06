#pragma once
#include "ParkingResults.h"
#include "ParkingSpotData.h"

struct HouseInfo;

/// @brief Interface between ParkingHouse and your storage system.
class IParkingDataBroker
{
public:
    virtual ~IParkingDataBroker() {}

    /// @brief Search for spot using partial data.
    /// @param dataToSearchFor Partial data is OK.
    /// @return BrokerResult and the spot data which was found, if any.
    virtual std::pair<BrokerResult, ParkingSpotData> findSpot(const ParkingSpotData& dataToSearchFor) const = 0;

    /// @brief Is called when an entry has been validated and can be stored.
    virtual void onValidEntry(const ParkingSpotData& entryData) = 0;

    /// @brief Is called when an exit has been validated and can be stored.
    virtual void onValidExit(const ParkingSpotData& exitData) = 0;
};