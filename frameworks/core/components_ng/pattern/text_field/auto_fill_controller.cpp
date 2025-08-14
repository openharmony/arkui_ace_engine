/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_field/auto_fill_controller.h"

#include <algorithm>
#include <cstdint>
#include <string>

#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t AUTO_FILL_ICON_ANIMATION_DURATION = 250;
constexpr float AUTO_FILL_SPRING_RESPONSE = 0.513f;
constexpr float AUTO_FILL_SPRING_DAMPING_FRACTION = 0.94f;
constexpr float AUTO_FILL_SPRING_RESPONSE_EXTRA_LONG = 0.613f;
constexpr float AUTO_FILL_SPRING_DAMPING_FRACTION_EXTRA_LONG = 0.93f;
constexpr uint32_t AUTO_FILL_SYMBOL_RENDERING_STRATEGY = 1;
constexpr float AUTO_FILL_ICON_INIT_SCALE = 0.2f;
constexpr int32_t AUTO_FILL_TEXT_SCROLL_DELAY_DURATION = 500;
constexpr int32_t AUTO_FILL_DEFAULT_CHAR_DELAY_DURATION = 150;
constexpr int32_t AUTO_FILL_ICON_HIDE_DELAY_DURATION_SHORT = 800;
constexpr int32_t AUTO_FILL_ICON_HIDE_DELAY_DURATION_MEDIUM = 900;
constexpr int32_t AUTO_FILL_ICON_HIDE_DELAY_DURATION_LONG = 1000;
constexpr int32_t AUTO_FILL_ICON_HIDE_DELAY_DURATION_EXTRA_LONG = 1100;
} // namespace

void AutoFillController::StartAutoFillAnimation(
    const std::function<void()>& onFinishCallback, const std::u16string& content)
{
    auto initParagraphSuc = InitAutoFillParagraph(content);
    auto createAutoFillIconSuc = CreateAutoFillIcon();
    if (!initParagraphSuc || !createAutoFillIconSuc) {
        if (onFinishCallback) {
            onFinishCallback();
        }
        ResetAutoFillAnimationStatus();
        return;
    }
    AutoFillContentLengthMode mode = GetAutoFillContentLengthMode();
    if (mode == AutoFillContentLengthMode::INVALID) {
        if (onFinishCallback) {
            onFinishCallback();
        }
        ResetAutoFillAnimationStatus();
        return;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->StopTwinkling();
    UpdateAnimationTextRect();
    if (mode == AutoFillContentLengthMode::EXTRA_LONG) {
        PlayAutoFillIconShowAnimation(mode);
        PlayAutoFillTextScrollAnimation();
        PlayAutoFillIconHideAnimation(onFinishCallback, mode);
    } else {
        PlayAutoFillIconShowAnimation(mode);
        PlayAutoFillIconHideAnimation(onFinishCallback, mode);
    }
}

AutoFillContentLengthMode AutoFillController::GetAutoFillContentLengthMode()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, AutoFillContentLengthMode::INVALID);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFieldPattern, AutoFillContentLengthMode::INVALID);
    CHECK_NULL_RETURN(autoFillParagraph_, AutoFillContentLengthMode::INVALID);

    float autoFillParagraphWidth = std::max(autoFillParagraph_->GetLongestLine(), 0.0f);
    auto contentRect = textFieldPattern->GetTextContentRect();
    float textFieldContentWidth = std::max(contentRect.Width(), 0.0f);
    if (LessOrEqual(autoFillParagraphWidth, 0.0f) || LessOrEqual(textFieldContentWidth, 0.0f)) {
        return AutoFillContentLengthMode::INVALID;
    }

    if (GreatNotEqual(autoFillParagraphWidth, textFieldContentWidth)) {
        return AutoFillContentLengthMode::EXTRA_LONG;
    }

    auto shortContentLength = textFieldContentWidth * 1.0f / 3.0f;
    auto middleContentLength = textFieldContentWidth * 2.0f / 3.0f;
    if (LessOrEqual(autoFillParagraphWidth, shortContentLength)) {
        return AutoFillContentLengthMode::SHORT;
    }

    if (LessOrEqual(autoFillParagraphWidth, middleContentLength)) {
        return AutoFillContentLengthMode::MEDIUM;
    }

    return AutoFillContentLengthMode::LONG;
}

