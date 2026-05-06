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

#include "core/components_ng/relaxed_interaction/parsers/slide_command_parser.h"

#include <memory>
#include <vector>

#include "base/json/json_util.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/executors/scroll_touch_executor.h"
#include "core/components_ng/relaxed_interaction/executors/smart_gesture_executor.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

SlideCommandParser::SlideCommandParser(WeakPtr<PipelineContext> context) : BaseCommandParser(context) {}

std::vector<std::unique_ptr<BaseExecutor>> SlideCommandParser::Parse(const std::unique_ptr<JsonValue>& json)
{
    (void)json;
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<SmartGestureExecutor>(context_, SmartGestureTrigger::SLIDE_FORWARD));

    // Add Scroll touch executor with screen center coordinates
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Pipeline context is null");
        return executors;
    }
    auto rootNode = context->GetRootElement();
    if (!rootNode) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Root node is null");
        return executors;
    }
    auto rootRect = context->GetRootRect();
    if (!rootRect.IsValid() || rootRect.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Root rect is null");
        return executors;
    }

    const float centerX = rootRect.Left() + rootRect.Width() / 2.0f;
    const float centerY = rootRect.Top() + rootRect.Height() / 2.0f;

    Command scrollCommand;
    scrollCommand.actionInfo.direction = RelaxedScrollDirection::FORWARD;
    scrollCommand.actionInfo.coordinates.x1 = centerX;
    scrollCommand.actionInfo.coordinates.y1 = centerY;
    scrollCommand.actionInfo.distance = rootRect.Height() / 3.0f;
    executors.emplace_back(std::make_unique<ScrollTouchExecutor>(context_, scrollCommand));
    return executors;
}

} // namespace OHOS::Ace::NG