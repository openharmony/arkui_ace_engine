/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_DRAG_MIN_DISTANCE = 4.0_vp;
constexpr Dimension INDICATOR_DRAG_MAX_DISTANCE = 18.0_vp;
constexpr Dimension INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE = 80.0_vp;
constexpr Dimension INDICATOR_BORDER_RADIUS = 16.0_vp;
constexpr float DEFAULT_COUNT = 2.0f;
} // namespace

IndicatorPattern::IndicatorPattern()
{
    indicatorController_ = MakeRefPtr<IndicatorController>();
}

void IndicatorPattern::SetSwiperDigitalParameters(const SwiperDigitalParameters& swiperDigitalParameters)
{
    swiperDigitalParameters_ = std::make_shared<SwiperDigitalParameters>(swiperDigitalParameters);
}

SwiperIndicatorType IndicatorPattern::GetIndicatorTypeFromProperty() const
{
    auto swiperIndicatorLayoutProperty = GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(swiperIndicatorLayoutProperty, SwiperIndicatorType::DOT);
    return swiperIndicatorLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::DOT);
}

int32_t IndicatorPattern::GetInitialIndexFromProperty() const
{
    auto swiperIndicatorLayoutProperty = GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(swiperIndicatorLayoutProperty, 0);
    return swiperIndicatorLayoutProperty->GetInitialIndex().value_or(0);
}

Axis IndicatorPattern::GetDirectionFromProperty() const
{
    auto swiperIndicatorLayoutProperty = GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(swiperIndicatorLayoutProperty, Axis::HORIZONTAL);
    return swiperIndicatorLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
}

int32_t IndicatorPattern::GetCountFromProperty() const
{
    auto swiperIndicatorLayoutProperty = GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(swiperIndicatorLayoutProperty, DEFAULT_COUNT);
    return swiperIndicatorLayoutProperty->GetCount().value_or(DEFAULT_COUNT);
}

bool IndicatorPattern::IsLoopFromProperty() const
{
    auto swiperIndicatorLayoutProperty = GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(swiperIndicatorLayoutProperty, true);
    return swiperIndicatorLayoutProperty->GetLoop().value_or(true);
}

void IndicatorPattern::FireChangeEvent() const
{
    auto indicatorEventHub = GetOrCreateEventHub<IndicatorEventHub>();
    CHECK_NULL_VOID(indicatorEventHub);
    indicatorEventHub->FireChangeEvent(GetLoopIndex(GetCurrentIndex()));
}

void IndicatorPattern::FireIndicatorIndexChangeEvent(int32_t index) const
{
    auto indicatorEventHub = GetOrCreateEventHub<IndicatorEventHub>();
    CHECK_NULL_VOID(indicatorEventHub);
    indicatorEventHub->FireChangeEvent(GetLoopIndex(index));
}

std::shared_ptr<SwiperParameters> IndicatorPattern::GetSwiperParameters()
{
    if (swiperParameters_ == nullptr) {
        swiperParameters_ = std::make_shared<SwiperParameters>();
        auto pipelineContext = GetContext();
        CHECK_NULL_RETURN(pipelineContext, swiperParameters_);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperIndicatorTheme, swiperParameters_);
        swiperParameters_->itemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->itemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters_->selectedItemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters_->maskValue = false;
        swiperParameters_->colorVal = swiperIndicatorTheme->GetColor();
        swiperParameters_->selectedColorVal = swiperIndicatorTheme->GetSelectedColor();
        swiperParameters_->dimSpace = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    }
    return swiperParameters_;
}

std::shared_ptr<SwiperDigitalParameters> IndicatorPattern::GetSwiperDigitalParameters()
{
    if (swiperDigitalParameters_ == nullptr) {
        swiperDigitalParameters_ = std::make_shared<SwiperDigitalParameters>();
        auto pipelineContext = GetContext();
        CHECK_NULL_RETURN(pipelineContext, swiperDigitalParameters_);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        swiperDigitalParameters_->fontColor = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
        swiperDigitalParameters_->selectedFontColor =
            swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
        swiperDigitalParameters_->fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        swiperDigitalParameters_->selectedFontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        swiperDigitalParameters_->fontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        swiperDigitalParameters_->selectedFontWeight =
            swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
    }
    return swiperDigitalParameters_;
}

