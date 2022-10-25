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

#include "core/components_ng/pattern/panel/drag_bar_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr Dimension MAX_DRAG_X = 10.0_vp;
constexpr Dimension MAX_DRAG_Y = 4.0_vp;
constexpr float DRAG_X_RATIO = 0.4;
constexpr float DRAG_Y_RATIO = 0.2;
constexpr float SCALE_ICON = 1.15;
constexpr float SCALE_WIDTH = 1.5 / SCALE_ICON;
constexpr int32_t DOWN_DURATION = 150;
constexpr int32_t RESET_DURATION = 250;
constexpr int32_t STYLE_DURATION = 200;
constexpr Dimension HOT_REGION_HEIGHT = 24.0_vp;

// For DragBar Shrink State Point.
const OffsetT<Dimension> POINT_L_SHRINK = OffsetT<Dimension>(17.0_vp, 15.0_vp); // Left Point position.
const OffsetT<Dimension> POINT_C_SHRINK = OffsetT<Dimension>(32.0_vp, 9.0_vp);  // Center Point position.
const OffsetT<Dimension> POINT_R_SHRINK = OffsetT<Dimension>(47.0_vp, 15.0_vp); // Right Point position.

// For DragBar Initial State Point.
const OffsetT<Dimension> POINT_L_INITIAL = OffsetT<Dimension>(18.0_vp, 12.0_vp); // Left Point position.
const OffsetT<Dimension> POINT_C_INITIAL = OffsetT<Dimension>(32.0_vp, 12.0_vp); // Center Point position.
const OffsetT<Dimension> POINT_R_INITIAL = OffsetT<Dimension>(46.0_vp, 12.0_vp); // Right Point position.

// For DragBar Expand State Point.
const OffsetT<Dimension> POINT_L_EXPAND = OffsetT<Dimension>(17.0_vp, 9.0_vp);  // Left Point position.
const OffsetT<Dimension> POINT_C_EXPAND = OffsetT<Dimension>(32.0_vp, 15.0_vp); // Center Point position.
const OffsetT<Dimension> POINT_R_EXPAND = OffsetT<Dimension>(47.0_vp, 9.0_vp);  // Right Point position.

} // namespace

void DragBarPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    InitProps();
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitTouchEvent(gestureHub);
    UpdateDrawPoint();
    MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void DragBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool DragBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<DragBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    return true;
}

void DragBarPattern::InitProps()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }

    if (!barTouchAnimator_) {
        barTouchAnimator_ = AceType::MakeRefPtr<Animator>(host->GetContext());
        auto touchAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(1.0, SCALE_ICON, Curves::SHARP);
        touchAnimation->AddListener([weak = AceType::WeakClaim(this)](float value) {
            auto dragBar = weak.Upgrade();
            if (dragBar) {
                dragBar->scaleIcon_ = value;
                dragBar->scaleWidth_ = 1.0 + (value - 1.0) / (SCALE_ICON - 1.0) * (SCALE_WIDTH - 1.0);
                dragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            }
        });
        barTouchAnimator_->ClearInterpolators();
        barTouchAnimator_->AddInterpolator(touchAnimation);
        barTouchAnimator_->SetFillMode(FillMode::FORWARDS);
    }
    if (!barRangeAnimator_) {
        barRangeAnimator_ = AceType::MakeRefPtr<Animator>(host->GetContext());
        barRangeAnimator_->SetFillMode(FillMode::FORWARDS);
        barRangeAnimator_->SetDuration(RESET_DURATION);
    }
    if (!barStyleAnimator_) {
        barStyleAnimator_ = AceType::MakeRefPtr<Animator>(host->GetContext());
        barStyleAnimator_->SetFillMode(FillMode::FORWARDS);
        barStyleAnimator_->SetDuration(STYLE_DURATION);
    }

    auto paintProps = host->GetPaintProperty<DragBarPaintProperty>();
    showMode_ = paintProps->GetPanelMode().value_or(PanelMode::HALF);

    dragRangeX_ = MAX_DRAG_X.ConvertToPx();
    dragRangeY_ = MAX_DRAG_Y.ConvertToPx();
}

void DragBarPattern::ShowArrow(bool show)
{
    PanelMode mode = PanelMode::HALF;
    if (show) {
        mode = PanelMode::FULL;
    } else {
        mode = PanelMode::HALF;
    }
    ShowInPanelMode(mode);
}

