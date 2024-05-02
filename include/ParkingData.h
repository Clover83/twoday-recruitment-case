#pragma once

#include <string>
#include <chrono>
#include <optional>

struct ParkingData
{
    int spotID = -1;
    std::string licensePlate = "";
    std::optional<std::time_t> startTime;
    std::optional<std::time_t> endTime;


    ParkingData() = default;
    bool operator==(ParkingData const& rhs)
    {
        if (spotID != rhs.spotID)
            return false;
        if (licensePlate != rhs.licensePlate)
            return false;
        if (startTime != rhs.startTime)
            return false;
        if (endTime != rhs.endTime)
            return false;

        return true;
    }

};

