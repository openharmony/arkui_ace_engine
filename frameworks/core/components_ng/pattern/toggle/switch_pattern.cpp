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

#include "core/components_ng/pattern/toggle/switch_pattern.h"

#include <cmath>
#include <cstdint>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/common/container.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/toggle/switch_layout_algorithm.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
void SwitchPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
}

bool SwitchPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    if (isOn_.value()) {
        currentOffset_ = GetSwitchWidth();
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto switchLayoutAlgorithm = DynamicCast<SwitchLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(switchLayoutAlgorithm, false);

    auto height = switchLayoutAlgorithm->GetHeight();
    auto width = switchLayoutAlgorithm->GetWidth();

    width_ = width;
    height_ = height;
    return true;
}

void SwitchPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetMarginProperty()) {
        MarginProperty margin;
        margin.left = CalcLength(switchTheme->GetHotZoneHorizontalPadding());
        margin.right = CalcLength(switchTheme->GetHotZoneHorizontalPadding());
        margin.top = CalcLength(switchTheme->GetHotZoneVerticalPadding());
        margin.bottom = CalcLength(switchTheme->GetHotZoneVerticalPadding());
        layoutProperty->UpdateMargin(margin);
    }
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }
    auto switchPaintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(switchPaintProperty);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    if (!isOn_.has_value() || (isOn_.has_value() && NearZero(geometryNode->GetContentSize().Width()) &&
                                  NearZero(geometryNode->GetContentSize().Height()))) {
        isOn_ = switchPaintProperty->GetIsOnValue();
    }
    auto isOn = switchPaintProperty->GetIsOnValue();
    if (isOn != isOn_.value()) {
        OnChange();
    }
    InitClickEvent();
    InitPanEvent(gestureHub);
    InitTouchEvent();
    InitMouseEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
}

void SwitchPattern::UpdateCurrentOffset(float offset)
{
    currentOffset_ = currentOffset_ + offset;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::PlayTranslateAnimation(float startPos, float endPos)
{
    LOGI("Play translate animation startPos: %{public}lf, endPos: %{public}lf", startPos, endPos);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto curve = GetCurve();
    if (!curve) {
        curve = Curves::LINEAR;
    }

    // If animation is still running, stop it before play new animation.
    StopTranslateAnimation();

    auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(startPos, endPos, curve);
    auto weak = AceType::WeakClaim(this);
    translate->AddListener(Animation<double>::ValueCallback([weak, startPos, endPos](double value) {
        auto switchPattern = weak.Upgrade();
        CHECK_NULL_VOID(switchPattern);
        if (!NearEqual(value, startPos) && !NearEqual(value, endPos) && !NearEqual(startPos, endPos)) {
            float moveRate =
                Curves::EASE_OUT->MoveInternal(static_cast<float>((value - startPos) / (endPos - startPos)));
            value = startPos + (endPos - startPos) * moveRate;
        }
        switchPattern->UpdateCurrentOffset(static_cast<float>(value - switchPattern->currentOffset_));
    }));

    if (!controller_) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        controller_ = AceType::MakeRefPtr<Animator>(pipeline);
    }
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();
    controller_->AddStopListener([weak]() {
        auto switchPattern = weak.Upgrade();
        CHECK_NULL_VOID(switchPattern);
        if (!switchPattern->isOn_.value()) {
            if (NearEqual(switchPattern->currentOffset_, switchPattern->GetSwitchWidth()) &&
                switchPattern->changeFlag_) {
                switchPattern->isOn_ = true;
                switchPattern->UpdateChangeEvent();
            }
        } else {
            if (NearEqual(switchPattern->currentOffset_, 0) && switchPattern->changeFlag_) {
                switchPattern->isOn_ = false;
                switchPattern->UpdateChangeEvent();
            }
        }
    });
    controller_->SetDuration(GetDuration());
    controller_->AddInterpolator(translate);
    controller_->Play();
}

RefPtr<Curve> SwitchPattern::GetCurve() const
{
    auto switchPaintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(switchPaintProperty, nullptr);
    return switchPaintProperty->GetCurve().value_or(nullptr);
}

int32_t SwitchPattern::GetDuration() const
{
    const int32_t DEFAULT_DURATION = 250;
    auto switchPaintProperty = GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(switchPaintProperty, DEFAULT_DURATION);
    return switchPaintProperty->GetDuration().value_or(DEFAULT_DURATION);
}

void SwitchPattern::StopTranslateAnimation()
{
    if (controller_ && !controller_->IsStopped()) {
        controller_->Stop();
    }
}

void SwitchPattern::OnChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto translateOffset = GetSwitchWidth();
    StopTranslateAnimation();
    changeFlag_ = true;
    if (!isOn_.value()) {
        PlayTranslateAnimation(0, translateOffset);
    } else {
        PlayTranslateAnimation(translateOffset, 0);
    }
}

float SwitchPattern::GetSwitchWidth() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto switchWidth = geometryNode->GetContentSize().Width() - geometryNode->GetContentSize().Height();
    return switchWidth;
}

void SwitchPattern::UpdateChangeEvent() const
{
    auto switchEventHub = GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(switchEventHub);
    switchEventHub->UpdateChangeEvent(isOn_.value());
}

void SwitchPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (controller_ && !controller_->IsStopped()) {
        // Clear stop listener before stop, otherwise the previous swipe will be considered complete.
        controller_->ClearStopListeners();
        controller_->Stop();
    }
    OnChange();
}

