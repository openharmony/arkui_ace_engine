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

namespace {
OffsetF GetPageOffset()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto stageManager = pipeline->GetStageManager();
    CHECK_NULL_RETURN(stageManager, OffsetF());
    auto page = stageManager->GetLastPage();
    CHECK_NULL_RETURN(page, OffsetF());
    return page->GetOffsetRelativeToWindow();
}
} // namespace

void MenuWrapperPattern::HideMenu(const RefPtr<FrameNode>& menu)
{
    isHided_ = true;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    for (auto subMenuId : subMenuIds_) {
        LOGI("MenuWrapperPattern::HideMenu subMenu id is %{public}d", subMenuId);
        overlayManager->HideMenu(subMenuId);
    }

    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    LOGI("MenuWrapperPattern closing menu %{public}d", targetId_);
    menuPattern->HideMenu();
}

void MenuWrapperPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();

    isHided_ = false;

    // if already initialized touch event
    CHECK_NULL_VOID_NOLOG(!onTouch_);

    // hide menu when touched outside the menu region
    auto callback = [weak = WeakClaim(RawPtr(host))](const TouchEventInfo& info) {
        if (info.GetTouches().empty()) {
            return;
        }
        auto touch = info.GetTouches().front();
        // filter out other touch types
        if (touch.GetTouchType() != TouchType::DOWN && touch.GetTouchType() != TouchType::UP) {
            return;
        }
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsHided()) {
            return;
        }
        OffsetF position = OffsetF(touch.GetGlobalLocation().GetX(), touch.GetGlobalLocation().GetY());
        position -= GetPageOffset();
        auto children = host->GetChildren();
        for (auto child = children.rbegin(); child != children.rend(); ++child) {
            // get menu frame node (child of menu wrapper)
            auto menuNode = DynamicCast<FrameNode>(*child);
            CHECK_NULL_VOID(menuNode);

            // get menuNode's touch region
            auto menuZone = menuNode->GetGeometryNode()->GetFrameRect();
            if (menuZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
                return;
            }
            // if DOWN-touched outside the menu region, then hide menu
            auto menuPattern = menuNode->GetPattern<MenuPattern>();
            CHECK_NULL_VOID(menuPattern);
            if (menuPattern->IsSubMenu()) {
                pattern->HideSubMenu();
            } else {
                pattern->HideMenu(menuNode);
            }
        }
    };
    onTouch_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    gestureHub->AddTouchEvent(onTouch_);
}

// close subMenu when mouse move outside
void MenuWrapperPattern::HandleMouseEvent(const MouseInfo& info, RefPtr<MenuItemPattern>& menuItemPattern)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto subMenu = host->GetChildren().back();
    if (host->GetChildren().size() <= 1) {
        return;
    }
    auto subMenuNode = DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuNode);
    auto subMenuPattern = subMenuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(subMenuPattern);
    auto currentHoverMenuItem = subMenuPattern->GetParentMenuItem();
    CHECK_NULL_VOID(currentHoverMenuItem);

    auto menuItemNode = menuItemPattern->GetHost();
    CHECK_NULL_VOID(menuItemNode);
    if (currentHoverMenuItem->GetId() != menuItemNode->GetId()) {
        return;
    }
    const auto& mousePosition = info.GetGlobalLocation();
    if (!menuItemPattern->IsInHoverRegions(mousePosition.GetX(), mousePosition.GetY()) &&
        menuItemPattern->IsSubMenuShowed()) {
        LOGI("MenuWrapperPattern Hide SubMenu");
        HideSubMenu();
        menuItemPattern->SetIsSubMenuShowed(false);
        menuItemPattern->ClearHoverRegions();
        menuItemPattern->ResetWrapperMouseEvent();
    }
}

void MenuWrapperPattern::HideMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuNode = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuNode);
    HideMenu(menuNode);
}

void MenuWrapperPattern::HideSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetChildren().size() <= 1) {
        // sub menu not show
        return;
    }
    auto subMenu = host->GetChildren().back();
    host->RemoveChild(subMenu);
    auto menuPattern = DynamicCast<FrameNode>(subMenu)->GetPattern<MenuPattern>();
    if (menuPattern) {
        menuPattern->RemoveParentHoverStyle();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}
} // namespace OHOS::Ace::NG
