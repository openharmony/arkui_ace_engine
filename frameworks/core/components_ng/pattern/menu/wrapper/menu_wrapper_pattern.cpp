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

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t FOCUS_MENU_NUM = 2;
void MenuWrapperPattern::HideMenu(const RefPtr<FrameNode>& menu)
{
    if (GetHost()->GetTag() == V2::SELECT_OVERLAY_ETS_TAG) {
        return;
    }
    SetIsStopHoverImageAnimation(true);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->HideMenu();
}

void MenuWrapperPattern::OnModifyDone()
{
    InitFocusEvent();
}

void MenuWrapperPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu due to lost focus");
        pattern->HideMenu();
    };
    focusHub->SetOnBlurInternal(std::move(blurTask));
}

RefPtr<FrameNode> MenuWrapperPattern::GetShowedSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    return DynamicCast<FrameNode>(host->GetLastChild());
}

RectF MenuWrapperPattern::GetMenuZone(RefPtr<UINode>& innerMenuNode)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RectF());
    auto children = host->GetChildren();
    CHECK_NULL_RETURN(!children.empty(), RectF());
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        if (!child || child->GetTag() != V2::MENU_ETS_TAG) {
            continue;
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(frameNode, RectF());
        auto geometryNode = frameNode->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, RectF());
        innerMenuNode = GetMenuChild(frameNode);
        if (!innerMenuNode) {
            innerMenuNode = child;
        }
        return geometryNode->GetFrameRect() + host->GetPaintRectOffset();
    }
    return RectF();
}

RefPtr<FrameNode> MenuWrapperPattern::FindTouchedMenuItem(const RefPtr<UINode>& menuNode, const OffsetF& position)
{
    CHECK_NULL_RETURN(menuNode, nullptr);
    RefPtr<FrameNode> menuItem = nullptr;
    const auto& children = menuNode->GetChildren();
    for (auto child : children) {
        if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            auto pattern = frameNode ? frameNode->GetPattern<MenuItemPattern>() : nullptr;
            menuItem = pattern ? pattern->FindTouchedEmbeddedMenuItem(position) : nullptr;
        } else {
            menuItem = FindTouchedMenuItem(child, position);
        }
        if (menuItem) {
            auto menuItemOffset = menuItem->GetPaintRectOffset();
            auto menuItemSize = menuItem->GetGeometryNode()->GetFrameSize();
            auto menuItemZone =
                RectF(menuItemOffset.GetX(), menuItemOffset.GetY(), menuItemSize.Width(), menuItemSize.Height());
            if (menuItemZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
                break;
            } else {
                menuItem = nullptr;
            }
        }
    }
    return menuItem;
}

