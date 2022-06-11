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

#include "core/components_ng/event/scrollable_event.h"

#include "base/geometry/offset.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ScrollableActuator::ScrollableActuator(const WeakPtr<FrameNode>& host) : host_(host) {}

void ScrollableActuator::OnCollectTouchTarget(
    const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    LOGI("TouchTest: OnCollectTouchTarget");
    if (!initialized_) {
        InitializeScrollable();
    }
    for (const auto& [axis, scrollable] : scrollables_) {
        scrollable->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        result.emplace_back(scrollable);
    }
}

void ScrollableActuator::InitializeScrollable()
{
    if (scrollableEvents_.empty()) {
        return;
    }
    auto host = host_.Upgrade();
    if (!host) {
        LOGE("the host is nullptr");
        return;
    }
    for (const auto& [axis, events] : scrollableEvents_) {
        auto callback = [weak = WeakClaim(this), axis = axis](double offset, int32_t source) {
            auto actuator = weak.Upgrade();
            if (!actuator) {
                return true;
            }
            bool canScroll = true;
            for (const auto& task : actuator->scrollableEvents_[axis]) {
                canScroll = task->GetScrollPositionCallback()(offset, source) && canScroll;
            }
            return canScroll;
        };
        auto scrollable = MakeRefPtr<Scrollable>(std::move(callback), axis);
        scrollable->Initialize(host->GetContext());
        scrollables_[axis] = scrollable;
    }
    initialized_ = true;
}

} // namespace OHOS::Ace::NG