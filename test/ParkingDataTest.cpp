#include "gtest/gtest.h"
#include "ParkingData.h"

TEST(ParkingDataTests, InitCorrectness)
{
    ParkingData a;
    ParkingData b;
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a.startTime.has_value());
    ASSERT_FALSE(a.endTime.has_value());
}

TEST(ParkingDataTests, EqualityWithoutTime)
{
    ParkingData a;
    ParkingData b;
    a.spotID = 10;
    b.spotID = 10;
    a.licensePlate = "AAA123";
    b.licensePlate = "AAA123";

    ASSERT_TRUE(a == b);
}

TEST(ParkingDataTests, EqualityWithTime)
{
    using namespace std::chrono;
    using std::make_optional, std::optional, std::time_t;

    auto now = system_clock::now();
    auto offset = now += hours(5);
    auto someTime = make_optional<time_t>(system_clock::to_time_t(now));
    auto someOtherTime = make_optional<time_t>(system_clock::to_time_t(offset));

    ParkingData a;
    ParkingData b;
    a.spotID = 10;
    b.spotID = 10;
    a.licensePlate = "AAA123";
    b.licensePlate = "AAA123";
    a.startTime = someTime;
    b.startTime = someTime;
    a.endTime = someOtherTime;
    b.endTime = someOtherTime;

    ASSERT_TRUE(a == b);
}