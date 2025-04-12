/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<TextClockController> TextClockModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TEXTCLOCK_ETS_TAG, nodeId);
    auto textClockNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTCLOCK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextClockPattern>(); });

    auto pattern = textClockNode->GetPattern<TextClockPattern>();
    if (textClockNode->GetChildren().empty()) {
        auto textId = pattern->GetTextId();
        auto textNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, textId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->MarkModifyDone();
        textNode->MountToParent(textClockNode);
    }
    stack->Push(textClockNode);
    return pattern ? pattern->GetTextClockController() : nullptr;
}

void TextClockModelNG::SetFormat(const std::string& format)
{
    if (format.empty()) {
        ACE_RESET_LAYOUT_PROPERTY(TextClockLayoutProperty, Format);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, Format, format);
    }
}

void TextClockModelNG::SetTextShadow(const std::vector<Shadow>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, TextShadow, value);
}

void TextClockModelNG::SetFontFeature(const FONT_FEATURES_LIST& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontFeature, value);
}

void TextClockModelNG::SetHoursWest(float hoursWest)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, HoursWest, hoursWest);
}

void TextClockModelNG::SetOnDateChange(std::function<void(const std::string)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDateChange(std::move(onChange));
}

void TextClockModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontSize, value);
}

void TextClockModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, TextColor, value);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void TextClockModelNG::ResetTextColor()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(TextClockLayoutProperty, TextColor, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColor);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorFlag);
    auto textClockNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(textClockNode);
    auto textNode = AceType::DynamicCast<FrameNode>(textClockNode->GetLastChild());
    CHECK_NULL_VOID(textNode);
    TextModelNG::ResetTextColor(Referenced::RawPtr<FrameNode>(textNode));
}

void TextClockModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, ItalicFontStyle, value);
}

void TextClockModelNG::SetFontWeight(FontWeight value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontWeight, value);
}

void TextClockModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontFamily, value);
}

void TextClockModelNG::InitFontDefault(const TextStyle& textStyle)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textClockLayoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_VOID(textClockLayoutProperty);
    if (!textClockLayoutProperty->GetFontSize().has_value()) {
        SetFontSize(textStyle.GetFontSize());
    }
    if (!textClockLayoutProperty->GetFontWeight().has_value()) {
        SetFontWeight(textStyle.GetFontWeight());
    }
    if (!textClockLayoutProperty->GetFontFamily().has_value()) {
        SetFontFamily(textStyle.GetFontFamilies());
    }
    if (!textClockLayoutProperty->GetItalicFontStyle().has_value()) {
        SetItalicFontStyle(textStyle.GetFontStyle());
    }
}

void TextClockModelNG::SetDateTimeOptions(const ZeroPrefixType& hourType)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, PrefixHour, hourType);
}

RefPtr<FrameNode> TextClockModelNG::CreateFrameNode(int32_t nodeId)
{
    auto textClockNode =
        FrameNode::CreateFrameNode(V2::TEXTCLOCK_ETS_TAG, nodeId, AceType::MakeRefPtr<TextClockPattern>());
    CHECK_NULL_RETURN(textClockNode, nullptr);
    auto pattern = textClockNode->GetPattern<TextClockPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (textClockNode->GetChildren().empty()) {
        auto textId = pattern->GetTextId();
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->MarkModifyDone();
        textNode->MountToParent(textClockNode);
    }
    auto pipeline = textClockNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto textTheme = pipeline->GetTheme<TextClockTheme>(textClockNode->GetThemeScopeId());
    if (textTheme) {
        InitFontDefault(AceType::RawPtr(textClockNode), textTheme->GetTextStyleClock());
    }
    return textClockNode;
}

RefPtr<TextClockController> TextClockModelNG::InitTextController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPatternPtr<TextClockPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTextClockController();
}

void TextClockModelNG::SetFormat(FrameNode* frameNode, const std::string& format)
{
    if (format.empty()) {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, Format, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, Format, format, frameNode);
    }
}

void TextClockModelNG::SetHoursWest(FrameNode* frameNode, float hoursWest)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, HoursWest, hoursWest, frameNode);
}

void TextClockModelNG::SetTextShadow(FrameNode* frameNode, const std::vector<Shadow>& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, TextShadow, value, frameNode);
}

void TextClockModelNG::SetFontFeature(FrameNode* frameNode, const FONT_FEATURES_LIST& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontFeature, value, frameNode);
}

void TextClockModelNG::SetFontColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, TextColor, value, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void TextClockModelNG::ResetFontColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        TextClockLayoutProperty, TextColor, PROPERTY_UPDATE_MEASURE_SELF, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorFlag, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    CHECK_NULL_VOID(textNode);
    TextModelNG::ResetTextColor(Referenced::RawPtr<FrameNode>(textNode));
}

void TextClockModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontSize, value, frameNode);
}

void TextClockModelNG::SetFontStyle(FrameNode* frameNode, Ace::FontStyle value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, ItalicFontStyle, value, frameNode);
}

void TextClockModelNG::SetFontWeight(FrameNode* frameNode, FontWeight value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontWeight, value, frameNode);
}

void TextClockModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontFamily, value, frameNode);
}

void TextClockModelNG::SetBuilderFunc(FrameNode* frameNode, TextClockMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void TextClockModelNG::InitFontDefault(FrameNode* frameNode, const TextStyle& textStyle)
{
    CHECK_NULL_VOID(frameNode);
    auto textClockLayoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_VOID(textClockLayoutProperty);
    if (!textClockLayoutProperty->GetFontSize().has_value()) {
        SetFontSize(frameNode, textStyle.GetFontSize());
    }
    if (!textClockLayoutProperty->GetFontWeight().has_value()) {
        SetFontWeight(frameNode, textStyle.GetFontWeight());
    }
    if (!textClockLayoutProperty->GetTextColor().has_value()) {
        SetFontColor(frameNode, textStyle.GetTextColor());
    }
    if (!textClockLayoutProperty->GetFontFamily().has_value()) {
        SetFontFamily(frameNode, textStyle.GetFontFamilies());
    }
    if (!textClockLayoutProperty->GetItalicFontStyle().has_value()) {
        SetFontStyle(frameNode, textStyle.GetFontStyle());
    }
}

void TextClockModelNG::SetDateTimeOptions(FrameNode* frameNode, const ZeroPrefixType& hourType)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextClockLayoutProperty, PrefixHour, hourType, frameNode);
}

void TextClockModelNG::SetJSTextClockController(FrameNode* frameNode, const RefPtr<Referenced>& controller)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetJSTextClockController(controller);
}

RefPtr<Referenced> TextClockModelNG::GetJSTextClockController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetJSTextClockController();
}

void TextClockModelNG::SetOnDateChange(FrameNode* frameNode, std::function<void(const std::string)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDateChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG
