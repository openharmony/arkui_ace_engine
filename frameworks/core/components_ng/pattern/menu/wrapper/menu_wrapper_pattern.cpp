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

#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

#include "core/components/common/properties/shadow_config.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/event/click_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void MenuWrapperPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();

    // close menu when clicked outside the menu region
    auto callback = [targetId = targetId_, host](const TouchEventInfo& info) {
        auto touch = info.GetTouches().front();
        // only hide menu when touch DOWN occurs
        if (touch.GetTouchType() != TouchType::DOWN) {
            return;
        }

        // get menuNode's touch region
        auto menuNode = host->GetChildAtIndex(0);
        CHECK_NULL_VOID(menuNode);
        if (!InstanceOf<FrameNode>(menuNode)) {
            LOGW("MenuWrapper's child is not a Menu! type = %{public}s", menuNode->GetTag().c_str());
        }
        auto menuZone = DynamicCast<FrameNode>(menuNode)->GetGeometryNode()->GetFrameRect();

        auto position = touch.GetGlobalLocation();
        // if DOWN-touched outside the menu region, then hide menu
        if (!menuZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
            auto pipeline = host->GetContext();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();

            overlayManager->HideMenu(targetId);
            LOGD("touch is outside the menu region (%{public}f, %{public}f), menu %{public}d removed", position.GetX(),
                position.GetY(), targetId);
        }
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(callback));
    gestureHub->AddTouchEvent(touchEvent);
}

} // namespace OHOS::Ace::NG
