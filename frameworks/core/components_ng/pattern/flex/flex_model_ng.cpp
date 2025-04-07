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

#include "core/components_ng/pattern/flex/flex_layout_pattern.h"

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

void FlexModelNG::SetMainAxisAlign(FrameNode* frameNode, std::optional<FlexAlign>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, frameNode);
    }
}

void FlexModelNG::SetWrapMainAlignment(WrapAlignment value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, value);
}

void FlexModelNG::SetWrapMainAlignment(FrameNode* frameNode, std::optional<WrapAlignment>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, frameNode);
    }
}

void FlexModelNG::SetCrossAxisAlign(FlexAlign align)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, align);
}

void FlexModelNG::SetWrapCrossAlignment(FrameNode* frameNode, std::optional<WrapAlignment>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, frameNode);
    }
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

void FlexModelNG::SetFlexRow(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, FlexDirection::ROW, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, FlexAlign::FLEX_START, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, FlexAlign::FLEX_START, frameNode);

    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    pattern->SetIsWrap(false);
}

void FlexModelNG::SetFlexWrap(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, WrapDirection, WrapDirection::HORIZONTAL, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, WrapAlignment::START, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, WrapAlignment::START, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, WrapAlignment::START, frameNode);

    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    pattern->SetIsWrap(true);
}

void FlexModelNG::SetFlexDirection(FrameNode* frameNode, FlexDirection value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, value, frameNode);
}

void FlexModelNG::SetFlexDirection(FrameNode* frameNode, std::optional<FlexDirection>& layoutDirection)
{
    CHECK_NULL_VOID(frameNode);
    if (layoutDirection) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, layoutDirection.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, FlexDirection, frameNode);
    }
}

void FlexModelNG::SetFlexWrapDirection(FrameNode* frameNode, WrapDirection value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, WrapDirection, value, frameNode);
}

void FlexModelNG::SetFlexJustifyContent(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAxisAlign, static_cast<FlexAlign>(value), frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, MainAlignment, static_cast<WrapAlignment>(value), frameNode);
}

void FlexModelNG::SetCrossAxisAlign(FrameNode* frameNode, std::optional<FlexAlign>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, frameNode);
    }
}

void FlexModelNG::SetFlexAlignItems(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAxisAlign, static_cast<FlexAlign>(value), frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossAlignment, static_cast<WrapAlignment>(value), frameNode);
}

void FlexModelNG::SetFlexAlignContent(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, static_cast<WrapAlignment>(value), frameNode);
}

void FlexModelNG::SetFlexAlignContent(FrameNode* frameNode, std::optional<WrapAlignment>& align)
{
    CHECK_NULL_VOID(frameNode);
    if (align.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, Alignment, frameNode);
    }
}

void FlexModelNG::SetWidthLayoutPolicy(uint8_t widthLayoutPolicy)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, WidthLayoutPolicy, widthLayoutPolicy);
}

void FlexModelNG::SetWidthLayoutPolicy(FrameNode* frameNode, uint8_t widthLayoutPolicy)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, WidthLayoutPolicy, widthLayoutPolicy, frameNode);
}

void FlexModelNG::SetHeightLayoutPolicy(uint8_t heightLayoutPolicy)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, HeightLayoutPolicy, heightLayoutPolicy);
}

void FlexModelNG::SetHeightLayoutPolicy(FrameNode* frameNode, uint8_t heightLayoutPolicy)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, HeightLayoutPolicy, heightLayoutPolicy, frameNode);
}

int FlexModelNG::GetFlexWrap(FrameNode* frameNode)
{
    int value = 0;
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        value = static_cast<int>(FlexWrap::NO_WRAP);
    } else {
        WrapDirection direction = WrapDirection::HORIZONTAL;
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
            FlexLayoutProperty, WrapDirection, direction, frameNode, direction);
        int intDirection = static_cast<int>(direction);
        if (intDirection == 0 || intDirection == 1) {
            value = static_cast<int>(FlexWrap::WRAP);
        } else {
            value = static_cast<int>(FlexWrap::WRAP_REVERSE);
        }
    }
    return value;
}

int FlexModelNG::GetFlexDirection(FrameNode* frameNode)
{
    FlexDirection value = FlexDirection::ROW;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(FlexLayoutProperty, FlexDirection, value, frameNode, value);
    return static_cast<int>(value);
}

int FlexModelNG::GetFlexJustifyContent(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        FlexAlign value = FlexAlign::AUTO;
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(FlexLayoutProperty, MainAxisAlign, value, frameNode, value);
        return static_cast<int>(value);
    }
    WrapAlignment value = WrapAlignment::START;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(FlexLayoutProperty, MainAlignment, value, frameNode, value);
    return static_cast<int>(value);
}

int FlexModelNG::GetFlexAlignItems(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        FlexAlign value = FlexAlign::AUTO;
        ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(FlexLayoutProperty, CrossAxisAlign, value, frameNode, value);
        return static_cast<int>(value);
    }
    WrapAlignment value = WrapAlignment::START;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(FlexLayoutProperty, CrossAlignment, value, frameNode, value);
    return static_cast<int>(value);
}

int FlexModelNG::GetFlexAlignContent(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    if (!pattern->GetIsWrap()) {
        return 0;
    }
    WrapAlignment value = WrapAlignment::START;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(FlexLayoutProperty, Alignment, value, frameNode, value);
    return static_cast<int>(value);
}

void FlexModelNG::SetMainSpace(const std::optional<Dimension>& space)
{
    CHECK_NULL_VOID(space);
    if (GreatOrEqual(space->Value(), 0.0)) {
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, Space, space.value());
    }
}

void FlexModelNG::SetCrossSpace(const std::optional<Dimension>& space)
{
    CHECK_NULL_VOID(space);
    if (GreatOrEqual(space->Value(), 0.0)) {
        ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossSpace, space.value());
    }
}

void FlexModelNG::SetMainSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(space);
    if (GreatOrEqual(space->Value(), 0.0)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, Space, space.value(), frameNode);
    }
}

void FlexModelNG::SetCrossSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(space);
    if (GreatOrEqual(space->Value(), 0.0)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, CrossSpace, space.value(), frameNode);
    }
}
} // namespace OHOS::Ace::NG
