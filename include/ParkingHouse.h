#pragma once

#include <unordered_map>
#include <memory>
#include "ParkingData.h"
#include "IParkingStorage.h"


struct ParkingHouseInfo
{
    int numFloors = 3;
    int spotsPerFloor = 15;
    float costPerHour = 15.0f;
    float costPerDay = 50.0f;
};

enum class RegistrationReturn
{
    VALID,
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
    ParkingHouse();
    ParkingHouse(ParkingHouseInfo data, std::shared_ptr<IParkingStorage> storageInterface);

    RegistrationReturn registerEntry(ParkingData data);
    RegistrationReturn registerExit(int spotID);
    float getCostFor(int spotID);

private:
    ParkingHouseInfo houseInfo;
    int totalSpots;
    std::shared_ptr<IParkingStorage> storageInterface;

};