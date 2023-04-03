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

#include "core/components_ng/pattern/slider/slider_pattern.h"

#include <valarray>

#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5;
constexpr Dimension ARROW_WIDTH = 32.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr float SLIDER_MIN = .0f;
constexpr float SLIDER_MAX = 100.0f;
} // namespace

void SliderPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto inputEventHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputEventHub);
    auto layoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAlignment(Alignment::CENTER);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    showTips_ = sliderPaintProperty->GetShowTips().value_or(false);
    value_ = sliderPaintProperty->GetValue().value_or(0.0f);
    float min = sliderPaintProperty->GetMin().value_or(0.0f);
    float max = sliderPaintProperty->GetMax().value_or(100.0f);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    CancelExceptionValue(min, max, step);
    valueRatio_ = (value_ - min) / (max - min);
    stepRatio_ = step / (max - min);
    InitTouchEvent(gestureHub);
    InitClickEvent(gestureHub);
    InitPanEvent(gestureHub);
    InitMouseEvent(inputEventHub);
    auto focusHub = hub->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    InitOnKeyEvent(focusHub);
}

void SliderPattern::CancelExceptionValue(float& min, float& max, float& step)
{
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    if (GreatOrEqual(min, max)) {
        min = SLIDER_MIN;
        max = SLIDER_MAX;
        sliderPaintProperty->UpdateMin(min);
        sliderPaintProperty->UpdateMax(max);
    }
    if (LessOrEqual(step, 0.0) || step > max - min) {
        step = 1;
        sliderPaintProperty->UpdateStep(step);
    }
    if (value_ < min || value_ > max) {
        value_ = std::clamp(value_, min, max);
        sliderPaintProperty->UpdateValue(value_);
        FireChangeEvent(SliderChangeMode::End);
    }
}

bool SliderPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool /*skipLayout*/)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto sliderLayoutAlgorithm = DynamicCast<SliderLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(sliderLayoutAlgorithm, false);
    trackThickness_ = sliderLayoutAlgorithm->GetTrackThickness();
    blockDiameter_ = sliderLayoutAlgorithm->GetBlockDiameter();
    blockHotSize_ = sliderLayoutAlgorithm->GetBlockHotSize();

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, false);
    std::optional<SizeF> contentSize = GetHostContentSize();
    CHECK_NULL_RETURN(contentSize.has_value(), false);
    float length = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? contentSize.value().Width()
                       : contentSize.value().Height();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, false);
    Dimension hotBlockShadowWidth = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
                                            SliderModel::SliderMode::OUTSET
                                        ? theme->GetOutsetHotBlockShadowWidth()
                                        : theme->GetInsetHotBlockShadowWidth();

    hotBlockShadowWidth_ = static_cast<float>(hotBlockShadowWidth.ConvertToPx());
    borderBlank_ = std::max(trackThickness_, blockDiameter_ + hotBlockShadowWidth_ / HALF);
    // slider track length
    sliderLength_ = length >= borderBlank_ ? length - borderBlank_ : 1;
    borderBlank_ = (length - sliderLength_) * HALF;

    return true;
}

void SliderPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleTouchEvent(info);
    };
    gestureHub->RemoveTouchEvent(touchEvent_);
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void SliderPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        hotFlag_ = true;
        UpdateValueByLocalLocation(info.GetChangedTouches().front().GetLocalLocation());
        if (showTips_) {
            bubbleFlag_ = true;
            InitializeBubble();
        }
        mousePressedFlag_ = true;
        FireChangeEvent(SliderChangeMode::Begin);
        OpenTranslateAnimation();
    } else if (touchType == TouchType::UP) {
        hotFlag_ = false;
        if (bubbleFlag_) {
            bubbleFlag_ = false;
        }
        mousePressedFlag_ = false;
        CloseTranslateAnimation();
    }
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (clickListener_) {
        return;
    }
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickListener_);
}

void SliderPattern::HandleClickEvent()
{
    FireChangeEvent(SliderChangeMode::Click);
    FireChangeEvent(SliderChangeMode::End);
}

