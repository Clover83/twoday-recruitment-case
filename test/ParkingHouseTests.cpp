#include "gtest/gtest.h"
#include "ParkingHouse.h"
#include "ExampleDataBroker.h"

class ParkingHouseTest : public testing::Test
{
public:
    std::shared_ptr<IParkingDataBroker> dataBroker;
    HouseInfo houseInfo;
    ParkingHouse house = ParkingHouse(houseInfo, dataBroker);

    std::time_t currentTime;
    std::time_t circaFiveMinutesLater;    
    std::time_t circaFiveHoursLater;    
    std::time_t circaFiveDaysLater;    

    double circaFiveMinutesCost;    
    double circaFiveHoursCost;    
    double circaFiveDaysCost;    

    ParkingSpotData validEntryData;

    void SetUp() override
    {
        using namespace std::chrono;
        // Set up parking house system.
        dataBroker = std::make_shared<ExampleDataBroker>(ExampleDataBroker());
        house = ParkingHouse(houseInfo, dataBroker);

        // Set reference times.
        auto now = system_clock::now();
        auto fiveMinutes = now +
            minutes(5) +
            seconds(18);
        auto fiveHours = now +
            hours(5) +
            minutes(18) +
            seconds(34); 
        auto fiveDays = now +
            hours(5 * 24) +
            hours(8) +
            minutes(21) +
            seconds(11);
        
        currentTime = system_clock::to_time_t(now);
        circaFiveMinutesLater = system_clock::to_time_t(fiveMinutes);
        circaFiveHoursLater = system_clock::to_time_t(fiveHours);
        circaFiveDaysLater = system_clock::to_time_t(fiveDays);

        // Corresponding cost calculations.
        circaFiveMinutesCost = houseInfo.costPerHour * (
            5.0 / 60.0 +
            18.0 / 3600.0);
        circaFiveHoursCost = houseInfo.costPerHour * (
            5.0 +
            18.0 / 60.0 +
            34.0 / 3600.0);
        circaFiveDaysCost = houseInfo.costPerDay * 5 +
            houseInfo.costPerHour * (
            8.0 +
            21.0 / 60.0 +
            11.0 / 3600.0);

        // Prepare valid entry data.
        validEntryData = ParkingSpotData(5, "ABC123", currentTime);
        validEntryData.timeStamp = currentTime;
    }

    double GetHoursCount(time_t start, time_t end)
    {
        time_t difference = end - start;
        return static_cast<double>(difference) / 60.0;
    }
};

// ---------------------------Entry Tests---------------------------

TEST_F(ParkingHouseTest, ValidEntry)
{
    EntryResult result = house.processEntry(validEntryData);

    ASSERT_TRUE(result.isValid)
        << "result.isValid is false.";
}

TEST_F(ParkingHouseTest, EntryIDOutOfRangeHigh)
{
    int spotCount = houseInfo.floorCount * houseInfo.spotsPerFloor;
    ParkingSpotData invalidData(spotCount + 15, "ABC123", currentTime);
    EntryResult result = house.processEntry(invalidData);

    ASSERT_FALSE(result.isValid)
        << "result.isValid is true.";

    ASSERT_TRUE(result.errorInfo.rangeCheckResult.has_value())
        << "RangeCheckResult does not contain a value.";

    ASSERT_EQ(result.errorInfo.rangeCheckResult.value(), RangeCheckResult::InvalidID)
        << "Range check did not return InvalidID.";
}


TEST_F(ParkingHouseTest, EntryIDOutOfRangeLow)
{
    ParkingSpotData invalidData(-5, "DEF456", currentTime);
    EntryResult result = house.processEntry(invalidData);

    ASSERT_FALSE(result.isValid)
        << "result.isValid is true.";
    
    ASSERT_TRUE(result.errorInfo.rangeCheckResult.has_value())
        << "RangeCheckResult does not contain a value.";

    ASSERT_EQ(result.errorInfo.rangeCheckResult.value(), RangeCheckResult::InvalidID)
        << "Range check did not return InvalidID.";
}

// ---------------------------Cost Tests----------------------------

TEST_F(ParkingHouseTest, CorrectFiveMinuteCost)
{
    double cost = house.getCost(circaFiveMinutesLater - currentTime);
    ASSERT_NEAR(cost, circaFiveMinutesCost, 0.1);
}

TEST_F(ParkingHouseTest, CorrectFiveHourCost)
{
    double cost = house.getCost(circaFiveHoursLater - currentTime);
    ASSERT_NEAR(cost, circaFiveHoursCost, 0.1);
}

TEST_F(ParkingHouseTest, CorrectFiveDayCost)
{
    double cost = house.getCost(circaFiveDaysLater - currentTime);
    ASSERT_NEAR(cost, circaFiveDaysCost, 0.1);
}

// ---------------------------Exit Tests----------------------------

TEST_F(ParkingHouseTest, ValidExit)
{
    house.processEntry(validEntryData);

    ParkingSpotData validExitData = validEntryData;    
    validExitData.timeStamp = circaFiveMinutesLater;
    ExitResult result = house.processExit(validExitData);

    ASSERT_TRUE(result.isValid)
        << "result.isValid is false.";
    ASSERT_NEAR(result.cost, circaFiveMinutesCost, 0.1);
}

TEST_F(ParkingHouseTest, ReversedExitTimes)
{
    ParkingSpotData invalidEntryData = validEntryData;
    invalidEntryData.timeStamp = circaFiveMinutesLater;

    ParkingSpotData invalidExitData = validEntryData;
    invalidExitData.timeStamp = currentTime;

    house.processEntry(invalidEntryData);
    ExitResult result = house.processExit(invalidExitData);

    ASSERT_FALSE(result.isValid)
        << "result.isValid is true.";
    
    ASSERT_TRUE(result.errorInfo.rangeCheckResult.has_value())
        << "RangeCheckResult does not contain a value.";

    ASSERT_EQ(result.errorInfo.rangeCheckResult.value(), RangeCheckResult::InvalidEndTime)
        << "Range check did not return InvalidEndTime";
}
