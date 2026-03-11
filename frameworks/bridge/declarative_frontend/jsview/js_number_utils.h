/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_NUMBER_UTILS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_NUMBER_UTILS_H

#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <type_traits>

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"

namespace OHOS::Ace::Framework {

// 日志宏定义（使用前需包含适当的日志头文件）
#ifndef LOGD
#define LOGD(...) printf("[DEBUG] " __VA_ARGS__)
#endif

enum class NumberValidationResult {
    VALID,
    NOT_NUMBER,
    IS_NAN,
    IS_POSITIVE_INFINITY,
    IS_NEGATIVE_INFINITY,
    OUT_OF_RANGE,
    NOT_INTEGER,
    INVALID_TYPE
};

enum class InfinityCheckMode {
    REJECT_ALL,           // 拒绝所有Infinity（正和负）
    ALLOW_POSITIVE,       // 允许正Infinity，拒绝负Infinity
    ALLOW_ALL             // 允许所有Infinity
};

template<typename T>
struct ValidatedNumber {
    NumberValidationResult result;
    T value;
    bool IsValid() const { return result == NumberValidationResult::VALID; }
    bool IsSpecialValue() const {
        return result == NumberValidationResult::IS_NAN ||
               result == NumberValidationResult::IS_POSITIVE_INFINITY ||
               result == NumberValidationResult::IS_NEGATIVE_INFINITY;
    }
};

class JSNumberUtils {
public:
    static NumberValidationResult ValidateDouble(double value)
    {
        if (std::isnan(value)) {
            return NumberValidationResult::IS_NAN;
        }
        if (std::isinf(value)) {
            return value > 0 ? NumberValidationResult::IS_POSITIVE_INFINITY
                             : NumberValidationResult::IS_NEGATIVE_INFINITY;
        }
        return NumberValidationResult::VALID;
    }

    static NumberValidationResult ValidateFloat(float value)
    {
        if (std::isnan(value)) {
            return NumberValidationResult::IS_NAN;
        }
        if (std::isinf(value)) {
            return value > 0 ? NumberValidationResult::IS_POSITIVE_INFINITY
                             : NumberValidationResult::IS_NEGATIVE_INFINITY;
        }
        return NumberValidationResult::VALID;
    }

    static bool IsSafeInt32(double value)
    {
        if (std::isnan(value) || std::isinf(value)) {
            return false;
        }

        constexpr int32_t minInt32 = std::numeric_limits<int32_t>::min();
        constexpr int32_t maxInt32 = std::numeric_limits<int32_t>::max();

        if (value < static_cast<double>(minInt32) || value > static_cast<double>(maxInt32)) {
            return false;
        }

        // 与原有ToNumber<int32_t>()行为保持一致：允许float截断，不要求精确整数
        return true;
    }

    static bool IsSafeUint32(double value)
    {
        if (std::isnan(value) || std::isinf(value)) {
            return false;
        }

        constexpr uint32_t maxUint32 = std::numeric_limits<uint32_t>::max();

        if (value < 0.0 || value > static_cast<double>(maxUint32)) {
            return false;
        }

        // 与原有ToNumber<uint32_t>()行为保持一致：允许float截断，不要求精确整数
        return true;
    }

    static bool IsSafeInt64(double value)
    {
        if (std::isnan(value) || std::isinf(value)) {
            return false;
        }

        constexpr int64_t minInt64 = std::numeric_limits<int64_t>::min();
        constexpr int64_t maxInt64 = std::numeric_limits<int64_t>::max();

        if (value < static_cast<double>(minInt64) || value > static_cast<double>(maxInt64)) {
            return false;
        }

        // 与原有ToNumber<int64_t>()行为保持一致：允许float截断，不要求精确整数
        return true;
    }

    static NumberValidationResult CheckInfinityMode(double value, InfinityCheckMode mode)
    {
        NumberValidationResult result = ValidateDouble(value);

        if (result == NumberValidationResult::VALID ||
            result == NumberValidationResult::IS_NAN) {
            return result;
        }

        switch (mode) {
            case InfinityCheckMode::REJECT_ALL:
                return result;  // 任何Infinity都拒绝
            case InfinityCheckMode::ALLOW_POSITIVE:
                return result == NumberValidationResult::IS_POSITIVE_INFINITY
                    ? NumberValidationResult::VALID
                    : result;  // 只允许正Infinity
            case InfinityCheckMode::ALLOW_ALL:
                return NumberValidationResult::VALID;  // 允许所有Infinity
            default:
                return result;
        }
    }

