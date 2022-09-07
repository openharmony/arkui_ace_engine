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

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/common/container.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/toggle/switch_layout_algorithm.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SwitchPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool SwitchPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto switchLayoutAlgorithm = DynamicCast<SwitchLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(switchLayoutAlgorithm, false);
    contentSize_.SetWidth(switchLayoutAlgorithm->GetWidth());
    contentSize_.SetHeight(switchLayoutAlgorithm->GetHeight());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto switchPaintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(switchPaintProperty, false);
    isOn_ = switchPaintProperty->GetIsOnValue();
    if (isOn_) {
        currentOffset_ = GetSwitchWidth();
    }
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

    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }
    auto switchPaintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(switchPaintProperty);
    isOn_ = switchPaintProperty->GetIsOnValue();
    InitTouchEvent(gestureHub);
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
        auto switch_ = weak.Upgrade();
        CHECK_NULL_VOID(switch_);
        if (!NearEqual(value, startPos) && !NearEqual(value, endPos) && !NearEqual(startPos, endPos)) {
            float moveRate =
                Curves::EASE_OUT->MoveInternal(static_cast<float>((value - startPos) / (endPos - startPos)));
            value = startPos + (endPos - startPos) * moveRate;
        }
        switch_->UpdateCurrentOffset(static_cast<float>(value - switch_->currentOffset_));
    }));

    if (!controller_) {
        controller_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();
    controller_->AddStopListener([weak, this]() {
        auto switch_ = weak.Upgrade();
        CHECK_NULL_VOID(switch_);
        if (!isOn_) {
            if (switch_->currentOffset_ == GetSwitchWidth()) {
                switch_->isOn_ = true;
                switch_->FireChangeEvent();
            }
        } else {
            if (switch_->currentOffset_ == 0) {
                switch_->isOn_ = false;
                switch_->FireChangeEvent();
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
    const int32_t DEFAULT_DURATION = 400;
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
    auto switchPaintProperty = host->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_VOID(switchPaintProperty);
    auto translateOffset = GetSwitchWidth();
    StopTranslateAnimation();
    if (!isOn_) {
        PlayTranslateAnimation(0, translateOffset);
    } else {
        PlayTranslateAnimation(translateOffset, 0);
    }
}

float SwitchPattern::GetSwitchWidth() const
{
    const float switchGap = 2.0f;
    auto switchWidth = contentSize_.Width() - contentSize_.Height() + switchGap;
    return switchWidth;
}

void SwitchPattern::FireChangeEvent() const
{
    auto switchEventHub = GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(switchEventHub);
    switchEventHub->FireChangeEvent(isOn_);
}

void SwitchPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };

    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void SwitchPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown();
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    }
}

void SwitchPattern::HandleTouchDown()
{
    // Stop translate animation when touch down.
    if (controller_ && !controller_->IsStopped()) {
        // Clear stop listener before stop, otherwise the previous swipe will be considered complete.
        controller_->ClearStopListeners();
        controller_->Stop();
    }
}

void SwitchPattern::HandleTouchUp()
{
    OnChange();
}

} // namespace OHOS::Ace::NG