#include "ExampleStorage.h"


bool ExampleStorage::store(ParkingData data) 
{
    auto [_, wasInserted] = activeSpots.insert({data.spotID, data});
    return wasInserted;
}

std::optional<ParkingData> ExampleStorage::retrieve(ParkingData dataToSearchFor) 
{
    auto foundSpot = activeSpots.find(dataToSearchFor.spotID);
    if (foundSpot == activeSpots.end())
        return std::nullopt;
    return std::make_optional(foundSpot->second);
}

void ExampleStorage::onEntry(ParkingData entryData)
{
        
}

void ExampleStorage::onExit(ParkingData exitData)
{
    // Do better error handling here, this is just an example.
    auto spotToMove = activeSpots.at(exitData.spotID);
    activeSpots.erase(exitData.spotID);
    oldSpots.push_back(spotToMove);
}