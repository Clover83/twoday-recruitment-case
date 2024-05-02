#include "ExampleStorage.h"


bool ExampleStorage::Store(ParkingData data) 
{
    return true;
}

std::optional<ParkingData> ExampleStorage::Retrieve(int spotID) 
{
    return std::nullopt;
}