void MenuWrapperPattern::HandleInteraction(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(!info.GetChangedTouches().empty());
    auto touch = info.GetChangedTouches().front();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto position = OffsetF(
        static_cast<float>(touch.GetGlobalLocation().GetX()), static_cast<float>(touch.GetGlobalLocation().GetY()));
    RefPtr<UINode> innerMenuNode = nullptr;
    auto menuZone = GetMenuZone(innerMenuNode);
    CHECK_NULL_VOID(innerMenuNode);

    ClearLastMenuItem();
    // get menuNode's touch region
    if (menuZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
        currentTouchItem_ = FindTouchedMenuItem(innerMenuNode, position);
        ChangeCurMenuItemBgColor();
        lastTouchItem_ = currentTouchItem_;
    }
    innerMenuNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuWrapperPattern::ChangeCurMenuItemBgColor()
{
    if (!currentTouchItem_) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto curMenuItemPattern = currentTouchItem_->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(curMenuItemPattern);
    if (curMenuItemPattern->IsDisabled() || curMenuItemPattern->IsStackSubmenuHeader()) {
        return;
    }
    curMenuItemPattern->NotifyPressStatus(true);
}

void MenuWrapperPattern::ClearLastMenuItem()
{
    if (lastTouchItem_) {
        auto lastMenuItemPattern = lastTouchItem_->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(lastMenuItemPattern);
        lastMenuItemPattern->NotifyPressStatus(false);
        lastTouchItem_ = nullptr;
    }
}

void MenuWrapperPattern::OnAttachToFrameNode()
{
    RegisterOnTouch();
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
        HideSubMenu();
        menuItemPattern->OnHover(false);
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

void MenuWrapperPattern::GetExpandingMode(const RefPtr<UINode>& subMenu, SubMenuExpandingMode& expandingMode,
    bool& hasAnimation)
{
    CHECK_NULL_VOID(subMenu);
    auto subMenuNode = DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuNode);
    auto subMenuPattern = subMenuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(subMenuPattern);
    hasAnimation = subMenuPattern->GetDisappearAnimation();
    auto menuItem = FrameNode::GetFrameNode(subMenuPattern->GetTargetTag(), subMenuPattern->GetTargetId());
    CHECK_NULL_VOID(menuItem);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    auto menuNode = menuItemPattern->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    expandingMode = menuProperty->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    menuItemPattern->SetIsSubMenuShowed (false);
}

void MenuWrapperPattern::HideSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetChildren().size() <= 1) {
        // sub menu not show
        return;
    }
    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetShowedSubMenu(nullptr);
    auto subMenu = host->GetChildren().back();
    auto focusMenu = MenuFocusViewShow();
    CHECK_NULL_VOID(focusMenu);
    auto innerMenu = GetMenuChild(focusMenu);
    if (!innerMenu) {
        UpdateMenuAnimation(host);
        SendToAccessibility(subMenu, false);
        host->RemoveChild(subMenu);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        return;
    }
    auto innerMenuPattern = innerMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(innerMenuPattern);
    auto layoutProps = innerMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    auto outterMenuPattern = focusMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(outterMenuPattern);
    bool hasAnimation = outterMenuPattern->GetDisappearAnimation();
    GetExpandingMode(subMenu, expandingMode, hasAnimation);
    if (expandingMode == SubMenuExpandingMode::STACK && hasAnimation) {
        HideStackExpandMenu(subMenu);
    } else {
        UpdateMenuAnimation(host);
        SendToAccessibility(subMenu, false);
        host->RemoveChild(subMenu);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

void MenuWrapperPattern::SendToAccessibility(const RefPtr<UINode>& subMenu, bool isShow)
{
    auto subMenuNode = AceType::DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuNode);
    auto accessibilityProperty = subMenuNode->GetAccessibilityProperty<MenuAccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityIsShow(isShow);
    subMenuNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CLOSE);
}

bool MenuWrapperPattern::HasStackSubMenu()
{
    auto outterMenu = GetMenu();
    CHECK_NULL_RETURN(outterMenu, false);
    auto innerMenu = GetMenuChild(outterMenu);
    CHECK_NULL_RETURN(innerMenu, false);
    auto innerMenuPattern = innerMenu->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(innerMenuPattern, false);
    auto layoutProps = innerMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, false);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    if (expandingMode != SubMenuExpandingMode::STACK) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto menuCount = 0;
    for (const auto& child : host->GetChildren()) {
        if (child && child->GetTag() == V2::MENU_ETS_TAG) {
            menuCount++;
        }
    }
    return menuCount > 1;
}

bool MenuWrapperPattern::HasEmbeddedSubMenu()
{
    auto outterMenu = GetMenu();
    CHECK_NULL_RETURN(outterMenu, false);
    auto innerMenu = GetMenuChild(outterMenu);
    CHECK_NULL_RETURN(innerMenu, false);
    auto innerMenuPattern = innerMenu->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(innerMenuPattern, false);
    auto layoutProps = innerMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, false);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    return expandingMode == SubMenuExpandingMode::EMBEDDED;
}

RefPtr<FrameNode> MenuWrapperPattern::MenuFocusViewShow()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto iter = host->GetChildren().begin();
    int32_t focusNodeId = static_cast<int32_t>(host->GetChildren().size()) - FOCUS_MENU_NUM;
    CHECK_NULL_RETURN(focusNodeId >= 0, nullptr);
    std::advance(iter, focusNodeId);
    auto focusMenu = DynamicCast<FrameNode>(*iter);
    CHECK_NULL_RETURN(focusMenu, nullptr);
    if (GetPreviewMode() != MenuPreviewMode::NONE && focusNodeId == 1) {
        focusMenu = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_RETURN(focusMenu, nullptr);
    }
    // SelectOverlay's custom menu does not need to be focused.
    auto isCustomMenu = IsSelectOverlayCustomMenu(focusMenu);
    if (!isCustomMenu) {
        auto menuPattern = focusMenu->GetPattern<MenuPattern>();
        CHECK_NULL_RETURN(menuPattern, nullptr);
        menuPattern->FocusViewShow();
    }
    return DynamicCast<FrameNode>(focusMenu);
}