bool AutoFillController::InitAutoFillParagraph(const std::u16string& content)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFieldPattern, false);
    autoFillParagraph_ = textFieldPattern->GetParagraph();
    CHECK_NULL_RETURN(autoFillParagraph_, false);
    auto textFieldContentModifier = textFieldPattern->GetContentModifier();
    CHECK_NULL_RETURN(textFieldContentModifier, false);
    textFieldContentModifier->SetAutoFillOriginTextColor(autoFillOriginTextColor_);
    return true;
}

void AutoFillController::PlayAutoFillIconShowAnimation(const AutoFillContentLengthMode& mode)
{
    auto symbolNode = autoFillIconNode_.Upgrade();
    CHECK_NULL_VOID(symbolNode);
    auto symbolRenderContext = symbolNode->GetRenderContext();
    CHECK_NULL_VOID(symbolRenderContext);
    AnimationOption option = AnimationOption();
    option.SetDuration(AUTO_FILL_ICON_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option,
        [symbolRenderContext]() {
            symbolRenderContext->UpdateOpacity(1.0);
            symbolRenderContext->UpdateTransformScale({ 1.0, 1.0 });
        },
        [weak = AceType::WeakClaim(this), mode]() {
            auto autofillController = weak.Upgrade();
            CHECK_NULL_VOID(autofillController);
            autofillController->PlayAutoFillTranslationAnimation(mode);
            autofillController->PlayAutoFillDefaultCharAnimation(mode);
        }, nullptr, symbolNode->GetContextRefPtr());
}

void AutoFillController::PlayAutoFillDefaultCharAnimation(const AutoFillContentLengthMode& mode)
{
    if (!autoFillParagraph_) {
        ResetAutoFillAnimationStatus();
        return;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    auto contentLength = autoFillParagraph_->GetParagraphText().length();
    auto response = GetSpringAnimationResponse(mode);
    auto damping = GetSpringAnimationDamping(mode);
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, damping);
    AnimationOption option;
    option.SetCurve(motion);
    option.SetDelay(AUTO_FILL_DEFAULT_CHAR_DELAY_DURATION);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), weakPattern = pattern_, contentLength]() {
        auto autofillController = weak.Upgrade();
        CHECK_NULL_VOID(autofillController);
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
        CHECK_NULL_VOID(textFieldPattern);
        auto textFieldContentModifier = textFieldPattern->GetContentModifier();
        CHECK_NULL_VOID(textFieldContentModifier);
        autofillController->autoFillAnimationStatus_ = AutoFillAnimationStatus::TRANSLATION;
        textFieldContentModifier->SetAutoFillDefaultCharIndex(std::max(contentLength - 1.0f, 0.0f));
    }, nullptr, nullptr, Claim(pattern->GetContext()));
}

void AutoFillController::PlayAutoFillTranslationAnimation(const AutoFillContentLengthMode& mode)
{
    if (!autoFillParagraph_) {
        ResetAutoFillAnimationStatus();
        return;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    auto symbolNode = autoFillIconNode_.Upgrade();
    CHECK_NULL_VOID(symbolNode);
    auto symbolRenderContext = symbolNode->GetRenderContext();
    CHECK_NULL_VOID(symbolRenderContext);
    float autoFillParagraphWidth = std::max(autoFillParagraph_->GetLongestLine(), 0.0f);
    auto contentRect = textFieldPattern->GetTextContentRect();
    float textFieldContentWidth = std::max(contentRect.Width(), 0.0f);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);
    auto iconSize = theme->GetAutoFillIconSize();
    auto iconWidth = static_cast<float>(iconSize.ConvertToPx());
    auto translationOffset =
        std::min(autoFillParagraphWidth + autoFillFirstCharOffset_, textFieldContentWidth - iconWidth);
    if (isRTL) {
        translationOffset = -translationOffset;
    }
    auto contentLength = autoFillParagraph_->GetParagraphText().length();
    auto response = GetSpringAnimationResponse(mode);
    auto damping = GetSpringAnimationDamping(mode);
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, damping);
    AnimationOption option;
    option.SetCurve(motion);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), weakPattern = pattern_, translationOffset,
                                        symbolRenderContext, contentLength]() {
        auto autofillController = weak.Upgrade();
        CHECK_NULL_VOID(autofillController);
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
        CHECK_NULL_VOID(textFieldPattern);
        auto textFieldContentModifier = textFieldPattern->GetContentModifier();
        CHECK_NULL_VOID(textFieldContentModifier);
        autofillController->autoFillAnimationStatus_ = AutoFillAnimationStatus::TRANSLATION;
        textFieldContentModifier->SetAutoFillEmphasizeCharIndex(std::max(contentLength - 1.0f, 0.0f));
        textFieldContentModifier->SetAutoFillTranslationOffset(translationOffset);
        symbolRenderContext->UpdateTransformTranslate({ translationOffset, 0.0f, 0.0f });
    }, nullptr, nullptr, Claim(pattern->GetContext()));
}

