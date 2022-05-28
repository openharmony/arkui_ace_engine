/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTILS_H

#include <chrono>
#include <cmath>
#include <cstdint>
#include <stdint.h>

namespace OHOS::Ace {

template<typename T, std::size_t N>
constexpr std::size_t ArraySize(T (&)[N]) noexcept
{
    return N;
}

template<typename T, int32_t N>
T ConvertIntToEnum(int32_t index, const T (&values)[N], T defaultValue)
{
    if (index >= 0 && index < N) {
        return values[index];
    }
    return defaultValue;
}

template<typename T>
class Epsilon {
public:
    inline static T Value();
};

template<>
inline float Epsilon<float>::Value()
{
    static constexpr float epsilon = 0.0001F;
    return epsilon;
}

template<>
inline double Epsilon<double>::Value()
{
    static constexpr double epsilon = 0.000001;
    return epsilon;
}

template<>
inline int32_t Epsilon<int32_t>::Value()
{
    return 0;
}

template<>
inline uint32_t Epsilon<uint32_t>::Value()
{
    return 0;
}

template<typename T>
inline bool NearEqual(T left, T right, T epsilon)
{
    return ((left - right) <= epsilon) && ((left - right) >= -epsilon);
}

template<typename T>
inline bool NearZero(T value, T epsilon)
{
    return NearEqual(value, static_cast<T>(0), epsilon);
}

template<typename T>
inline bool NearEqual(T left, T right)
{
    return NearEqual(left, right, Epsilon<T>::Value());
}

inline bool NearEqual(double left, float right)
{
    return NearEqual(left, static_cast<double>(right));
}

inline bool NearEqual(float left, double right)
{
    return NearEqual(left, static_cast<float>(right));
}

template<typename T>
inline bool NearZero(T left)
{
    return NearZero(left, Epsilon<T>::Value());
}

template<typename T>
inline bool LessNotEqual(T left, T right)
{
    return (left - right) < -Epsilon<T>::Value();
}

inline bool LessNotEqual(double left, int32_t right)
{
    return LessNotEqual(left, static_cast<double>(right));
}

template<typename T>
inline bool LessOrEqual(T left, T right)
{
    return LessNotEqual(left, right) || NearEqual(left, right);
}

inline bool LessOrEqual(float left, double right)
{
    return LessNotEqual(left, static_cast<float>(right)) || NearEqual(left, static_cast<float>(right));
}

template<typename T>
inline bool GreatNotEqual(T left, T right)
{
    return (left - right) > Epsilon<T>::Value();
}

inline bool GreatNotEqual(float left, double right)
{
    return GreatNotEqual(left, static_cast<float>(right));
}

inline bool GreatNotEqual(double left, float right)
{
    return GreatNotEqual(left, static_cast<double>(right));
}

template<typename T>
inline bool GreatOrEqual(T left, T right)
{
    return GreatNotEqual(left, right) || NearEqual(left, right);
}

inline bool GreatOrEqual(float left, double right)
{
    return GreatNotEqual(left, static_cast<float>(right)) || NearEqual(left, static_cast<float>(right));
}

template<typename T>
inline bool Negative(T value)
{
    return LessNotEqual(value, static_cast<T>(0));
}

template<typename T>
inline bool NonNegative(T value)
{
    return GreatOrEqual(value, static_cast<T>(0));
}

template<typename T>
inline bool Positive(T value)
{
    return GreatNotEqual(value, static_cast<T>(0));
}

template<typename T>
inline bool NonPositive(T value)
{
    return LessOrEqual(value, static_cast<T>(0));
}

inline double Round(double rawNum)
{
    static constexpr double epsilon = 0.000001;
    return std::round(rawNum + epsilon);
}

inline bool InRegion(double lowerBound, double upperBound, double destNum)
{
    return LessOrEqual(lowerBound, destNum) && LessOrEqual(destNum, upperBound);
}

inline uint64_t GetMilliseconds()
{
    auto now = std::chrono::system_clock::now();
    auto millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return millisecs.count();
}

inline uint64_t GetNanoseconds()
{
    auto now = std::chrono::system_clock::now();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    return nanoseconds.count();
}

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTILS_H
