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

#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/text/text_emoji_processor.h"

#define ACE_UPDATE_SPAN_PROPERTY(name, value)                                                                    \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode()); \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
    } while (false)
#define ACE_RESET_SPAN_PROPERTY(name)                                                                            \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode()); \
        CHECK_NULL_VOID(spanNode);                                                                               \
        if (spanNode->Has##name()) {                                                                             \
            spanNode->MarkTextDirty();                                                                           \
        }                                                                                                        \
        spanNode->Reset##name();                                                                                 \
    } while (false)
#define ACE_UPDATE_NODE_SPAN_PROPERTY(name, value, frameNode)                                                    \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
    } while (false)
#define ACE_RESET_NODE_SPAN_PROPERTY(name, frameNode)                                                            \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        if (spanNode->Has##name()) {                                                                             \
            spanNode->MarkTextDirty();                                                                           \
        }                                                                                                        \
        spanNode->Reset##name();                                                                                 \
    } while (false)
namespace OHOS::Ace::NG {

void SpanModelNG::Create(const std::u16string& content)
{
    RefPtr<ResourceObject> resObj;
    Create(content, resObj);
}

void SpanModelNG::Create(const std::u16string& content, RefPtr<ResourceObject>& resObj)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    stack->Push(spanNode);
    auto contentModified = content;
    UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(contentModified.data()), contentModified.length(), 0);
    ACE_UPDATE_SPAN_PROPERTY(Content, contentModified);
    if (resObj) {
        auto&& updateFunc = [weakptr = WeakPtr<NG::SpanNode>(spanNode)](const RefPtr<ResourceObject>& resObj) {
            auto spanNode = weakptr.Upgrade();
            CHECK_NULL_VOID(spanNode);
            spanNode->UpdateSpanResource<std::u16string>("value", resObj);
        };
        spanNode->AddResObj("value", resObj, std::move(updateFunc));
    }
}

RefPtr<SpanNode> SpanModelNG::CreateSpanNode(int32_t nodeId, const std::u16string& content)
{
    auto spanNode = SpanNode::CreateSpanNode(nodeId);
    CHECK_NULL_RETURN(spanNode, nullptr);
    spanNode->UpdateContent(content);
    return spanNode;
}

void SpanModelNG::SetFont(const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(value.fontSize.value());
    } else {
        ResetFontSize();
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(value.fontWeight.value());
    } else {
        ResetFontWeight();
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(value.fontFamilies);
    } else {
        ResetFontFamily();
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(value.fontStyle.value());
    } else {
        ResetItalicFontStyle();
    }
}

void SpanModelNG::ResetFont()
{
    ResetFontSize();
    ResetFontWeight();
    ResetFontFamily();
    ResetItalicFontStyle();
}

void SpanModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontSize, value);
}

void SpanModelNG::ResetFontSize()
{
    ACE_RESET_SPAN_PROPERTY(FontSize);
}

void SpanModelNG::SetTextColor(const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateSpanTextColor(value);
}

void SpanModelNG::ResetTextColor()
{
    ACE_RESET_SPAN_PROPERTY(TextColor);
}

void SpanModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(ItalicFontStyle, value);
}

void SpanModelNG::ResetItalicFontStyle()
{
    ACE_RESET_SPAN_PROPERTY(ItalicFontStyle);
}

void SpanModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontWeight, value);
}

void SpanModelNG::ResetFontWeight()
{
    ACE_RESET_SPAN_PROPERTY(FontWeight);
}

void SpanModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontFamily, value);
}

void SpanModelNG::ResetFontFamily()
{
    ACE_RESET_SPAN_PROPERTY(FontFamily);
}

void SpanModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecoration, {value});
}

void SpanModelNG::SetTextDecorationStyle(Ace::TextDecorationStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationStyle, value);
}

void SpanModelNG::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationColor, value);
}

void SpanModelNG::SetLineThicknessScale(float value)
{
    ACE_UPDATE_SPAN_PROPERTY(LineThicknessScale, value);
}

void SpanModelNG::SetTextCase(Ace::TextCase value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextCase, value);
}

void SpanModelNG::SetTextShadow(const std::vector<Shadow>& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextShadow, value);
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto index = 0;
    for (auto& shadow : value) {
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto key = "shadow_" + std::to_string(index);
        auto&& updateFunc = [shadow, weak = WeakPtr<SpanNode>(spanNode), index](const RefPtr<ResourceObject>& resObj) {
            auto spanNode = weak.Upgrade();
            CHECK_NULL_VOID(spanNode);
            Shadow& shadowValue = const_cast<Shadow&>(shadow);
            shadowValue.ReloadResources();
            auto origArr = spanNode->GetTextShadow();
            if (origArr.has_value() && GreatNotEqual(origArr.value().size(), index)) {
                auto origArrVal = origArr.value();
                origArrVal[index] = shadowValue;
                spanNode->UpdateTextShadow(origArrVal);
            }
        };
        spanNode->AddResObj(key, resObj, std::move(updateFunc));
        index ++;
    }
}

