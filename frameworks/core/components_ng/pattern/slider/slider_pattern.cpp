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

#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5;
constexpr float SLIDER_MIN = .0f;
constexpr float SLIDER_MAX = 100.0f;
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
} // namespace

void SliderPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
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
    float min = sliderPaintProperty->GetMin().value_or(0.0f);
    float max = sliderPaintProperty->GetMax().value_or(100.0f);
    value_ = sliderPaintProperty->GetValue().value_or(min);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    CancelExceptionValue(min, max, step);
    valueRatio_ = (value_ - min) / (max - min);
    stepRatio_ = step / (max - min);
    UpdateCircleCenterOffset();
    UpdateBlock();
    InitTouchEvent(gestureHub);
    InitPanEvent(gestureHub);
    InitMouseEvent(inputEventHub);
    auto focusHub = hub->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    InitializeBubble();
    SetAccessibilityAction();
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
    blockSize_ = sliderLayoutAlgorithm->GetBlockSize();
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

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    Dimension hotBlockShadowWidth = sliderMode == SliderModel::SliderMode::OUTSET
                                        ? theme->GetOutsetHotBlockShadowWidth()
                                        : theme->GetInsetHotBlockShadowWidth();

    auto direction = sliderLayoutProperty->GetDirectionValue(Axis::HORIZONTAL);
    auto blockLength = direction == Axis::HORIZONTAL ? blockSize_.Width() : blockSize_.Height();

    hotBlockShadowWidth_ = static_cast<float>(hotBlockShadowWidth.ConvertToPx());
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        borderBlank_ = std::max(trackThickness_, blockLength + hotBlockShadowWidth_ / HALF);
    } else {
        borderBlank_ = trackThickness_ + hotBlockShadowWidth_ / HALF;
    }
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
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };
    gestureHub->RemoveTouchEvent(touchEvent_);
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

bool SliderPattern::AtMousePanArea(const Offset& offsetInFrame)
{
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, false);
    auto contentOffset = content->GetRect().GetOffset();
    auto offset = Offset(offsetInFrame.GetX() - contentOffset.GetX(), offsetInFrame.GetY() - contentOffset.GetY());
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto blockType = paintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT);
    if (blockType == SliderModelNG::BlockStyleType::DEFAULT) {
        double distanceCircle = std::min(blockSize_.Width(), blockSize_.Height()) * HALF + hotBlockShadowWidth_;
        auto diffX = circleCenter_.GetX() - offset.GetX();
        auto diffY = circleCenter_.GetY() - offset.GetY();
        return diffX * diffX + diffY * diffY <= distanceCircle * distanceCircle;
    } else {
        float sideHotSizeX = blockSize_.Width() * HALF;
        float sideHotSizeY = blockSize_.Height() * HALF;
        return !(circleCenter_.GetX() - sideHotSizeX > offset.GetX() ||
                 circleCenter_.GetY() - sideHotSizeY > offset.GetY() ||
                 circleCenter_.GetX() + sideHotSizeX < offset.GetX() ||
                 circleCenter_.GetY() + sideHotSizeY < offset.GetY());
    }
}

bool SliderPattern::AtTouchPanArea(const Offset& offsetInFrame)
{
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, false);
    auto contentOffset = content->GetRect().GetOffset();
    auto offset = Offset(offsetInFrame.GetX() - contentOffset.GetX(), offsetInFrame.GetY() - contentOffset.GetY());
    float sideHotSizeX = blockHotSize_.Width() * HALF;
    float sideHotSizeY = blockHotSize_.Height() * HALF;
    return !(circleCenter_.GetX() - sideHotSizeX > offset.GetX() ||
        circleCenter_.GetY() - sideHotSizeY > offset.GetY() ||
        circleCenter_.GetX() + sideHotSizeX < offset.GetX() ||
        circleCenter_.GetY() + sideHotSizeY < offset.GetY());
}

bool SliderPattern::AtPanArea(const Offset& offset, const SourceType& sourceType)
{
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, false);
    if (sliderPaintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT) !=
        SliderModelNG::BlockStyleType::DEFAULT) {
        return false;
    }
    bool flag = false;
    switch (sourceType) {
        case SourceType::MOUSE:
            flag = AtMousePanArea(offset);
            break;
        case SourceType::TOUCH:
            flag = AtTouchPanArea(offset);
            break;
        case SourceType::NONE:
        default:
            break;
    }
    return flag;
}

void SliderPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchList = info.GetChangedTouches();
    CHECK_NULL_VOID(!touchList.empty());
    auto touchInfo = touchList.front();
    auto touchType = touchInfo.GetTouchType();
    if (touchType == TouchType::DOWN) {
        axisFlag_ = false;
        // when Touch Down area is at Pan Area, value is unchanged.
        if (!AtPanArea(touchInfo.GetLocalLocation(), info.GetSourceDevice())) {
            UpdateValueByLocalLocation(touchInfo.GetLocalLocation());
        }
        if (showTips_) {
            bubbleFlag_ = true;
            UpdateBubble();
        }
        mousePressedFlag_ = true;
        FireChangeEvent(SliderChangeMode::Begin);
        OpenTranslateAnimation();
    } else if (touchType == TouchType::UP) {
        if (bubbleFlag_) {
            bubbleFlag_ = false;
        }
        mousePressedFlag_ = false;
        FireChangeEvent(SliderChangeMode::Click);
        FireChangeEvent(SliderChangeMode::End);
        CloseTranslateAnimation();
    }
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::InitializeBubble()
{
    CHECK_NULL_VOID(showTips_);
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
}

void SliderPattern::HandlingGestureStart(const GestureEvent& info)
{
    if (info.GetInputEventType() != InputEventType::AXIS) {
        UpdateValueByLocalLocation(info.GetLocalLocation());
        UpdateBubble();
    }
    panMoveFlag_ = true;
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandlingGestureEvent(const GestureEvent& info)
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (info.GetInputEventType() == InputEventType::AXIS) {
        auto offset = NearZero(info.GetOffsetX()) ? info.GetOffsetY() : info.GetOffsetX();
        // offset > 0 when Wheel Up, offset < 0 when Wheel Down
        if (direction_ == Axis::HORIZONTAL) {
            offset > 0.0 ? MoveStep(1) : MoveStep(-1);
        } else {
            auto reverse = paintProperty->GetReverseValue(false);
            reverse ? (offset > 0.0 ? MoveStep(1) : MoveStep(-1)) : (offset > 0.0 ? MoveStep(-1) : MoveStep(1));
        }
        if (hotFlag_) {
            // Only when the mouse hovers over the slider, axisFlag_ can be set true
            axisFlag_ = true;
        }
        if (showTips_ && axisFlag_) {
            bubbleFlag_ = true;
            InitializeBubble();
        }
    } else {
        UpdateValueByLocalLocation(info.GetLocalLocation());
        UpdateBubble();
    }
    panMoveFlag_ = true;
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandledGestureEvent()
{
    panMoveFlag_ = false;

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
    CHECK_NULL_VOID(sliderPaintProperty);
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentOffset = content->GetRect().GetOffset();
    float length = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? static_cast<float>(localLocation->GetX() - contentOffset.GetX())
                       : static_cast<float>(localLocation->GetY() - contentOffset.GetY());
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
    sliderPaintProperty->UpdateValue(value_);
    valueChangeFlag_ = !NearEqual(oldValue, value_);
    UpdateCircleCenterOffset();
}

void SliderPattern::UpdateTipsValue()
{
    CHECK_NULL_VOID(valueChangeFlag_);
    CHECK_NULL_VOID(showTips_);
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

void SliderPattern::UpdateBubble()
{
    CHECK_NULL_VOID(bubbleFlag_);
    // update the tip value according to the slider value, update the tip position according to current block position
    UpdateTipsValue();
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
        CHECK_NULL_VOID(pattern);
        pattern->HandlingGestureStart(info);
        pattern->OpenTranslateAnimation();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlingGestureEvent(info);
        pattern->FireChangeEvent(SliderChangeMode::Moving);
        pattern->OpenTranslateAnimation();
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandledGestureEvent();
        pattern->CloseTranslateAnimation();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandledGestureEvent();
        pattern->FireChangeEvent(SliderChangeMode::End);
        pattern->axisFlag_ = false;
        pattern->CloseTranslateAnimation();
    };
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));

    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void SliderPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto onBlur = [wp = WeakClaim(this)]() {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->bubbleFlag_ = false;
        pattern->focusFlag_ = false;
        pattern->UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
    focusHub->SetOnBlurInternal(std::move(onBlur));
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
    auto appTheme = PipelineBase::GetCurrentContext()->GetTheme<AppTheme>();
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusSideDistance = theme->GetFocusSideDistance();
    auto focusDistance = paintWidth * HALF + focusSideDistance;
    auto halfWidth = blockSize_.Width() * HALF + static_cast<float>(focusDistance.ConvertToPx());
    auto halfHeight = blockSize_.Height() * HALF + static_cast<float>(focusDistance.ConvertToPx());
    paintRect.SetRect(RectF(circleCenter_.GetX() - halfWidth + contentOffset.GetX(),
        circleCenter_.GetY() - halfHeight + contentOffset.GetY(), halfWidth / HALF, halfHeight / HALF));
    paintRect.SetCornerRadius(focusDistance.ConvertToPx());
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto blockType = paintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT);
    if (blockType == SliderModelNG::BlockStyleType::DEFAULT) {
        auto focusRadius =
            std::min(blockSize_.Width(), blockSize_.Height()) * HALF + static_cast<float>(focusDistance.ConvertToPx());
        paintRect.SetRect(RectF(circleCenter_.GetX() - focusRadius + contentOffset.GetX(),
            circleCenter_.GetY() - focusRadius + contentOffset.GetY(), focusRadius / HALF, focusRadius / HALF));
        paintRect.SetCornerRadius(focusRadius);
    } else if (blockType == SliderModelNG::BlockStyleType::SHAPE) {
        auto shape = paintProperty->GetBlockShape();
        if (shape.has_value() && shape.value()->GetBasicShapeType() == BasicShapeType::CIRCLE) {
            auto circle = DynamicCast<Circle>(shape.value());
            CHECK_NULL_VOID(circle);
            float focusRadius;
            if (circle->GetRadius().IsValid()) {
                focusRadius = circle->GetRadius().ConvertToPx() + focusDistance.ConvertToPx();
            } else {
                focusRadius = std::min(circle->GetWidth().ConvertToPx(), circle->GetHeight().ConvertToPx()) * HALF +
                              focusDistance.ConvertToPx();
            }
            paintRect.SetRect(RectF(circleCenter_.GetX() - focusRadius + contentOffset.GetX(),
                circleCenter_.GetY() - focusRadius + contentOffset.GetY(), focusRadius / HALF, focusRadius / HALF));
            paintRect.SetCornerRadius(focusRadius);
        }
    }
}

