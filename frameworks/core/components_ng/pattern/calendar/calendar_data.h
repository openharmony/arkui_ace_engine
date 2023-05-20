/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_DATA_H

#include <optional>
#include "base/geometry/dimension.h"
#include "core/components/calendar/calendar_controller_v2.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/calendar/calendar_controller_ng.h"

namespace OHOS::Ace {
struct CurrentDayStyleData {
    std::optional<Color> dayColor;
    std::optional<Color> lunarColor;
    std::optional<Color> markLunarColor;
    std::optional<Dimension> dayFontSize;
    std::optional<Dimension> lunarDayFontSize;
    std::optional<Dimension> dayHeight;
    std::optional<Dimension> dayWidth;
    std::optional<Dimension> gregorianCalendarHeight;
    std::optional<Dimension> lunarHeight;
    std::optional<Dimension> dayYAxisOffset;
    std::optional<Dimension> lunarDayYAxisOffset;
    std::optional<Dimension> underscoreXAxisOffset;
    std::optional<Dimension> underscoreYAxisOffset;
    std::optional<Dimension> scheduleMarkerXAxisOffset;
    std::optional<Dimension> scheduleMarkerYAxisOffset;
    std::optional<Dimension> colSpace;
    std::optional<Dimension> dailyFiveRowSpace;
    std::optional<Dimension> dailySixRowSpace;
    std::optional<Dimension> underscoreWidth;
    std::optional<Dimension> underscoreLength;
    std::optional<Dimension> scheduleMarkerRadius;
    std::optional<Dimension> boundaryRowOffset;
    std::optional<Dimension> boundaryColOffset;
    std::optional<Dimension> touchCircleStrokeWidth;
};

struct NonCurrentDayStyleData {
    std::optional<Color> nonCurrentMonthDayColor;
    std::optional<Color> nonCurrentMonthLunarColor;
    std::optional<Color> nonCurrentMonthWorkDayMarkColor;
    std::optional<Color> nonCurrentMonthOffDayMarkColor;
};

struct TodayStyleData {
    std::optional<Color> focusedDayColor;
    std::optional<Color> focusedLunarColor;
    std::optional<Color> focusedAreaBackgroundColor;
    std::optional<Dimension> focusedAreaRadius;
};

struct WeekStyleData {
    std::optional<Color> weekColor;
    std::optional<Color> weekendDayColor;
    std::optional<Color> weekendLunarColor;
    std::optional<Dimension> weekFontSize;
    std::optional<Dimension> weekHeight;
    std::optional<Dimension> weekWidth;
    std::optional<Dimension> weekAndDayRowSpace;
};

struct WorkStateStyleData {
    std::optional<Color> workDayMarkColor;
    std::optional<Color> offDayMarkColor;
    std::optional<Dimension> workDayMarkSize;
    std::optional<Dimension> offDayMarkSize;
    std::optional<Dimension> workStateWidth;
    std::optional<Dimension> workStateHorizontalMovingDistance;
    std::optional<Dimension> workStateVerticalMovingDistance;
};

struct CalendarModelData {
    CalendarDay date;
    ObtainedMonth currentData;
    ObtainedMonth preData;
    ObtainedMonth nextData;
    RefPtr<AceType> controller = nullptr;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_DATA_H