void MenuWrapperPattern::HideStackExpandMenu(const RefPtr<UINode>& subMenu)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuNode = host->GetFirstChild();
    CHECK_NULL_VOID(menuNode);
    AnimationOption option;
    option.SetOnFinishEvent(
        [weak = WeakClaim(RawPtr(host)), subMenuWk = WeakClaim(RawPtr(subMenu))] {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto taskExecutor = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak, subMenuWk]() {
                    auto subMenuNode = subMenuWk.Upgrade();
                    CHECK_NULL_VOID(subMenuNode);
                    auto menuWrapper = weak.Upgrade();
                    CHECK_NULL_VOID(menuWrapper);
                    menuWrapper->RemoveChild(subMenuNode);
                    menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
                },
                TaskExecutor::TaskType::UI, "HideStackExpandMenu");
    });
    auto menuNodePattern = DynamicCast<FrameNode>(menuNode)->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuNodePattern);
    menuNodePattern->ShowStackExpandDisappearAnimation(DynamicCast<FrameNode>(menuNode),
        DynamicCast<FrameNode>(subMenu), option);
    menuNodePattern->SetDisappearAnimation(true);
}

void MenuWrapperPattern::RegisterOnTouch()
{
    // if already initialized touch event
    CHECK_NULL_VOID(!onTouch_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    // hide menu when touched outside the menu region
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnTouchEvent(info);
    };
    onTouch_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(onTouch_);
}

void MenuWrapperPattern::OnTouchEvent(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(!info.GetChangedTouches().empty());
    auto touch = info.GetChangedTouches().front();
    // filter out other touch types
    if (touch.GetTouchType() != TouchType::DOWN &&
        Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    if (IsHide()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto position = OffsetF(
        static_cast<float>(touch.GetGlobalLocation().GetX()), static_cast<float>(touch.GetGlobalLocation().GetY()));
    position -= host->GetPaintRectOffset();
    auto children = host->GetChildren();
    if (touch.GetTouchType() == TouchType::DOWN) {
        // Record the latest touch finger ID. If other fingers are pressed, the latest one prevails
        fingerId_ = touch.GetFingerId();
        TAG_LOGD(AceLogTag::ACE_MENU, "record newest finger ID %{public}d", fingerId_);
        for (auto child = children.rbegin(); child != children.rend(); ++child) {
            // get child frame node of menu wrapper
            auto menuWrapperChildNode = DynamicCast<FrameNode>(*child);
            CHECK_NULL_VOID(menuWrapperChildNode);
            // get menuWrapperChildNode's touch region
            auto menuWrapperChildZone = menuWrapperChildNode->GetGeometryNode()->GetFrameRect();
            if (menuWrapperChildZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
                HandleInteraction(info);
                return;
            }
            // if DOWN-touched outside the menu region, then hide menu
            auto menuPattern = menuWrapperChildNode->GetPattern<MenuPattern>();
            if (!menuPattern) {
                continue;
            }
            TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu due to touch down");
            HideMenu(menuPattern, menuWrapperChildNode, position);
        }
        return;
    }
    // When the Move or Up event is not the recorded finger ID, this event is not responded
    if (fingerId_ != touch.GetFingerId()) {
        return;
    }
    ChangeTouchItem(info, touch.GetTouchType());
}

void MenuWrapperPattern::ChangeTouchItem(const TouchEventInfo& info, TouchType touchType)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (touchType == TouchType::MOVE) {
        auto menuNode = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_VOID(menuNode);
        if (GetPreviewMode() != MenuPreviewMode::NONE || IsSelectOverlayCustomMenu(menuNode)) {
            return;
        }
        HandleInteraction(info);
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        if (currentTouchItem_) {
            auto currentTouchItemPattern = currentTouchItem_->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(currentTouchItemPattern);
            currentTouchItemPattern->NotifyPressStatus(false);
            currentTouchItem_ = nullptr;
        }
        // Reset finger ID when touch Up or Cancel
        TAG_LOGD(AceLogTag::ACE_MENU, "reset finger ID %{public}d", fingerId_);
        fingerId_ = -1;
    }
}

void MenuWrapperPattern::HideMenu(const RefPtr<MenuPattern>& menuPattern, const RefPtr<FrameNode>& menu,
    const OffsetF& position)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mainMenu = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(mainMenu);
    auto mainMenuZone = mainMenu->GetGeometryNode()->GetFrameRect();
    bool isFindTargetId = false;
    if (mainMenuZone.IsInRegion(PointF(position.GetX(), position.GetY()))) {
        isFindTargetId = true;
    }
    if (menuPattern->IsSubMenu() || menuPattern->IsSelectOverlaySubMenu()) {
        if (HasStackSubMenu() && !isFindTargetId) {
            UpdateMenuAnimation(host);
        }
        HideSubMenu();
    } else {
        if (HasEmbeddedSubMenu() && embeddedSubMenuCount_ > 0 && !isFindTargetId) {
            UpdateMenuAnimation(host);
        }
        HideMenu(menu);
    }
}

