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

#include "core/components_ng/pattern/menu/menu_pattern.h"

#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void MenuPattern::OnModifyDone()
{
    RegisterOnTouch();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    RegisterOnKeyEvent(focusHub);
    DisableTabInMenu();

    if (IsMultiMenu()) {
        return;
    }

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // get theme from SelectThemeManager
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();

    // set background color
    auto bgColor = theme->GetBackgroundColor();
    renderContext->UpdateBackgroundColor(bgColor);

    // make menu round rect
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(theme->GetMenuBorderRadius());
    renderContext->UpdateBorderRadius(borderRadius);
    renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowM);
    renderContext->SetClipToBounds(true);
}

// close menu on touch up
void MenuPattern::RegisterOnTouch()
{
    CHECK_NULL_VOID_NOLOG(!onTouch_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->OnTouchEvent(info);
    };
    onTouch_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(onTouch_);
}

void MenuPattern::OnTouchEvent(const TouchEventInfo& info)
{
    if (IsMultiMenuOutside() || IsMultiMenu()) {
        // not click hide menu for multi menu
        return;
    }
    if (!options_.empty()) {
        // not click hide menu for select and bindMenu default option
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        lastTouchOffset_ = info.GetTouches().front().GetLocalLocation();
    } else if (touchType == TouchType::UP) {
        if (lastTouchOffset_.has_value() && info.GetTouches().front().GetLocalLocation() == lastTouchOffset_) {
            HideMenu();
        }
        lastTouchOffset_.reset();
    }
}

void MenuPattern::RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool MenuPattern::OnKeyEvent(const KeyEvent& event) const
{
    if (event.action != KeyAction::DOWN || IsMultiMenu()) {
        return false;
    }
    if (event.code == KeyCode::KEY_ESCAPE) {
        HideMenu();
        return true;
    }
    if (event.code == KeyCode::KEY_DPAD_LEFT && IsSubMenu()) {
        auto menuWrapper = GetMenuWrapper();
        CHECK_NULL_RETURN(menuWrapper, true);
        auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_RETURN(wrapperPattern, true);
        wrapperPattern->HideSubMenu();
        return true;
    }
    return false;
}

void MenuPattern::RemoveParentHoverStyle()
{
    if (!IsSubMenu()) {
        return;
    }
    auto menuItemParent = GetParentMenuItem();
    CHECK_NULL_VOID(menuItemParent);
    auto menuItemPattern = menuItemParent->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetIsSubMenuShowed(false);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    menuItemPattern->UpdateBackgroundColor(theme->GetBackgroundColor());
}

void MenuPattern::HideMenu() const
{
    if (IsContextMenu()) {
        SubwindowManager::GetInstance()->HideMenuNG(targetId_);
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->HideMenu(targetId_);
    LOGI("MenuPattern closing menu %{public}d", targetId_);
}

RefPtr<FrameNode> MenuPattern::GetMenuWrapper() const
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

// judge children has component menu
bool MenuPattern::IsMultiMenuOutside() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto child = host->GetChildAtIndex(0);
    while (child) {
        // is component menu
        if (child->GetTag() == V2::MENU_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(child);
        }
        child = child->GetChildAtIndex(0);
    }
    return false;
}

// mount option on menu
void MenuPattern::MountOption(const RefPtr<FrameNode>& option)
{
    auto column = GetMenuColumn();
    CHECK_NULL_VOID(column);
    auto pattern = option->GetPattern<OptionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenu(WeakClaim(RawPtr(GetHost())));
    AddOptionNode(option);
    option->MountToParent(column);
}

// remove option from menu
void MenuPattern::RemoveOption()
{
    auto column = GetMenuColumn();
    CHECK_NULL_VOID(column);
    auto endOption = column->GetChildren().back();
    CHECK_NULL_VOID(endOption);
    column->RemoveChild(endOption);
    PopOptionNode();
}

RefPtr<FrameNode> MenuPattern::GetMenuColumn() const
{
    auto menu = GetHost();
    CHECK_NULL_RETURN(menu, nullptr);
    auto scroll = menu->GetChildren().front();
    CHECK_NULL_RETURN(scroll, nullptr);
    auto column = scroll->GetChildren().front();
    return DynamicCast<FrameNode>(column);
}

void MenuPattern::DisableTabInMenu()
{
    if (IsMultiMenu()) {
        // multi menu not has scroll and column
        return;
    }
    // disable tab in menu
    auto column = GetMenuColumn();
    CHECK_NULL_VOID(column);
    auto columnFocusHub = column->GetOrCreateFocusHub();
    CHECK_NULL_VOID(columnFocusHub);

    auto onKeyEvent = [](const KeyEvent& event) -> bool {
        if (event.action != KeyAction::DOWN) {
            return false;
        }
        return event.code == KeyCode::KEY_TAB;
    };
    columnFocusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}
} // namespace OHOS::Ace::NG