void SliderPattern::InitializeBubble()
{
    CHECK_NULL_VOID(bubbleFlag_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sliderTheme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(sliderTheme);
    std::string content = std::to_string(static_cast<int>(std::round(valueRatio_ * 100.0f))) + '%';
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    sliderPaintProperty->UpdatePadding(sliderTheme->GetTipTextPadding());
    sliderPaintProperty->UpdateTipColor(sliderTheme->GetTipColor());
    sliderPaintProperty->UpdateTextColor(sliderTheme->GetTipTextColor());
    sliderPaintProperty->UpdateFontSize(sliderTheme->GetTipFontSize());
    sliderPaintProperty->UpdateContent(content);
    UpdateBubble();
}

void SliderPattern::HandlingGestureEvent(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
        info.GetMainDelta() > 0.0 ? MoveStep(-1) : MoveStep(1);
    } else {
        UpdateValueByLocalLocation(info.GetLocalLocation());
        UpdateBubble();
    }
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandledGestureEvent()
{
    hotFlag_ = false;
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::UpdateValueByLocalLocation(const std::optional<Offset>& localLocation)
{
    CHECK_NULL_VOID(localLocation.has_value());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    float length = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? static_cast<float>(localLocation->GetX())
                       : static_cast<float>(localLocation->GetY());
    float touchLength = sliderPaintProperty->GetReverse().value_or(false) ? borderBlank_ + sliderLength_ - length
                                                                          : length - borderBlank_;
    float min = sliderPaintProperty->GetMin().value_or(0.0f);
    float max = sliderPaintProperty->GetMax().value_or(100.0f);
    touchLength = std::clamp(touchLength, 0.0f, sliderLength_);
    CHECK_NULL_VOID(sliderLength_ != 0);
    valueRatio_ = touchLength / sliderLength_;
    CHECK_NULL_VOID(stepRatio_ != 0);
    valueRatio_ = NearEqual(valueRatio_, 1) ? 1 : std::round(valueRatio_ / stepRatio_) * stepRatio_;
    float oldValue = value_;
    value_ = valueRatio_ * (max - min) + min;
    valueChangeFlag_ = !NearEqual(oldValue, value_);
}

void SliderPattern::UpdateTipsValue()
{
    CHECK_NULL_VOID_NOLOG(valueChangeFlag_);
    CHECK_NULL_VOID_NOLOG(showTips_);
    CHECK_NULL_VOID(bubbleFlag_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    std::string content = std::to_string(static_cast<int>(std::round(valueRatio_ * 100.0f))) + '%';
    frameNode->GetPaintProperty<SliderPaintProperty>()->UpdateContent(content);
}

void SliderPattern::UpdateCircleCenterOffset()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentSize = GetHostContentSize();
    CHECK_NULL_VOID(contentSize.has_value());
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    auto touchLength = valueRatio_ * sliderLength_;
    auto touchOffset = sliderPaintProperty->GetReverse().value_or(false) ? sliderLength_ - touchLength + borderBlank_
                                                                         : touchLength + borderBlank_;
    if (sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        circleCenter_.SetX(touchOffset);
        circleCenter_.SetY(contentSize->Height() * HALF);
    } else {
        circleCenter_.SetX(contentSize->Width() * HALF);
        circleCenter_.SetY(touchOffset);
    }
}

void SliderPattern::UpdateBubbleSizeAndLayout()
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    SizeF textSize = { 0, 0 };
    if (paragraph_) {
        textSize = SizeF(paragraph_->GetMaxIntrinsicWidth(), paragraph_->GetHeight());
    }
    OffsetF textOffsetInBubble = { 0, 0 };
    auto padding = static_cast<float>(paintProperty->GetPadding().value_or(0.0_vp).ConvertToPx());
    float bubbleSizeHeight = textSize.Height() + padding + padding;
    float bubbleSizeWidth = textSize.Width();
    if (paintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        bubbleSizeWidth = std::max(static_cast<float>(ARROW_WIDTH.ConvertToPx()), bubbleSizeWidth);
        bubbleSize_ = SizeF(
            bubbleSizeWidth + bubbleSizeHeight, bubbleSizeHeight + static_cast<float>(ARROW_HEIGHT.ConvertToPx()));
        textOffsetInBubble.SetX((bubbleSize_.Width() - textSize.Width()) * HALF);
        textOffsetInBubble.SetY(padding);

        bubbleOffset_.SetX(circleCenter_.GetX() - bubbleSize_.Width() * HALF);
        bubbleOffset_.SetY(circleCenter_.GetY() -
                           static_cast<float>(theme->GetBubbleToCircleCenterDistance().ConvertToPx()) -
                           bubbleSize_.Height());
    } else {
        bubbleSizeHeight = std::max(static_cast<float>(ARROW_WIDTH.ConvertToPx()), bubbleSizeHeight);
        bubbleSize_ =
            SizeF(bubbleSizeWidth + static_cast<float>(ARROW_HEIGHT.ConvertToPx()), bubbleSizeHeight + bubbleSizeWidth);
        textOffsetInBubble.SetY((bubbleSize_.Height() - textSize.Height()) * HALF);

        bubbleOffset_.SetY(circleCenter_.GetY() - bubbleSize_.Height() * HALF);
        bubbleOffset_.SetX(circleCenter_.GetX() -
                           static_cast<float>(theme->GetBubbleToCircleCenterDistance().ConvertToPx()) -
                           bubbleSize_.Width());
    }
    textOffset_ = bubbleOffset_ + textOffsetInBubble;
}

void SliderPattern::UpdateBubble()
{
    CHECK_NULL_VOID_NOLOG(showTips_);
    UpdateTipsValue();
    CreateParagraphFunc();
    UpdateCircleCenterOffset();
    UpdateBubbleSizeAndLayout();
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (direction_ == GetDirection() && panEvent_) {
        return;
    }
    direction_ = GetDirection();
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlingGestureEvent(info);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlingGestureEvent(info);
        pattern->FireChangeEvent(SliderChangeMode::Moving);
        pattern->CloseTranslateAnimation();
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandledGestureEvent();
        pattern->FireChangeEvent(SliderChangeMode::End);
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandledGestureEvent();
        pattern->FireChangeEvent(SliderChangeMode::End);
    };
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));

    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    float distance = static_cast<float>(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP).ConvertToPx());
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void SliderPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

void SliderPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        GetOutsetInnerFocusPaintRect(paintRect);
    } else {
        GetInsetInnerFocusPaintRect(paintRect);
    }
}

void SliderPattern::GetOutsetInnerFocusPaintRect(RoundRect& paintRect)
{
    UpdateCircleCenterOffset();
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentOffset = content->GetRect().GetOffset();
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto appTheme = PipelineBase::GetCurrentContext()->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusSideDistance = theme->GetFocusSideDistance();
    auto focusDistance = paintWidth * HALF + focusSideDistance;
    auto focusRadius = blockDiameter_ * HALF + static_cast<float>(focusDistance.ConvertToPx());
    paintRect.SetRect(RectF(circleCenter_.GetX() - focusRadius + contentOffset.GetX(),
        circleCenter_.GetY() - focusRadius + contentOffset.GetY(), focusRadius / HALF, focusRadius / HALF));
    paintRect.SetCornerRadius(focusRadius);
}

void SliderPattern::GetInsetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto frameSize = GetHostFrameSize();
    CHECK_NULL_VOID(frameSize);
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto focusSideDistance = theme->GetFocusSideDistance();
    auto appTheme = PipelineBase::GetCurrentContext()->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusDistance = paintWidth * HALF + focusSideDistance;
    float offsetX = 0;
    float offsetY = 0;
    float width = frameSize->Width();
    float height = frameSize->Height();
    float focusRadius = trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
    if (direction_ == Axis::HORIZONTAL) {
        offsetX = borderBlank_ - trackThickness_ * HALF - static_cast<float>(focusDistance.ConvertToPx());
        offsetY = (frameSize->Height() - trackThickness_) * HALF - static_cast<float>(focusDistance.ConvertToPx());
        width = sliderLength_ + trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        height = trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
    } else {
        offsetX = (frameSize->Width() - trackThickness_) * HALF - static_cast<float>(focusDistance.ConvertToPx());
        offsetY = borderBlank_ - trackThickness_ * HALF - static_cast<float>(focusDistance.ConvertToPx());
        width = trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        height = sliderLength_ + trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
    }
    paintRect.SetRect(RectF(offsetX, offsetY, width, height));
    paintRect.SetCornerRadius(focusRadius);
}

void SliderPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool SliderPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT) ||
        (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
        MoveStep(-1);
        PaintFocusState();
    }
    if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT) ||
        (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
        MoveStep(1);
        PaintFocusState();
    }
    return false;
}

bool SliderPattern::MoveStep(int32_t stepCount)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, false);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    float min = sliderPaintProperty->GetMin().value_or(0.0f);
    float max = sliderPaintProperty->GetMax().value_or(100.0f);
    if (NearZero(step)) {
        return false;
    }
    float nextValue = -1.0;
    nextValue = value_ + static_cast<float>(stepCount) * step;
    if (NearEqual(nextValue, -1.0)) {
        return false;
    }
    nextValue = std::clamp(nextValue, min, max);
    nextValue = std::round(nextValue / step) * step;
    if (NearEqual(nextValue, value_)) {
        return false;
    }
    value_ = nextValue;
    valueRatio_ = (value_ - min) / (max - min);
    LOGD("Move %{public}d steps, Value change to %{public}f", stepCount, value_);
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

void SliderPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputEventHub)
{
    auto hoverEvent = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleHoverEvent(isHover);
    };
    if (hoverEvent_) {
        inputEventHub->RemoveOnHoverEvent(hoverEvent_);
    }
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverEvent));
    inputEventHub->AddOnHoverEvent(hoverEvent_);

    auto mouseEvent = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleMouseEvent(info);
    };
    if (mouseEvent_) {
        inputEventHub->RemoveOnMouseEvent(mouseEvent_);
    }
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseEvent));
    inputEventHub->AddOnMouseEvent(mouseEvent_);
}

void SliderPattern::HandleHoverEvent(bool isHover)
{
    mouseHoverFlag_ = mouseHoverFlag_ && isHover;
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandleMouseEvent(const MouseInfo& info)
{
    UpdateCircleCenterOffset();
    auto mouseToCenterDistanceX = static_cast<float>(std::abs(info.GetLocalLocation().GetX() - circleCenter_.GetX()));
    auto mouseToCenterDistanceY = static_cast<float>(std::abs(info.GetLocalLocation().GetY() - circleCenter_.GetY()));
    float mouseToCenterDistance = std::max(mouseToCenterDistanceX, mouseToCenterDistanceY);
    mouseHoverFlag_ = LessOrEqual(mouseToCenterDistance, blockHotSize_ * HALF);
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::FireChangeEvent(int32_t mode)
{
    auto sliderEventHub = GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(sliderEventHub);
    if ((mode == SliderChangeMode::Click || mode == SliderChangeMode::Moving) &&
        NearEqual(value_, sliderEventHub->GetValue())) {
        return;
    }
    sliderEventHub->FireChangeEvent(static_cast<float>(value_), mode);
    valueChangeFlag_ = false;
}

void SliderPattern::UpdateMarkDirtyNode(const PropertyChangeFlag& Flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(Flag);
}

Axis SliderPattern::GetDirection() const
{
    auto sliderLayoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, Axis::HORIZONTAL);
    return sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
}

RefPtr<AccessibilityProperty> SliderPattern::CreateAccessibilityProperty()
{
    return MakeRefPtr<SliderAccessibilityProperty>();
}
 
void SliderPattern::CreateParagraphFunc()
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sliderTheme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(sliderTheme);
    auto fontStyle = std::make_unique<NG::FontStyle>();
    fontStyle->UpdateTextColor(paintProperty->GetTextColor().value_or(sliderTheme->GetTipTextColor()));
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, nullptr, pipeline->GetTheme<TextTheme>());
    auto layoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    auto contentSize = layoutProperty->CreateContentConstraint();
    CreateParagraphAndLayout(textStyle, paintProperty->GetContent().value_or(""), contentSize);
}

void SliderPattern::CreateParagraphAndLayout(
    const TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint)
{
    if (!CreateParagraph(textStyle, content)) {
        return;
    }
    CHECK_NULL_VOID(paragraph_);
    auto size = contentConstraint.selfIdealSize;
    size.UpdateIllegalSizeWithCheck(contentConstraint.maxSize);
    auto maxSize = size.ConvertToSizeT();
    paragraph_->Layout(maxSize.Width());
}