void SliderPattern::GetInsetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    const auto& content = frameNode->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto focusSideDistance = theme->GetFocusSideDistance();
    auto appTheme = PipelineBase::GetCurrentContext()->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusDistance = paintWidth * HALF + focusSideDistance;
    // use content area
    float offsetX = content->GetRect().GetX();
    float offsetY = content->GetRect().GetY();
    float width = content->GetRect().Width();
    float height = content->GetRect().Height();
    float focusRadius = trackThickness_ * HALF + static_cast<float>(focusDistance.ConvertToPx());
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    if (paintProperty && paintProperty->GetTrackBorderRadius().has_value()) {
        focusRadius = static_cast<float>(paintProperty->GetTrackBorderRadius().value().ConvertToPx()) +
                      static_cast<float>(focusDistance.ConvertToPx());
    }
    if (direction_ == Axis::HORIZONTAL) {
        offsetX += borderBlank_ - trackThickness_ * HALF - static_cast<float>(focusDistance.ConvertToPx());
        offsetY += (height - trackThickness_) * HALF - static_cast<float>(focusDistance.ConvertToPx());
        width = sliderLength_ + trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        height = trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
    } else {
        offsetX += (width - trackThickness_) * HALF - static_cast<float>(focusDistance.ConvertToPx());
        offsetY += borderBlank_ - trackThickness_ * HALF - static_cast<float>(focusDistance.ConvertToPx());
        width = trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        height = sliderLength_ + trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
    }
    paintRect.SetRect(RectF(offsetX, offsetY, width, height));
    paintRect.SetCornerRadius(focusRadius);
}