void AutoFillController::PlayAutoFillTextScrollAnimation()
{
    if (!autoFillParagraph_) {
        ResetAutoFillAnimationStatus();
        return;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    float autoFillParagraphWidth = std::max(autoFillParagraph_->GetLongestLine(), 0.0f);
    auto contentRect = textFieldPattern->GetTextContentRect();
    float textFieldContentWidth = std::max(contentRect.Width(), 0.0f);
    auto startScrollOffset = isRTL ? autoFillParagraphWidth - textFieldContentWidth : 0;
    auto endScrollOffset = isRTL ? 0 : autoFillParagraphWidth - textFieldContentWidth;
    auto textFieldContentModifier = textFieldPattern->GetContentModifier();
    CHECK_NULL_VOID(textFieldContentModifier);
    textFieldContentModifier->SetAutoFillTextScrollOffset(startScrollOffset);
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(
        AUTO_FILL_SPRING_RESPONSE_EXTRA_LONG, AUTO_FILL_SPRING_DAMPING_FRACTION_EXTRA_LONG);
    AnimationOption option;
    option.SetCurve(motion);
    option.SetDelay(AUTO_FILL_TEXT_SCROLL_DELAY_DURATION);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), weakPattern = pattern_, endScrollOffset]() {
        auto autofillController = weak.Upgrade();
        CHECK_NULL_VOID(autofillController);
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
        CHECK_NULL_VOID(textFieldPattern);
        auto textFieldContentModifier = textFieldPattern->GetContentModifier();
        CHECK_NULL_VOID(textFieldContentModifier);
        autofillController->autoFillAnimationStatus_ = AutoFillAnimationStatus::TRANSLATION;
        textFieldContentModifier->SetAutoFillTextScrollOffset(endScrollOffset);
    }, nullptr, nullptr, Claim(pattern->GetContext()));
}

void AutoFillController::PlayAutoFillIconHideAnimation(
    const std::function<void()>& onFinishCallback, const AutoFillContentLengthMode& mode)
{
    auto symbolNode = autoFillIconNode_.Upgrade();
    if (!symbolNode) {
        ResetAutoFillAnimationStatus();
        return;
    }
    auto symbolRenderContext = symbolNode->GetRenderContext();
    if (!symbolRenderContext) {
        ResetAutoFillAnimationStatus();
        return;
    }
    auto delayDuration = AUTO_FILL_ICON_HIDE_DELAY_DURATION_SHORT;
    if (mode == AutoFillContentLengthMode::MEDIUM) {
        delayDuration = AUTO_FILL_ICON_HIDE_DELAY_DURATION_MEDIUM;
    } else if (mode == AutoFillContentLengthMode::LONG) {
        delayDuration = AUTO_FILL_ICON_HIDE_DELAY_DURATION_LONG;
    } else if (mode == AutoFillContentLengthMode::EXTRA_LONG) {
        delayDuration = AUTO_FILL_ICON_HIDE_DELAY_DURATION_EXTRA_LONG;
    }

    AnimationOption option = AnimationOption();
    option.SetDuration(AUTO_FILL_ICON_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetDelay(delayDuration);
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this), symbolRenderContext]() {
            auto autofillController = weak.Upgrade();
            CHECK_NULL_VOID(autofillController);
            autofillController->autoFillAnimationStatus_ = AutoFillAnimationStatus::HIDE_ICON;
            symbolRenderContext->UpdateOpacity(0.0);
            symbolRenderContext->UpdateTransformScale({ AUTO_FILL_ICON_INIT_SCALE, AUTO_FILL_ICON_INIT_SCALE });
        },
        [weak = AceType::WeakClaim(this), weakPattern = pattern_, onFinish = std::move(onFinishCallback)]() {
            auto autofillController = weak.Upgrade();
            CHECK_NULL_VOID(autofillController);
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
            CHECK_NULL_VOID(textFieldPattern);
            autofillController->ResetAutoFillAnimationStatus();
            autofillController->ResetAutoFillIcon();
            textFieldPattern->StartTwinkling();
            if (onFinish) {
                onFinish();
            }
        }, nullptr, symbolNode->GetContextRefPtr());
}

