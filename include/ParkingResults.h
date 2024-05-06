#pragma once
#include <optional>

/// @brief Status codes returned by a data broker.
enum class BrokerResult
{
    Vacant,
    Occupied,
    IDNotFound,
    InvalidLicensePlate,
    LicensePlateNotFound,
    CouldNotStoreData,
    CouldNotAccessData
};

/// @brief Status codes returned by the parking house system.
enum class RangeCheckResult
{
    Valid,
    InvalidID,
    UnsetTimeStamp,
    InvalidStartTime,
    InvalidEndTime
};

/// @brief Error data for entry/exit results.
struct RegistrationError
{
    std::optional<BrokerResult> brokerResult; 
    std::optional<RangeCheckResult> rangeCheckResult;

    RegistrationError() = default;

    RegistrationError(std::optional<RangeCheckResult> rangeCheckResult)
        : rangeCheckResult(rangeCheckResult) {}

    RegistrationError(std::optional<BrokerResult> brokerResult)
        : brokerResult(brokerResult) {}
};

/// @brief Whether the entry was processed correctly, and any error info if it wasn't.
struct EntryResult
{
    bool isValid = false;
    RegistrationError errorInfo;

    EntryResult(bool isValid, RegistrationError errorInfo = RegistrationError())
        : isValid(isValid), errorInfo(errorInfo) {}

    EntryResult(bool isValid, RangeCheckResult rangeCheckResult)
        : isValid(isValid), errorInfo(rangeCheckResult) {}

    EntryResult(bool isValid, BrokerResult brokerResult)
        : isValid(isValid), errorInfo(brokerResult) {}
};

/// @brief Whether the exit was processed correctly, its cost, and any error info if it failed to process.
struct ExitResult
{
    bool isValid;
    double cost;
    RegistrationError errorInfo;

    ExitResult(bool isValid, double cost)
        : isValid(isValid), cost(cost), errorInfo(errorInfo) {}

    ExitResult(bool isValid, double cost, RangeCheckResult rangeCheckResult)
        : isValid(isValid), cost(cost), errorInfo(rangeCheckResult) {}

    ExitResult(bool isValid, double cost, BrokerResult brokerResult)
        : isValid(isValid), cost(cost), errorInfo(brokerResult) {}
};