    static ValidatedNumber<int32_t> GetValidatedInt32(
        const JSRef<JSVal>& jsValue, int32_t defaultValue = 0)
    {
        if (!jsValue->IsNumber()) {
            return { NumberValidationResult::NOT_NUMBER, defaultValue };
        }

        double doubleValue = jsValue->ToNumber<double>();
        NumberValidationResult result = ValidateDouble(doubleValue);

        if (result != NumberValidationResult::VALID) {
            return { result, defaultValue };
        }

        if (!IsSafeInt32(doubleValue)) {
            return { NumberValidationResult::NOT_INTEGER, defaultValue };
        }

        int32_t intValue = static_cast<int32_t>(doubleValue);

        return { NumberValidationResult::VALID, intValue };
    }

    static ValidatedNumber<uint32_t> GetValidatedUint32(
        const JSRef<JSVal>& jsValue, uint32_t defaultValue = 0)
    {
        if (!jsValue->IsNumber()) {
            return { NumberValidationResult::NOT_NUMBER, defaultValue };
        }

        double doubleValue = jsValue->ToNumber<double>();
        NumberValidationResult result = ValidateDouble(doubleValue);

        if (result != NumberValidationResult::VALID) {
            return { result, defaultValue };
        }

        if (!IsSafeUint32(doubleValue)) {
            return { NumberValidationResult::NOT_INTEGER, defaultValue };
        }

        uint32_t uintValue = static_cast<uint32_t>(doubleValue);

        return { NumberValidationResult::VALID, uintValue };
    }

    static ValidatedNumber<int64_t> GetValidatedInt64(
        const JSRef<JSVal>& jsValue, int64_t defaultValue = 0)
    {
        if (!jsValue->IsNumber()) {
            return { NumberValidationResult::NOT_NUMBER, defaultValue };
        }

        double doubleValue = jsValue->ToNumber<double>();
        NumberValidationResult result = ValidateDouble(doubleValue);

        if (result != NumberValidationResult::VALID) {
            return { result, defaultValue };
        }

        if (!IsSafeInt64(doubleValue)) {
            return { NumberValidationResult::NOT_INTEGER, defaultValue };
        }

        int64_t intValue = static_cast<int64_t>(doubleValue);

        return { NumberValidationResult::VALID, intValue };
    }

    static ValidatedNumber<float> GetValidatedFloat(
        const JSRef<JSVal>& jsValue, float defaultValue = 0.0f,
        InfinityCheckMode infinityMode = InfinityCheckMode::REJECT_ALL)
    {
        if (!jsValue->IsNumber()) {
            return { NumberValidationResult::NOT_NUMBER, defaultValue };
        }

        float floatValue = jsValue->ToNumber<float>();
        NumberValidationResult result = ValidateFloat(floatValue);

        if (result == NumberValidationResult::IS_NAN) {
            return { NumberValidationResult::IS_NAN, defaultValue };
        }

        result = CheckInfinityMode(static_cast<double>(floatValue), infinityMode);

        if (result != NumberValidationResult::VALID) {
            return { result, defaultValue };
        }

        return { NumberValidationResult::VALID, floatValue };
    }

    static ValidatedNumber<double> GetValidatedDouble(
        const JSRef<JSVal>& jsValue, double defaultValue = 0.0,
        InfinityCheckMode infinityMode = InfinityCheckMode::REJECT_ALL)
    {
        if (!jsValue->IsNumber()) {
            return { NumberValidationResult::NOT_NUMBER, defaultValue };
        }

        double doubleValue = jsValue->ToNumber<double>();
        NumberValidationResult result = ValidateDouble(doubleValue);

        if (result == NumberValidationResult::IS_NAN) {
            return { NumberValidationResult::IS_NAN, defaultValue };
        }

        result = CheckInfinityMode(doubleValue, infinityMode);

        if (result != NumberValidationResult::VALID) {
            return { result, defaultValue };
        }

        return { NumberValidationResult::VALID, doubleValue };
    }

