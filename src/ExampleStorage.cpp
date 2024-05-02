#include "ExampleStorage.h"


bool ExampleStorage::store(ParkingData data) 
{
    return true;
}

std::optional<ParkingData> ExampleStorage::retrieve(int spotID) 
{
    return std::nullopt;
}