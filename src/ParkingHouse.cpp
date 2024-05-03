#include "ParkingHouse.h"

ParkingHouse::ParkingHouse(ParkingHouseInfo data, std::shared_ptr<IParkingStorage> storageInterface)
    : houseInfo(data), storageInterface(storageInterface)
{
    totalSpots = houseInfo.numFloors * houseInfo.spotsPerFloor;
}

RegistrationResult ParkingHouse::registerEntry(ParkingData data)
{
    if (data.spotID < 0 || data.spotID > totalSpots)
    {
        return RegistrationResult::INVALID_ID;
    }

    if (!data.startTime)
    {
        return RegistrationResult::INVALID_START_DATE;
    }

    storageInterface->store(data);
    return RegistrationResult::VALID;
}

std::pair<RegistrationResult, double> ParkingHouse::registerExit(ParkingData data)
{
    return {RegistrationResult::VALID, 0.0f};
}

double ParkingHouse::getCost(time_t seconds)
{

    //double hoursParked = secondsParked / 60.0f;
    //double expectedCost = hoursParked * houseInfo.costPerHour;
    //if (hoursParked > 24.0f)
    //{
        //double daysParked = hoursParked / 24.0;
        //double wholeDays, remainderDays;
        //remainderDays = modf(daysParked, &wholeDays);

        //expectedCost = remainderDays * houseInfo.costPerDay;
        //if (remainderDays > 0.0f)
        //{
            //expectedCost += remainderDays * 24.0 * houseInfo.costPerHour;
        //}
    //}
    return 0.0f;
}

bool ParkingHouse::isSpotVacant(int spotID)
{
    return true;
}
