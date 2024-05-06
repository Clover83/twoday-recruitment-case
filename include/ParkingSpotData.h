#pragma once
#include <chrono>
#include <string>

using SpotID = int;

/// @brief The data the user will fill in during exit/entry.
struct ParkingSpotData
{
    SpotID spotID = -1;
    std::string licensePlate = "";
    time_t timeStamp;

    ParkingSpotData() = default;
    ParkingSpotData(SpotID spotID, const std::string& licensePlate, time_t timeStamp)
        : spotID(spotID), licensePlate(licensePlate), timeStamp(timeStamp) {}

    friend bool operator==(const ParkingSpotData& rhs, const ParkingSpotData& lhs) 
    {
        if (rhs.spotID != lhs.spotID)
            return false;
        if (rhs.licensePlate != lhs.licensePlate)
            return false;
        if (rhs.timeStamp != lhs.timeStamp)
            return false;
        return true;
    }
};