void SpanModelNG::SetTextShadow(UINode* uiNode, const std::vector<Shadow>& value)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(TextShadow, value, uiNode);
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto index = 0;
    for (auto& shadow : value) {
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto key = "shadow_" + std::to_string(index);
        auto&& updateFunc = [shadow, weak = AceType::WeakClaim(spanNode), index]
            (const RefPtr<ResourceObject>& resObj) {
            auto spanNode = weak.Upgrade();
            CHECK_NULL_VOID(spanNode);
            Shadow& shadowValue = const_cast<Shadow&>(shadow);
            shadowValue.ReloadResources();
            auto origArr = spanNode->GetTextShadow();
            if (origArr.has_value() && GreatNotEqual(origArr.value().size(), index)) {
                auto origArrVal = origArr.value();
                origArrVal[index] = shadowValue;
                spanNode->UpdateTextShadow(origArrVal);
            }
        };
        spanNode->AddResObj(key, resObj, std::move(updateFunc));
        index ++;
    }
}

void SpanModelNG::ResetTextShadow(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextShadow, uiNode);
}

void SpanModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LetterSpacing, value);
}

void SpanModelNG::SetBaselineOffset(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(BaselineOffset, value);
}

void SpanModelNG::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LineHeight, value);
}

void SpanModelNG::SetOnClick(std::function<void(BaseEventInfo* info)>&& click)
{
    auto clickFunc = [func = std::move(click)](GestureEvent& info) { func(&info); };
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, std::move(clickFunc));
}

void SpanModelNG::SetOnClick(UINode* uiNode, GestureEventFunc&& click)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(OnClickEvent, std::move(click), uiNode);
}

void SpanModelNG::ClearOnClick()
{
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, nullptr);
}

void SpanModelNG::ClearOnClick(UINode* uiNode)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(OnClickEvent, nullptr, uiNode);
}

void SpanModelNG::SetOnLongPress(UINode* uiNode, GestureEventFunc&& onLongPress)
{
    if (uiNode->GetTag() == V2::SPAN_ETS_TAG) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(OnLongPressEvent, std::move(onLongPress), uiNode);
    } else {
        auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        CHECK_NULL_VOID(frameNode);
        auto eventHub = frameNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        auto focusHub = eventHub->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetOnLongPressCallback(std::move(onLongPress));
    }
}

void SpanModelNG::ClearOnLongPress(UINode* uiNode)
{
    if (uiNode->GetTag() == V2::SPAN_ETS_TAG) {
        ACE_UPDATE_NODE_SPAN_PROPERTY(OnLongPressEvent, nullptr, uiNode);
    } else {
        auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        CHECK_NULL_VOID (frameNode);
        auto eventHub = frameNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        auto focusHub = eventHub->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetOnLongPressCallback(std::move(nullptr));
    }
}

void SpanModelNG::SetAccessibilityText(const std::string& text)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityText(text);
}

void SpanModelNG::SetAccessibilityDescription(const std::string& description)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityDescription(description);
}

void SpanModelNG::SetAccessibilityImportance(const std::string& importance)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityLevel(importance);
}

void SpanModelNG::InitSpan(UINode* uiNode, const std::u16string& content)
{
    ACE_UPDATE_NODE_SPAN_PROPERTY(Content, content, uiNode);
}

void SpanModelNG::SetFontWeight(UINode* uiNode, FontWeight value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontWeight(value);
}

void SpanModelNG::ResetFontWeight(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(FontWeight, uiNode);
}

void SpanModelNG::SetTextCase(UINode* uiNode, TextCase value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextCase(value);
}

void SpanModelNG::ResetTextCase(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextCase, uiNode);
}

void SpanModelNG::SetItalicFontStyle(UINode* uiNode, Ace::FontStyle value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateItalicFontStyle(value);
}

void SpanModelNG::ResetItalicFontStyle(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(ItalicFontStyle, uiNode);
}

void SpanModelNG::SetLineHeight(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateLineHeight(value);
}

void SpanModelNG::ResetLineHeight(UINode* uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(LineHeight, uiNode);
}

void SpanModelNG::SetFontSize(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontSize(value);
}

void SpanModelNG::ResetFontSize(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(FontSize, uiNode);
}

void SpanModelNG::SetFontFamily(UINode* uiNode, const std::vector<std::string>& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateFontFamily(value);
}

void SpanModelNG::ResetFontFamily(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(FontFamily, uiNode);
}

void SpanModelNG::SetTextDecoration(UINode* uiNode, TextDecoration value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecoration({value});
}