void MenuWrapperPattern::UpdateMenuAnimation(const RefPtr<FrameNode>& host)
{
    // update Menu disappear animation direction
    // change to LEFT_BOTTOM -> RIGHT_TOP by calling SetExitAnimation
    // or keep BOTTOM -> TOP by default
    CHECK_NULL_VOID(host);
    auto outterMenu = host->GetFirstChild();
    CHECK_NULL_VOID(outterMenu);
    auto innerMenu = GetMenuChild(outterMenu);
    if (!innerMenu && host->GetChildren().size() > 1) {
        SetExitAnimation(host);
        return;
    }
    CHECK_NULL_VOID(innerMenu);
    auto innerMenuPattern = innerMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(innerMenuPattern);
    auto layoutProps = innerMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    if (host->GetChildren().size() > 1) {
        SetExitAnimation(host);
    }
    if (expandingMode == SubMenuExpandingMode::EMBEDDED && embeddedSubMenuCount_ > 0) {
        SetExitAnimation(host);
    }
}

void MenuWrapperPattern::SetExitAnimation(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto outterMenu = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(outterMenu);
    auto outterMenuPattern = outterMenu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(outterMenuPattern);
    outterMenuPattern->SetDisappearAnimation(false);
}

void MenuWrapperPattern::CheckAndShowAnimation()
{
    if (isFirstShow_) {
        // only start animation when menu wrapper mount on.
        StartShowAnimation();
        isFirstShow_ = false;
    }
}

void MenuWrapperPattern::MarkWholeSubTreeNoDraggable(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureEventHub = eventHub->GetGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    gestureEventHub->SetDragForbiddenForcely(true);
}

void MenuWrapperPattern::MarkAllMenuNoDraggable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (const auto& child : host->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::MENU_ETS_TAG) {
            MarkWholeSubTreeNoDraggable(node);
        }
    }
}

bool MenuWrapperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto expandDisplay = theme->GetExpandDisplay();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto menuNode = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_RETURN(menuNode, false);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menuNode->GetPattern());
    CHECK_NULL_RETURN(menuPattern, false);
    // copy menu pattern properties to rootMenu
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    isShowInSubWindow_ = layoutProperty->GetShowInSubWindowValue(true);
    if ((IsContextMenu() && !IsHide()) || ((expandDisplay && isShowInSubWindow_) && !IsHide())) {
        SetHotAreas(dirty);
    }
    MarkAllMenuNoDraggable();
    MarkWholeSubTreeNoDraggable(GetPreview());
    CheckAndShowAnimation();
    return false;
}

