#include <cmath>
#include "ParkingHouse.h"

using std::nullopt;

ParkingHouse::ParkingHouse(const HouseInfo & houseInfo, std::shared_ptr<IParkingDataBroker> dataBroker)
    : houseInfo(houseInfo), dataBroker(dataBroker)
{

}

EntryResult ParkingHouse::processEntry(const ParkingSpotData &entryData)
{
    RangeCheckResult inRangeResult = checkLimits(entryData);
    if (inRangeResult != RangeCheckResult::Valid)
        return EntryResult(false, inRangeResult);

    auto [brokerResult, _] = dataBroker->findSpot(entryData);
    if (brokerResult != BrokerResult::Vacant)
        return EntryResult(false, brokerResult);

    dataBroker->onValidEntry(entryData);
    return EntryResult(true);
}

ExitResult ParkingHouse::processExit(const ParkingSpotData &exitData)
{
    RangeCheckResult inRangeResult = checkLimits(exitData);
    if (inRangeResult != RangeCheckResult::Valid)
        return ExitResult(false, 0.0, inRangeResult);

    auto [brokerResult, entryData] = dataBroker->findSpot(exitData);
    if (brokerResult != BrokerResult::Occupied)
        return ExitResult(false, 0.0, brokerResult);

    auto [timeCheckResult, secondsParked] = getSecondsParked(entryData, exitData);
    if (timeCheckResult != RangeCheckResult::Valid)
        return ExitResult(false, 0.0, timeCheckResult);

    double cost = getCost(secondsParked);
    dataBroker->onValidExit(exitData);
    return ExitResult(true, cost);
}

double ParkingHouse::getCost(int secondsParked) const
{
    if (secondsParked <= 0)
        return 0.0;
    
    double hoursParked = static_cast<double>(secondsParked) / 3600.0;
    if (hoursParked <= 24.0)
        return hoursParked * houseInfo.costPerHour;
    
    int fullDays = static_cast<int>(hoursParked / 24.0);
    double remainingHours = std::fmod(hoursParked, 24.0);
    return fullDays * houseInfo.costPerDay + remainingHours * houseInfo.costPerHour;
}

RangeCheckResult ParkingHouse::checkLimits(const ParkingSpotData &spotData) const
{
    int spotCount = houseInfo.floorCount * houseInfo.spotsPerFloor;
    if (spotData.spotID < 0 || spotData.spotID > spotCount)
        return RangeCheckResult::InvalidID;
    if (spotData.timeStamp < 0)
        return RangeCheckResult::UnsetTimeStamp;

    return RangeCheckResult::Valid;
}

std::pair<RangeCheckResult, time_t> ParkingHouse::getSecondsParked(const ParkingSpotData& entryData, const ParkingSpotData& exitData)
{
    if (exitData.timeStamp < entryData.timeStamp)
        return {RangeCheckResult::InvalidEndTime, 0};

    time_t secondsParked = exitData.timeStamp - entryData.timeStamp;
    return {RangeCheckResult::Valid, secondsParked};
}
