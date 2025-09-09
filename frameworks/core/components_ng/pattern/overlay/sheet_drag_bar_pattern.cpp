/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
// Maximum displacement of the control bar in the x direction when dragging the control bar.
constexpr Dimension MAX_DRAG_X = 12.0_vp;

// Maximum displacement of the control bar in the y direction when dragging the control bar.
constexpr Dimension MAX_DRAG_Y = 5.0_vp;

// For every 1 unit distance the finger moves in the y direction, the control bar moves 0.04 unit distance.
constexpr float SCALE = 1.5;
constexpr int32_t DOWN_DURATION = 150;
constexpr int32_t RESET_DURATION = 250;
constexpr Dimension BAR_WIDTH = 4.0_vp;

// For DragBar Initial State Point.
const OffsetT<Dimension> POINT_L_INITIAL = OffsetT<Dimension>(8.0_vp, 12.0_vp);  // Left Point position.
const OffsetT<Dimension> POINT_C_INITIAL = OffsetT<Dimension>(32.0_vp, 12.0_vp); // Center Point position.
const OffsetT<Dimension> POINT_R_INITIAL = OffsetT<Dimension>(56.0_vp, 12.0_vp); // Right Point position.

const OffsetT<Dimension> POINT_L_TOUCH = OffsetT<Dimension>(6.0_vp, 12.0_vp);  // Left Point position.
const OffsetT<Dimension> POINT_C_TOUCH = OffsetT<Dimension>(32.0_vp, 12.0_vp); // Center Point position.
const OffsetT<Dimension> POINT_R_TOUCH = OffsetT<Dimension>(58.0_vp, 12.0_vp); // Right Point position.
} // namespace

void SheetDragBarPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    dragOffsetX_ = MAX_DRAG_X.ConvertToPx();
    dragOffsetY_ = MAX_DRAG_Y.ConvertToPx();
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitTouchEvent(gestureHub);
    InitClickEvent();
    UpdateDrawPoint();
    MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetDragBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
}

void SheetDragBarPattern::UpdateDrawPoint()
{
    OffsetT<Dimension> leftPoint = POINT_L_INITIAL;
    OffsetT<Dimension> centerPoint = POINT_C_INITIAL;
    OffsetT<Dimension> rightPoint = POINT_R_INITIAL;
    auto paintProperty = GetPaintProperty<SheetDragBarPaintProperty>();
    paintProperty->UpdateBarLeftPoint(leftPoint);
    paintProperty->UpdateBarCenterPoint(centerPoint);
    paintProperty->UpdateBarRightPoint(rightPoint);
    paintProperty->UpdateBarWidth(BAR_WIDTH);
}

void SheetDragBarPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
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

void SheetDragBarPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto sheetDragBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(sheetDragBarPattern);
        sheetDragBarPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void SheetDragBarPattern::OnClick()
{
    if (!clickArrowCallback_) {
        return;
    }
    clickArrowCallback_();
}

void SheetDragBarPattern::ScaleAnimation(bool isDown)
{
    CreatePropertyCallback();
    CHECK_NULL_VOID(property_);
    StopAnimation();
    auto weak = AceType::WeakClaim(this);
    isDown_ = isDown;
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetFillMode(FillMode::FORWARDS);
    if (isDown) {
        option.SetDuration(DOWN_DURATION);
    } else {
        option.SetDuration(RESET_DURATION);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->AttachNodeAnimatableProperty(property_);
    auto pipeline = host->GetContextRefPtr();
    AnimationUtils::Animate(
        option,
        [weak]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            ref->property_->Set(1.0f);
        },
        nullptr, nullptr, pipeline);
}

void SheetDragBarPattern::StopAnimation()
{
    auto weak = AceType::WeakClaim(this);
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(0);
    option.SetDelay(0);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    AnimationUtils::Animate(
        option,
        [weak]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            ref->property_->Set(0.0);
        },
        nullptr, nullptr, pipeline);
}

void SheetDragBarPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto frontInfo = info.GetTouches().front();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(frontInfo);
    }
    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        HandleTouchUp();
    }
}

void SheetDragBarPattern::HandleTouchDown(const TouchLocationInfo& info)
{
    // Display the click-to-magnify effect.
    downPoint_ = OffsetF(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    ScaleAnimation(true);
}

void SheetDragBarPattern::HandleTouchUp()
{
    // Restore the click-to-magnify effect.
    ScaleAnimation(false);
}

void SheetDragBarPattern::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(extraFlag);
}

void SheetDragBarPattern::CreatePropertyCallback()
{
    if (property_) {
        return;
    }
    auto weak = AceType::WeakClaim(this);
    auto propertyCallback = [weak](float scale) {
        if (NearZero(scale)) {
            return;
        }
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        auto paintProperty = ref->GetPaintProperty<SheetDragBarPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto barWidth = paintProperty->GetBarWidth().value_or(BAR_WIDTH);
        if (ref->isDown_) {
            OffsetT<Dimension> leftPoint = POINT_L_INITIAL;
            OffsetT<Dimension> rightPoint = POINT_R_INITIAL;
            auto widthValue = BAR_WIDTH.Value() + BAR_WIDTH.Value() * (SCALE - 1.0f) * scale;
            auto leftX = POINT_L_TOUCH.GetX().Value() - POINT_L_INITIAL.GetX().Value();
            auto rightX = POINT_R_TOUCH.GetX().Value() - POINT_R_INITIAL.GetX().Value();
            leftPoint.SetX(Dimension(POINT_L_INITIAL.GetX().Value() + leftX * scale, DimensionUnit::VP));
            rightPoint.SetX(Dimension(POINT_R_INITIAL.GetX().Value() + rightX * scale, DimensionUnit::VP));
            barWidth.SetValue(widthValue);
            paintProperty->UpdateBarWidth(barWidth);
            paintProperty->UpdateBarLeftPoint(leftPoint);
            paintProperty->UpdateBarRightPoint(rightPoint);
        } else {
            OffsetT<Dimension> leftPoint = POINT_L_TOUCH;
            OffsetT<Dimension> rightPoint = POINT_R_TOUCH;
            auto widthValue = BAR_WIDTH.Value() * SCALE + BAR_WIDTH.Value() * (1.0f - SCALE) * scale;
            auto leftX = POINT_L_INITIAL.GetX().Value() - POINT_L_TOUCH.GetX().Value();
            auto rightX = POINT_R_INITIAL.GetX().Value() - POINT_R_TOUCH.GetX().Value();
            leftPoint.SetX(Dimension(POINT_L_TOUCH.GetX().Value() + leftX * scale, DimensionUnit::VP));
            rightPoint.SetX(Dimension(POINT_R_TOUCH.GetX().Value() + rightX * scale, DimensionUnit::VP));
            barWidth.SetValue(widthValue);
            paintProperty->UpdateBarWidth(barWidth);
            paintProperty->UpdateBarLeftPoint(leftPoint);
            paintProperty->UpdateBarRightPoint(rightPoint);
        }
        ref->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
    property_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
}
} // namespace OHOS::Ace::NG
