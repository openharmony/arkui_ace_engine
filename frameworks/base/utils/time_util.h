/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_TIME_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_TIME_UTIL_H

#include <cstdint>
#include <ctime>
#include <float.h>
#include <limits.h>
#include <string>

#include "base/utils/macros.h"

namespace OHOS::Ace {
constexpr int32_t DEFAULT_HOURS_WEST = -8;

/**
* The GetMicroTickCount function get current microseconds since the system was started.
*/
ACE_FORCE_EXPORT int64_t GetMicroTickCount();

int64_t GetSysTimestamp();

/**
* return milliseconds to 1970-1-1 0:0:0
*/
int64_t GetCurrentTimestamp();
int64_t GetCurrentTimestampMicroSecond();
std::string ConvertTimestampToStr(int64_t timestamp);

struct TimeOfNow final {
    explicit TimeOfNow(double hoursWest = INT_MAX) : hoursWest_(hoursWest) {}
    ~TimeOfNow() = default;

    // hours west of Greenwich, for e.g., [hoursWest] is [-8] in  UTC+8.
    // Valid range of [hoursWest] is [-14, 12]. Set default value to DBL_MAX to use current time zone by default.
    int32_t hoursWest_ = INT_MAX;
    int32_t second_ = 0;
    int32_t minute_ = 0;
    int32_t hour12_ = 0;    // 12-hour clock
    int32_t hour24_ = 0;    // 24-hour clock
    int64_t timeUsec_ = 0L; // microsecond. 1 second = 1000 millisecond = 1000000 microsecond
};

bool IsHoursWestValid(int32_t& hoursWest);

TimeOfNow GetTimeOfNow(int32_t hoursWest = INT_MAX);

bool IsDayTime(const TimeOfNow& timeOfNow);

struct TimeOfZone final {
    explicit TimeOfZone(int32_t hoursWest = DEFAULT_HOURS_WEST) : hoursWest_(hoursWest) {}
    ~TimeOfZone() = default;

    // hours west of Greenwich, for e.g., [hoursWest] is [-8] in  UTC+8.
    // Valid range of [hoursWest] is [-14, 12].
    // Set default value to DEFAULT_HOURS_WEST to use current time zone by default.
    int32_t hoursWest_ = DEFAULT_HOURS_WEST;
    int32_t second_ = 0;
    int32_t minute_ = 0;
    int32_t hour12_ = 0;    // 12-hour clock
    int32_t hour24_ = 0;    // 24-hour clock
    int64_t timeUsec_ = 0L; // microsecond. 1 second = 1000 millisecond = 1000000 microsecond
};

bool HoursWestIsValid(int32_t& hoursWest);

TimeOfZone GetTimeOfZone(int32_t hoursWest = DEFAULT_HOURS_WEST);

bool IsDayTime(const TimeOfZone& timeOfZone);

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_TIME_UTIL_H
