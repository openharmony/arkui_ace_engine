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
#include "base/utils/multi_thread.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/interfaces/native/node/menu_modifier.h"
#include "core/interfaces/native/node/menu_item_modifier.h"

namespace OHOS::Ace::NG {
namespace {
std::string ConvertModalModeToString(std::optional<ModalMode> modalModeOpt)
{
    if (!modalModeOpt.has_value()) {
        return "undefined";
    }
    auto modalMode = modalModeOpt.value();
    switch (modalMode) {
        case ModalMode::AUTO:
            return "ModalMode.AUTO";
        case ModalMode::NONE:
            return "ModalMode.NONE";
        case ModalMode::TARGET_WINDOW:
            return "ModalMode.TARGET_WINDOW";
        default:
            return "ModalMode.AUTO";
    }
}
} // namespace
RefPtr<FrameNode> MenuWrapperPattern::GetHoverImageFlexNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto node = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_RETURN(node, nullptr);
    if (node->GetTag() != V2::FLEX_ETS_TAG) {
        return nullptr;
    }
    return node;
}

RefPtr<FrameNode> MenuWrapperPattern::GetHoverImageStackNode()
{
    auto hoverImageFlexNode = GetHoverImageFlexNode();
    CHECK_NULL_RETURN(hoverImageFlexNode, nullptr);
    auto node = AceType::DynamicCast<FrameNode>(hoverImageFlexNode->GetChildAtIndex(0));
    CHECK_NULL_RETURN(node, nullptr);
    if (node->GetTag() != V2::STACK_ETS_TAG) {
        return nullptr;
    }
    return node;
}

RefPtr<FrameNode> MenuWrapperPattern::GetHoverImagePreview()
{
    auto hoverImageStackNode = GetHoverImageStackNode();
    CHECK_NULL_RETURN(hoverImageStackNode, nullptr);
    auto node = AceType::DynamicCast<FrameNode>(hoverImageStackNode->GetChildAtIndex(0));
    CHECK_NULL_RETURN(node, nullptr);
    if (node->GetTag() != V2::IMAGE_ETS_TAG) {
        return nullptr;
    }
    return node;
}

RefPtr<FrameNode> MenuWrapperPattern::GetHoverImageCustomPreview()
{
    auto hoverImageStackNode = GetHoverImageStackNode();
    CHECK_NULL_RETURN(hoverImageStackNode, nullptr);
    auto node = AceType::DynamicCast<FrameNode>(hoverImageStackNode->GetChildAtIndex(1));
    CHECK_NULL_RETURN(node, nullptr);
    if (node->GetTag() != V2::MENU_PREVIEW_ETS_TAG) {
        return nullptr;
    }
    return node;
}

RefPtr<FrameNode> MenuWrapperPattern::GetPreview()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto preview = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_RETURN(preview, nullptr);
    if (preview->GetTag() == V2::FLEX_ETS_TAG) {
        auto hoverImageCustomPreview = GetHoverImageCustomPreview();
        CHECK_NULL_RETURN(hoverImageCustomPreview, preview);
        return hoverImageCustomPreview;
    }
    return preview;
}

// used to obtain the Badge node and delete it.
RefPtr<FrameNode> MenuWrapperPattern::GetBadgeNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    for (const auto& child : host->GetChildren()) {
        auto node = DynamicCast<FrameNode>(child);
        if (node && node->GetTag() == V2::TEXT_ETS_TAG) {
            return node;
        }
    }
    return nullptr;
}

void MenuWrapperPattern::HideMenu(const RefPtr<FrameNode>& menu, const HideMenuType& reason)
{
    CHECK_NULL_VOID(menu);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetTag() == V2::SELECT_OVERLAY_ETS_TAG) {
        return;
    }
    SetIsStopHoverImageAnimation(true);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    menuModifier->hideMenu(menu, reason);
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
        pattern->HideMenu(HideMenuType::WRAPPER_LOSE_FOCUS);
    };
    focusHub->SetOnBlurInternal(std::move(blurTask));
}

RefPtr<FrameNode> MenuWrapperPattern::GetShowedSubMenu()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    return DynamicCast<FrameNode>(host->GetLastChild());
}

bool MenuWrapperPattern::GetInnerMenu(RefPtr<UINode>& innerMenuNode, const PointF& position)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto children = host->GetChildren();
    CHECK_NULL_RETURN(!children.empty(), false);
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        if (!child || child->GetTag() != V2::MENU_ETS_TAG) {
            continue;
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(frameNode, false);
        const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
        CHECK_NULL_RETURN(menuModifier, false);
        auto subMenuNode = menuModifier->getShowedSubMenu(frameNode);
        innerMenuNode = subMenuNode ? subMenuNode : menuModifier->getFirstInnerMenu(frameNode);
        if (!innerMenuNode) {
            innerMenuNode = child;
        }
        auto geometryNode = frameNode->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, false);
        return CheckPointInMenuZone(frameNode, position);
    }
    return false;
}

