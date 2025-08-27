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

#include "bridge/declarative_frontend/jsview/models/text_model_impl.h"

#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void TextModelImpl::Create(const std::string& content)
{
    auto textComponent = AceType::MakeRefPtr<TextComponentV2>(content);
    ViewStackProcessor::GetInstance()->ClaimElementId(textComponent);
    ViewStackProcessor::GetInstance()->Push(textComponent);

    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    if (focusableComponent) {
        focusableComponent->SetFocusable(false);
        focusableComponent->SetFocusNode(true);
    }

    // Init text style, allowScale is not supported in declarative.
    auto textStyle = textComponent->GetTextStyle();
    textStyle.SetAllowScale(false);
    constexpr Dimension fontSize = 30.0_px;
    textStyle.SetFontSize(fontSize);
    textComponent->SetTextStyle(textStyle);
}

void TextModelImpl::Create(const std::u16string& content)
{
    Create(UtfUtils::Str16DebugToStr8(content));
}

void TextModelImpl::SetFont(const Font& value) {}

void TextModelImpl::SetFontSize(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontSize(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextColor(const Color& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetTextColor(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextShadow(const std::vector<Shadow>& value) {}

void TextModelImpl::SetTextCaretColor(const Color& value) {}

void TextModelImpl::SetSelectedBackgroundColor(const Color& value) {}

void TextModelImpl::SetItalicFontStyle(Ace::FontStyle value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontStyle(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetFontWeight(Ace::FontWeight value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontWeight(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetMinFontScale(const float value) {}

void TextModelImpl::SetMaxFontScale(const float value) {}

void TextModelImpl::SetFontFamily(const std::vector<std::string>& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontFamilies(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextAlign(Ace::TextAlign value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetTextAlign(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextOverflow(Ace::TextOverflow value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextOverflow(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetMaxLines(uint32_t value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetMaxLines(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextIndent(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetTextIndent(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetLineHeight(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetLineHeight(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextDecoration(Ace::TextDecoration value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextDecoration(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextDecorationColor(const Color& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextDecorationColor(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextDecorationStyle(TextDecorationStyle value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextDecorationStyle(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetBaselineOffset(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetBaselineOffset(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetTextCase(Ace::TextCase value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetTextCase(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetLetterSpacing(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetLetterSpacing(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetLineSpacing(const Dimension& value) {}

void TextModelImpl::SetIsOnlyBetweenLines(bool isOnlyBetweenLines) {}

void TextModelImpl::SetOptimizeTrailingSpace(bool trim) {}

void TextModelImpl::SetGradientShaderStyle(NG::Gradient& gradient) {}

void TextModelImpl::SetColorShaderStyle(const Color& value) {}

void TextModelImpl::ResetGradientShaderStyle() {}

void TextModelImpl::SetAdaptMinFontSize(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetAdaptMinFontSize(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetAdaptMaxFontSize(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetAdaptMaxFontSize(value);
    component->SetTextStyle(textStyle);
}

void TextModelImpl::SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value) {}

void TextModelImpl::SetTextDetectEnable(bool value) {}

void TextModelImpl::SetTextDetectConfig(const TextDetectConfig& textDetectConfig) {}

void TextModelImpl::OnSetWidth()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    CHECK_NULL_VOID(box);
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetMaxWidthLayout(box->GetWidthDimension().IsValid());
}

void TextModelImpl::OnSetHeight()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    CHECK_NULL_VOID(box);
    box->SetBoxClipFlag(true);
}

RefPtr<TextComponentV2> TextModelImpl::GetComponent()
{
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<TextComponentV2>(stack->GetMainComponent());
    return component;
}

void TextModelImpl::OnSetAlign()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    CHECK_NULL_VOID(box);
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto alignment = box->GetAlignment();
    if (NearEqual(alignment.GetHorizontal(), -1.0)) {
        component->SetAlignment(TextAlign::LEFT);
    } else if (NearEqual(alignment.GetHorizontal(), 0.0)) {
        component->SetAlignment(TextAlign::CENTER);
    } else if (NearEqual(alignment.GetHorizontal(), 1.0)) {
        component->SetAlignment(TextAlign::RIGHT);
    }
}

void TextModelImpl::SetOnClick(std::function<void(BaseEventInfo*)>&& click, double distanceThreshold)
{
    auto clickId = EventMarker(std::move(click));
    auto gesture = ViewStackProcessor::GetInstance()->GetClickGestureListenerComponent();
    if (gesture) {
        gesture->SetOnClickId(clickId);
    }
    auto component = GetComponent();
    if (component) {
        component->SetOnClick(clickId);
    }

    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetOnClickId(clickId);
    }
}

void TextModelImpl::SetRemoteMessage(std::function<void()>&& event)
{
    auto textComponent = GetComponent();
    CHECK_NULL_VOID(textComponent);
    textComponent->SetRemoteMessageEvent(EventMarker(std::move(event)));
}

void TextModelImpl::SetCopyOption(CopyOptions copyOption)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetCopyOption(copyOption);
}

void TextModelImpl::SetOnDragStart(NG::OnDragStartFunc&& onDragStart)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnDragStartId(ViewAbstractModelImpl::ToDragFunc(std::move(onDragStart)));
}

void TextModelImpl::SetHalfLeading(bool halfLeading) {}
} // namespace OHOS::Ace::Framework