void SliderPattern::PaintFocusState()
{
    focusFlag_ = true;
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
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto reverse = paintProperty->GetReverseValue(false);
    if (event.action == KeyAction::DOWN) {
        if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT) ||
            (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
            reverse ? MoveStep(1) : MoveStep(-1);
            if (showTips_) {
                InitializeBubble();
            }
            PaintFocusState();
            return true;
        }
        if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT) ||
            (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
            reverse ? MoveStep(-1) : MoveStep(1);
            if (showTips_) {
                InitializeBubble();
            }
            PaintFocusState();
            return true;
        }
    } else if (event.action == KeyAction::UP) {
        if (showTips_) {
            bubbleFlag_ = true;
            InitializeBubble();
        }
        PaintFocusState();
    }
    return false;
}

bool SliderPattern::MoveStep(int32_t stepCount)
{
    // stepCount > 0, slider value increases, block moves in the direction of growth
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
    sliderPaintProperty->UpdateValue(value_);
    valueRatio_ = (value_ - min) / (max - min);
    FireChangeEvent(SliderChangeMode::Begin);
    FireChangeEvent(SliderChangeMode::End);
    LOGD("Move %{public}d steps, Value change to %{public}f", stepCount, value_);
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

void SliderPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputEventHub)
{
    auto hoverEvent = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleHoverEvent(isHover);
    };
    if (hoverEvent_) {
        inputEventHub->RemoveOnHoverEvent(hoverEvent_);
    }
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverEvent));
    inputEventHub->AddOnHoverEvent(hoverEvent_);

    auto mouseEvent = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
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
    hotFlag_ = isHover;
    mouseHoverFlag_ = mouseHoverFlag_ && isHover;
    if (!mouseHoverFlag_) {
        bubbleFlag_ = false;
        axisFlag_ = false;
    }
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandleMouseEvent(const MouseInfo& info)
{
    UpdateCircleCenterOffset();
    // MouseInfo's LocalLocation is relative to the frame area, circleCenter_ is relative to the content area
    mouseHoverFlag_ = AtMousePanArea(info.GetLocalLocation());
    if (mouseHoverFlag_) {
        if (showTips_) {
            bubbleFlag_ = true;
            InitializeBubble();
        }
    }
    // when mouse hovers over slider, distinguish between hover block and Wheel operation.
    if (!mouseHoverFlag_ && !axisFlag_) {
        bubbleFlag_ = false;
    }

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

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (mode == SliderChangeMode::Begin) {
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
    } else if (mode == SliderChangeMode::End) {
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    }
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

SliderContentModifier::Parameters SliderPattern::UpdateContentParameters()
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, SliderContentModifier::Parameters());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, SliderContentModifier::Parameters());
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, SliderContentModifier::Parameters());
    SliderContentModifier::Parameters parameters { trackThickness_, blockSize_, stepRatio_, hotBlockShadowWidth_,
        mouseHoverFlag_, mousePressedFlag_ };
    auto contentSize = GetHostContentSize();
    CHECK_NULL_RETURN(contentSize, SliderContentModifier::Parameters());
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, SliderContentModifier::Parameters());
    auto contentOffset = content->GetRect().GetOffset();
    // Distance between slide track and Content boundary
    auto centerWidth = direction_ == Axis::HORIZONTAL ? contentSize->Height() : contentSize->Width();
    centerWidth *= HALF;
    parameters.selectColor = paintProperty->GetSelectColor().value_or(theme->GetTrackSelectedColor());
    parameters.trackBackgroundColor = paintProperty->GetTrackBackgroundColor().value_or(theme->GetTrackBgColor());
    parameters.blockColor = paintProperty->GetBlockColor().value_or(theme->GetBlockColor());

    GetSelectPosition(parameters, centerWidth, contentOffset);
    GetBackgroundPosition(parameters, centerWidth, contentOffset);
    GetCirclePosition(parameters, centerWidth, contentOffset);
    UpdateCircleCenterOffset();
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