RefPtr<FrameNode> MenuWrapperPattern::FindTouchedMenuItem(const RefPtr<UINode>& menuNode, const PointF& position)
{
    CHECK_NULL_RETURN(menuNode, nullptr);
    RefPtr<FrameNode> menuItem = nullptr;
    const auto& children = menuNode->GetChildren();
    for (auto child : children) {
        if (!child) {
            continue;
        }
        if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
            menuItem = menuItemModifier ? menuItemModifier->findTouchedEmbeddedMenuItem(child, position) : nullptr;
        } else {
            menuItem = FindTouchedMenuItem(child, position);
        }
        if (menuItem) {
            if (CheckPointInMenuZone(menuItem, position)) {
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
    auto position = PointF(
        static_cast<float>(touch.GetGlobalLocation().GetX()), static_cast<float>(touch.GetGlobalLocation().GetY()));
    RefPtr<UINode> innerMenuNode = nullptr;
    auto isInRegion = GetInnerMenu(innerMenuNode, position);
    CHECK_NULL_VOID(innerMenuNode);

    if (isClearLastMenuItem_ || isInRegion) {
        ClearLastMenuItem();
    }
    // get menuNode's touch region
    if (isInRegion) {
        isClearLastMenuItem_ = true;
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
    CHECK_NULL_VOID(menuItemModifier);
    if (menuItemModifier->isDisabled(currentTouchItem_) || menuItemModifier->isStackSubmenuHeader(currentTouchItem_)) {
        return;
    }
    menuItemModifier->notifyPressStatus(currentTouchItem_, true);
}

void MenuWrapperPattern::ClearLastMenuItem()
{
    if (lastTouchItem_) {
        const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
        CHECK_NULL_VOID(menuItemModifier);
        menuItemModifier->notifyPressStatus(lastTouchItem_, false);
        lastTouchItem_ = nullptr;
    }
}

void MenuWrapperPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode);
    RegisterOnTouch();
}

void MenuWrapperPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    THREAD_SAFE_NODE_CHECK(host, OnAttachToMainTree);
    RegisterDetachCallback();
}

void MenuWrapperPattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    THREAD_SAFE_NODE_CHECK(host, OnDetachFromMainTree);
    OnDetachFromMainTreeImpl();
}

void MenuWrapperPattern::OnDetachFromMainTreeImpl()
{
    UnRegisterDetachCallback();
    CHECK_NULL_VOID(filterColumnNode_);
    auto pipeline = filterColumnNode_->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlay = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlay);
    overlay->RemoveMenuFilter(GetHost());
}

void MenuWrapperPattern::RegisterDetachCallback()
{
    auto targetNode = FrameNode::GetFrameNodeOnly(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto destructor = [id = targetNode->GetId(),
                          weakMenuWrapper = AceType::WeakClaim(AceType::RawPtr(host))]() mutable {
        auto wrapperNode = weakMenuWrapper.Upgrade();
        CHECK_NULL_VOID(wrapperNode);
        auto context = wrapperNode->GetContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        taskExecutor->PostTask(
            [id, weakOverlay = AceType::WeakClaim(AceType::RawPtr(overlayManager))]() {
                auto overlayManager = weakOverlay.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->DeleteMenu(id);
                const auto* menuViewModifier = NG::NodeModifier::GetMenuViewInnerModifier();
                menuViewModifier ? menuViewModifier->removeMenuHoverScaleStatus(id) : void();
            },
            TaskExecutor::TaskType::UI, "TargetDestroyDeleteMenu");
    };
    targetNode->PushDestroyCallbackWithTag(destructor, std::to_string(host->GetId()));
}

void MenuWrapperPattern::UnRegisterDetachCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetNode = FrameNode::GetFrameNodeOnly(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    targetNode->RemoveDestroyCallbackWithTag(std::to_string(host->GetId()));
}

// close subMenu when mouse move outside
void MenuWrapperPattern::HandleMouseEvent(const MouseInfo& info, const RefPtr<FrameNode>& menuItemNode)
{
    CHECK_NULL_VOID(menuItemNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto subMenu = host->GetChildren().back();
    if (host->GetChildren().size() <= 1) {
        return;
    }
    auto subMenuNode = DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuNode);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    auto currentHoverMenuItem = menuModifier->getParentMenuItem(subMenuNode);
    CHECK_NULL_VOID(currentHoverMenuItem);
    auto geometryNode = subMenuNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto offset = subMenuNode->GetPaintRectOffset(false, true);
    auto frameSize = geometryNode->GetFrameSize();
    auto menuZone = RectF(offset.GetX(), offset.GetY(), frameSize.Width(), frameSize.Height());
    if (currentHoverMenuItem->GetId() != menuItemNode->GetId()) {
        return;
    }
    const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
    const auto& mousePosition = info.GetGlobalLocation();
    if (!menuItemModifier->isInHoverRegions(menuItemNode, mousePosition.GetX(), mousePosition.GetY()) &&
        menuItemModifier->isSubMenuShowed(menuItemNode)) {
        menuItemModifier->checkHideSubMenu(
            menuItemNode,
            [weak = WeakClaim(this), weakSubMenu = WeakClaim(RawPtr(subMenuNode))] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto subMenu = weakSubMenu.Upgrade();
                CHECK_NULL_VOID(subMenu);
                if (subMenu == pattern->GetShowedSubMenu()) {
                    pattern->HideSubMenu();
                }
            },
            PointF(mousePosition.GetX(), mousePosition.GetY()), menuZone);
    } else {
        menuItemModifier->cancelHideSubMenuTask(menuItemNode, PointF(mousePosition.GetX(), mousePosition.GetY()));
    }
}

