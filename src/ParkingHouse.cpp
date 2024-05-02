#include "ParkingHouse.h"

ParkingHouse::ParkingHouse()
{
    totalSpots = houseInfo.numFloors * houseInfo.spotsPerFloor;
}

ParkingHouse::ParkingHouse(ParkingHouseInfo data, IParkingStorage storageInterface)
    : houseInfo(data), storageInterface(storageInterface)
{
    totalSpots = houseInfo.numFloors * houseInfo.spotsPerFloor;
}

RegistrationReturn ParkingHouse::registerEntry(ParkingData data)
{
    if (data.spotID < 0 || data.spotID > totalSpots)
    {
        return RegistrationReturn::INVALID_ID;
    }

    if (!data.validStartTime)
    {
        return RegistrationReturn::INVALID_START_DATE;
    }

    storageInterface.Store(data);
}

RegistrationReturn ParkingHouse::registerExit(int spotID)
{
    return RegistrationReturn::VALID;
}

float ParkingHouse::getCostFor(int spotID)
{
    return 0.0f;
}
