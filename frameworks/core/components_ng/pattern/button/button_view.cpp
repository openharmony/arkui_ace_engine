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
#include "core/components_ng/pattern/button/button_view.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_paint_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
void ButtonView::CreateLabel(const std::string& label)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, [label]() { return AceType::MakeRefPtr<ButtonPattern>(label); });
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(label);
        frameNode->AddChild(textNode);
    } else {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(label);
    }
    stack->Push(frameNode);
}

void ButtonView::CreateChild()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    stack->Push(frameNode);
}

void ButtonView::Type(ButtonType buttonType)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, buttonType);
}

void ButtonView::StateEffect(bool stateEffect)
{
    ACE_UPDATE_PAINT_PROPERTY(ButtonPaintProperty, StateEffect, stateEffect);
}

void ButtonView::FontSize(const Dimension& fontSize)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (!frameNode->GetChildren().empty()) {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateFontSize(fontSize);
    }
}

void ButtonView::FontWeight(Ace::FontWeight fontWeight)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (!frameNode->GetChildren().empty()) {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateFontWeight(fontWeight);
    }
}

void ButtonView::ItalicFontStyle(Ace::FontStyle fontStyle)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (!frameNode->GetChildren().empty()) {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateItalicFontStyle(fontStyle);
    }
}

void ButtonView::FontFamily(const std::vector<std::string>& fontFamilies)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (!frameNode->GetChildren().empty()) {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateFontFamily(fontFamilies);
    }
}

void ButtonView::TextColor(const Color& textColor)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (!frameNode->GetChildren().empty()) {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateTextColor(textColor);
    }
}
} // namespace OHOS::Ace::NG