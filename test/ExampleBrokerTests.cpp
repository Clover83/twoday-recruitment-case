#include "gtest/gtest.h"
#include "ExampleDataBroker.h"

struct BrokerTestInsertResult
{
    BrokerResult preInsert;
    BrokerResult postInsert;
    ParkingSpotData foundData; 

    BrokerTestInsertResult(BrokerResult preInsert, BrokerResult postInsert, ParkingSpotData foundData)
        : preInsert(preInsert), postInsert(postInsert), foundData(foundData) {}
};

class ExampleBrokerTest : public testing::Test
{
public:
    ExampleDataBroker broker;

    BrokerTestInsertResult getInsertResults(const ParkingSpotData& data)
    {
        auto [resultPreInsert, foundDataPre] = broker.findSpot(data);

        if (resultPreInsert != BrokerResult::Vacant)
            return BrokerTestInsertResult(resultPreInsert, resultPreInsert, foundDataPre);

        broker.onValidEntry(data);
        auto [resultPostInsert, foundDataPost] = broker.findSpot(data);
        return BrokerTestInsertResult(resultPreInsert, resultPostInsert, foundDataPost);
    }
};

TEST_F(ExampleBrokerTest, VacantEntry)
{
    ParkingSpotData validEntry(10, "ABC123");
    auto results = getInsertResults(validEntry);

    ASSERT_EQ(results.preInsert, BrokerResult::Vacant)
        << "Spot is not vacant pre-insertion.";
    ASSERT_EQ(results.postInsert, BrokerResult::Occupied)
        << "Spot is not occupied post-insertion.";
    ASSERT_EQ(results.foundData, validEntry)
        << "Inserted data does not mach found data.";
}

TEST_F(ExampleBrokerTest, OccupiedEntry)
{
    ParkingSpotData firstEntry(10, "ABC123");
    ParkingSpotData secondEntry(10, "DEF456");

    broker.onValidEntry(firstEntry);
    auto results = getInsertResults(secondEntry);

    ASSERT_EQ(results.preInsert, BrokerResult::Occupied)
        << "Spot is not occupied pre-insertion.";
    ASSERT_EQ(results.foundData, firstEntry)
        << "Found data does not match first entry.";
}

TEST_F(ExampleBrokerTest, LicensePlateCollision)
{
    ParkingSpotData firstEntry(10, "ABC123");
    ParkingSpotData secondEntry(15, "ABC123");

    broker.onValidEntry(firstEntry);
    auto [result, _] = broker.findSpot(secondEntry);
    ASSERT_EQ(result, BrokerResult::InvalidLicensePlate)
        << "InvalidLicensePlate not returned on license plate collision.";
}