void MenuWrapperPattern::SetHotAreas(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    if ((layoutWrapper->GetAllChildrenWithBuild().empty() || !IsContextMenu()) &&
        !(expandDisplay && isShowInSubWindow_)) {
        return;
    }
    auto layoutProps = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    float safeAreaInsetsLeft = 0.0f;
    float safeAreaInsetsTop = 0.0f;
    auto&& safeAreaInsets = layoutProps->GetSafeAreaInsets();
    if (safeAreaInsets) {
        safeAreaInsetsLeft = static_cast<float>(safeAreaInsets->left_.end);
        safeAreaInsetsTop = static_cast<float>(safeAreaInsets->top_.end);
    }
    std::vector<Rect> rects;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto frameRect = child->GetGeometryNode()->GetFrameRect();
        // rect is relative to window
        auto childNode = child->GetHostNode();
        if (childNode &&
            (childNode->GetTag() == V2::MENU_PREVIEW_ETS_TAG || childNode->GetTag() == V2::IMAGE_ETS_TAG)) {
            frameRect = childNode->GetPaintRectWithTransform(); // get preview area with scale transform
        }
        auto rect = Rect(frameRect.GetX() + safeAreaInsetsLeft, frameRect.GetY() + safeAreaInsetsTop, frameRect.Width(),
            frameRect.Height());

        rects.emplace_back(rect);
    }
    // If container is UIExtensionWindow, set hotArea size equals to subwindow's filterColumnNode's size
    if (IsContextMenu() && GetPreviewMode() != MenuPreviewMode::NONE) {
        auto filterNode = GetFilterColumnNode();
        if (filterNode) {
            auto frameRect = filterNode->GetGeometryNode()->GetFrameRect();
            auto rect = Rect(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
            rects.emplace_back(rect);
        }
    }
    SubwindowManager::GetInstance()->SetHotAreas(rects, GetHost()->GetId(), GetContainerId());
}

void MenuWrapperPattern::StartShowAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (GetPreviewMode() == MenuPreviewMode::NONE) {
        context->UpdateOffset(GetAnimationOffset());
        context->UpdateOpacity(0.0);
    }

    AnimationUtils::Animate(
        animationOption_,
        [context, weak = WeakClaim(this)]() {
            if (context) {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (pattern->GetPreviewMode() == MenuPreviewMode::NONE) {
                    context->UpdateOffset(OffsetT<Dimension>());
                    context->UpdateOpacity(1.0);
                }
            }
        },
        animationOption_.GetOnFinishEvent());
}

void MenuWrapperPattern::SetAniamtinOption(const AnimationOption& animationOption)
{
    animationOption_.SetCurve(animationOption.GetCurve());
    animationOption_.SetDuration(animationOption.GetDuration());
    animationOption_.SetFillMode(animationOption.GetFillMode());
    animationOption_.SetOnFinishEvent(animationOption.GetOnFinishEvent());
}

OffsetT<Dimension> MenuWrapperPattern::GetAnimationOffset()
{
    OffsetT<Dimension> offset;

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, offset);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, offset);
    auto animationOffset = theme->GetMenuAnimationOffset();

    switch (menuPlacement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            offset.SetX(animationOffset);
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            offset.SetX(-animationOffset);
            break;
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            offset.SetY(animationOffset);
            break;
        default:
            offset.SetY(-animationOffset);
            break;
    }
    return offset;
}

bool MenuWrapperPattern::IsSelectOverlayCustomMenu(const RefPtr<FrameNode>& menu) const
{
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->IsSelectOverlayCustomMenu();
}

void MenuWrapperPattern::RegisterMenuCallback(const RefPtr<FrameNode>& menuWrapperNode, const MenuParam& menuParam)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "register menu enter");
    CHECK_NULL_VOID(menuWrapperNode);
    auto pattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RegisterMenuAppearCallback(menuParam.onAppear);
    pattern->RegisterMenuDisappearCallback(menuParam.onDisappear);
    pattern->RegisterMenuAboutToAppearCallback(menuParam.aboutToAppear);
    pattern->RegisterMenuAboutToDisappearCallback(menuParam.aboutToDisappear);
    pattern->RegisterMenuStateChangeCallback(menuParam.onStateChange);
}

