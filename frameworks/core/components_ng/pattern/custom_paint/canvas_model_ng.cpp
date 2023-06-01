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

#include "core/components_ng/pattern/custom_paint/canvas_model_ng.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"

namespace OHOS::Ace::NG {
RefPtr<AceType> CanvasModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CustomPaintPattern>(); });
    stack->Push(frameNode);
    return frameNode->GetPattern<CustomPaintPattern>();
}

RefPtr<AceType> CanvasModelNG::GetTaskPool(RefPtr<AceType>& pattern)
{
    return pattern;
}

void CanvasModelNG::SetOnReady(std::function<void(uint32_t)>&& onReady)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CustomPaintEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto func = onReady;
    auto onReadyEvent = [func]() { func(0); };
    eventHub->SetOnReady(std::move(onReadyEvent));
}
} // namespace OHOS::Ace::NG
