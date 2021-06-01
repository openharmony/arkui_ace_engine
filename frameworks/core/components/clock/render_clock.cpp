/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/clock/render_clock.h"

#include <cmath>

#include "base/i18n/localization.h"
#include "core/components/clock/clock_component.h"
#include "core/components/image/image_component.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

constexpr double HOUR_HAND_RATIO = 0.062; // [width-of-clock-hand-image] / [width-of-clock-face-image]
constexpr double RADIAN_FOR_ONE_HOUR = 30 * 3.1415926 / 180.0;
constexpr double DIGIT_SIZE_RATIO_UPPER_BOUND = 1.0 / 7.0;
constexpr double DIGIT_RADIUS_RATIO_UPPER_BOUND = 1.0;
constexpr double EPSILON = 0.000001;
constexpr int32_t TOTAL_HOURS_OF_ANALOG_CLOCK = 12;

} // namespace

RenderClock::RenderClock()
{
    for (int32_t i = 1; i <= TOTAL_HOURS_OF_ANALOG_CLOCK; i++) {
        auto digitStr = Localization::GetInstance()->NumberFormat(i);
        digits_.emplace_back(digitStr);
        auto renderDigit = AceType::DynamicCast<RenderText>(RenderText::Create());
        AddChild(renderDigit);
        digitRenderNodes_.emplace_back(renderDigit);
        radians_.emplace_back(i * RADIAN_FOR_ONE_HOUR);
    }

    renderClockFace_ = AceType::DynamicCast<RenderImage>(RenderImage::Create());
    AddChild(renderClockFace_);

    renderClockHand_ = AceType::DynamicCast<RenderClockHand>(RenderClockHand::Create());
    renderClockHand_->SetDayToNightCallback([wp = WeakClaim(this)]() {
        auto renderClock = wp.Upgrade();
        if (renderClock) {
            renderClock->UseNightConfig();
            renderClock->MarkNeedLayout();
        }
    });
    renderClockHand_->SetNightToDayCallback([wp = WeakClaim(this)]() {
        auto renderClock = wp.Upgrade();
        if (renderClock) {
            renderClock->UseDayConfig();
            renderClock->MarkNeedLayout();
        }
    });
    renderClockHand_->SetAccessibilityTimeCallback([wp = WeakClaim(this)](double hour, double minute) {
        auto renderClock = wp.Upgrade();
        if (renderClock) {
            renderClock->UpdateAccessibilityInfo(hour, minute);
        }
    });
    renderHourHand_ = AceType::DynamicCast<RenderImage>(RenderImage::Create());
    renderMinuteHand_ = AceType::DynamicCast<RenderImage>(RenderImage::Create());
    renderSecondHand_ = AceType::DynamicCast<RenderImage>(RenderImage::Create());
    AddChild(renderClockHand_);
}

void RenderClock::Update(const RefPtr<Component>& component)
{
    RefPtr<ClockComponent> clock = AceType::DynamicCast<ClockComponent>(component);
    if (clock) {
        hoursWest_ = clock->GetHoursWest();
        defaultSize_ = clock->GetDefaultSize();
        auto inputDigitSizeRatio = clock->GetDigitSizeRatio();
        digitSizeRatio_ = InRegion(EPSILON, DIGIT_SIZE_RATIO_UPPER_BOUND, inputDigitSizeRatio) ? inputDigitSizeRatio
                                                                                               : digitSizeRatio_;
        auto inputDigitRadiusRatio = clock->GetDigitRadiusRatio();
        digitRadiusRatio_ = InRegion(EPSILON, DIGIT_RADIUS_RATIO_UPPER_BOUND, inputDigitRadiusRatio)
                                ? inputDigitRadiusRatio
                                : digitRadiusRatio_;
        fontFamilies_ = clock->GetFontFamilies();
        showDigit_ = clock->GetShowDigit();

        // update attributes and styles for day mode
        clockFaceSrc_ = clock->GetClockFaceSrc();
        hourHandSrc_ = clock->GetHourHandSrc();
        minuteHandSrc_ = clock->GetMinuteHandSrc();
        secondHandSrc_ = clock->GetSecondHandSrc();
        digitColor_ = clock->GetDigitColor();

        // update attributes and styles for night mode
        clockFaceNightSrc_ = clock->GetClockFaceNightSrc();
        hourHandNightSrc_ = clock->GetHourHandNightSrc();
        minuteHandNightSrc_ = clock->GetMinuteHandNightSrc();
        secondHandNightSrc_ = clock->GetSecondHandNightSrc();
        digitColorNight_ = clock->GetDigitColorNight();

        CheckNightConfig();

        auto timeOfNow = GetTimeOfNow(hoursWest_);
        IsDayTime(timeOfNow) ? UseDayConfig() : UseNightConfig();

        renderClockHand_->SetHoursWest(hoursWest_);
        renderClockHand_->Attach(GetContext());
        renderClockHand_->SetOnHourCallback(
            AceAsyncEvent<void(const std::string&)>::Create(clock->GetOnHourChangeEvent(), context_));
    }
    MarkNeedLayout();
}