void MenuWrapperPattern::HideMenu(const HideMenuType& reason)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuNode = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(menuNode);
    HideMenu(menuNode, reason);
}

void MenuWrapperPattern::GetExpandingMode(const RefPtr<UINode>& subMenu, SubMenuExpandingMode& expandingMode,
    bool& hasAnimation)
{
    CHECK_NULL_VOID(subMenu);
    auto subMenuNode = DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuNode);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    hasAnimation = menuModifier->getDisappearAnimation(subMenuNode);
    auto menuItem =
        FrameNode::GetFrameNode(menuModifier->getTargetTag(subMenuNode), menuModifier->getTargetId(subMenuNode));
    CHECK_NULL_VOID(menuItem);
    const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
    CHECK_NULL_VOID(menuItemModifier);
    auto menuNode = menuItemModifier->getMenu(menuItem, false);
    CHECK_NULL_VOID(menuNode);
    expandingMode = menuModifier->getExpandingMode(menuNode).value_or(SubMenuExpandingMode::SIDE);
    menuItemModifier->setIsSubMenuShowed(menuItem, false);
}

void MenuWrapperPattern::HideSubMenuByDepth(const RefPtr<FrameNode>& menuItem)
{
    CHECK_NULL_VOID(menuItem);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetChildren().size() <= 1) {
        // sub menu not show
        return;
    }
    const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
    CHECK_NULL_VOID(menuItemModifier);
    auto menuNode = menuItemModifier->getMenu(menuItem, true);
    CHECK_NULL_VOID(menuNode);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    auto curDepth = menuModifier->getSubMenuDepth(menuNode);
    auto children = host->GetChildren();
    bool clearShowedSubMenu = true;
    for (auto child = children.rbegin(); child != children.rend(); ++child) {
        auto childNode = DynamicCast<FrameNode>(*child);
        CHECK_NULL_VOID(childNode);
        if (childNode->GetTag() != V2::MENU_ETS_TAG) {
            continue;
        }
        if (menuModifier->getSubMenuDepth(childNode) <= curDepth) {
            break;
        }
        auto parentMenuItem = menuModifier->getParentMenuItem(childNode);
        CHECK_NULL_VOID(parentMenuItem);
        if (menuItemModifier->hasHideTask(parentMenuItem)) {
            clearShowedSubMenu = false;
            continue;
        }
        if (parentMenuItem->GetId() == menuItem->GetId()) {
            clearShowedSubMenu = false;
            break;
        }
        menuModifier->removeParentHoverStyle(childNode);
        UpdateMenuAnimation(host);
        SendToAccessibility(childNode, false);
        host->RemoveChild(childNode);
    }
    if (clearShowedSubMenu) {
        menuModifier->setShowedSubMenu(menuNode, nullptr);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
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
    CHECK_NULL_VOID(subMenu);
    auto subMenuFrameNode = DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuFrameNode);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    menuModifier->removeParentHoverStyle(subMenuFrameNode);

    auto menuNode = GetParentMenu(subMenu);
    CHECK_NULL_VOID(menuNode);
    MenuFocusViewShow(menuNode);
    menuModifier->setShowedSubMenu(menuNode, nullptr);
    auto innerMenu = GetMenuChild(menuNode);
    if (!innerMenu) {
        UpdateMenuAnimation(host);
        SendToAccessibility(subMenu, false);
        host->RemoveChild(subMenu);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        return;
    }
    auto layoutProps = menuModifier->getLayoutProperty(innerMenu);
    CHECK_NULL_VOID(layoutProps);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    bool hasAnimation = menuModifier->getDisappearAnimation(menuNode);
    GetExpandingMode(subMenu, expandingMode, hasAnimation);
    if (expandingMode == SubMenuExpandingMode::STACK && hasAnimation) {
        HideStackExpandMenu(subMenu);
    } else {
        UpdateMenuAnimation(host);
        ShowSubMenuDisappearAnimation(host, subMenu);
    }
}

