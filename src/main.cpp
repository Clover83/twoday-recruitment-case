#include <iostream>
#include "ParkingHouse.h"
#include "ExampleStorage.h"

struct TestingInstance
{
    ParkingHouseInfo info;
    ParkingHouse house;
    ExampleStorage storage;
    TestingInstance()
    {
        house = ParkingHouse(info, storage);
    }

    void testEntry()
    {
        ParkingData userData;
        userData.licensePlate = "AAA123";
        
        auto now = std::chrono::system_clock::now();
        userData.startTime = std::chrono::system_clock::to_time_t(now);

        house.registerEntry(userData);
        auto ret = storage.retrieve(userData.spotID);
        // if (ret)
        // {
        //     userData.
        // }
    }
};


void testExit()
{

}

int main() 
{
    std::cout << "Hello World\n"; 
}