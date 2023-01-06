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

#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void MenuItemPattern::OnModifyDone()
{
    RegisterOnClick();
    RegisterOnTouch();
    RegisterOnHover();
}

RefPtr<FrameNode> MenuItemPattern::GetMenuWrapper()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

RefPtr<FrameNode> MenuItemPattern::GetMenu()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

void MenuItemPattern::ShowSubMenu()
{
    auto buildFunc = GetSubBuilder();
    if (buildFunc && !isSubMenuShowed_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);

        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        auto menuNode = MenuView::Create(customNode, host->GetId(), MenuType::SUB_MENU);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        menuPattern->SetParentMenuItem(host);
        subMenuId_ = menuNode->GetId();
        AddSelfHoverRegion(host);
        LOGI("MenuItemPattern Show SubMenu");
        isSubMenuShowed_ = true;
        OffsetF offset = GetSubMenuPostion(host);
        overlayManager->ShowMenu(host->GetId(), offset, menuNode);

        RegisterWrapperMouseEvent();
    }
}

void MenuItemPattern::CloseMenu()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (GetSubBuilder() != nullptr && isSubMenuShowed_) {
        int32_t itemId = GetHost()->GetId();
        overlayManager->HideMenu(itemId);
    }

    int32_t menuTargetId = 0;
    bool isInContextMenu = false;

    auto menuWrapper = GetMenuWrapper();
    if (menuWrapper) {
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        menuTargetId = menuWrapperPattern->GetTargetId();

        auto menu = AceType::DynamicCast<FrameNode>(menuWrapper->GetChildAtIndex(0));
        CHECK_NULL_VOID(menu);
        auto menuPattern = menu->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        isInContextMenu = menuPattern->IsContextMenu();
    } else {
        auto subMenu = GetMenu();
        CHECK_NULL_VOID(subMenu);
        auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(subMenuPattern);
        menuTargetId = subMenuPattern->IsSubMenu() ? subMenuPattern->GetTargetId() : -1;
    }

    if (isInContextMenu) {
        SubwindowManager::GetInstance()->HideMenuNG(menuTargetId);
        return;
    }
    overlayManager->HideMenu(menuTargetId);
}

void MenuItemPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<MenuItemEventHub>();

    auto event = [onChange = hub->GetOnChange(), weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetChange();
        if (onChange) {
            LOGI("trigger onChange");
            onChange(pattern->IsChange());
        }

        if (pattern->GetSubBuilder() != nullptr) {
            pattern->ShowSubMenu();
            return;
        }

        // hide menu when menu item is clicked
        pattern->CloseMenu();
    };
    auto clickEvent = MakeRefPtr<ClickEvent>(std::move(event));

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->AddClickEvent(clickEvent);
}

void MenuItemPattern::RegisterOnTouch()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnPress(info);
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent);
}

void MenuItemPattern::RegisterOnHover()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHover(isHover);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent);
}

void MenuItemPattern::OnPress(const TouchEventInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto touchType = info.GetTouches().front().GetTouchType();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (touchType == TouchType::DOWN) {
        // change background color, update press status
        auto clickedColor = theme->GetClickedColor();
        renderContext->UpdateBackgroundColor(clickedColor);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else if (touchType == TouchType::UP) {
        auto bgColor = theme->GetBackgroundColor();
        renderContext->UpdateBackgroundColor(bgColor);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void MenuItemPattern::OnHover(bool isHover)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    if (isHover || isSubMenuShowed_) {
        auto hoverColor = theme->GetHoverColor();
        renderContext->UpdateBackgroundColor(hoverColor);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

        ShowSubMenu();
    } else {
        auto bgColor = theme->GetBackgroundColor();
        renderContext->UpdateBackgroundColor(bgColor);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void MenuItemPattern::RegisterWrapperMouseEvent()
{
    auto menuWrapper = GetMenuWrapper();
    if (menuWrapper && !wrapperMouseEvent_) {
        auto inputHub = menuWrapper->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);

        auto mouseTask = [weak = WeakClaim(this), menuWrapperPattern](MouseInfo& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (menuWrapperPattern) {
                menuWrapperPattern->HandleMouseEvent(info, pattern);
            }
        };
        wrapperMouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
        inputHub->AddOnMouseEvent(wrapperMouseEvent_);
    }
}

void MenuItemPattern::AddSelfHoverRegion(const RefPtr<FrameNode>& targetNode)
{
    OffsetF topLeftPoint;
    OffsetF bottomRightPoint;
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    topLeftPoint = targetNode->GetPaintRectOffset();
    bottomRightPoint = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), frameSize.Height());
    AddHoverRegions(topLeftPoint, bottomRightPoint);
}

OffsetF MenuItemPattern::GetSubMenuPostion(const RefPtr<FrameNode>& targetNode)
{
    // show menu at left top point of targetNode
    OffsetF position;
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    position = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width(), 0.0);
    return position;
}

void MenuItemPattern::AddHoverRegions(const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint)
{
    TouchRegion hoverRegion = TouchRegion(
        Offset(topLeftPoint.GetX(), topLeftPoint.GetY()), Offset(bottomRightPoint.GetX(), bottomRightPoint.GetY()));
    hoverRegions_.emplace_back(hoverRegion);
    LOGI("MenuItemPattern::AddHoverRegions hoverRegion is %{private}s to %{private}s", topLeftPoint.ToString().c_str(),
        bottomRightPoint.ToString().c_str());
}

bool MenuItemPattern::IsInHoverRegions(double x, double y)
{
    for (auto hoverRegion : hoverRegions_) {
        if (hoverRegion.ContainsInRegion(x, y)) {
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace::NG