void IndicatorPattern::SaveDigitIndicatorProperty()
{
    auto indicatorNode = GetHost();
    CHECK_NULL_VOID(indicatorNode);
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = indicatorNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    auto swiperDigitalParameters = GetSwiperDigitalParameters();
    CHECK_NULL_VOID(swiperDigitalParameters);
    layoutProperty->ResetIndicatorLayoutStyle();
    if (swiperDigitalParameters->dimLeft.has_value()) {
        layoutProperty->UpdateLeft(swiperDigitalParameters->dimLeft.value());
    }
    if (swiperDigitalParameters->dimTop.has_value()) {
        layoutProperty->UpdateTop(swiperDigitalParameters->dimTop.value());
    }
    if (swiperDigitalParameters->dimRight.has_value()) {
        layoutProperty->UpdateRight(swiperDigitalParameters->dimRight.value());
    }
    if (swiperDigitalParameters->dimBottom.has_value()) {
        layoutProperty->UpdateBottom(swiperDigitalParameters->dimBottom.value());
    }
    layoutProperty->UpdateFontColor(swiperDigitalParameters->fontColor.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor()));
    layoutProperty->UpdateSelectedFontColor(swiperDigitalParameters->selectedFontColor.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor()));
    layoutProperty->UpdateFontSize(
        swiperDigitalParameters->fontSize.value_or(swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize()));
    layoutProperty->UpdateSelectedFontSize(swiperDigitalParameters->selectedFontSize.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize()));
    layoutProperty->UpdateFontWeight(swiperDigitalParameters->fontWeight.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    layoutProperty->UpdateSelectedFontWeight(swiperDigitalParameters->selectedFontWeight.value_or(
        swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    ResetDotModifier();
}

void IndicatorPattern::SaveDotIndicatorProperty()
{
    auto indicatorNode = GetHost();
    CHECK_NULL_VOID(indicatorNode);
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto swiperParameters = GetSwiperParameters();
    CHECK_NULL_VOID(swiperParameters);
    layoutProperty->ResetIndicatorLayoutStyle();
    if (swiperParameters->dimLeft.has_value()) {
        layoutProperty->UpdateLeft(swiperParameters->dimLeft.value());
    }
    if (swiperParameters->dimTop.has_value()) {
        layoutProperty->UpdateTop(swiperParameters->dimTop.value());
    }
    if (swiperParameters->dimRight.has_value()) {
        layoutProperty->UpdateRight(swiperParameters->dimRight.value());
    }
    if (swiperParameters->dimBottom.has_value()) {
        layoutProperty->UpdateBottom(swiperParameters->dimBottom.value());
    }

    bool isRtl = GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (swiperParameters->dimStart.has_value()) {
        auto dimValue = swiperParameters->dimStart.value();
        isRtl ? layoutProperty->UpdateRight(dimValue) : layoutProperty->UpdateLeft(dimValue);
    }
    if (swiperParameters->dimEnd.has_value()) {
        auto dimValue = swiperParameters->dimEnd.value();
        isRtl ? layoutProperty->UpdateLeft(dimValue) : layoutProperty->UpdateRight(dimValue);
    }
    if (swiperParameters->dimSpace.has_value()) {
        layoutProperty->UpdateSpace(swiperParameters->dimSpace.value());
    }
    UpdatePaintProperty();
}

void IndicatorPattern::UpdatePaintProperty()
{
    auto indicatorNode = GetHost();
    CHECK_NULL_VOID(indicatorNode);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = indicatorNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto swiperParameters = GetSwiperParameters();
    CHECK_NULL_VOID(swiperParameters);
    paintProperty->UpdateItemWidth(swiperParameters->itemWidth.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateItemHeight(swiperParameters->itemHeight.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateSelectedItemWidth(
        swiperParameters->selectedItemWidth.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateSelectedItemHeight(
        swiperParameters->selectedItemHeight.value_or(swiperIndicatorTheme->GetSize()));
    paintProperty->UpdateIndicatorMask(swiperParameters->maskValue.value_or(false));
    paintProperty->UpdateColor(swiperParameters->colorVal.value_or(swiperIndicatorTheme->GetColor()));
    paintProperty->UpdateSelectedColor(
        swiperParameters->selectedColorVal.value_or(swiperIndicatorTheme->GetSelectedColor()));
    paintProperty->UpdateIsCustomSize(isCustomSize_);
    paintProperty->UpdateSpace(swiperParameters->dimSpace.value_or(swiperIndicatorTheme->GetIndicatorDotItemSpace()));
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void IndicatorPattern::OnModifyDone()
{
    if (!hasSetInitialIndex_) {
        hasSetInitialIndex_ = true;
        auto initialIndex = GetInitialIndexFromProperty();
        if ((initialIndex < 0) || (initialIndex >= RealTotalCount())) {
            initialIndex = 0;
        }
        currentIndexInSingleMode_ = initialIndex;
    }
    if (currentIndexInSingleMode_ > RealTotalCount() - 1) {
        currentIndexInSingleMode_ = 0;
    }
    auto indicatorNode = GetHost();
    CHECK_NULL_VOID(indicatorNode);
    if (GetIndicatorType() == SwiperIndicatorType::DOT) {
        SaveDotIndicatorProperty();
    } else {
        SaveDigitIndicatorProperty();
    }

    auto renderContext = indicatorNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty radius;
    auto commonRadiusValue = renderContext->GetBorderRadius();
    if (commonRadiusValue.has_value()) {
        radius.UpdateWithCheck(commonRadiusValue.value());
    } else {
        radius.SetRadius(INDICATOR_BORDER_RADIUS);
    }
    renderContext->UpdateBorderRadius(radius);
    auto focusHub = indicatorNode->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
    SwiperIndicatorPattern::OnModifyDone();
}

void IndicatorPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool IndicatorPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((GetDirection() == Axis::HORIZONTAL &&
            event.code == (IsHorizontalAndRightToLeft() ? KeyCode::KEY_DPAD_RIGHT : KeyCode::KEY_DPAD_LEFT)) ||
        (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
        ShowPrevious();
        return true;
    }
    if ((GetDirection() == Axis::HORIZONTAL &&
            event.code == (IsHorizontalAndRightToLeft() ? KeyCode::KEY_DPAD_LEFT : KeyCode::KEY_DPAD_RIGHT)) ||
        (GetDirection() == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
        ShowNext();
        return true;
    }
    return false;
}

bool IndicatorPattern::GetDotCurrentOffset(OffsetF& offset, float indicatorWidth, float indicatorHeight)
{
    return false;
}

bool IndicatorPattern::GetDigitFrameSize(RefPtr<GeometryNode>& geoNode, SizeF& frameSize) const
{
    CHECK_NULL_RETURN(geoNode, false);
    frameSize = geoNode->GetFrameSize();
    return true;
}

void IndicatorPattern::OnIndexChangeInSingleMode(int32_t index)
{
    if (!IsLoop() || IsHover() || IsPressed()) {
        singleIndicatorTouchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
        if (index >= RealTotalCount()) {
            SetCurrentIndexInSingleMode(RealTotalCount() - 1);
            return;
        } else if (index < 0) {
            SetCurrentIndexInSingleMode(0);
            return;
        }
    }
    SetCurrentIndexInSingleMode(GetLoopIndex(index));
    FireChangeEvent();
    SwiperIndicatorPattern::IndicatorOnChange();
}

void IndicatorPattern::ShowPrevious()
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::ShowPrevious();
    }

    singleIndicatorTouchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    if (IsHorizontalAndRightToLeft()) {
        singleGestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
        if (IsLoop() && GetCurrentIndex() == 0) {
            singleIndicatorTouchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
        }
    } else {
        singleGestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
        if (IsLoop() && GetCurrentIndex() == 0) {
            singleIndicatorTouchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
        }
    }
    auto dotIndicatorModifier = GetDotIndicatorModifier();
    if (dotIndicatorModifier && !dotIndicatorModifier->GetIsBottomAnimationFinished()) {
        dotIndicatorModifier->FinishAnimationToTargetImmediately(dotIndicatorModifier->GetTargetCenter());
    }
    lastIndex_ = GetCurrentIndex();
    OnIndexChangeInSingleMode(GetCurrentIndex() - 1);
}

void IndicatorPattern::ShowNext()
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::ShowNext();
    }
    singleIndicatorTouchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    if (IsHorizontalAndRightToLeft()) {
        singleGestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
        if (IsLoop() && GetCurrentIndex() == (RealTotalCount() - 1)) {
            singleIndicatorTouchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
        }
    } else {
        singleGestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
        if (IsLoop() && GetCurrentIndex() == (RealTotalCount() - 1)) {
            singleIndicatorTouchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
        }
    }
    auto dotIndicatorModifier = GetDotIndicatorModifier();
    if (dotIndicatorModifier && !dotIndicatorModifier->GetIsBottomAnimationFinished()) {
        dotIndicatorModifier->FinishAnimationToTargetImmediately(dotIndicatorModifier->GetTargetCenter());
    }
    lastIndex_ = GetCurrentIndex();
    OnIndexChangeInSingleMode(GetCurrentIndex() + 1);
}

void IndicatorPattern::ChangeIndex(int32_t index, bool useAnimation)
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::ChangeIndex(index, useAnimation);
    }
    if ((index < 0) || (index >= RealTotalCount())) {
        index = 0;
    }

    if (useAnimation) {
        if (GetLoopIndex(GetCurrentIndex()) > GetLoopIndex(index)) {
            singleGestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
        } else if (GetLoopIndex(GetCurrentIndex()) < GetLoopIndex(index)) {
            singleGestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
        }
    } else {
        singleGestureState_ = GestureState::GESTURE_STATE_INIT;
    }
    auto dotIndicatorModifier = GetDotIndicatorModifier();
    if (dotIndicatorModifier) {
        dotIndicatorModifier->StopAnimation();
    }
    OnIndexChangeInSingleMode(index);
}

int32_t IndicatorPattern::GetCurrentIndex() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::GetCurrentIndex();
    }
    return currentIndexInSingleMode_;
}

