#include "ParkingHouse.h"

ParkingHouse::ParkingHouse(ParkingHouseInfo data, std::shared_ptr<IParkingStorage> storageInterface)
    : houseInfo(data), storageInterface(storageInterface)
{
    totalSpots = houseInfo.numFloors * houseInfo.spotsPerFloor;
}

RegistrationResult ParkingHouse::registerEntry(ParkingData data)
{
    if (data.spotID < 0 || data.spotID > totalSpots)
        return RegistrationResult::INVALID_ID;

    if (!data.startTime.has_value())
        return RegistrationResult::INVALID_START_DATE;
    
    if (!isSpotVacant(data.spotID))
        return RegistrationResult::OCCUPIED;

    storageInterface->store(data);
    return RegistrationResult::VALID;
}

std::pair<RegistrationResult, double> ParkingHouse::registerExit(ParkingData data)
{
    auto maybeFound = storageInterface->retrieve(data);
    if (!maybeFound.has_value())
        return {RegistrationResult::COULD_NOT_RETRIEVE_DATA, 0.0};
    ParkingData found = maybeFound.value();
    
    if (!found.startTime.has_value())
        return {RegistrationResult::INVALID_START_DATE, 0.0};

    if (!found.endTime.has_value() || data.endTime < found.startTime)
        return {RegistrationResult::INVALID_END_DATE, 0.0};
    
    time_t timeParked = data.endTime.value() - found.startTime.value();
    return {RegistrationResult::VALID, getCost(timeParked)};
}

double ParkingHouse::getCost(time_t secondsParked)
{
    if (secondsParked <= 0)
        return 0.0;
    double hoursParked = secondsParked / 60.0;
    double expectedCost = hoursParked * houseInfo.costPerHour;
    if (hoursParked > 24.0)
    {
        double daysParked = hoursParked / 24.0;
        double wholeDays, remainderDays;
        remainderDays = modf(daysParked, &wholeDays);

        expectedCost = remainderDays * houseInfo.costPerDay;
        if (remainderDays > 0.0)
        {
            expectedCost += remainderDays * 24.0 * houseInfo.costPerHour;
        }
    }
    return expectedCost;
}

bool ParkingHouse::isSpotVacant(int spotID)
{
    ParkingData searcher = ParkingData();
    searcher.spotID = spotID;
    auto found = storageInterface->retrieve(searcher);
    return !found.has_value();
}