void MenuWrapperPattern::ShowSubMenuDisappearAnimation(const RefPtr<FrameNode>& host, const RefPtr<UINode>& subMenu)
{
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(subMenu);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (theme->GetMenuAnimationDuration()) {
        auto animationOption = AnimationOption();
        animationOption.SetDuration(theme->GetMenuAnimationDuration());
        animationOption.SetCurve(theme->GetMenuAnimationCurve());
        double scale = theme->GetMenuAnimationScale();
        AnimationUtils::Animate(
            animationOption,
            [weak = WeakClaim(RawPtr(subMenu)), scale]() {
                auto subMenuNode = weak.Upgrade();
                CHECK_NULL_VOID(subMenuNode);
                auto subMenu = AceType::DynamicCast<FrameNode>(subMenuNode);
                CHECK_NULL_VOID(subMenu);
                auto renderContext = subMenu->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateTransformScale(VectorF(scale, scale));
                renderContext->UpdateOpacity(MENU_ANIMATION_MIN_OPACITY);
            },
            [hostWeak = WeakClaim(RawPtr(host)), subMenuWeak = WeakClaim(RawPtr(subMenu))]() {
                auto host = hostWeak.Upgrade();
                CHECK_NULL_VOID(host);
                auto subMenu = subMenuWeak.Upgrade();
                CHECK_NULL_VOID(subMenu);
                auto wrapperPattern = host->GetPattern<MenuWrapperPattern>();
                if (wrapperPattern) {
                    wrapperPattern->SendToAccessibility(subMenu, false);
                }
                host->RemoveChild(subMenu);
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
            }, nullptr, host->GetContextRefPtr());
    } else {
        SendToAccessibility(subMenu, false);
        host->RemoveChild(subMenu);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

RefPtr<FrameNode> MenuWrapperPattern::GetParentMenu(const RefPtr<UINode>& subMenu)
{
    auto subMenuNode = AceType::DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_RETURN(subMenuNode, nullptr);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, nullptr);
    auto menuItem = menuModifier->getParentMenuItem(subMenuNode);
    CHECK_NULL_RETURN(menuItem, nullptr);
    const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
    CHECK_NULL_RETURN(menuItemModifier, nullptr);
    return menuItemModifier->getMenu(menuItem, true);
}

void MenuWrapperPattern::SendToAccessibility(const RefPtr<UINode>& subMenu, bool isShow)
{
    auto subMenuNode = AceType::DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuNode);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    menuModifier->setAccessibilityIsShow(subMenuNode, isShow);
    subMenuNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CLOSE);
}

bool MenuWrapperPattern::HasStackSubMenu()
{
    auto outterMenu = GetMenu();
    CHECK_NULL_RETURN(outterMenu, false);
    auto innerMenu = GetMenuChild(outterMenu);
    CHECK_NULL_RETURN(innerMenu, false);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    auto layoutProps = menuModifier->getLayoutProperty(innerMenu);
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
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    auto layoutProps = menuModifier->getLayoutProperty(innerMenu);
    CHECK_NULL_RETURN(layoutProps, false);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    return expandingMode == SubMenuExpandingMode::EMBEDDED;
}

bool MenuWrapperPattern::HasSideSubMenu()
{
    auto outterMenu = GetMenu();
    CHECK_NULL_RETURN(outterMenu, false);
    auto innerMenu = GetMenuChild(outterMenu);
    CHECK_NULL_RETURN(innerMenu, false);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    auto layoutProps = menuModifier->getLayoutProperty(innerMenu);
    CHECK_NULL_RETURN(layoutProps, false);
    auto expandingMode = layoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    return expandingMode == SubMenuExpandingMode::SIDE;
}

void MenuWrapperPattern::MenuFocusViewShow(const RefPtr<FrameNode>& menuNode)
{
    CHECK_NULL_VOID(menuNode);
    // SelectOverlay's custom menu does not need to be focused.
    auto isCustomMenu = IsSelectOverlayCustomMenu(menuNode);
    auto isRightClickMenu = IsSelectOverlayRightClickMenu(menuNode);
    if (!isCustomMenu && !isRightClickMenu) {
        const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
        CHECK_NULL_VOID(menuModifier);
        menuModifier->focusViewShow(menuNode, false);
    }
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
            auto host = weak.Upgrade();
            CHECK_NULL_VOID(host);
            auto pipeline = host->GetContext();
            CHECK_NULL_VOID(pipeline);
            auto taskExecutor = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak, subMenuWk]() {
                    auto subMenuNode = subMenuWk.Upgrade();
                    CHECK_NULL_VOID(subMenuNode);
                    auto menuWrapper = weak.Upgrade();
                    CHECK_NULL_VOID(menuWrapper);

                    auto subMenuFrameNode = DynamicCast<FrameNode>(subMenuNode);
                    CHECK_NULL_VOID(subMenuFrameNode);
                    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
                    CHECK_NULL_VOID(menuModifier);
                    menuModifier->setAccessibilityIsShow(subMenuFrameNode, false);
                    subMenuFrameNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CLOSE,
                        WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
                    TAG_LOGI(AceLogTag::ACE_MENU, "Send event to %{public}d",
                        static_cast<int32_t>(AccessibilityEventType::PAGE_CLOSE));

                    menuWrapper->RemoveChild(subMenuNode);
                    menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
                },
                TaskExecutor::TaskType::UI, "HideStackExpandMenu");
    });
    auto menuFrameNode = DynamicCast<FrameNode>(menuNode);
    CHECK_NULL_VOID(menuFrameNode);
    auto subMenuFrameNode = DynamicCast<FrameNode>(subMenu);
    CHECK_NULL_VOID(subMenuFrameNode);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    menuModifier->showStackMenuDisappearAnimation(menuFrameNode, subMenuFrameNode, option);
    menuModifier->setDisappearAnimation(menuFrameNode, true);
    menuModifier->setSubMenuShow(subMenuFrameNode, false);
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

    auto position = PointF(
        static_cast<float>(touch.GetGlobalLocation().GetX()), static_cast<float>(touch.GetGlobalLocation().GetY()));
    auto children = host->GetChildren();
    if (touch.GetTouchType() == TouchType::DOWN) {
        // Record the latest touch finger ID. If other fingers are pressed, the latest one prevails
        fingerId_ = touch.GetFingerId();
        TAG_LOGD(AceLogTag::ACE_MENU, "record newest finger ID %{public}d", fingerId_);
        std::vector<RefPtr<FrameNode>> toHideMenus;
        for (auto child = children.rbegin(); child != children.rend(); ++child) {
            auto menuWrapperChildNode = DynamicCast<FrameNode>(*child);
            CHECK_NULL_VOID(menuWrapperChildNode);
            // get menuWrapperChildNode's touch region
            if (CheckPointInMenuZone(menuWrapperChildNode, position)) {
                HandleInteraction(info);
                break;
            }
            const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
            CHECK_NULL_CONTINUE(menuModifier);
            isClearLastMenuItem_ = true;
            if ((menuModifier->isSubMenu(menuWrapperChildNode) ||
                    menuModifier->isSelectOverlaySubMenu(menuWrapperChildNode)) &&
                HasSideSubMenu() && IsTouchWithinParentMenuItemZone(child, children, position)) {
                continue;
            }
            // if DOWN-touched outside the menu region, then hide menu
            TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu due to touch down");
            toHideMenus.push_back(menuWrapperChildNode);
        }
        if (!toHideMenus.empty()) {
            for (auto node : toHideMenus) {
                HideMenu(node, position, HideMenuType::WRAPPER_TOUCH_DOWN);
            }
            toHideMenus.clear();
        }
        return;
    }
    // When the Move or Up event is not the recorded finger ID, this event is not responded
    if (fingerId_ != touch.GetFingerId()) {
        return;
    }
    ChangeTouchItem(info, touch.GetTouchType());
}

bool MenuWrapperPattern::IsTouchWithinParentMenuItemZone(std::list<RefPtr<UINode>>::reverse_iterator& child,
    const std::list<RefPtr<UINode>>& children, const PointF& position)
{
    auto currentMenuNode = DynamicCast<FrameNode>(*child);
    CHECK_NULL_RETURN(currentMenuNode, false);
    auto menuIterator = child;
    menuIterator++;
    while (menuIterator != children.rend()) {
        auto parentMenuNode = DynamicCast<FrameNode>(*menuIterator);
        CHECK_NULL_RETURN(parentMenuNode, false);
        if (parentMenuNode->GetTag() != V2::MENU_ETS_TAG) {
            menuIterator++;
            continue;
        }
        if (CheckPointInMenuZone(parentMenuNode, position)) {
            const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
            CHECK_NULL_RETURN(menuModifier, false);
            auto innerMenuNode = menuModifier->getFirstInnerMenu(parentMenuNode);
            if (!innerMenuNode) {
                innerMenuNode = parentMenuNode;
            }
            auto currentTouchItem = FindTouchedMenuItem(innerMenuNode, position);
            if (currentTouchItem == menuModifier->getParentMenuItem(currentMenuNode)) {
                ClearLastMenuItem();
                currentTouchItem_ = currentTouchItem;
                ChangeCurMenuItemBgColor();
                lastTouchItem_ = currentTouchItem_;
                isClearLastMenuItem_ = false;
                return true;
            }
        }
        return false;
    }
    return false;
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
            const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
            menuItemModifier ? menuItemModifier->notifyPressStatus(currentTouchItem_, false) : void();
            currentTouchItem_ = nullptr;
        }
        // Reset finger ID when touch Up or Cancel
        TAG_LOGD(AceLogTag::ACE_MENU, "reset finger ID %{public}d", fingerId_);
        fingerId_ = -1;
    }
}

