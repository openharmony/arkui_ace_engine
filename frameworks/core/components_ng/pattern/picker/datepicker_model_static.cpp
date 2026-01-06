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

#include "core/components_ng/pattern/picker/datepicker_model_static.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"

namespace OHOS::Ace::NG {
void DatePickerModelStatic::SetOnChange(FrameNode* frameNode, DateChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void DatePickerModelStatic::SetChangeEvent(FrameNode* frameNode, DateChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}

void DatePickerModelStatic::SetSelectedDate(FrameNode* frameNode, const int64_t& value)
{
    std::time_t time = static_cast<std::time_t>(value / 1000);
    std::tm local_tm{};
#ifdef WINDOWS_PLATFORM
    errno_t err = localtime_s(&local_tm, &time);
    if (err != 0) {
        LOGE("Failed to convert time to local time, error code: %{public}d", err);
        return;
    }
#else
    localtime_r(&time, &local_tm);
#endif

    const auto year = local_tm.tm_year + 1900;
    const auto month = local_tm.tm_mon + 1;
    const auto day = local_tm.tm_mday;
    DatePickerModelNG::SetSelectedDate(frameNode, PickerDate(year, month, day));
}
} // namespace OHOS::Ace::NG
 