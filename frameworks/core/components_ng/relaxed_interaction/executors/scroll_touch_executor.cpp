/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/relaxed_interaction/executors/scroll_touch_executor.h"

#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ScrollTouchExecutor::ScrollTouchExecutor(WeakPtr<PipelineContext> context, const Command& cmd)
    : BaseExecutor(context), cmd_(cmd)
{}

ExecutorResult ScrollTouchExecutor::ExecuteStep()
{
    bool result = ExecuteTargetMode();
    return result ? ExecutorResult::SUCCESS : ExecutorResult::FAILED;
}

PointF ScrollTouchExecutor::ToPoint(const ScrollActionInfo& actionInfo)
{
    float dx = 0.0f;
    float dy = 0.0f;
    switch (actionInfo.direction) {
        case RelaxedScrollDirection::UP:
            dy = -actionInfo.distance;
            break;
        case RelaxedScrollDirection::DOWN:
            dy = actionInfo.distance;
            break;
        case RelaxedScrollDirection::LEFT:
            dx = -actionInfo.distance;
            break;
        case RelaxedScrollDirection::RIGHT:
            dx = actionInfo.distance;
            break;
        case RelaxedScrollDirection::FORWARD:
            dy = -actionInfo.distance;
            break;
        case RelaxedScrollDirection::BACKWARD:
            dy = actionInfo.distance;
            break;
        default:
            break;
    }
    return PointF { dx, dy };
}

bool ScrollTouchExecutor::ExecuteTargetMode()
{
    float x = cmd_.actionInfo.coordinates.x1;
    float y = cmd_.actionInfo.coordinates.y1;

    RefPtr<ScrollPattern> scroll = FindScrollPattern(x, y);
    if (!scroll) {
        return false;
    }

    RefPtr<ScrollableController> scrollController = scroll->GetOrCreatePositionController();
    auto point = ToPoint(cmd_.actionInfo);
    scrollController->ScrollBy(point.GetX(), point.GetY(), true);
    return true;
}

RefPtr<ScrollPattern> ScrollTouchExecutor::FindScrollPattern(float x, float y)
{
    auto context = context_.Upgrade();
    if (!context) {
        return nullptr;
    }
    auto result = FindFrameNode(x, y, ScrollRecognizerPred());
    if (!result.GetNode()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "No FrameNode found at coordinates.");
        return nullptr;
    }
    return AceType::DynamicCast<ScrollPattern>(result.GetNode()->GetPattern());
}

} // namespace OHOS::Ace::NG