void SpanModelNG::ResetTextDecoration(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextDecoration, uiNode);
}

void SpanModelNG::SetTextDecorationStyle(UINode* uiNode, TextDecorationStyle value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecorationStyle(value);
}

void SpanModelNG::ResetTextDecorationStyle(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextDecorationStyle, uiNode);
}

void SpanModelNG::SetTextDecorationColor(UINode* uiNode, const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextDecorationColor(value);
}

void SpanModelNG::ResetTextDecorationColor(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextDecorationColor, uiNode);
}

void SpanModelNG::SetLineThicknessScale(UINode *uiNode, float value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateLineThicknessScale(value);
}

void SpanModelNG::ResetLineThicknessScale(UINode* uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(LineThicknessScale, uiNode);
}

void SpanModelNG::SetTextColor(UINode* uiNode, const Color& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateSpanTextColor(value);
}

void SpanModelNG::ResetTextColor(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(TextColor, uiNode);
}

void SpanModelNG::SetLetterSpacing(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateLetterSpacing(value);
}

void SpanModelNG::ResetLetterSpacing(UINode *uiNode)
{
    ACE_RESET_NODE_SPAN_PROPERTY(LetterSpacing, uiNode);
}

void SpanModelNG::SetBaselineOffset(UINode* uiNode, const Dimension& value)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateBaselineOffset(value);
}

void SpanModelNG::SetFont(UINode* uiNode, const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(uiNode, value.fontSize.value());
    } else {
        ResetFontSize(uiNode);
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(uiNode, value.fontWeight.value());
    } else {
        ResetFontWeight(uiNode);
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(uiNode, value.fontFamilies);
    } else {
        ResetFontFamily(uiNode);
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(uiNode, value.fontStyle.value());
    } else {
        ResetItalicFontStyle(uiNode);
    }
}

void SpanModelNG::ResetFont(UINode *uiNode)
{
    ResetFontSize(uiNode);
    ResetFontWeight(uiNode);
    ResetFontFamily(uiNode);
    ResetItalicFontStyle(uiNode);
}

void SpanModelNG::CreateContainSpan()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = ContainerSpanNode::GetOrCreateSpanNode(nodeId);
    stack->Push(spanNode);
}

void SpanModelNG::SetTextBackgroundStyle(const TextBackgroundStyle& style)
{
    auto baseSpan = AceType::DynamicCast<BaseSpan>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(baseSpan);
    baseSpan->SetTextBackgroundStyle(style);
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto key = "textbackgroundStyle";
    auto&& updateFunc = [style, weak = WeakPtr<BaseSpan>(baseSpan)](const RefPtr<ResourceObject>& resObj) {
        auto baseSpan = weak.Upgrade();
        CHECK_NULL_VOID(baseSpan);
        TextBackgroundStyle& styleValue = const_cast<TextBackgroundStyle&>(style);
        styleValue.ReloadResources();
        baseSpan->SetTextBackgroundStyle(styleValue);
    };
    baseSpan->AddResObj(key, resObj, std::move(updateFunc));
}

void SpanModelNG::SetTextBackgroundStyle(UINode* uiNode, const TextBackgroundStyle& style)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->SetTextBackgroundStyle(style);
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto key = "textbackgroundStyle";
    auto&& updateFunc = [style, weak = AceType::WeakClaim(spanNode)](const RefPtr<ResourceObject>& resObj) {
        auto spanNode = weak.Upgrade();
        CHECK_NULL_VOID(spanNode);
        TextBackgroundStyle& styleValue = const_cast<TextBackgroundStyle&>(style);
        styleValue.ReloadResources();
        spanNode->SetTextBackgroundStyle(styleValue);
    };
    spanNode->AddResObj(key, resObj, std::move(updateFunc));
}

void SpanModelNG::SetTextBackgroundStyleByBaseSpan(UINode* uiNode, const TextBackgroundStyle& style)
{
    auto spanNode = AceType::DynamicCast<BaseSpan>(uiNode);
    CHECK_NULL_VOID(spanNode);
    spanNode->SetTextBackgroundStyle(style);
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto key = "textbackgroundStyle";
    auto&& updateFunc = [style, weak = AceType::WeakClaim(spanNode)](const RefPtr<ResourceObject>& resObj) {
        auto spanNode = weak.Upgrade();
        CHECK_NULL_VOID(spanNode);
        TextBackgroundStyle& styleValue = const_cast<TextBackgroundStyle&>(style);
        styleValue.ReloadResources();
        spanNode->SetTextBackgroundStyle(styleValue);
    };
    spanNode->AddResObj(key, resObj, std::move(updateFunc));
}

std::u16string SpanModelNG::GetContent(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, u"");
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_RETURN(spanItem, u"");
    return spanItem->GetSpanContent();
}