void DragBarPattern::ShowInPanelMode(PanelMode mode)
{
    if (showMode_ == mode) {
        return;
    }
    showMode_ = mode;
    UpdateDrawPoint();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void DragBarPattern::UpdateDrawPoint()
{
    OffsetT<Dimension> leftPoint;
    OffsetT<Dimension> centerPoint;
    OffsetT<Dimension> rightPoint;
    switch (showMode_) {
        case PanelMode::MINI:
            leftPoint = POINT_L_SHRINK;
            centerPoint = POINT_C_SHRINK;
            rightPoint = POINT_R_SHRINK;
            break;
        case PanelMode::HALF:
            leftPoint = POINT_L_INITIAL;
            centerPoint = POINT_C_INITIAL;
            rightPoint = POINT_R_INITIAL;
            break;
        case PanelMode::FULL:
            leftPoint = POINT_L_EXPAND;
            centerPoint = POINT_C_EXPAND;
            rightPoint = POINT_R_EXPAND;
            break;
        default:
            LOGE("Unsupported Show Mode:%{public}d", showMode_);
            return;
    }
    auto paintProperty = GetPaintProperty<DragBarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (isFirstUpdate_) {
        // No need to do animation when first time to display.
        paintProperty->UpdateBarLeftPoint(leftPoint);
        paintProperty->UpdateBarCenterPoint(centerPoint);
        paintProperty->UpdateBarRightPoint(rightPoint);
        isFirstUpdate_ = false;
    } else {
        DoStyleAnimation(leftPoint, centerPoint, rightPoint);
    }
}

// TODO Implicit animation scheme using the new framework
void DragBarPattern::DoStyleAnimation(
    const OffsetT<Dimension>& leftPoint, const OffsetT<Dimension>& centerPoint, const OffsetT<Dimension>& rightPoint)
{
    if (barStyleAnimator_->IsRunning()) {
        barStyleAnimator_->Stop();
    }
    auto paintProperty = GetPaintProperty<DragBarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto barLeftPoint = paintProperty->GetBarLeftPoint().value_or(POINT_L_INITIAL);
    auto barCenterPoint = paintProperty->GetBarCenterPoint().value_or(POINT_C_INITIAL);
    auto barRightPoint = paintProperty->GetBarRightPoint().value_or(POINT_R_INITIAL);
    auto leftAnimation =
        AceType::MakeRefPtr<CurveAnimation<OffsetT<Dimension>>>(barLeftPoint, leftPoint, Curves::SHARP);
    leftAnimation->AddListener([weak = AceType::WeakClaim(this)](const OffsetT<Dimension>& value) {
        auto dragBar = weak.Upgrade();
        if (dragBar) {
            dragBar->GetPaintProperty<DragBarPaintProperty>()->UpdateBarLeftPoint(value);
            dragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    });
    auto centerAnimation =
        AceType::MakeRefPtr<CurveAnimation<OffsetT<Dimension>>>(barCenterPoint, centerPoint, Curves::SHARP);
    centerAnimation->AddListener([weak = AceType::WeakClaim(this)](const OffsetT<Dimension>& value) {
        auto dragBar = weak.Upgrade();
        if (dragBar) {
            dragBar->GetPaintProperty<DragBarPaintProperty>()->UpdateBarCenterPoint(value);
        }
    });
    auto rightAnimation =
        AceType::MakeRefPtr<CurveAnimation<OffsetT<Dimension>>>(barRightPoint, rightPoint, Curves::SHARP);
    rightAnimation->AddListener([weak = AceType::WeakClaim(this)](const OffsetT<Dimension>& value) {
        auto dragBar = weak.Upgrade();
        if (dragBar) {
            dragBar->GetPaintProperty<DragBarPaintProperty>()->UpdateBarRightPoint(value);
        }
    });
    barStyleAnimator_->ClearInterpolators();
    barStyleAnimator_->AddInterpolator(leftAnimation);
    barStyleAnimator_->AddInterpolator(centerAnimation);
    barStyleAnimator_->AddInterpolator(rightAnimation);
    barStyleAnimator_->Play();
}

void DragBarPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };

    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void DragBarPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto frontInfo = info.GetTouches().front();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(frontInfo);
    }
    if (touchType == TouchType::MOVE) {
        HandleTouchMove(frontInfo);
    }
    if (touchType == TouchType::UP) {
        HandleTouchUp();
    }
}

