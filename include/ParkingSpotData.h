#pragma once
#include <chrono>
#include <string>
#include <optional>

using SpotID = int;

struct ParkingSpotData
{
    SpotID spotID = -1;
    std::string licensePlate = "";
    std::optional<std::time_t> startTime;
    std::optional<std::time_t> endTime;

    ParkingSpotData() = default;
    ParkingSpotData(SpotID spotID, const std::string& licensePlate)
        : spotID(spotID), licensePlate(licensePlate) {}

    friend bool operator==(const ParkingSpotData& rhs, const ParkingSpotData& lhs) 
    {
        if (rhs.spotID != lhs.spotID)
            return false;
        if (rhs.licensePlate != lhs.licensePlate)
            return false;
        if (rhs.startTime != lhs.startTime)
            return false;
        if (rhs.endTime != lhs.endTime)
            return false;
        return true;
    }
};