void MenuWrapperPattern::HideMenu(const RefPtr<FrameNode>& menu, const PointF& position, const HideMenuType& reason)
{
    CHECK_NULL_VOID(menu);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mainMenu = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(mainMenu);
    bool isFindTargetId = false;
    if (CheckPointInMenuZone(mainMenu, position)) {
        isFindTargetId = true;
    }
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    auto isSubMenu = menuModifier ? menuModifier->isSubMenu(menu) : false;
    auto isSelectOverlaySubMenu = menuModifier ? menuModifier->isSelectOverlaySubMenu(menu) : false;
    if (isSubMenu || isSelectOverlaySubMenu) {
        if (HasStackSubMenu() && !isFindTargetId) {
            UpdateMenuAnimation(host);
        }
        HideSubMenu();
    } else {
        if (HasEmbeddedSubMenu() && embeddedSubMenuCount_ > 0 && !isFindTargetId) {
            UpdateMenuAnimation(host);
        }
        HideMenu(menu, reason);
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
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    auto layoutProps = menuModifier->getLayoutProperty(innerMenu);
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
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_VOID(menuModifier);
    menuModifier->setDisappearAnimation(outterMenu, false);
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
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
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
    forceUpdateEmbeddedMenu_ = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto expandDisplay = theme->GetExpandDisplay();
    auto menuNode = DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_RETURN(menuNode, false);
    // copy menu pattern properties to rootMenu
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    auto layoutProperty = menuModifier->getLayoutProperty(menuNode);
    CHECK_NULL_RETURN(layoutProperty, false);
    isShowInSubWindow_ = layoutProperty->GetShowInSubWindowValue(true);
    if (host->IsOnMainTree() &&
        ((IsContextMenu() && !IsHide()) || (((expandDisplay || isOpenMenu_) && isShowInSubWindow_) && !IsHide()) ||
            GetIsSelectOverlaySubWindowWrapper())) {
        SetHotAreas(dirty);
    }
    MarkAllMenuNoDraggable();
    MarkWholeSubTreeNoDraggable(GetPreview());
    if (!GetHoverScaleInterruption()) {
        CheckAndShowAnimation();
    }
    return false;
}

bool MenuWrapperPattern::IsNeedSetHotAreas(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    bool menuNotNeedsHotAreas = (layoutWrapper->GetAllChildrenWithBuild().empty() || !IsContextMenu()) &&
                                !((theme->GetExpandDisplay() || isOpenMenu_) && isShowInSubWindow_);
    if (menuNotNeedsHotAreas && !GetIsSelectOverlaySubWindowWrapper()) {
        return false;
    }

    return true;
}

void MenuWrapperPattern::AddTargetWindowHotArea(std::vector<Rect>& rects)
{
    if (menuParam_.modalMode.value_or(ModalMode::AUTO) != ModalMode::TARGET_WINDOW) {
        return;
    }
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    auto context = targetNode->GetContext();
    CHECK_NULL_VOID(context);
    auto container = AceEngine::Get().GetContainer(context->GetInstanceId());
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer()) {
        return;
    }
    if (container->IsUIExtensionWindow()) {
        auto windowRect = container->GetUIExtensionHostWindowRect();
        rects.emplace_back(windowRect);
    } else {
        auto windowRect = context->GetDisplayWindowRectInfo();
        auto titleHeight = context->GetCustomTitleHeight().ConvertToPx();
        rects.emplace_back(Rect(
            windowRect.Left(), windowRect.Top() + titleHeight, windowRect.Width(), windowRect.Height() - titleHeight));
    }
}

void MenuWrapperPattern::AddWrapperChildHotArea(std::vector<Rect>& rects, const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto layoutProps = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    float safeAreaInsetsLeft = 0.0f;
    float safeAreaInsetsTop = 0.0f;
    auto&& safeAreaInsets = layoutProps->GetSafeAreaInsets();
    if (safeAreaInsets) {
        safeAreaInsetsLeft = static_cast<float>(safeAreaInsets->left_.end);
        safeAreaInsetsTop = static_cast<float>(safeAreaInsets->top_.end);
    }
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        CHECK_NULL_VOID(child);
        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        auto frameRect = childGeometryNode->GetFrameRect();
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
}

