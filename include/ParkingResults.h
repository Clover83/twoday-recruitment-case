#pragma once
#include <optional>

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

enum class RangeCheckResult
{
    Valid,
    InvalidID,
    InvalidStartTime,
    InvalidEndTime
};

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