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

#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_position_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

namespace OHOS::Ace::NG {
void WaterFlowModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WATERFLOW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WaterFlowPattern>(); });
    stack->Push(frameNode);
}
void WaterFlowModelNG::SetFooter(std::function<void()>&& footer) {}
RefPtr<ScrollControllerBase> WaterFlowModelNG::CreateScrollController()
{
    return AceType::MakeRefPtr<WaterFlowPositionController>();
}
RefPtr<ScrollProxy> WaterFlowModelNG::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<NG::ScrollBarProxy>();
}
void WaterFlowModelNG::SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy) {}
void WaterFlowModelNG::SetColumnsTemplate(const std::string& value) {}
void WaterFlowModelNG::SetRowsTemplate(const std::string& value) {}
void WaterFlowModelNG::SetItemMinWidth(const Dimension& minWidth) {}
void WaterFlowModelNG::SetItemMinHeight(const Dimension& minHeight) {}
void WaterFlowModelNG::SetItemMaxWidth(const Dimension& maxWidth) {}
void WaterFlowModelNG::SetItemMaxHeight(const Dimension& maxHeight) {}
void WaterFlowModelNG::SetColumnsGap(const Dimension& value) {}
void WaterFlowModelNG::SetRowsGap(const Dimension& value) {}
void WaterFlowModelNG::SetLayoutDirection(FlexDirection value) {}
void WaterFlowModelNG::SetOnReachStart(OnReachEvent&& onReachStart) {}
void WaterFlowModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd) {}
} // namespace OHOS::Ace::NG