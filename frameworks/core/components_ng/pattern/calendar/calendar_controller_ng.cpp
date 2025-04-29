/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_controller_ng.h"

namespace OHOS::Ace::NG {

void CalendarControllerNg::BackToToday()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto calendarPattern = AceType::DynamicCast<CalendarPattern>(pattern);
    calendarPattern->FireFirstRequestData();
    calendarPattern->SetBackToToday(true);
}

void CalendarControllerNg::GoTo(int32_t year, int32_t month, int32_t day)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto calendarPattern = AceType::DynamicCast<CalendarPattern>(pattern);
    calendarPattern->FireGoToRequestData(year, month, day);
    calendarPattern->SetGoTo(true);
}

} // namespace OHOS::Ace::NG