void SwitchPattern::OnTouchDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = true;
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto originalPaintRect = renderContext->GetPaintRectWithoutTransform();
    auto frameSize = geometryNode->GetFrameSize();
    if (originalPaintRect.GetSize() == frameSize) {
        originalPaintRect = GetHotZoneRect(true);
    }
    renderContext->SyncGeometryProperties(originalPaintRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    auto frameSize = geometryNode->GetFrameSize();
    if (paintRect.GetSize() != frameSize && !isHover_) {
        paintRect = GetHotZoneRect(false);
    }
    renderContext->SyncGeometryProperties(paintRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGD("Pan event start");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragUpdate(info);
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGD("Pan event end mainVelocity: %{public}lf", info.GetMainVelocity());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleDragEnd();
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        LOGD("Pan event cancel");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragEnd();
    };

    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;

    float distance = static_cast<float>(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP).ConvertToPx());
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void SwitchPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto switchPattern = weak.Upgrade();
        CHECK_NULL_VOID(switchPattern);
        switchPattern->OnClick();
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void SwitchPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto switchPattern = weak.Upgrade();
        CHECK_NULL_VOID(switchPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            switchPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            switchPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void SwitchPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto eventHub = GetHost()->GetEventHub<SwitchEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleMouseEvent(isHover);
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent_);
}

void SwitchPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void SwitchPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto switchTheme = pipelineContext->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    auto focusPaintPadding = switchTheme->GetFocusPaintPadding().ConvertToPx();

    auto height = height_ + focusPaintPadding * 2;
    auto width = width_ + focusPaintPadding * 2;
    auto radio = height / 2.0;
    auto Rect = RectF(-focusPaintPadding, -focusPaintPadding, width, height);

    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, radio, radio);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, radio, radio);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, radio, radio);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, radio, radio);
    paintRect.SetRect(Rect);
}

void SwitchPattern::HandleMouseEvent(bool isHover)
{
    isHover_ = isHover;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isTouch_ = false;
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto originalPaintRect = renderContext->GetPaintRectWithoutTransform();
    auto frameSize = geometryNode->GetFrameSize();
    if (isHover_ && originalPaintRect.GetSize() == frameSize) {
        originalPaintRect = GetHotZoneRect(true);
    } else if (!isHover_ && originalPaintRect.GetSize() != frameSize) {
        originalPaintRect = GetHotZoneRect(false);
    }
    renderContext->SyncGeometryProperties(originalPaintRect);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwitchPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto isOutOfBoundary = IsOutOfBoundary(mainDelta + currentOffset_);
    if (isOutOfBoundary) {
        LOGD("Switch has reached boundary, can't drag any more.");
        return;
    }
    UpdateCurrentOffset(static_cast<float>(mainDelta));
}

void SwitchPattern::HandleDragEnd()
{
    LOGD("Drag end currentOffset: %{public}lf", currentOffset_);
    // Play translate animation.
    auto mainSize = GetSwitchWidth();
    if (std::abs(currentOffset_) >= mainSize / 2) {
        if (!isOn_.value()) {
            changeFlag_ = true;
            PlayTranslateAnimation(mainSize, mainSize);
        } else {
            changeFlag_ = false;
            PlayTranslateAnimation(currentOffset_, mainSize);
        }
    } else if (std::abs(currentOffset_) < mainSize / 2) {
        if (isOn_.value()) {
            changeFlag_ = true;
            PlayTranslateAnimation(0.0f, 0.0f);
        } else {
            changeFlag_ = false;
            PlayTranslateAnimation(currentOffset_, 0.0f);
        }
    }
}

bool SwitchPattern::IsOutOfBoundary(double mainOffset) const
{
    return mainOffset < 0 || mainOffset > GetSwitchWidth();
}

RectF SwitchPattern::GetHotZoneRect(bool isOriginal) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_RETURN(switchTheme, {});
    auto defaultWidth = switchTheme->GetDefaultWidth().ConvertToPx();
    auto defaultHeight = switchTheme->GetDefaultHeight().ConvertToPx();
    auto defaultWidthGap =
        defaultWidth - (switchTheme->GetWidth() - switchTheme->GetHotZoneHorizontalPadding() * 2).ConvertToPx();
    auto defaultHeightGap =
        defaultHeight - (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, {});
    auto originalPaintRect = renderContext->GetPaintRectWithoutTransform();
    auto offset = originalPaintRect.GetOffset();
    double actualWidth = 0.0;
    double actualHeight = 0.0;
    if (isOriginal) {
        actualWidth = geometryNode->GetFrameSize().Width() + defaultWidthGap;
        actualHeight = geometryNode->GetFrameSize().Height() + defaultHeightGap;
        offset.SetX(offset.GetX() - defaultWidthGap / 2);
        offset.SetY(offset.GetY() - defaultHeightGap / 2);
    } else {
        actualWidth = geometryNode->GetFrameSize().Width();
        actualHeight = geometryNode->GetFrameSize().Height();
        offset.SetX(offset.GetX() + defaultWidthGap / 2);
        offset.SetY(offset.GetY() + defaultHeightGap / 2);
    }
    return RectF(offset, SizeF(actualWidth, actualHeight));
}

} // namespace OHOS::Ace::NG