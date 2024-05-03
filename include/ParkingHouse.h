#pragma once

#include <unordered_map>
#include <memory>
#include <chrono>
#include "ParkingData.h"
#include "IParkingStorage.h"

struct ParkingHouseInfo
{
    int numFloors = 3;
    int spotsPerFloor = 15;
    double costPerHour = 15.0;
    double costPerDay = 50.0;
    int getTotalSpots()
    {
        return numFloors * spotsPerFloor;
    }
};

enum class RegistrationResult
{
    VALID,
    OCCUPIED,
    INVALID_ID,
    INVALID_LICENSE_PLATE,
    LICENSE_PLATE_NOT_FOUND,
    INVALID_START_DATE,
    INVALID_END_DATE,
    COULD_NOT_STORE_DATA,
    COULD_NOT_RETRIEVE_DATA
};

class ParkingHouse
{
public:
    ParkingHouse(ParkingHouseInfo data, std::shared_ptr<IParkingStorage> storageInterface);

    RegistrationResult registerEntry(ParkingData data);
    std::pair<RegistrationResult, double> registerExit(ParkingData data);
    double getCost(time_t secondsParked);
    bool isSpotVacant(int spotID);

private:
    ParkingHouseInfo houseInfo;
    int totalSpots;
    std::shared_ptr<IParkingStorage> storageInterface;

};