void RenderClock::UseDayConfig()
{
    UpdateRenderImage(renderClockFace_, clockFaceSrc_);

    UpdateRenderImage(renderHourHand_, hourHandSrc_);
    renderClockHand_->SetHourHand(renderHourHand_);
    UpdateRenderImage(renderMinuteHand_, minuteHandSrc_);
    renderClockHand_->SetMinuteHand(renderMinuteHand_);
    UpdateRenderImage(renderSecondHand_, secondHandSrc_);
    renderClockHand_->SetSecondHand(renderSecondHand_);
    renderClockHand_->SetIsDay(true);
}

void RenderClock::UseNightConfig()
{
    UpdateRenderImage(renderClockFace_, clockFaceNightSrc_);

    UpdateRenderImage(renderHourHand_, hourHandNightSrc_);
    renderClockHand_->SetHourHand(renderHourHand_);
    UpdateRenderImage(renderMinuteHand_, minuteHandNightSrc_);
    renderClockHand_->SetMinuteHand(renderMinuteHand_);
    UpdateRenderImage(renderSecondHand_, secondHandNightSrc_);
    renderClockHand_->SetSecondHand(renderSecondHand_);
    renderClockHand_->SetIsDay(false);
}

void RenderClock::CheckNightConfig()
{
    UseDaySourceIfEmpty(clockFaceNightSrc_, clockFaceSrc_);
    UseDaySourceIfEmpty(hourHandNightSrc_, hourHandSrc_);
    UseDaySourceIfEmpty(minuteHandNightSrc_, minuteHandSrc_);
    UseDaySourceIfEmpty(secondHandNightSrc_, secondHandSrc_);
    if (digitColorNight_ == Color::TRANSPARENT) {
        digitColorNight_ = digitColor_;
    }
}

void RenderClock::UseDaySourceIfEmpty(std::string& nightSource, const std::string& daySource)
{
    if (nightSource.empty()) {
        nightSource = daySource;
    }
}

void RenderClock::UpdateAccessibilityInfo(double hour, double minute)
{
    auto node = GetAccessibilityNode().Upgrade();
    if (!node) {
        return;
    }
    std::string content = std::to_string(static_cast<int32_t>(hour))
        .append(":")
        .append(std::to_string(static_cast<int32_t>(minute)));
    node->SetText(content);

    auto context = context_.Upgrade();
    if (context) {
        AccessibilityEvent accessibilityEvent;
        accessibilityEvent.nodeId = node->GetNodeId();
        accessibilityEvent.eventType = "textchange";
        context->SendEventToAccessibility(accessibilityEvent);
    }
}