int32_t IndicatorPattern::GetCurrentShownIndex() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::GetCurrentShownIndex();
    }
    return currentIndexInSingleMode_;
}

int32_t IndicatorPattern::DisplayIndicatorTotalCount() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::DisplayIndicatorTotalCount();
    }
    return GetCountFromProperty();
}

int32_t IndicatorPattern::RealTotalCount() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::RealTotalCount();
    }
    return GetCountFromProperty();
}

Axis IndicatorPattern::GetDirection() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::GetDirection();
    }
    return GetDirectionFromProperty();
}

bool IndicatorPattern::IsHorizontalAndRightToLeft() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::IsHorizontalAndRightToLeft();
    }
    return GetDirection() == Axis::HORIZONTAL && GetNonAutoLayoutDirection() == TextDirection::RTL;
}

TextDirection IndicatorPattern::GetNonAutoLayoutDirection() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::GetNonAutoLayoutDirection();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, TextDirection::LTR);
    CHECK_NULL_RETURN(host->GetLayoutProperty(), TextDirection::LTR);
    return host->GetLayoutProperty()->GetNonAutoLayoutDirection();
}

bool IndicatorPattern::IsLoop() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::IsLoop();
    }
    return IsLoopFromProperty();
}

void IndicatorPattern::GetTextContentSub(std::string& firstContent, std::string& lastContent) const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::GetTextContentSub(firstContent, lastContent);
    }
    // If the mode is set to single mode, the initial information is taken from the Indicator component
    // interface.
    auto currentIndex = GetLoopIndex(GetCurrentIndex()) + 1;
    bool isRtl = GetNonAutoLayoutDirection() == TextDirection::RTL;
    firstContent = isRtl ? std::to_string(GetCountFromProperty()) : std::to_string(currentIndex);
    lastContent = isRtl ? std::to_string(currentIndex) + "\\" : "/" + std::to_string(GetCountFromProperty());
}

