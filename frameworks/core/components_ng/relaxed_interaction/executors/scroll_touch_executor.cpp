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
#include "core/components_ng/manager/smart_gesture/smart_gesture_types.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"
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

bool ScrollTouchExecutor::ExecuteTargetMode()
{
    float x = cmd_.actionInfo.coordinates.x1;
    float y = cmd_.actionInfo.coordinates.y1;

    RefPtr<Pattern> scroll = FindScrollPattern(x, y);
    if (!scroll) {
        return false;
    }

    ScrollingConfig config;
    switch (cmd_.actionInfo.direction) {
        case RelaxedScrollDirection::UP:
        case RelaxedScrollDirection::LEFT:
        case RelaxedScrollDirection::BACKWARD:
            config.direction = SmartGestureDirection::BACKWARD;
            break;
        default:
            config.direction = SmartGestureDirection::FORWARD;
            break;
    }

    if (!scroll->IsScrollAble(config.direction)) {
        WorkflowDumper::GetInstance().AddLog("Node is not scrollable");
        return false;
    }

    config.distance = static_cast<double>(cmd_.actionInfo.distance);
    scroll->PerformScroll(config);
    return true;
}

RefPtr<Pattern> ScrollTouchExecutor::FindScrollPattern(float x, float y)
{
    auto context = context_.Upgrade();
    if (!context) {
        return nullptr;
    }
    auto result = FindFrameNode(x, y, ScrollRecognizerPred(cmd_.actionInfo.direction));
    if (!result.GetNode()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "No FrameNode found at coordinates.");
        return nullptr;
    }
    return result.GetNode()->GetPattern();
}

} // namespace OHOS::Ace::NG