void MenuWrapperPattern::SetMenuTransitionEffect(const RefPtr<FrameNode>& menuWrapperNode, const MenuParam& menuParam)
{
    TAG_LOGD(AceLogTag::ACE_DIALOG, "set menu transition effect");
    CHECK_NULL_VOID(menuWrapperNode);
    auto pattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHasTransitionEffect(menuParam.hasTransitionEffect);
    if (menuParam.hasTransitionEffect) {
        auto renderContext = menuWrapperNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        CHECK_NULL_VOID(menuParam.transition);
        renderContext->UpdateChainedTransition(menuParam.transition);
    }
    pattern->SetHasPreviewTransitionEffect(menuParam.hasPreviewTransitionEffect);
    if (menuParam.hasPreviewTransitionEffect) {
        auto previewChild = pattern->GetPreview();
        CHECK_NULL_VOID(previewChild);
        auto renderContext = previewChild->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        CHECK_NULL_VOID(menuParam.previewTransition);
        renderContext->UpdateChainedTransition(menuParam.previewTransition);
    }
}

RefPtr<FrameNode> MenuWrapperPattern::GetMenuChild(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    RefPtr<FrameNode> menuChild;
    auto child = node->GetChildAtIndex(0);
    while (child) {
        if (child->GetTag() == V2::JS_VIEW_ETS_TAG) {
            auto customNode = DynamicCast<CustomNode>(child);
            CHECK_NULL_RETURN(customNode, nullptr);
            customNode->Render();
        } else if (child->GetTag() == V2::MENU_ETS_TAG) {
            menuChild = DynamicCast<FrameNode>(child);
            break;
        }
        child = child->GetChildAtIndex(0);
    }
    return menuChild;
}

void MenuWrapperPattern::ClearAllSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (auto child = children.rbegin(); child != children.rend(); ++child) {
        auto frameNode = DynamicCast<FrameNode>(*child);
        if (!frameNode) {
            continue;
        }
        auto pattern = frameNode->GetPattern<MenuPattern>();
        if (pattern && pattern->IsSubMenu()) {
            host->RemoveChild(frameNode);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        }
    }
}

void MenuWrapperPattern::StopPreviewMenuAnimation()
{
    if (HasTransitionEffect() || HasPreviewTransitionEffect()) {
        return;
    }

    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuContext = menu->GetRenderContext();
    CHECK_NULL_VOID(menuContext);

    RefPtr<RenderContext> previewPositionContext;
    RefPtr<RenderContext> previewScaleContext;
    if (isShowHoverImage_) {
        auto flexNode = GetHoverImageFlexNode();
        CHECK_NULL_VOID(flexNode);
        previewPositionContext = flexNode->GetRenderContext();
        CHECK_NULL_VOID(previewPositionContext);

        auto stackNode = GetHoverImageStackNode();
        CHECK_NULL_VOID(stackNode);
        previewScaleContext = stackNode->GetRenderContext();
        CHECK_NULL_VOID(previewScaleContext);
    } else {
        auto preview = GetPreview();
        CHECK_NULL_VOID(preview);
        previewPositionContext = preview->GetRenderContext();
        CHECK_NULL_VOID(previewPositionContext);
        previewScaleContext = previewPositionContext;
    }

    auto option = AnimationOption(Curves::LINEAR, 0);
    AnimationUtils::Animate(option, [previewPositionContext, previewScaleContext, menuContext,
                                        previewStopOffset = previewDisappearStartOffset_,
                                        animationInfo = animationInfo_]() {
        auto previewOffset = previewStopOffset.NonOffset() ? animationInfo.previewOffset : previewStopOffset;
        if (previewPositionContext && !previewOffset.NonOffset()) {
            previewPositionContext->UpdatePosition(
                OffsetT<Dimension>(Dimension(previewOffset.GetX()), Dimension(previewOffset.GetY())));
        }

        auto menuOffset = animationInfo.menuOffset;
        if (menuContext && !menuOffset.NonOffset()) {
            menuContext->UpdatePosition(OffsetT<Dimension>(Dimension(menuOffset.GetX()), Dimension(menuOffset.GetY())));
        }

        if (menuContext && Positive(animationInfo.menuScale)) {
            menuContext->UpdateTransformScale(VectorF(animationInfo.menuScale, animationInfo.menuScale));
        }

        if (previewScaleContext && Positive(animationInfo.previewScale)) {
            previewScaleContext->UpdateTransformScale(VectorF(animationInfo.previewScale, animationInfo.previewScale));

            if (Positive(animationInfo.borderRadius)) {
                previewScaleContext->UpdateBorderRadius(BorderRadiusProperty(Dimension(animationInfo.borderRadius)));
            }
        }
    });
}