Ace::TextDecoration SpanModelNG::GetTextDecoration(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, TextDecoration::NONE);
    return spanNode->GetTextDecorationFirst();
}

Color SpanModelNG::GetTextDecorationColor(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, Color::BLACK);
    return spanNode->GetTextDecorationColor().value_or(Color::BLACK);
}

Ace::TextDecorationStyle SpanModelNG::GetTextDecorationStyle(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, TextDecorationStyle::SOLID);
    return spanNode->GetTextDecorationStyle().value_or(TextDecorationStyle::SOLID);
}

TextStyle SpanModelNG::GetDefaultTextStyle(int32_t themeScopeId)
{
    TextStyle textStyle;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, textStyle);
    auto textTheme = pipelineContext->GetTheme<TextTheme>(themeScopeId);
    CHECK_NULL_RETURN(textTheme, textStyle);
    return textTheme->GetTextStyle();
}

Color SpanModelNG::GetFontColor(UINode* uiNode)
{
    auto themeScopeId = uiNode ? uiNode->GetThemeScopeId() : 0;
    auto defaultColor = GetDefaultTextStyle(themeScopeId).GetTextColor();
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultColor);
    return spanNode->GetTextColor().value_or(defaultColor);
}

Dimension SpanModelNG::GetFontSize(UINode* uiNode)
{
    auto themeScopeId = uiNode ? uiNode->GetThemeScopeId() : 0;
    const Dimension& defaultFontSize = GetDefaultTextStyle(themeScopeId).GetFontSize();
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultFontSize);
    return spanNode->GetFontSize().value_or(defaultFontSize);
}

Ace::FontStyle SpanModelNG::GetFontStyle(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, Ace::FontStyle::NORMAL);
    return spanNode->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL);
}

FontWeight SpanModelNG::GetFontWeight(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, FontWeight::NORMAL);
    return spanNode->GetFontWeight().value_or(FontWeight::NORMAL);
}

Dimension SpanModelNG::GetTextLineHeight(UINode* uiNode)
{
    Dimension defaultLineHeight(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, Dimension(0));
    return spanNode->GetLineHeight().value_or(defaultLineHeight);
}

Ace::TextCase SpanModelNG::GetTextCase(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, TextCase::NORMAL);
    return spanNode->GetTextCase().value_or(TextCase::NORMAL);
}

Dimension SpanModelNG::GetLetterSpacing(UINode* uiNode)
{
    Dimension defaultLetterSpacing(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultLetterSpacing);
    return spanNode->GetLetterSpacing().value_or(defaultLetterSpacing);
}

Dimension SpanModelNG::GetBaselineOffset(UINode* uiNode)
{
    Dimension defaultBaselineOffset(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultBaselineOffset);
    return spanNode->GetBaselineOffset().value_or(defaultBaselineOffset);
}

TextBackgroundStyle SpanModelNG::GetSpanTextBackgroundStyle(UINode* uiNode)
{
    TextBackgroundStyle backgroundStyle;
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, backgroundStyle);
    return spanNode->GetTextBackgroundStyle().value_or(backgroundStyle);
}

std::vector<Shadow> SpanModelNG::GetTextShadow(UINode* uiNode)
{
    std::vector<Shadow> defaultShadow;
    CHECK_NULL_RETURN(uiNode, defaultShadow);
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, defaultShadow);
    return spanNode->GetTextShadow().value_or(defaultShadow);
}

void SpanModelNG::SetAccessibilityText(UINode* uiNode, const std::string& text)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityText(text);
}

void SpanModelNG::SetAccessibilityDescription(UINode* uiNode, const std::string& description)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityDescription(description);
}

void SpanModelNG::SetAccessibilityImportance(UINode* uiNode, const std::string& importance)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    CHECK_NULL_VOID(spanItem->accessibilityProperty);
    spanItem->accessibilityProperty->SetAccessibilityLevel(importance);
}

std::vector<std::string> SpanModelNG::GetSpanFontFamily(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    std::vector<std::string> value;
    CHECK_NULL_RETURN(spanNode, value);
    return spanNode->GetFontFamily().value_or(value);
}

void SpanModelNG::SetOnHover(OnHoverFunc&& onHoverEventFunc)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    spanItem->SetHoverEvent(std::move(onHoverEventFunc));
}

void SpanModelNG::SetOnHover(UINode* uiNode, OnHoverFunc&& onHoverEventFunc)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    spanItem->SetHoverEvent(std::move(onHoverEventFunc));
}

void SpanModelNG::ResetOnHover()
{
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    spanItem->ResetHoverEvent();
}

void SpanModelNG::ResetOnHover(UINode* uiNode)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_VOID(spanNode);
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    spanItem->ResetHoverEvent();
}
} // namespace OHOS::Ace::NG
