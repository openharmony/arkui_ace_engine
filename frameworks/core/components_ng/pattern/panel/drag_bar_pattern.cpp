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
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// For DragBar Shrink State Point.
const Offset POINT_L_SHRINK = Offset(17.0, 15.0); // Left Point position.
const Offset POINT_C_SHRINK = Offset(32.0, 9.0);  // Center Point position.
const Offset POINT_R_SHRINK = Offset(47.0, 15.0); // Right Point position.

// For DragBar Initial State Point.
const Offset POINT_L_INITIAL = Offset(18.0, 12.0); // Left Point position.
const Offset POINT_C_INITIAL = Offset(32.0, 12.0); // Center Point position.
const Offset POINT_R_INITIAL = Offset(46.0, 12.0); // Right Point position.

// For DragBar Expand State Point.
const Offset POINT_L_EXPAND = Offset(17.0, 9.0);  // Left Point position.
const Offset POINT_C_EXPAND = Offset(32.0, 15.0); // Center Point position.
const Offset POINT_R_EXPAND = Offset(47.0, 9.0);  // Right Point position.

} // namespace

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

void DragBarPattern::ShowInPanelMode(PanelMode mode)
{
    if (showMode_ == mode) {
        return;
    }
    showMode_ = mode;
    UpdateDrawPoint();
}

void DragBarPattern::UpdateDrawPoint()
{
    Offset leftPoint;
    Offset centerPoint;
    Offset rightPoint;
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
    barLeftPoint_ = leftPoint;
    barCenterPoint_ = centerPoint;
    barRightPoint_ = rightPoint;
}

void DragBarPattern::InitTouch(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info.GetTouches().front());
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent_);
}

void DragBarPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitTouch(gestureHub);
}

void DragBarPattern::HandleTouchEvent(const TouchLocationInfo& info)
{
    // TODO change background color when touch down.
}

} // namespace OHOS::Ace::NG
