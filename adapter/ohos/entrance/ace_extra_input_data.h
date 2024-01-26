/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_EXTRA_INPUT_DATA_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_EXTRA_INPUT_DATA_H

#include "input_event.h"

#include "frameworks/core/components_ng/event/touch_event.h"

namespace OHOS {
namespace Ace {
struct AceExtraInputData {
    float interpolatedX = 0.f;
    float interpolatedY = 0.f;
    float interpolatedDisplayX = 0.f;
    float interpolatedDisplayY = 0.f;
    uint64_t msSinceEpoch = 0;

    AceExtraInputData() = default;
    AceExtraInputData(float x, float y, float displayX, float displayY, const TimeStamp& time)
        : interpolatedX(x), interpolatedY(y), interpolatedDisplayX(displayX), interpolatedDisplayY(displayY)
    {
        auto stamp = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
        msSinceEpoch = static_cast<uint64_t>(stamp);
    }
    static void WriteToInput(const std::shared_ptr<MMI::InputEvent>& inputEvent, AceExtraInputData &data);
    static void ReadToTouchEvent(const std::shared_ptr<MMI::InputEvent>& inputEvent, TouchEvent& touchEvent);
    static void InsertInterpolatePoints(const TouchEventInfo& info);
};

} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_EXTRA_INPUT_DATA_H
