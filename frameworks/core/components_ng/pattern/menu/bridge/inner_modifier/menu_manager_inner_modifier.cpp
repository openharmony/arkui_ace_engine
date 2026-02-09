/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_manager_inner_modifier.h"

#include "core/components_ng/pattern/menu/menu_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
void HideAllMenusWithoutAnimation(const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager,
    bool showInSubwindow = false)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->HideAllMenusWithoutAnimation(overlayManager, showInSubwindow);
}

void ShowMenu(const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager,
    int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu = nullptr)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->ShowMenu(overlayManager, targetId, offset, menu);
}

void HideMenu(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menu,
    const RefPtr<OverlayManager>& overlayManager,
    const HideMenuParam& hideMenuParam, const HideMenuType& reason = HideMenuType::NORMAL)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->HideMenu(menu, overlayManager, hideMenuParam.targetId, hideMenuParam.isMenuOnTouch, reason);
}

void DeleteMenu(const RefPtr<AceType>& menuManager, int32_t targetId, const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->DeleteMenu(targetId, overlayManager);
}

void ShowMenuInSubWindow(
    const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager,
    int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu = nullptr)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->ShowMenuInSubWindow(overlayManager, targetId, offset, menu);
}

void HideMenuInSubWindow(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menu,
    const RefPtr<OverlayManager>& overlayManager, int32_t targetId)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->HideMenuInSubWindow(menu, overlayManager, targetId);
}

RefPtr<FrameNode> GetMenuNodeWithExistContent(const RefPtr<AceType>& menuManager, const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(menuManager, nullptr);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->GetMenuNodeWithExistContent(node);
}

RefPtr<FrameNode> GetMenuNode(const RefPtr<AceType>& menuManager, int32_t targetId)
{
    CHECK_NULL_RETURN(menuManager, nullptr);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->GetMenuNode(targetId);
}

void HideMenuInSubWindow(const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager,
    bool showPreviewAnimation = true, bool startDrag = false)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->HideMenuInSubWindow(overlayManager, showPreviewAnimation, startDrag);
}

void CleanMenuInSubWindow(const RefPtr<AceType>& menuManager, int32_t targetId)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->CleanMenuInSubWindow(targetId);
}

void CleanPreviewInSubWindow(const RefPtr<AceType>& menuManager)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->CleanPreviewInSubWindow();
}

void CleanHoverImagePreviewInSubWindow(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& flexNode)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->CleanHoverImagePreviewInSubWindow(flexNode);
}

void CleanMenuInSubWindowWithAnimation(const RefPtr<AceType>& menuManager,
    const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->CleanMenuInSubWindowWithAnimation(overlayManager);
}

void HideAllMenus(const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->HideAllMenus(overlayManager);
}

bool RemoveMenu(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& overlay)
{
    CHECK_NULL_RETURN(menuManager, false);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->RemoveMenu(overlay);
}

bool RemoveMenuInSubWindow(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menuWrapper,
    const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_RETURN(menuManager, false);
    CHECK_NULL_RETURN(overlayManager, false);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->RemoveMenuInSubWindow(menuWrapper, overlayManager);
}

void RemoveMenuFilter(const RefPtr<AceType>& menuManager,
    const RefPtr<FrameNode>& menuWrapper, bool hasAnimation = true)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->RemoveMenuFilter(menuWrapper, hasAnimation);
}

void UpdateContextMenuDisappearPosition(const RefPtr<AceType>& menuManager,
    const NG::OffsetF& offset, float menuScale = 1.0f,
    bool isRedragStart = false, int32_t menuWrapperId = -1)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->UpdateContextMenuDisappearPosition(offset, menuScale, isRedragStart, menuWrapperId);
}

void ContextMenuSwitchDragPreviewAnimation(
    const RefPtr<AceType>& menuManager, const RefPtr<NG::FrameNode>& dragPreviewNode, const NG::OffsetF& offset)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->ContextMenuSwitchDragPreviewAnimation(dragPreviewNode, offset);
}