bool SliderPattern::CreateParagraph(const TextStyle& textStyle, std::string content)
{
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph_, false);
    paragraph_->PushStyle(textStyle);
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    paragraph_->AddText(StringUtils::Str8ToStr16(content));
    paragraph_->Build();
    return true;
}

SliderContentModifier::Parameters SliderPattern::UpdateContentParameters()
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, SliderContentModifier::Parameters());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, SliderContentModifier::Parameters());
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, SliderContentModifier::Parameters());
    SliderContentModifier::Parameters parameters { trackThickness_, blockDiameter_, stepRatio_, hotBlockShadowWidth_,
        mouseHoverFlag_, mousePressedFlag_ };
    auto contentSize = GetHostContentSize();
    auto contentOffset = GetHost()->GetGeometryNode()->GetContent()->GetRect().GetOffset();
    // Distance between slide track and Content boundary
    auto centerWidth = direction_ == Axis::HORIZONTAL ? contentSize->Height() : contentSize->Width();
    centerWidth *= HALF;
    parameters.selectColor = paintProperty->GetSelectColor().value_or(theme->GetTrackSelectedColor());
    parameters.trackBackgroundColor = paintProperty->GetTrackBackgroundColor().value_or(theme->GetTrackBgColor());
    parameters.blockColor = paintProperty->GetBlockColor().value_or(theme->GetBlockColor());

    GetSelectPosition(parameters, centerWidth, contentOffset);
    GetBackgroundPosition(parameters, centerWidth, contentOffset);
    GetCirclePosition(parameters, centerWidth, contentOffset);
    return parameters;
}

void SliderPattern::GetSelectPosition(
    SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset)
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    float sliderSelectLength = std::clamp(sliderLength_ * valueRatio_, 0.0f, sliderLength_);
    PointF start;
    PointF end;
    if (!paintProperty->GetReverseValue(false)) {
        start = direction_ == Axis::HORIZONTAL ? PointF(offset.GetX() + borderBlank_, offset.GetY() + centerWidth)
                                               : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_);
        end = direction_ == Axis::HORIZONTAL
                  ? PointF(offset.GetX() + borderBlank_ + sliderSelectLength, offset.GetY() + centerWidth)
                  : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderSelectLength);
    } else {
        start = direction_ == Axis::HORIZONTAL
                    ? PointF(offset.GetX() + borderBlank_ + sliderLength_, offset.GetY() + centerWidth)
                    : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderLength_);
        end =
            direction_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + borderBlank_ + sliderLength_ - sliderSelectLength, offset.GetY() + centerWidth) :
                PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderLength_ - sliderSelectLength);
    }
    parameters.selectStart = start;
    parameters.selectEnd = end;
}

void SliderPattern::GetBackgroundPosition(
    SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset)
{
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    auto start = direction_ == Axis::HORIZONTAL ? PointF(startPointX + borderBlank_, startPointY + centerWidth)
                                                : PointF(startPointX + centerWidth, startPointY + borderBlank_);
    auto end = direction_ == Axis::HORIZONTAL
                   ? PointF(startPointX + borderBlank_ + sliderLength_, startPointY + centerWidth)
                   : PointF(startPointX + centerWidth, startPointY + borderBlank_ + sliderLength_);
    parameters.backStart = start;
    parameters.backEnd = end;
}

void SliderPattern::GetCirclePosition(
    SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset)
{
    float sliderSelectLength = std::clamp(sliderLength_ * valueRatio_, 0.0f, sliderLength_);
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    PointF center;
    if (!paintProperty->GetReverseValue(false)) {
        center = direction_ == Axis::HORIZONTAL
                     ? PointF(offset.GetX() + borderBlank_ + sliderSelectLength, offset.GetY() + centerWidth)
                     : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderSelectLength);
    } else {
        center =
            direction_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + borderBlank_ + sliderLength_ - sliderSelectLength, offset.GetY() + centerWidth) :
                PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderLength_ - sliderSelectLength);
    }
    parameters.circleCenter = center;
}

void SliderPattern::OpenTranslateAnimation()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetAnimated();
}

void SliderPattern::CloseTranslateAnimation()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetNotAnimated();
}
} // namespace OHOS::Ace::NG
