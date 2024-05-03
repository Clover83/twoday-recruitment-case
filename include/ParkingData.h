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
    bool hasBeenProcessed = false;


    ParkingData() = default;

    // Friend to work nicely with GTests, since otherwise the first argument is implicitly 'this'.
    friend bool operator==(ParkingData const& lhs, ParkingData const& rhs)
    {
        if (lhs.spotID != rhs.spotID)
            return false;
        if (lhs.licensePlate != rhs.licensePlate)
            return false;
        if (lhs.startTime != rhs.startTime)
            return false;
        if (lhs.endTime != rhs.endTime)
            return false;

        return true;
        return false;
    }

};

