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

#include "ace_extra_input_data.h"

#include "pointer_event.h"

#define CHECK_FALSE_RETURN CHECK_NULL_RETURN

namespace OHOS::Ace {
void AceExtraInputData::WriteToInput(const std::shared_ptr<MMI::InputEvent>& inputEvent, AceExtraInputData& data)
{
    std::shared_ptr<uint8_t[]> dst(new uint8_t[sizeof(AceExtraInputData)], [](uint8_t* ptr) { delete[] ptr; });
    auto* src = reinterpret_cast<uint8_t*>(&data);
    std::copy(src, src + sizeof(AceExtraInputData), dst.get());
    inputEvent->SetExtraData(dst, sizeof(AceExtraInputData));
}

void AceExtraInputData::ReadToTouchEvent(const std::shared_ptr<MMI::InputEvent>& inputEvent, TouchEvent& event)
{
    std::shared_ptr<const uint8_t[]> raw;
    uint32_t length = 0;
    inputEvent->GetExtraData(raw, length);
    if (length == 0 || !raw) {
        return;
    }

    const AceExtraInputData* data = reinterpret_cast<const AceExtraInputData*>(raw.get());
    event.x = data->interpolatedX;
    event.y = data->interpolatedY;
    event.screenX = data->interpolatedDisplayX;
    event.screenY = data->interpolatedDisplayY;
    uint64_t stampCnt = data->msSinceEpoch;
    auto msSinceEpoch = std::chrono::milliseconds(stampCnt);
    std::chrono::high_resolution_clock::time_point timeStamp(msSinceEpoch);
    event.time = timeStamp;
}

void AceExtraInputData::InsertInterpolatePoints(const TouchEventInfo& info)
{
    const auto pointerEvent = info.GetPointerEvent();
    MMI::PointerEvent::PointerItem item;
    if (!pointerEvent->GetPointerItem(pointerEvent->GetPointerId(), item)) {
        return;
    }

    const auto changedInfo = info.GetChangedTouches();
    if (changedInfo.empty()) {
        return;
    }
    const auto& point = changedInfo.front();
    const Offset& location = point.GetLocalLocation();
    const auto& screenLocation = point.GetScreenLocation();
    AceExtraInputData aceData(
        location.GetX(), location.GetY(), screenLocation.GetX(), screenLocation.GetY(), info.GetTimeStamp());
    aceData.WriteToInput(pointerEvent, aceData);
}
} // namespace OHOS::Ace