void DragBarPattern::HandleTouchDown(const TouchLocationInfo& info)
{
    // Display the click-to-magnify effect.
    downPoint_ = OffsetF(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    barTouchAnimator_->SetDuration(DOWN_DURATION);
    barTouchAnimator_->Forward();
}

void DragBarPattern::HandleTouchMove(const TouchLocationInfo& info)
{
    auto movePoint = OffsetF(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    // Display the dragging offset effect.
    OffsetF distance = movePoint - downPoint_;
    OffsetF dragOffset;
    dragOffset.SetX(std::clamp(distance.GetX() * DRAG_X_RATIO, -dragRangeX_, dragRangeX_));
    dragOffset.SetY(std::clamp(distance.GetY() * DRAG_Y_RATIO, -dragRangeY_, dragRangeY_));
    auto paintProperty = GetPaintProperty<DragBarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetDragOffset().value_or(OffsetF()) != dragOffset) {
        paintProperty->UpdateDragOffset(dragOffset);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void DragBarPattern::HandleTouchUp()
{
    // Restore the click-to-magnify effect.
    barTouchAnimator_->SetDuration(RESET_DURATION);
    barTouchAnimator_->Backward();

    auto paintProperty = GetPaintProperty<DragBarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto dragOffset = paintProperty->GetDragOffset().value_or(OffsetF());
    // Restore the dragging offset effect.
    if (dragOffset == OffsetF()) {
        return; // No need to back to center with animation.
    }

    auto dragAnimation = AceType::MakeRefPtr<CurveAnimation<OffsetF>>(dragOffset, OffsetF(), Curves::SHARP);
    dragAnimation->AddListener([weak = AceType::WeakClaim(this)](OffsetF value) {
        auto dragBar = weak.Upgrade();
        if (dragBar) {
            dragBar->GetPaintProperty<DragBarPaintProperty>()->UpdateDragOffset(value);
            dragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    });
    barRangeAnimator_->ClearInterpolators();
    barRangeAnimator_->AddInterpolator(dragAnimation);
    barRangeAnimator_->Play();
}

void DragBarPattern::SetStatusBarHeight(float height)
{
    // Reset full window animation.
    if (animator_->IsRunning()) {
        animator_->ClearAllListeners();
        animator_->ClearInterpolators();
        Stretching();
        FadingOut();
    }
    if (GreatOrEqual(height, 0.0) && !NearEqual(statusBarHeight_.Value(), height)) {
        statusBarHeight_.SetValue(height);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
}

void DragBarPattern::Stretching()
{
    auto layoutProperty = GetLayoutProperty<DragBarLayoutProperty>();
    auto hotRegionHeight = layoutProperty->GetHotRegionHeight().value_or(HOT_REGION_HEIGHT.ConvertToPx());
    auto keyframeFrom = AceType::MakeRefPtr<Keyframe<float>>(0.0f, hotRegionHeight);
    auto keyframeTo = AceType::MakeRefPtr<Keyframe<float>>(1.0f, GetStatusBarHeight());
    auto animation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    animation->AddKeyframe(keyframeFrom);
    animation->AddKeyframe(keyframeTo);
    animation->AddListener([weak = AceType::WeakClaim(this)](const float& height) {
        auto dragBar = weak.Upgrade();
        if (!dragBar) {
            return;
        }
        dragBar->GetLayoutProperty<DragBarLayoutProperty>()->UpdateHotRegionHeight(height);
        dragBar->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    });
    animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto dragBar = weak.Upgrade();
        if (!dragBar) {
            return;
        }
        dragBar->GetLayoutProperty<DragBarLayoutProperty>()->UpdateFullScreenMode(true);
        dragBar->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    });
    animator_->AddInterpolator(animation);
}

void DragBarPattern::FadingOut()
{
    auto keyframeFrom = AceType::MakeRefPtr<Keyframe<float>>(0.0, 1.0);
    auto keyframeTo = AceType::MakeRefPtr<Keyframe<float>>(1.0, 0.0);
    auto animation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    animation->AddKeyframe(keyframeFrom);
    animation->AddKeyframe(keyframeTo);
    animation->AddListener([weak = AceType::WeakClaim(this)](const float& opacity) {
        auto dragBar = weak.Upgrade();
        if (dragBar) {
            dragBar->GetPaintProperty<DragBarPaintProperty>()->UpdateOpacity(opacity);
        }
    });
    animator_->AddInterpolator(animation);
}

void DragBarPattern::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(extraFlag);
}

} // namespace OHOS::Ace::NG
