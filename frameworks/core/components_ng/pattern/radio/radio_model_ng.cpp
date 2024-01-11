/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/radio/radio_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void RadioModelNG::Create(const std::optional<std::string>& value, const std::optional<std::string>& group)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::RADIO_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RADIO_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (value.has_value()) {
        eventHub->SetValue(value.value());
    }
    if (group.has_value()) {
        eventHub->SetGroup(group.value());
    }
}

void RadioModelNG::SetChecked(bool isChecked)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isChecked);

    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioCheck, isChecked);
}

void RadioModelNG::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void RadioModelNG::SetWidth(const Dimension& width)
{
    NG::ViewAbstract::SetWidth(NG::CalcLength(width));
}

void RadioModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
}

void RadioModelNG::SetPadding(const NG::PaddingPropertyF& /*args*/, const NG::PaddingProperty& newArgs)
{
    NG::ViewAbstract::SetPadding(newArgs);
}

void RadioModelNG::SetCheckedBackgroundColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColor, color);
}

void RadioModelNG::SetUncheckedBorderColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColor, color);
}

void RadioModelNG::SetIndicatorColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColor, color);
}

void RadioModelNG::SetOnChangeEvent(ChangeEvent&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

void RadioModelNG::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(responseRegion);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

void RadioModelNG::SetHoverEffect(HoverEffectType hoverEffect)
{
    NG::ViewAbstract::SetHoverEffect(hoverEffect);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShowHoverEffect(hoverEffect != HoverEffectType::NONE);
}

void RadioModelNG::SetChecked(FrameNode* frameNode, bool isChecked)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheck, isChecked, frameNode);
}

void RadioModelNG::SetCheckedBackgroundColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColor, color, frameNode);
}

void RadioModelNG::SetUncheckedBorderColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColor, color, frameNode);
}

void RadioModelNG::SetIndicatorColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColor, color, frameNode);
}

void RadioModelNG::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    NG::ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
}

void RadioModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
}

void RadioModelNG::SetHoverEffect(FrameNode* frameNode, HoverEffectType hoverEffect)
{
    NG::ViewAbstract::SetHoverEffect(frameNode, hoverEffect);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShowHoverEffect(hoverEffect != HoverEffectType::NONE);
}

void RadioModelNG::SetPadding(FrameNode* frameNode, const NG::PaddingProperty& newArgs)
{
    NG::ViewAbstract::SetPadding(frameNode, newArgs);
}

void RadioModelNG::SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(frameNode, responseRegion);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}
} // namespace OHOS::Ace::NG
