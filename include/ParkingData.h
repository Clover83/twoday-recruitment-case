#pragma once

#include <string>
#include <chrono>
#include <optional>

struct ParkingData
{
    int spotID = -1;
    std::string licensePlate = "";
    std::time_t startTime;
    std::time_t endTime;
    bool validStartTime = false;
    bool validEndTime = false;
    //std::optional<std::time_t> startTime;
    //std::optional<std::time_t> endTime;


    ParkingData() = default;
    bool operator==(ParkingData const& rhs)
    {
        if (spotID != rhs.spotID)
            return false;
        return true;
    }

};