void IndicatorPattern::SwipeTo(std::optional<int32_t> mouseClickIndex)
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::SwipeTo(mouseClickIndex);
    }
    if (mouseClickIndex) {
        OnIndexChangeInSingleMode(mouseClickIndex.value());
    }
}

bool IndicatorPattern::CheckIsTouchBottom(const TouchLocationInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto currentIndex = GetCurrentIndex();
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    float touchBottomRate = 0.0;
    float touchOffset = 0.0;
    auto offset = dragPoint - GetDragStartPoint();
    touchOffset = GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    touchBottomRate = LessOrEqual(std::abs(touchOffset), INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx())
                            ? touchOffset / INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx() : 1;
    touchBottomRate_ = std::abs(touchBottomRate);
    TouchBottomType touchBottomType = TouchBottomType::NONE;
    if (currentIndex <= 0) {
        if (IsHorizontalAndRightToLeft()) {
            if (Positive(touchOffset)) {
                touchBottomType = TouchBottomType::END;
            }
        } else {
            if (NonPositive(touchOffset)) {
                touchBottomType = TouchBottomType::START;
            }
        }
    }
    if (currentIndex >= RealTotalCount() - 1) {
        if (IsHorizontalAndRightToLeft()) {
            if (NonPositive(touchOffset)) {
                touchBottomType = TouchBottomType::START;
            }
        } else {
            if (Positive(touchOffset)) {
                touchBottomType = TouchBottomType::END;
            }
        }
    }
    SetTouchBottomType(touchBottomType);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return touchBottomType == TouchBottomType::NONE ? false : true;
}

