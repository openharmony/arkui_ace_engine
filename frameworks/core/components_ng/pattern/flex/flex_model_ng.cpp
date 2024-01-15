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

#include "core/components_ng/pattern/flex/flex_model_ng.h"

#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void FlexModelNG::CreateFlexRow()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::FLEX_ETS_TAG, nodeId);
    auto childFrameNode = FrameNode::GetFrameNode(V2::FLEX_ETS_TAG, nodeId);
    if (!childFrameNode) {
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::FLEX_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(); });
        stack->Push(frameNode);

        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, FlexDirection::ROW);
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, FlexAlign::FLEX_START);
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, FlexAlign::FLEX_START);
        return;
    }
    stack->Push(childFrameNode);
    auto pattern = childFrameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        return;
    }
    // wrap to flex
    pattern->SetIsWrap(false);
    auto layoutProperty = pattern->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetWrapLayoutAttribute();
}

void FlexModelNG::CreateWrap()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::FLEX_ETS_TAG, nodeId);
    auto childFrameNode = FrameNode::GetFrameNode(V2::FLEX_ETS_TAG, nodeId);
    if (!childFrameNode) {
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::FLEX_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
        stack->Push(frameNode);
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, WrapDirection, WrapDirection::HORIZONTAL);
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, WrapAlignment::START);
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, WrapAlignment::START);
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, WrapAlignment::START);
        return;
    }
    stack->Push(childFrameNode);
    auto pattern = childFrameNode->GetPattern<FlexLayoutPattern>();
    if (pattern->GetIsWrap()) {
        return;
    }
    // flex to wrap
    pattern->SetIsWrap(true);
    auto layoutProperty = childFrameNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetFlexLayoutAttribute();
}

RefPtr<FrameNode> FlexModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::FLEX_ETS_TAG, nodeId, AceType::MakeRefPtr<FlexLayoutPattern>());
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    return frameNode;
}

void FlexModelNG::SetDirection(FlexDirection direction)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, direction);
}

void FlexModelNG::SetWrapDirection(WrapDirection direction)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, WrapDirection, direction);
}

void FlexModelNG::SetMainAxisAlign(FlexAlign align)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, align);
}

void FlexModelNG::SetWrapMainAlignment(WrapAlignment value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, value);
}

void FlexModelNG::SetCrossAxisAlign(FlexAlign align)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, align);
}

void FlexModelNG::SetWrapCrossAlignment(WrapAlignment value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, value);
}

void FlexModelNG::SetWrapAlignment(WrapAlignment value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, value);
}

void FlexModelNG::SetAlignItems(int32_t value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        SetCrossAxisAlign(static_cast<FlexAlign>(value));
        return;
    }
    SetWrapCrossAlignment(static_cast<WrapAlignment>(value));
}

void FlexModelNG::SetJustifyContent(int32_t value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        SetMainAxisAlign(static_cast<FlexAlign>(value));
        return;
    }
    SetWrapMainAlignment(static_cast<WrapAlignment>(value));
}

void FlexModelNG::SetAlignContent(int32_t value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        return;
    }
    SetWrapAlignment(static_cast<WrapAlignment>(value));
}

} // namespace OHOS::Ace::NG