void SliderPattern::UpdateBlock()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);

    if (sliderPaintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT) ==
        SliderModelNG::BlockStyleType::IMAGE) {
        if (imageFrameNode_ == nullptr) {
            auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
            imageFrameNode_ =
                FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
            imageFrameNode_->MountToParent(host);
        }
        if (imageFrameNode_ != nullptr) {
            auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(imageFrameNode_->GetLayoutProperty());
            imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(sliderPaintProperty->GetBlockImage().value()));
            imageLayoutProperty->UpdateImageFit(ImageFit::COVER);
            imageLayoutProperty->UpdateAutoResize(true);
            imageFrameNode_->MarkModifyDone();
        }
    } else {
        if (imageFrameNode_ != nullptr) {
            host->RemoveChild(imageFrameNode_);
            imageFrameNode_ = nullptr;
        }
    }
}

std::string SliderPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, "");
    jsonObj->Put("value", sliderPaintProperty->GetValue().value_or(0.0f));
    return jsonObj->ToString();
}

void SliderPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonValue = info->GetValue("value");
    sliderPaintProperty->UpdateValue(jsonValue->GetDouble());
    OnModifyDone();
}

void SliderPattern::LayoutImageNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
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

OffsetF SliderPattern::GetBubbleVertexPosition(const OffsetF& blockCenter, float trackThickness, const SizeF& blockSize)
{
    OffsetF bubbleVertex = blockCenter;
    auto sliderLayoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, bubbleVertex);
    auto sliderMode = sliderLayoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        if (direction_ == Axis::HORIZONTAL) {
            bubbleVertex.AddY(0 - blockSize.Height() * HALF - BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
        } else {
            bubbleVertex.AddX(0 - blockSize.Width() * HALF - BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
        }
    } else {
        if (direction_ == Axis::HORIZONTAL) {
            bubbleVertex.AddY(0 - trackThickness * HALF - BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
        } else {
            bubbleVertex.AddX(0 - trackThickness * HALF - BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
        }
    }
    return bubbleVertex;
}

void SliderPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->MoveStep(1);

        if (pattern->showTips_) {
            pattern->bubbleFlag_ = true;
            pattern->InitializeBubble();
        }
        pattern->PaintFocusState();
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->MoveStep(-1);

        if (pattern->showTips_) {
            pattern->bubbleFlag_ = true;
            pattern->InitializeBubble();
        }
        pattern->PaintFocusState();
    });
}

void SliderPattern::UpdateValue(float value)
{
    if (panMoveFlag_) {
        return;
    }
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateValue(value);
}

void SliderPattern::OnAttachToFrameNode()
{
    RegisterVisibleAreaChange();
}

void SliderPattern::OnVisibleChange(bool isVisible)
{
    isVisible_ = isVisible;
    LOGD("Slider OnVisibleChange: isVisible = %d", isVisible_);
    isVisible_ ? StartAnimation() : StopAnimation();
}

void SliderPattern::StartAnimation()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    LOGD("Slider StartAnimation: isVisibleArea_ = %d, isVisible_ = %d, isShow_ = %d", isVisibleArea_, isVisible_,
        isShow_);
    if (sliderContentModifier_->GetVisible()) {
        return;
    }
    if (IsSliderVisible()) {
        sliderContentModifier_->SetVisible(true);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SliderPattern::StopAnimation()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    if (!sliderContentModifier_->GetVisible()) {
        return;
    }
    LOGD("Slider StopAnimation");
    sliderContentModifier_->SetVisible(false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::RegisterVisibleAreaChange()
{
    if (hasVisibleChangeRegistered_) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        LOGD("Slider VisibleAreaChange CallBack: visible = %d", visible);
        pattern->isVisibleArea_  = visible;
        visible ? pattern->StartAnimation() : pattern->StopAnimation();
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback);

    pipeline->AddWindowStateChangedCallback(host->GetId());
    hasVisibleChangeRegistered_ = true;
}

void SliderPattern::OnWindowHide()
{
    isShow_ = false;
    LOGD("Slider OnWindowHide");
    StopAnimation();
}

void SliderPattern::OnWindowShow()
{
    isShow_ = true;
    LOGD("Slider OnWindowShow");
    StartAnimation();
}

bool SliderPattern::IsSliderVisible()
{
    return isVisibleArea_ && isVisible_ && isShow_;
}
} // namespace OHOS::Ace::NG
