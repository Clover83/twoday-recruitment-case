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

    if (!entryData.startTime.has_value() && !exitData.startTime.has_value())
        return ExitResult(false, 0.0, RangeCheckResult::InvalidStartTime);

    if (!entryData.endTime.has_value() && !exitData.endTime.has_value())
        return ExitResult(false, 0.0, RangeCheckResult::InvalidEndTime);

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

    if (!spotData.startTime.has_value()) 
        return RangeCheckResult::InvalidStartTime;

    if (spotData.endTime.has_value() && spotData.endTime.value() <= spotData.startTime.value())
        return RangeCheckResult::InvalidEndTime;

    return RangeCheckResult::Valid;
}

std::pair<RangeCheckResult, time_t> ParkingHouse::getSecondsParked(const ParkingSpotData& oldData, const ParkingSpotData& newData)
{
    time_t startTime;
    if (oldData.startTime.has_value())
        startTime = oldData.startTime.value();
    else if (newData.startTime.has_value())
        startTime = newData.startTime.value();
    else
        return {RangeCheckResult::InvalidStartTime, 0};

    time_t endTime;
    if (newData.endTime.has_value())
        endTime = newData.endTime.value();
    else if (oldData.startTime.has_value())
        endTime = oldData.endTime.value();
    else
        return {RangeCheckResult::InvalidEndTime, 0};
    
    if (endTime <= startTime)
        return {RangeCheckResult::InvalidEndTime, 0};
    
    return {RangeCheckResult::Valid, endTime - startTime};
}