    template<typename T>
    static T GetNumberOrDefault(
        const JSRef<JSVal>& jsValue, T defaultValue,
        InfinityCheckMode infinityMode = InfinityCheckMode::REJECT_ALL)
    {
        static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");

        if constexpr (std::is_same_v<T, int32_t>) {
            auto validated = GetValidatedInt32(jsValue, static_cast<int32_t>(defaultValue));
            return validated.IsValid() ? validated.value : defaultValue;
        } else if constexpr (std::is_same_v<T, uint32_t>) {
            auto validated = GetValidatedUint32(jsValue, static_cast<uint32_t>(defaultValue));
            return validated.IsValid() ? validated.value : defaultValue;
        } else if constexpr (std::is_same_v<T, int64_t>) {
            auto validated = GetValidatedInt64(jsValue, static_cast<int64_t>(defaultValue));
            return validated.IsValid() ? validated.value : defaultValue;
        } else if constexpr (std::is_same_v<T, float>) {
            auto validated = GetValidatedFloat(jsValue, static_cast<float>(defaultValue), infinityMode);
            return validated.IsValid() ? validated.value : defaultValue;
        } else if constexpr (std::is_same_v<T, double>) {
            auto validated = GetValidatedDouble(jsValue, static_cast<double>(defaultValue), infinityMode);
            return validated.IsValid() ? validated.value : defaultValue;
        }

        return defaultValue;
    }

    static int32_t GetInt32WithRangeCheck(
        const JSRef<JSVal>& jsValue, int32_t defaultValue, int32_t minValue, int32_t maxValue)
    {
        auto validated = GetValidatedInt32(jsValue, defaultValue);

        if (!validated.IsValid()) {
            return defaultValue;
        }

        if (validated.value < minValue || validated.value > maxValue) {
            return defaultValue;
        }

        return validated.value;
    }

    static uint32_t GetUint32WithRangeCheck(
        const JSRef<JSVal>& jsValue, uint32_t defaultValue, uint32_t maxValue)
    {
        auto validated = GetValidatedUint32(jsValue, defaultValue);

        if (!validated.IsValid()) {
            return defaultValue;
        }

        if (validated.value > maxValue) {
            return defaultValue;
        }

        return validated.value;
    }

    static double GetDoubleWithRangeCheck(
        const JSRef<JSVal>& jsValue, double defaultValue, double minValue, double maxValue,
        InfinityCheckMode infinityMode = InfinityCheckMode::REJECT_ALL)
    {
        auto validated = GetValidatedDouble(jsValue, defaultValue, infinityMode);

        if (!validated.IsValid()) {
            return defaultValue;
        }

        if (validated.value < minValue || validated.value > maxValue) {
            return defaultValue;
        }

        return validated.value;
    }

    static bool IsNumberValid(const JSRef<JSVal>& jsValue)
    {
        if (!jsValue->IsNumber()) {
            return false;
        }

        double doubleValue = jsValue->ToNumber<double>();
        NumberValidationResult result = ValidateDouble(doubleValue);

        return result == NumberValidationResult::VALID;
    }

    static bool IsNumberPositive(const JSRef<JSVal>& jsValue, double minValue = 0.0)
    {
        if (!jsValue->IsNumber()) {
            return false;
        }

        double doubleValue = jsValue->ToNumber<double>();
        NumberValidationResult result = ValidateDouble(doubleValue);

        if (result != NumberValidationResult::VALID) {
            return false;
        }

        return doubleValue >= minValue;
    }

    static const char* GetValidationResultString(NumberValidationResult result)
    {
        switch (result) {
            case NumberValidationResult::VALID:
                return "VALID";
            case NumberValidationResult::NOT_NUMBER:
                return "NOT_NUMBER";
            case NumberValidationResult::IS_NAN:
                return "IS_NAN";
            case NumberValidationResult::IS_POSITIVE_INFINITY:
                return "IS_POSITIVE_INFINITY";
            case NumberValidationResult::IS_NEGATIVE_INFINITY:
                return "IS_NEGATIVE_INFINITY";
            case NumberValidationResult::OUT_OF_RANGE:
                return "OUT_OF_RANGE";
            case NumberValidationResult::NOT_INTEGER:
                return "NOT_INTEGER";
            case NumberValidationResult::INVALID_TYPE:
                return "INVALID_TYPE";
            default:
                return "UNKNOWN";
        }
    }

    static const char* GetInfinityCheckModeString(InfinityCheckMode mode)
    {
        switch (mode) {
            case InfinityCheckMode::REJECT_ALL:
                return "REJECT_ALL";
            case InfinityCheckMode::ALLOW_POSITIVE:
                return "ALLOW_POSITIVE";
            case InfinityCheckMode::ALLOW_ALL:
                return "ALLOW_ALL";
            default:
                return "UNKNOWN";
        }
    }
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_NUMBER_UTILS_H