bool GetMenuPreviewCenter(const RefPtr<AceType>& menuManager, NG::OffsetF& offset)
{
    CHECK_NULL_RETURN(menuManager, false);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->GetMenuPreviewCenter(offset);
}

RefPtr<FrameNode> BuildAIEntityMenu(
    const RefPtr<AceType>& menuManager, const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions)
{
    CHECK_NULL_RETURN(menuManager, nullptr);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->BuildAIEntityMenu(menuOptions);
}

RefPtr<FrameNode> CreateAIEntityMenu(const RefPtr<AceType>& menuManager,
    const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions, const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(menuManager, nullptr);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->CreateAIEntityMenu(menuOptions, targetNode);
}

bool ShowAIEntityMenu(const RefPtr<AceType>& menuManager,
    const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
    const RectF& aiRect, const RefPtr<FrameNode>& targetNode, const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_RETURN(menuManager, false);
    CHECK_NULL_RETURN(overlayManager, false);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->ShowAIEntityMenu(menuOptions, aiRect, targetNode, overlayManager);
}

void CloseAIEntityMenu(const RefPtr<AceType>& menuManager,
    const RefPtr<OverlayManager>& overlayManager, int32_t targetId)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->CloseAIEntityMenu(overlayManager, targetId);
}

bool IsGatherWithMenu(const RefPtr<AceType>& menuManager)
{
    CHECK_NULL_RETURN(menuManager, false);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->IsGatherWithMenu();
}

void SetIsGatherWithMenu(const RefPtr<AceType>& menuManager, bool isGatherWithMenu)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->SetIsGatherWithMenu(isGatherWithMenu);
}

void RemoveMenuBadgeNode(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menuWrapperNode)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->RemoveMenuBadgeNode(menuWrapperNode);
}

void ShowFilterAnimation(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& columnNode,
    const RefPtr<FrameNode>& menuWrapperNode, const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(menuManager);
    CHECK_NULL_VOID(overlayManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->ShowFilterAnimation(columnNode, menuWrapperNode, overlayManager);
}

void EraseMenuInfo(const RefPtr<AceType>& menuManager, int32_t targetId)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->EraseMenuInfo(targetId);
}

bool IsMenuShow(const RefPtr<AceType>& menuManager)
{
    CHECK_NULL_RETURN(menuManager, false);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->IsMenuShow();
}

void PublishMenuStatus(const RefPtr<AceType>& menuManager, bool isMenuShow, const RefPtr<FrameNode>& menuNode = nullptr)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->PublishMenuStatus(isMenuShow, menuNode);
}

void SetIsMenuShow(const RefPtr<AceType>& menuManager, bool isMenuShow, const RefPtr<FrameNode>& menuNode = nullptr)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->SetIsMenuShow(isMenuShow, menuNode);
}

OffsetF CalculateMenuPosition(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menuWrapperNode,
    const RefPtr<OverlayManager>& overlayManager, const OffsetF& offset)
{
    CHECK_NULL_RETURN(menuManager, OffsetF());
    CHECK_NULL_RETURN(overlayManager, OffsetF());
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, OffsetF());
    return manager->CalculateMenuPosition(menuWrapperNode, overlayManager, offset);
}

void SkipMenuShow(const RefPtr<AceType>& menuManager, int32_t targetId)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->SkipMenuShow(targetId);
}

void ResumeMenuShow(const RefPtr<AceType>& menuManager, int32_t targetId)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->ResumeMenuShow(targetId);
}
bool CheckSkipMenuShow(const RefPtr<AceType>& menuManager, int32_t targetId)
{
    CHECK_NULL_RETURN(menuManager, false);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, false);
    return manager->CheckSkipMenuShow(targetId);
}

void RegisterMenuLifeCycleCallback(const RefPtr<AceType>& menuManager, int32_t targetId,
    const std::function<void(const MenuLifeCycleEvent& menuLifeCycleEvent)>&& callback)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->RegisterMenuLifeCycleCallback(targetId, std::move(callback));
}