void IndicatorPattern::HandleDragEnd(double dragVelocity)
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::HandleDragEnd(dragVelocity);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    SetTouchBottomType(TouchBottomType::NONE);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

RectF IndicatorPattern::CalcBoundsRect() const
{
    RectF boundsRect;
    if (GetDotIndicatorModifier()) {
        boundsRect = GetDotIndicatorModifier()->GetBoundsRect();
    }
    return boundsRect;
}

void IndicatorPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    SwiperIndicatorPattern::InitTouchEvent(gestureHub);
    auto stopAnimationCb = [weak = WeakClaim(this)](bool ifImmediately) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (pattern->GetDotIndicatorModifier()) {
                pattern->GetDotIndicatorModifier()->StopAnimation(ifImmediately);
            }
            if (pattern->GetOverlengthDotIndicatorModifier()) {
                pattern->GetOverlengthDotIndicatorModifier()->StopAnimation(ifImmediately);
            }
        }
    };
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetStopIndicatorAnimationCb(stopAnimationCb);
}

void IndicatorPattern::HandleLongDragUpdate(const TouchLocationInfo& info)
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::HandleLongDragUpdate(info);
    }
    if (CheckIsTouchBottom(info)) {
        return;
    }
    float turnPageRate = 0.0;
    float turnPageRateOffset = 0.0;
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));

    auto offset = dragPoint - GetDragStartPoint();
    turnPageRateOffset = GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    if (LessNotEqual(std::abs(turnPageRateOffset), INDICATOR_DRAG_MIN_DISTANCE.ConvertToPx())) {
        return;
    }
    turnPageRate = -(turnPageRateOffset / INDICATOR_DRAG_MAX_DISTANCE.ConvertToPx());
    if (IsHorizontalAndRightToLeft()) {
        turnPageRateOffset = -turnPageRateOffset;
    }
    if (std::abs(turnPageRate) >= 1) {
        if (Positive(turnPageRateOffset)) {
            ShowNext();
        }
        if (NonPositive(turnPageRateOffset)) {
            ShowPrevious();
        }
        SetDragStartPoint(dragPoint);
    }
}

int32_t IndicatorPattern::GetTouchCurrentIndex() const
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::GetTouchCurrentIndex();
    }

    auto currentIndex = GetCurrentIndex();
    auto isRtl = IsHorizontalAndRightToLeft();
    if (isRtl) {
        currentIndex = RealTotalCount() - 1 - currentIndex;
    }

    return currentIndex;
}

std::pair<int32_t, int32_t> IndicatorPattern::CalMouseClickIndexStartAndEnd(
    int32_t itemCount, int32_t currentIndex)
{
    if (GetBindSwiperNode()) {
        return SwiperIndicatorPattern::CalMouseClickIndexStartAndEnd(itemCount, currentIndex);
    }

    int32_t loopCount = SwiperIndicatorUtils::CalcLoopCount(currentIndex, itemCount);
    int32_t start = currentIndex >= 0 ? loopCount * itemCount : -(loopCount + 1) * itemCount;
    int32_t end = currentIndex >= 0 ? (loopCount + 1) * itemCount : -loopCount * itemCount;
    if (IsHorizontalAndRightToLeft()) {
        end = currentIndex >= 0 ? loopCount * itemCount - 1 : -(loopCount + 1) * itemCount - 1;
        start = currentIndex >= 0 ? (loopCount + 1) * itemCount - 1 : -loopCount * itemCount - 1;
    }
    return { start, end };
}
} // namespace OHOS::Ace::NG
