#include <memory>
#include "gtest/gtest.h"
#include "IParkingStorage.h"
#include "ExampleStorage.h"

class StorageTest : public testing::Test
{
protected:
    std::shared_ptr<IParkingStorage> storage;
    ParkingData mockData;
    StorageTest()
    {
        using namespace std::chrono;
        auto now = system_clock::now();

        ParkingData data;
        data.spotID = 10;
        data.licensePlate = "AAA123";
        data.startTime = system_clock::to_time_t(now);

        storage = std::make_shared<ExampleStorage>();
    }
};

TEST_F(StorageTest, Store)
{
    ASSERT_TRUE(storage->store(mockData));
}

TEST_F(StorageTest, Retrieve)
{
    auto maybeData = storage->retrieve(mockData.spotID);
    ASSERT_TRUE(maybeData);
    ASSERT_TRUE(maybeData.value() == mockData);

}