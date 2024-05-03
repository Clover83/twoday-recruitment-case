#include "ExampleStorage.h"


bool ExampleStorage::store(ParkingData data) 
{
    auto [_, wasInserted] = spots.insert({data.spotID, data});
    return wasInserted;
}

std::optional<ParkingData> ExampleStorage::retrieve(ParkingData dataToSearchFor) 
{
    auto foundSpot = spots.find(dataToSearchFor.spotID);
    if (foundSpot == spots.end())
        return std::nullopt;
    return std::make_optional(foundSpot->second);
}