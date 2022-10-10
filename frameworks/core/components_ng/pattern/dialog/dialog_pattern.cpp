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

#include "core/components_ng/pattern/dialog/dialog_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void DialogPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitTouchEvent(gestureHub);
}

void DialogPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
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

void DialogPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto clickPos = info.GetTouches().front().GetLocalLocation();
    if (touchType == TouchType::UP) {
        HandleTouchUp(clickPos);
    }
}

void DialogPattern::HandleTouchUp(const Offset& clickPosition)
{
    // TODO: need to check click position
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dialogRenderProp = host->GetPaintProperty<DialogRenderProperty>();
    CHECK_NULL_VOID(dialogRenderProp);
    auto autoCancel = dialogRenderProp->GetAutoCancel().value_or(true);
    if (autoCancel) {
        auto content = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(content);
        auto contentRect = content->GetGeometryNode()->GetFrameRect();
        // close dialog if clicked outside content rect
        if (!contentRect.IsInRegion(PointF(clickPosition.GetX(), clickPosition.GetY()))) {
            PopDialog();
        }
    }
}

void DialogPattern::PopDialog()
{
    LOGI("DialogPattern::PopDialog from click");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // trigger onCancel callback
    auto hub = host->GetEventHub<DialogEventHub>();
    hub->FireChangeEvent();

    overlayManager->CloseDialog(host);
}

} // namespace OHOS::Ace::NG