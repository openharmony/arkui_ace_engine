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

#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/event/click_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void MenuWrapperPattern::HideMenu(const RefPtr<FrameNode>& menu) const
{
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    LOGI("closing menu %{public}d", targetId_);
    // ContextMenu: close in subwindowManager
    if (menuPattern->IsContextMenu()) {
        SubwindowManager::GetInstance()->HideMenuNG(targetId_);
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->HideMenu(targetId_);
}

void MenuWrapperPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();

    // if already initialized touch event
    CHECK_NULL_VOID_NOLOG(!onTouch_);

    // hide menu when touched outside the menu region
    auto callback = [weak = WeakClaim(RawPtr(host))](const TouchEventInfo& info) {
        if (info.GetTouches().empty()) {
            return;
        }
        auto touch = info.GetTouches().front();
        // filter out other touch types
        if (touch.GetTouchType() != TouchType::DOWN) {
            return;
        }
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(pattern);
        // get menu frame node (child of menu wrapper)
        auto menuNode = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(menuNode);

        // get menuNode's touch region
        auto menuZone = menuNode->GetGeometryNode()->GetFrameRect();
        const auto& position = touch.GetGlobalLocation();
        // if DOWN-touched outside the menu region, then hide menu
        if (!menuZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
            pattern->HideMenu(menuNode);
        }
    };
    onTouch_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    gestureHub->AddTouchEvent(onTouch_);
}

// close subMenu when mouse move outside
void MenuWrapperPattern::HandleMouseEvent(const MouseInfo& info, RefPtr<MenuItemPattern>& menuItemPattern)
{
    auto menuItem = menuItemPattern->GetHost();
    CHECK_NULL_VOID(menuItem);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    const auto& mousePosition = info.GetGlobalLocation();
    if (!menuItemPattern->IsInHoverRegions(mousePosition.GetX(), mousePosition.GetY()) &&
        menuItemPattern->IsSubMenuShowed()) {
        LOGI("MenuWrapperPattern Hide SubMenu");
        overlayManager->HideMenu(menuItem->GetId());
        menuItemPattern->SetIsSubMenuShowed(false);
        menuItemPattern->ClearHoverRegions();
        menuItemPattern->ResetWrapperMouseEvent();
    }
}
} // namespace OHOS::Ace::NG
