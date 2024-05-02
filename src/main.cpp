#include <iostream>
#include "ParkingHouse.h"
#include "ExampleStorage.h"
class TestingInstance
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
    }
};


void testExit()
{

}

int main() 
{
    std::cout << "Hello World\n"; 
}