bool AutoFillController::CreateAutoFillIcon()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textFieldPattern, false);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(symbolNode, false);
    autoFillIconNode_ = WeakClaim(RawPtr(symbolNode));
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(symbolProperty, false);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_RETURN(theme, false);
    symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetAutoFillSymbolId()));
    symbolProperty->UpdateFontSize(theme->GetAutoFillIconSize());
    symbolProperty->UpdateSymbolColorList(
        { theme->GetAutoFillIconPrimaryColor(), theme->GetAutoFillIconEmphasizeColor() });
    symbolProperty->UpdateSymbolRenderingStrategy(AUTO_FILL_SYMBOL_RENDERING_STRATEGY);
    auto symbolRenderContext = symbolNode->GetRenderContext();
    CHECK_NULL_RETURN(symbolRenderContext, false);
    symbolRenderContext->UpdateOpacity(0.0);
    symbolRenderContext->UpdateTransformScale({ AUTO_FILL_ICON_INIT_SCALE, AUTO_FILL_ICON_INIT_SCALE });
    CHECK_NULL_RETURN(autoFillParagraph_, false);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto lineMetrics = autoFillParagraph_->GetLineMetrics(0);
    autoFillFirstCharOffset_ = lineMetrics.x;
    auto startOffset = autoFillFirstCharOffset_;
    auto contentRect = textFieldPattern->GetTextContentRect();
    if (isRTL) {
        // animation from right to left
        startOffset = contentRect.Width() - (startOffset + lineMetrics.width);
        startOffset = std::max(startOffset, 0.0f);
        autoFillFirstCharOffset_ = startOffset;
        startOffset = -startOffset;
    }
    symbolRenderContext->UpdateTransformTranslate({ startOffset, 0.0f, 0.0f });
    symbolNode->MountToParent(host);
    symbolNode->MarkModifyDone();
    symbolNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

void AutoFillController::ResetAutoFillIcon()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto symbolNode = autoFillIconNode_.Upgrade();
    CHECK_NULL_VOID(symbolNode);
    host->RemoveChild(symbolNode);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void AutoFillController::ResetAutoFillAnimationStatus()
{
    autoFillAnimationStatus_ = AutoFillAnimationStatus::INIT;
    if (autoFillParagraph_) {
        autoFillParagraph_ = nullptr;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldContentModifier = textFieldPattern->GetContentModifier();
    CHECK_NULL_VOID(textFieldContentModifier);
    textFieldContentModifier->SetAutoFillTranslationOffset(0.0f);
    textFieldContentModifier->SetAutoFillTextScrollOffset(0.0f);
    textFieldContentModifier->SetAutoFillEmphasizeCharIndex(0.0f);
    textFieldContentModifier->SetAutoFillDefaultCharIndex(0.0f);
}

float AutoFillController::GetSpringAnimationResponse(const AutoFillContentLengthMode& mode)
{
    return mode == AutoFillContentLengthMode::EXTRA_LONG ? AUTO_FILL_SPRING_RESPONSE_EXTRA_LONG
                                                         : AUTO_FILL_SPRING_RESPONSE;
}

float AutoFillController::GetSpringAnimationDamping(const AutoFillContentLengthMode& mode)
{
    return mode == AutoFillContentLengthMode::EXTRA_LONG ? AUTO_FILL_SPRING_DAMPING_FRACTION_EXTRA_LONG
                                                         : AUTO_FILL_SPRING_DAMPING_FRACTION;
}

void AutoFillController::UpdateAnimationTextRect()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldPattern);
    auto textRect = textFieldPattern->GetTextRect();
    auto contentRect = textFieldPattern->GetTextContentRect();
    animationTextRect_ = textRect;
    animationTextRect_.SetLeft(contentRect.GetX());
}
} // namespace OHOS::Ace::NG