void MenuWrapperPattern::AddFilterHotArea(std::vector<Rect>& rects)
{
    if (!IsContextMenu() || GetPreviewMode() == MenuPreviewMode::NONE) {
        return;
    }
    auto filterNode = GetFilterColumnNode();
    if (filterNode && GetIsFilterInSubwindow()) {
        auto filterNodeGeometryNode = filterNode->GetGeometryNode();
        CHECK_NULL_VOID(filterNodeGeometryNode);
        auto frameRect = filterNodeGeometryNode->GetFrameRect();
        auto rect = Rect(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
        rects.emplace_back(rect);
    }
}

void MenuWrapperPattern::SetHotAreas(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (!IsNeedSetHotAreas(layoutWrapper)) {
        return;
    }

    std::vector<Rect> rects;
    AddTargetWindowHotArea(rects);
    AddWrapperChildHotArea(rects, layoutWrapper);
    // If container is UIExtensionWindow, set hotArea size equals to subwindow's filterColumnNode's size
    AddFilterHotArea(rects);
    auto subwindowManager = SubwindowManager::GetInstance();
    CHECK_NULL_VOID(subwindowManager);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (GetIsSelectOverlaySubWindowWrapper()) {
        subwindowManager->SetSelectOverlayHotAreas(rects, host->GetId(), GetContainerId());
    } else {
        subwindowManager->SetHotAreas(rects, SubwindowType::TYPE_MENU, host->GetId(), GetContainerId());
    }
}

void MenuWrapperPattern::StartShowAnimation()
{
    TAG_LOGI(AceLogTag::ACE_MENU, "start show menu animation");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (GetPreviewMode() == MenuPreviewMode::NONE) {
        context->UpdateOffset(GetAnimationOffset());
        context->UpdateOpacity(0.0);
    }
    if (theme->GetMenuAnimationDuration() && GetPreviewMode() == MenuPreviewMode::NONE) {
        auto menu = GetMenu();
        auto menuGeometryNode = menu ? menu->GetGeometryNode() : nullptr;
        if (menuGeometryNode) {
            auto offset = menuGeometryNode->GetFrameOffset();
            context->UpdateTransformCenter(DimensionOffset(Dimension(offset.GetX()), Dimension(offset.GetY())));
        }
        context->UpdateTransformScale(VectorF(theme->GetMenuAnimationScale(), theme->GetMenuAnimationScale()));
        context->UpdateOpacity(MENU_ANIMATION_MIN_OPACITY);
    }
    CallMenuOnWillAppearCallback();
    AnimationUtils::Animate(
        animationOption_,
        [context, weak = WeakClaim(this), theme]() {
            if (context) {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (pattern->GetPreviewMode() == MenuPreviewMode::NONE) {
                    context->UpdateOffset(OffsetT<Dimension>());
                    context->UpdateOpacity(1.0);
                }
                CHECK_NULL_VOID(theme);
                if (theme->GetMenuAnimationDuration() && pattern->GetPreviewMode() == MenuPreviewMode::NONE) {
                    context->UpdateTransformScale(VectorF(MENU_ANIMATION_MAX_SCALE, MENU_ANIMATION_MAX_SCALE));
                }
            }
        },
        animationOption_.GetOnFinishEvent(), nullptr, host->GetContextRefPtr());
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

    auto host = GetHost();
    CHECK_NULL_RETURN(host, offset);
    auto pipeline = host->GetContext();
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
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    return menuModifier->isSelectOverlayCustomMenu(menu);
}

bool MenuWrapperPattern::IsSelectOverlayRightClickMenu(const RefPtr<FrameNode>& menu) const
{
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    return menuModifier->isSelectOverlayRightClickMenu(menu);
}

void MenuWrapperPattern::RegisterMenuCallback(const RefPtr<FrameNode>& menuWrapperNode, const MenuParam& menuParam)
{
    TAG_LOGD(AceLogTag::ACE_MENU, "register menu enter");
    CHECK_NULL_VOID(menuWrapperNode);
    auto pattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RegisterMenuAppearCallback(menuParam.onAppear);
    pattern->RegisterMenuDisappearCallback(menuParam.onDisappear);
    pattern->RegisterMenuAboutToAppearCallback(menuParam.aboutToAppear);
    pattern->RegisterMenuAboutToDisappearCallback(menuParam.aboutToDisappear);
    pattern->RegisterMenuStateChangeCallback(menuParam.onStateChange);
    pattern->RegisterMenuOnWillAppearCallback(menuParam.onWillAppear);
    pattern->RegisterMenuOnDidAppearCallback(menuParam.onDidAppear);
    pattern->RegisterMenuOnWillDisappearCallback(menuParam.onWillDisappear);
    pattern->RegisterMenuOnDidDisappearCallback(menuParam.onDidDisappear);
}

void MenuWrapperPattern::SetMenuTransitionEffect(const RefPtr<FrameNode>& menuWrapperNode, const MenuParam& menuParam)
{
    TAG_LOGD(AceLogTag::ACE_MENU, "set menu transition effect");
    CHECK_NULL_VOID(menuWrapperNode);
    FREE_NODE_CHECK(menuWrapperNode, SetMenuTransitionEffect, menuWrapperNode, menuParam);
    SetMenuTransitionEffectImpl(menuWrapperNode, menuParam);
}

void MenuWrapperPattern::SetMenuTransitionEffectImpl(
    const RefPtr<FrameNode>& menuWrapperNode, const MenuParam& menuParam)
{
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
        const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
        if (menuModifier && menuModifier->isSubMenu(frameNode)) {
            host->RemoveChild(frameNode);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        }
    }
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

bool MenuWrapperPattern::IsMenuPreviewNode(const RefPtr<FrameNode>& frameNode) const
{
    if (GetPreviewMode() == MenuPreviewMode::NONE) {
        return false;
    }

    CHECK_NULL_RETURN(frameNode, false);
    auto tag = frameNode->GetTag();
    auto isPreviewTag = tag == V2::IMAGE_ETS_TAG || tag == V2::MENU_PREVIEW_ETS_TAG || tag == V2::FLEX_ETS_TAG;
    CHECK_NULL_RETURN(isPreviewTag, false);

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto preview = host->GetChildAtIndex(1);
    CHECK_NULL_RETURN(preview, false);
    return preview->GetId() == frameNode->GetId();
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
    DumpLog::GetInstance().AddDesc("ShowInSubWindow: " + std::to_string(dumpInfo_.showInSubWindow));
    DumpLog::GetInstance().AddDesc("CanExpandCurrentWindow: " + std::to_string(dumpInfo_.canExpandCurrentWindow));
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
    DumpLog::GetInstance().AddDesc("AnchorPosition: " + dumpInfo_.anchorPosition.ToString());
    auto modalMode = ConvertModalModeToString(menuParam_.modalMode);
    DumpLog::GetInstance().AddDesc("ModalMode: " + modalMode);
}

void MenuWrapperPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("MenuPreviewMode", std::to_string(dumpInfo_.menuPreviewMode).c_str());
    json->Put("MenuType", std::to_string(dumpInfo_.menuType).c_str());
    json->Put("EnableArrow", std::to_string(dumpInfo_.enableArrow).c_str());
    json->Put("Offset", dumpInfo_.offset.ToString().c_str());
    json->Put("TargetNode", dumpInfo_.targetNode.c_str());
    json->Put("TargetOffset", dumpInfo_.targetOffset.ToString().c_str());
    json->Put("TargetSize", dumpInfo_.targetSize.ToString().c_str());
    json->Put("ShowInSubWindow", std::to_string(dumpInfo_.showInSubWindow).c_str());
    json->Put("CanExpandCurrentWindow", std::to_string(dumpInfo_.canExpandCurrentWindow).c_str());
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
    json->Put("AnchorPosition", dumpInfo_.anchorPosition.ToString().c_str());
    auto modalMode = ConvertModalModeToString(menuParam_.modalMode);
    json->Put("ModalMode", modalMode.c_str());
}

