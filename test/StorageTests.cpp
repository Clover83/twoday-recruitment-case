#include <memory>
#include "gtest/gtest.h"
#include "IParkingStorage.h"
#include "ExampleStorage.h"

class StorageTests : public testing::Test
{
protected:
    std::shared_ptr<IParkingStorage> storage;
    ParkingData mockData;
    void SetUp() override
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

TEST_F(StorageTests, StoreAndRetrieve)
{
    ASSERT_TRUE(storage->store(mockData));

    auto maybeData = storage->retrieve(mockData.spotID);
    ASSERT_TRUE(maybeData);
    ASSERT_TRUE(maybeData.value() == mockData);
}
