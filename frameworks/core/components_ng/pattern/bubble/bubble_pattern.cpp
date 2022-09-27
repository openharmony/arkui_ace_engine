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

#include "core/components_ng/pattern/bubble/bubble_pattern.h"

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

bool BubblePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto bubbleLayoutAlgorithm = DynamicCast<BubbleLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(bubbleLayoutAlgorithm, false);
    showTopArrow_ = bubbleLayoutAlgorithm->ShowTopArrow();
    showBottomArrow_ = bubbleLayoutAlgorithm->ShowBottomArrow();
    showCustomArrow_ = bubbleLayoutAlgorithm->ShowCustomArrow();
    arrowPosition_ = bubbleLayoutAlgorithm->GetArrowPosition();
    childOffset_ = bubbleLayoutAlgorithm->GetChildOffset();
    childSize_ = bubbleLayoutAlgorithm->GetChildSize();
    touchRegion_ = bubbleLayoutAlgorithm->GetTouchRegion();
    return true;
}

void BubblePattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitTouchEvent(gestureHub);
}

void BubblePattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
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
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void BubblePattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto clickPos = info.GetTouches().front().GetLocalLocation();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(clickPos);
    }
}

void BubblePattern::HandleTouchDown(const Offset& clickPosition)
{
    // TODO: need to check click position
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto bubbleRenderProp = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(bubbleRenderProp);
    if (touchRegion_.IsInRegion(PointF(clickPosition.GetX(), clickPosition.GetY()))) {
        LOGI("Contains the touch region.");
        return;
    }
    auto autoCancel = bubbleRenderProp->GetAutoCancel().value_or(true);
    if (autoCancel) {
        PopBubble();
    }
}

void BubblePattern::PopBubble()
{
    LOGI("BubblePattern::PopBubble from click");
    auto pipelineNg = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineNg);
    auto overlayManager = pipelineNg->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto popupInfo = overlayManager->GetPopupInfo(targetNodeId_);
    if (!popupInfo.isCurrentOnShow) {
        return;
    }
    popupInfo.markNeedUpdate = true;
    overlayManager->UpdatePopupNode(targetNodeId_, popupInfo);
}

} // namespace OHOS::Ace::NG