void MenuWrapperPattern::RequestPathRender()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<MenuWrapperPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto flag = paintProperty->GetRenderFlagValue(0);
    flag++;
    paintProperty->UpdateRenderFlag(flag);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuWrapperPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc("MenuPreviewMode: " + std::to_string(dumpInfo_.menuPreviewMode));
    DumpLog::GetInstance().AddDesc("MenuType: " + std::to_string(dumpInfo_.menuType));
    DumpLog::GetInstance().AddDesc("EnableArrow: " + std::to_string(dumpInfo_.enableArrow));
    DumpLog::GetInstance().AddDesc("Offset: " + dumpInfo_.offset.ToString());
    DumpLog::GetInstance().AddDesc("TargetNode: " + dumpInfo_.targetNode);
    DumpLog::GetInstance().AddDesc("TargetOffset: " + dumpInfo_.targetOffset.ToString());
    DumpLog::GetInstance().AddDesc("TargetSize: " + dumpInfo_.targetSize.ToString());
    DumpLog::GetInstance().AddDesc("MenuWindowRect: " + dumpInfo_.menuWindowRect.ToString());
    DumpLog::GetInstance().AddDesc("WrapperRect: " + dumpInfo_.wrapperRect.ToString());
    DumpLog::GetInstance().AddDesc("PreviewBeginScale: " + std::to_string(dumpInfo_.previewBeginScale));
    DumpLog::GetInstance().AddDesc("PreviewEndScale: " + std::to_string(dumpInfo_.previewEndScale));
    DumpLog::GetInstance().AddDesc("Top: " + std::to_string(dumpInfo_.top));
    DumpLog::GetInstance().AddDesc("Bottom: " + std::to_string(dumpInfo_.bottom));
    DumpLog::GetInstance().AddDesc("Left: " + std::to_string(dumpInfo_.left));
    DumpLog::GetInstance().AddDesc("Right: " + std::to_string(dumpInfo_.right));
    DumpLog::GetInstance().AddDesc("GlobalLocation: " + dumpInfo_.globalLocation.ToString());
    DumpLog::GetInstance().AddDesc("OriginPlacement: " + dumpInfo_.originPlacement);
    DumpLog::GetInstance().AddDesc("DefaultPlacement: " + dumpInfo_.defaultPlacement);
    DumpLog::GetInstance().AddDesc("FinalPosition: " + dumpInfo_.finalPosition.ToString());
    DumpLog::GetInstance().AddDesc("FinalPlacement: " + dumpInfo_.finalPlacement);
}

void MenuWrapperPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("MenuPreviewMode", std::to_string(dumpInfo_.menuPreviewMode).c_str());
    json->Put("MenuType", std::to_string(dumpInfo_.menuType).c_str());
    json->Put("EnableArrow", std::to_string(dumpInfo_.enableArrow).c_str());
    json->Put("TargetNode", dumpInfo_.targetNode.c_str());
    json->Put("TargetOffset", dumpInfo_.targetOffset.ToString().c_str());

    json->Put("TargetSize", dumpInfo_.targetSize.ToString().c_str());
    json->Put("MenuWindowRect", dumpInfo_.menuWindowRect.ToString().c_str());
    json->Put("WrapperRect", dumpInfo_.wrapperRect.ToString().c_str());
    json->Put("PreviewBeginScale", std::to_string(dumpInfo_.previewBeginScale).c_str());
    json->Put("PreviewEndScale", std::to_string(dumpInfo_.previewEndScale).c_str());
    json->Put("Top", std::to_string(dumpInfo_.top).c_str());
    json->Put("Bottom", std::to_string(dumpInfo_.bottom).c_str());
    json->Put("Left", std::to_string(dumpInfo_.left).c_str());
    json->Put("Right", std::to_string(dumpInfo_.right).c_str());
    json->Put("GlobalLocation", dumpInfo_.globalLocation.ToString().c_str());
    json->Put("OriginPlacement", dumpInfo_.originPlacement.c_str());
    json->Put("DefaultPlacement", dumpInfo_.defaultPlacement.c_str());
    json->Put("FinalPosition", dumpInfo_.finalPosition.ToString().c_str());
    json->Put("FinalPlacement", dumpInfo_.finalPlacement.c_str());
}
} // namespace OHOS::Ace::NG
