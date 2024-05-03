#include <memory>
#include <math.h>
#include "gtest/gtest.h"
#include "ParkingHouse.h"
#include "ExampleStorage.h"

// A fixture for storing data needed throughout different test blocks.
class ParkingHouseTests : public testing::Test
{
protected:
    ParkingHouseInfo houseInfo;
    std::shared_ptr<IParkingStorage> storageInterface;
    std::shared_ptr<ParkingHouse> parkingHouse;

    time_t currentTime;
    time_t fiveHourOffset;
    time_t fiveDayOffset;
    time_t variedOffset;

    double fiveHourOffsetCost;
    double fiveDayOffsetCost;
    double variedOffsetCost;
    

    void SetUp() override
    {
        storageInterface = std::make_shared<ExampleStorage>();
        parkingHouse = std::make_shared<ParkingHouse>(
            ParkingHouse(houseInfo, storageInterface));
        
        using namespace std::chrono;
        auto now = system_clock::now();
        auto smallOffsetTP = now + hours(5);
        auto largeOffsetTP = now + hours(5 * 24);
        auto variedOffsetTP = now +
            hours(6 * 24) +
            hours(4) +
            minutes(17) +
            seconds(42);
        currentTime = system_clock::to_time_t(now);
        fiveHourOffset = system_clock::to_time_t(smallOffsetTP);
        fiveDayOffset = system_clock::to_time_t(largeOffsetTP);
        variedOffset = system_clock::to_time_t(variedOffsetTP);

        fiveHourOffsetCost = 5.0 * houseInfo.costPerHour;
        fiveDayOffsetCost = 5.0 * houseInfo.costPerDay;
        // Calculate cost for 6 days, 4 hours, 17 minutes, 42 seconds.
        variedOffsetCost = 6.0 * houseInfo.costPerDay +
            (4.0 + 17.0/60.0 + 42.0/3600.0) * houseInfo.costPerHour;
    }

    // Gets valid data but without the endTime set.
    ParkingData getValidParkingData()
    {
        ParkingData data;
        data.spotID = 10;
        data.licensePlate = "AAA123";
        data.startTime = currentTime;
        return data;
    }
};

TEST_F(ParkingHouseTests, RegisterValidEntry)
{
    ParkingData parkingData = getValidParkingData();
    auto result = parkingHouse->registerEntry(parkingData);
    ASSERT_EQ(result, RegistrationResult::VALID);

    auto storageData = storageInterface->retrieve(parkingData.spotID);
    ASSERT_TRUE(storageData);
    ASSERT_EQ(parkingData, storageData.value());
}


TEST_F(ParkingHouseTests, RegisterValidExit)
{
    ParkingData parkingData = getValidParkingData();
    parkingHouse->registerEntry(parkingData);

    parkingData.endTime = fiveHourOffset;
    auto [result, returnedCost] = 
        parkingHouse->registerExit(parkingData);

    ASSERT_EQ(result, RegistrationResult::VALID);

    ASSERT_TRUE(parkingData.startTime && parkingData.endTime)
        << "Start and/or end time optional is empty.";

    time_t secondsParked = parkingData.endTime.value() - parkingData.startTime.value();
    ASSERT_GT(secondsParked, 0);
}

TEST_F(ParkingHouseTests, CorrectHourlyCost)
{
    ParkingData parkingData = getValidParkingData();
    parkingHouse->registerEntry(parkingData);

    double expectedCost = fiveHourOffsetCost;
    parkingData.endTime = fiveHourOffset;
    auto [result, returnedCost] = 
        parkingHouse->registerExit(parkingData);

    ASSERT_DOUBLE_EQ(returnedCost, expectedCost);
}

TEST_F(ParkingHouseTests, CorrectDailyCost)
{
    ParkingData parkingData = getValidParkingData();
    parkingHouse->registerEntry(parkingData);

    double expectedCost = fiveDayOffsetCost;
    parkingData.endTime = fiveDayOffset;
    auto [result, returnedCost] = 
        parkingHouse->registerExit(parkingData);

    ASSERT_DOUBLE_EQ(returnedCost, expectedCost);
}

TEST_F(ParkingHouseTests, CorrectVariedCost)
{
    ParkingData parkingData = getValidParkingData();
    parkingHouse->registerEntry(parkingData);

    double expectedCost = variedOffsetCost;
    parkingData.endTime = variedOffset;
    auto [result, returnedCost] = 
        parkingHouse->registerExit(parkingData);

    ASSERT_DOUBLE_EQ(returnedCost, expectedCost);
}

TEST_F(ParkingHouseTests, SpotIDValidation)
{
    ParkingData validData = getValidParkingData();

    ParkingData invalidIDLow = validData;
    invalidIDLow.spotID = -50;
    
    ParkingData invalidIDHigh = validData;
    invalidIDHigh.spotID = houseInfo.getTotalSpots() + 1000;

    ASSERT_EQ(
        parkingHouse->registerEntry(invalidIDLow),
        RegistrationResult::INVALID_ID);

    ASSERT_EQ(
        parkingHouse->registerEntry(invalidIDHigh),
        RegistrationResult::INVALID_ID);

}

TEST_F(ParkingHouseTests, LicensePlateValidation)
{
    ParkingData unregisteredLicencePlate = getValidParkingData();
    unregisteredLicencePlate.licensePlate = "AAAAAA";
    ASSERT_EQ(
        parkingHouse->registerEntry(unregisteredLicencePlate), 
        RegistrationResult::LICENSE_PLATE_NOT_FOUND);
}

TEST_F(ParkingHouseTests, DateValidation)
{
    // Cannot register without valid start date.
    ParkingData validData = getValidParkingData();
    ParkingData invalidStartDate = validData;
    invalidStartDate.startTime = std::nullopt;
    ASSERT_EQ(parkingHouse->registerEntry(invalidStartDate), RegistrationResult::INVALID_START_DATE);

    // End time cannot be before start time.
    ParkingData invalidEndDate = validData;
    invalidEndDate.startTime = variedOffset;
    invalidEndDate.endTime = currentTime; 
    
    // If the end date is already provided in Entry, still fail in case of future expansion.
    ASSERT_EQ(parkingHouse->registerEntry(invalidEndDate), RegistrationResult::INVALID_END_DATE);
    // Also fail on Exit.
    parkingHouse->registerEntry(validData);
    ASSERT_EQ(parkingHouse->registerExit(invalidEndDate), RegistrationResult::INVALID_END_DATE);
}

TEST_F(ParkingHouseTests, CheckVacancy)
{
    ParkingData parkerA = getValidParkingData();
    ParkingData parkerB = getValidParkingData();
    parkerB.licensePlate = "AAAAAA";
    parkerB.startTime = fiveHourOffset;
    parkerB.endTime = fiveDayOffset;

    ASSERT_TRUE(parkingHouse->isSpotVacant(parkerA.spotID));
    parkingHouse->registerEntry(parkerA);
    ASSERT_FALSE(parkingHouse->isSpotVacant(parkerA.spotID));
    ASSERT_EQ(parkingHouse->registerEntry(parkerB), RegistrationResult::OCCUPIED);
}
