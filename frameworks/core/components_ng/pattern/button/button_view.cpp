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
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_accessibility_property.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
void ButtonView::CreateWithLabel(const std::string& label)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    if (buttonNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textNode);
        textNode->SetInternal();
        SetTextDefaultStyle(textNode, label);
        buttonNode->AddChild(textNode);
    }
    auto buttonAccessibilityProperty = buttonNode->GetAccessibilityProperty<ButtonAccessibilityProperty>();
    CHECK_NULL_VOID(buttonAccessibilityProperty);
    buttonAccessibilityProperty->SetText(label);
    stack->Push(buttonNode);
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Label, label);
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto padding = buttonTheme->GetPadding();
    PaddingProperty defaultPadding({ CalcLength(padding.Left()), CalcLength(padding.Right()), CalcLength(padding.Top()),
        CalcLength(padding.Bottom()) });
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Padding, defaultPadding);
}

void ButtonView::Create(const std::string& tagName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(tagName, nodeId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    stack->Push(frameNode);
}

void ButtonView::SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, const std::string& label)
{
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    auto textStyle = buttonTheme->GetTextStyle();
    textLayoutProperty->UpdateContent(label);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateMaxLines(buttonTheme->GetTextMaxLines());
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
}

void ButtonView::SetType(ButtonType buttonType)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, Type, buttonType);
}

void ButtonView::SetStateEffect(bool stateEffect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(stateEffect);
}

void ButtonView::SetFontSize(const Dimension& fontSize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, fontSize);
}

void ButtonView::SetFontWeight(Ace::FontWeight fontWeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontWeight, fontWeight);
}

void ButtonView::SetFontStyle(Ace::FontStyle fontStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontStyle, fontStyle);
}

void ButtonView::SetFontFamily(const std::vector<std::string>& fontFamilies)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontFamily, fontFamilies);
}

void ButtonView::SetFontColor(const Color& textColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontColor, textColor);
}

void ButtonView::SetBorderRadius(const Dimension& radius)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ButtonLayoutProperty, BorderRadius, radius);
}

} // namespace OHOS::Ace::NG