void RenderClock::UpdateRenderText(double digitSize, const Color& digitColor)
{
    if (digits_.size() == digitRenderNodes_.size()) {
        RefPtr<TextComponent> textComponent = AceType::MakeRefPtr<TextComponent>("");
        TextStyle textStyle;
        textStyle.SetAllowScale(false);
        textStyle.SetTextColor(digitColor);
        textStyle.SetFontSize(Dimension(digitSize));
        textStyle.SetFontFamilies(fontFamilies_);
        textComponent->SetTextStyle(textStyle);
        textComponent->SetFocusColor(digitColor);

        for (size_t i = 0; i < digitRenderNodes_.size(); i++) {
            textComponent->SetData(digits_[i]);
            digitRenderNodes_[i]->Attach(GetContext());
            digitRenderNodes_[i]->Update(textComponent);
        }
        return;
    }
    LOGE("Size of [digits] and [digitRenderNodes] does not match! Please check!");
}

void RenderClock::UpdateRenderImage(RefPtr<RenderImage>& renderImage, const std::string& imageSrc)
{
    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>(imageSrc);
    renderImage->Attach(GetContext());
    renderImage->Update(imageComponent);
}

void RenderClock::PerformLayout()
{
    defaultSize_ = Dimension(NormalizeToPx(defaultSize_), DimensionUnit::PX);
    CalculateLayoutSize();
    SetLayoutSize(GetLayoutParam().Constrain(drawSize_));
    LayoutClockImage(renderClockFace_, drawSize_);
    auto textColor = renderClockHand_->GetIsDay() ? digitColor_ : digitColorNight_;
    if (showDigit_) {
        LayoutParam textLayoutParam = GetLayoutParam();
        textLayoutParam.SetMinSize(Size());
        UpdateRenderText(drawSize_.Width() * digitSizeRatio_, textColor);
        for (const auto& renderDigit : digitRenderNodes_) {
            renderDigit->Layout(textLayoutParam);
        }
    }

    LayoutParam layoutParam = GetLayoutParam();
    layoutParam.SetMaxSize(drawSize_);
    renderClockHand_->Layout(layoutParam);

    paintOffset_ = Alignment::GetAlignPosition(GetLayoutSize(), drawSize_, Alignment::CENTER);
}

void RenderClock::CalculateLayoutSize()
{
    auto maxSize = GetLayoutParam().GetMaxSize();
    if (!maxSize.IsValid()) {
        LOGE("LayoutParam invalid!");
        return;
    }
    uint8_t infiniteStatus =
        (static_cast<uint8_t>(maxSize.IsWidthInfinite()) << 1) | static_cast<uint8_t>(maxSize.IsHeightInfinite());
    drawSize_ = maxSize;
    switch (infiniteStatus) {
        case 0b00: // both width and height are valid
            break;
        case 0b01: // width is valid but height is infinite
            drawSize_.SetHeight(defaultSize_.Value());
            break;
        case 0b10: // height is valid but width is infinite
            drawSize_.SetWidth(defaultSize_.Value());
            break;
        case 0b11: // both width and height are infinite
        default:
            drawSize_ = Size(defaultSize_.Value(), defaultSize_.Value());
            break;
    }
    double shorterEdge = std::min(drawSize_.Width(), drawSize_.Height());
    drawSize_ = Size(shorterEdge, shorterEdge);
}

void RenderClock::LayoutClockImage(const RefPtr<RenderImage>& renderImage, const Size& imageComponentSize)
{
    LayoutParam imageLayoutParam;
    imageLayoutParam.SetFixedSize(imageComponentSize);
    renderImage->SetImageComponentSize(imageComponentSize);
    renderImage->Layout(imageLayoutParam);
}

void RenderClockHand::PerformLayout()
{
    SetLayoutSize(GetLayoutParam().GetMaxSize());
    auto clockSize = GetLayoutSize();
    RenderClock::LayoutClockImage(renderHourHand_, Size(clockSize.Width() * HOUR_HAND_RATIO, clockSize.Height()));
    RenderClock::LayoutClockImage(renderMinuteHand_, Size(clockSize.Width() * HOUR_HAND_RATIO, clockSize.Height()));
    RenderClock::LayoutClockImage(renderSecondHand_, Size(clockSize.Width() * HOUR_HAND_RATIO, clockSize.Height()));
}

} // namespace OHOS::Ace