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

#include "core/components_ng/relaxed_interaction/parsers/tap_command_parser.h"

#include <memory>
#include <vector>

#include "base/json/json_util.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/executors/smart_gesture_executor.h"
#include "core/components_ng/relaxed_interaction/executors/strict_click_executor.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

TapCommandParser::TapCommandParser(WeakPtr<PipelineContext> context) : BaseCommandParser(context) {}

std::vector<std::unique_ptr<BaseExecutor>> TapCommandParser::Parse(const std::unique_ptr<JsonValue>& json)
{
    (void)json;
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<SmartGestureExecutor>(context_, SmartGestureTrigger::TAP));

    // Add StrictClickExecutor with screen center coordinates
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

    PointF centerPoint(centerX, centerY);
    executors.emplace_back(std::make_unique<StrictClickExecutor>(context_, centerPoint));
    return executors;
}

} // namespace OHOS::Ace::NG