bool MenuWrapperPattern::CheckPointInMenuZone(const RefPtr<FrameNode>& node, const PointF& point)
{
    CHECK_NULL_RETURN(node, false);
    auto childOffset = node->GetPaintRectOffset(false, true);
    auto childSize = node->GetPaintRectWithTransform();
    auto menuZone = RectF(childOffset.GetX(), childOffset.GetY(), childSize.Width(), childSize.Height());
    return menuZone.IsInRegion(point);
}

bool MenuWrapperPattern::GetMenuMaskEnable() const
{
    return menuParam_.maskEnable.value_or(false);
}

Color MenuWrapperPattern::GetMenuMaskColor() const
{
    if (menuParam_.maskType.has_value() && menuParam_.maskType->maskColor.has_value()) {
        return menuParam_.maskType->maskColor.value();
    }

    Color Color(NG::MENU_MASK_COLOR);
    auto node = GetHost();
    CHECK_NULL_RETURN(node, Color);
    auto pipelineContext = node->GetContext();
    CHECK_NULL_RETURN(pipelineContext, Color);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_RETURN(menuTheme, Color);
    return menuTheme->GetPreviewMenuMaskColor();
}

BlurStyle MenuWrapperPattern::GetMenuMaskBlurStyle() const
{
    if (menuParam_.maskType.has_value() && menuParam_.maskType->maskBackGroundBlurStyle.has_value()) {
        return menuParam_.maskType->maskBackGroundBlurStyle.value();
    }
    return BlurStyle::BACKGROUND_THIN;
}

void MenuWrapperPattern::UpdateFilterMaskType()
{
    auto filterNode = GetFilterColumnNode();
    if (filterNode) {
        BlurStyleOption styleOption;
        styleOption.blurStyle = GetMenuMaskBlurStyle();
        auto filterRenderContext = filterNode->GetRenderContext();
        CHECK_NULL_VOID(filterRenderContext);
        filterRenderContext->UpdateBackBlurStyle(styleOption);
        filterRenderContext->UpdateBackgroundColor(GetMenuMaskColor());
    }
}
bool MenuWrapperPattern::IsContextMenu() const
{
    auto menu = GetMenu();
    CHECK_NULL_RETURN(menu, false);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    return menuModifier->isContextMenu(menu);
}

MenuPreviewMode MenuWrapperPattern::GetPreviewMode() const
{
    auto menu = GetMenu();
    CHECK_NULL_RETURN(menu, MenuPreviewMode::NONE);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, MenuPreviewMode::NONE);
    return menuModifier->getPreviewMode(menu);
}

bool MenuWrapperPattern::IsSelectMenu() const
{
    auto menu = GetMenu();
    CHECK_NULL_RETURN(menu, false);
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    return menuModifier->isSelectMenu(menu);
}
} // namespace OHOS::Ace::NG
