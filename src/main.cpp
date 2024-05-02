#include <iostream>
#include "ParkingHouse.h"
#include "ExampleStorage.h"

struct TestingInstance
{
    ParkingHouseInfo info;
    ParkingHouse house;
    std::shared_ptr<ExampleStorage> storage;
    TestingInstance()
    {
        storage = std::make_shared<ExampleStorage>();
        house = ParkingHouse(info, storage);
    }

    void testEntry()
    {
        ParkingData userData;
        userData.licensePlate = "AAA123";
        
        auto now = std::chrono::system_clock::now();
        userData.startTime = std::chrono::system_clock::to_time_t(now);

        house.registerEntry(userData);
        auto ret = storage->retrieve(userData.spotID);
        if (ret && userData == ret.value())
        {
            std::cout << "OK\n"; 
            return;
        }
        std::cout << "ERROR: ENTRY FAILED\n";
    }
    
    void testExit()
    {

    }
};



int main() 
{
    TestingInstance ti;
    ti.testEntry();
}