void UnRegisterMenuLifeCycleCallback(const RefPtr<AceType>& menuManager, int32_t targetId)
{
    CHECK_NULL_VOID(menuManager);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_VOID(manager);
    manager->UnRegisterMenuLifeCycleCallback(targetId);
}

std::function<void(const MenuLifeCycleEvent&)>& GetMenuLifeCycleCallback(const RefPtr<AceType>& menuManager,
    int32_t targetId)
{
    static std::function<void(const MenuLifeCycleEvent&)> emptyCallback;
    CHECK_NULL_RETURN(menuManager, emptyCallback);
    auto manager = AceType::DynamicCast<MenuManager>(menuManager);
    CHECK_NULL_RETURN(manager, emptyCallback);
    return manager->GetMenuLifeCycleCallback(targetId);
}

RefPtr<AceType> GetMenuManager(const RefPtr<FrameNode>& rootNode)
{
    CHECK_NULL_RETURN(rootNode, nullptr);
    return AceType::MakeRefPtr<MenuManager>(rootNode);
}

namespace InnerModifier {
const ArkUIMenuManagerInnerModifier* GetMenuManagerInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMenuManagerInnerModifier modifier = {
        .hideAllMenusWithoutAnimation = HideAllMenusWithoutAnimation,
        .showMenu = ShowMenu,
        .hideMenu = HideMenu,
        .deleteMenu = DeleteMenu,
        .showMenuInSubWindow = ShowMenuInSubWindow,
        .hideMenuInSubWindow = HideMenuInSubWindow,
        .getMenuNodeWithExistContent = GetMenuNodeWithExistContent,
        .getMenuNode = GetMenuNode,
        .hideMenuInSubWindowIsStartDrag = HideMenuInSubWindow,
        .cleanMenuInSubWindow = CleanMenuInSubWindow,
        .cleanPreviewInSubWindow = CleanPreviewInSubWindow,
        .cleanHoverImagePreviewInSubWindow = CleanHoverImagePreviewInSubWindow,
        .cleanMenuInSubWindowWithAnimation = CleanMenuInSubWindowWithAnimation,
        .hideAllMenus = HideAllMenus,
        .removeMenu = RemoveMenu,
        .removeMenuInSubWindow = RemoveMenuInSubWindow,
        .removeMenuFilter = RemoveMenuFilter,
        .updateContextMenuDisappearPosition = UpdateContextMenuDisappearPosition,
        .contextMenuSwitchDragPreviewAnimation = ContextMenuSwitchDragPreviewAnimation,
        .getMenuPreviewCenter = GetMenuPreviewCenter,
        .buildAIEntityMenu = BuildAIEntityMenu,
        .createAIEntityMenu = CreateAIEntityMenu,
        .showAIEntityMenu = ShowAIEntityMenu,
        .closeAIEntityMenu = CloseAIEntityMenu,
        .isGatherWithMenu = IsGatherWithMenu,
        .setIsGatherWithMenu = SetIsGatherWithMenu,
        .removeMenuBadgeNode = RemoveMenuBadgeNode,
        .showFilterAnimation = ShowFilterAnimation,
        .eraseMenuInfo = EraseMenuInfo,
        .isMenuShow = IsMenuShow,
        .publishMenuStatus = PublishMenuStatus,
        .setIsMenuShow = SetIsMenuShow,
        .calculateMenuPosition = CalculateMenuPosition,
        .skipMenuShow = SkipMenuShow,
        .resumeMenuShow = ResumeMenuShow,
        .checkSkipMenuShow = CheckSkipMenuShow,
        .registerMenuLifeCycleCallback = RegisterMenuLifeCycleCallback,
        .unRegisterMenuLifeCycleCallback = UnRegisterMenuLifeCycleCallback,
        .getMenuLifeCycleCallback = GetMenuLifeCycleCallback,
        .getMenuManager = GetMenuManager,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace InnerModifier
} // namespace OHOS::Ace::NG