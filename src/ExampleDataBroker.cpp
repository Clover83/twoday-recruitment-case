#include "ExampleDataBroker.h"

std::pair<BrokerResult, ParkingSpotData> ExampleDataBroker::findSpot(const ParkingSpotData &dataToSearchFor) const
{
    auto foundSpot = activeSpots.find(dataToSearchFor.spotID);
    if (foundSpot != activeSpots.end())
        return {BrokerResult::Occupied, foundSpot->second};

    auto licensePlateCollision = licenceToID.find(dataToSearchFor.licensePlate);
    if (licensePlateCollision != licenceToID.end())
        return {BrokerResult::InvalidLicensePlate, dataToSearchFor};

    return {BrokerResult::Vacant, dataToSearchFor};
}

void ExampleDataBroker::onValidEntry(const ParkingSpotData &entryData)
{
    activeSpots.insert({entryData.spotID, entryData});
    licenceToID.insert({entryData.licensePlate, entryData.spotID});
}

void ExampleDataBroker::onValidExit(const ParkingSpotData &exitData)
{
    ParkingSpotData toMove = activeSpots.at(exitData.spotID);

    archivedSpots.insert({toMove.spotID, toMove});
    licenceToID.erase(toMove.licensePlate);
    activeSpots.erase(toMove.spotID);
}
