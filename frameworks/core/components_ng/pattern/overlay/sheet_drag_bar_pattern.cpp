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

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/property.h"
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

// For DragBar Initial State Point.
const OffsetT<Dimension> POINT_L_INITIAL = OffsetT<Dimension>(8.0_vp, 12.0_vp);  // Left Point position.
const OffsetT<Dimension> POINT_C_INITIAL = OffsetT<Dimension>(32.0_vp, 12.0_vp); // Center Point position.
const OffsetT<Dimension> POINT_R_INITIAL = OffsetT<Dimension>(56.0_vp, 12.0_vp); // Right Point position.
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
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetFillMode(FillMode::FORWARDS);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    if (isDown) {
        option.SetDuration(DOWN_DURATION);
        context->ScaleAnimation(option, 1.0f, SCALE);
    } else {
        option.SetDuration(RESET_DURATION);
        context->ScaleAnimation(option, SCALE, 1.0f);
    }
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
} // namespace OHOS::Ace::NG
