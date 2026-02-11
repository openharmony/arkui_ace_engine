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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_MANAGER_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_MANAGER_INNER_MODIFIER_H

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
struct HideMenuParam {
    int32_t targetId;
    bool isMenuOnTouch = false;
};

enum class HideMenuType;
enum class MenuLifeCycleEvent;
class FrameNode;
class MenuManager;
class OverlayManager;
class UINode;

template<typename T>
class OffsetT;
using OffsetF = OffsetT<float>;

template<typename T>
class RectT;
using RectF = RectT<float>;

struct ArkUIMenuManagerInnerModifier {
    void (*hideAllMenusWithoutAnimation)(const RefPtr<AceType>& menuManager,
        const RefPtr<OverlayManager>& overlayManager,
        bool showInSubwindow);
    void (*showMenu)(const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager,
        int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu);
    void (*hideMenu)(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menu,
        const RefPtr<OverlayManager>& overlayManager,
        const HideMenuParam& hideMenuParam, const HideMenuType& reason);
    void (*deleteMenu)(const RefPtr<AceType>& menuManager, int32_t targetId,
        const RefPtr<OverlayManager>& overlayManager);
    void (*showMenuInSubWindow)(const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager,
        int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu);
    void (*hideMenuInSubWindow)(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menu,
        const RefPtr<OverlayManager>& overlayManager, int32_t targetId);
    RefPtr<FrameNode> (*getMenuNodeWithExistContent)(const RefPtr<AceType>& menuManager, const RefPtr<UINode>& node);
    RefPtr<FrameNode> (*getMenuNode)(const RefPtr<AceType>& menuManager, int32_t targetId);
    void (*hideMenuInSubWindowIsStartDrag)(const RefPtr<AceType>& menuManager,
        const RefPtr<OverlayManager>& overlayManager,
        bool showPreviewAnimation, bool startDrag);
    void (*cleanMenuInSubWindow)(const RefPtr<AceType>& menuManager, int32_t targetId);
    void (*cleanPreviewInSubWindow)(const RefPtr<AceType>& menuManager);
    void (*cleanHoverImagePreviewInSubWindow)(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& flexNode);
    void (*cleanMenuInSubWindowWithAnimation)(const RefPtr<AceType>& menuManager,
        const RefPtr<OverlayManager>& overlayManager);
    void (*hideAllMenus)(const RefPtr<AceType>& menuManager, const RefPtr<OverlayManager>& overlayManager);
    bool (*removeMenu)(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& overlay);
    bool (*removeMenuInSubWindow)(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menuWrapper,
        const RefPtr<OverlayManager>& overlayManager);
    void (*removeMenuFilter)(const RefPtr<AceType>& menuManager,
        const RefPtr<FrameNode>& menuWrapper, bool hasAnimation);
    void (*updateContextMenuDisappearPosition)(
        const RefPtr<AceType>& menuManager, const NG::OffsetF& offset,
        float menuScale, bool isRedragStart, int32_t menuWrapperId);
    void (*contextMenuSwitchDragPreviewAnimation)(
        const RefPtr<AceType>& menuManager, const RefPtr<NG::FrameNode>& dragPreviewNode, const NG::OffsetF& offset);
    bool (*getMenuPreviewCenter)(const RefPtr<AceType>& menuManager, NG::OffsetF& offset);
    RefPtr<FrameNode> (*buildAIEntityMenu)(const RefPtr<AceType>& menuManager,
        const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions);
    RefPtr<FrameNode> (*createAIEntityMenu)(const RefPtr<AceType>& menuManager,
        const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
        const RefPtr<FrameNode>& targetNode);
    bool (*showAIEntityMenu)(const RefPtr<AceType>& menuManager,
        const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions, const RectF& aiRect,
        const RefPtr<FrameNode>& targetNode, const RefPtr<OverlayManager>& overlayManager);
    void (*closeAIEntityMenu)(const RefPtr<AceType>& menuManager,
        const RefPtr<OverlayManager>& overlayManager, int32_t targetId);
    bool (*isGatherWithMenu)(const RefPtr<AceType>& menuManager);
    void (*setIsGatherWithMenu)(const RefPtr<AceType>& menuManager, bool isGatherWithMenu);
    void (*removeMenuBadgeNode)(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menuWrapperNode);
    void (*showFilterAnimation)(const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& columnNode,
        const RefPtr<FrameNode>& menuWrapperNode, const RefPtr<OverlayManager>& overlayManager);
    void (*eraseMenuInfo)(const RefPtr<AceType>& menuManager, int32_t targetId);
    bool (*isMenuShow)(const RefPtr<AceType>& menuManager);
    void (*publishMenuStatus)(const RefPtr<AceType>& menuManager, bool isMenuShow, const RefPtr<FrameNode>& menuNode);
    void (*setIsMenuShow)(const RefPtr<AceType>& menuManager, bool isMenuShow, const RefPtr<FrameNode>& menuNode);
    OffsetF (*calculateMenuPosition)(
        const RefPtr<AceType>& menuManager, const RefPtr<FrameNode>& menuWrapperNode,
        const RefPtr<OverlayManager>& overlayManager, const OffsetF& offset);
    void (*skipMenuShow)(const RefPtr<AceType>& menuManager, int32_t targetId);
    void (*resumeMenuShow)(const RefPtr<AceType>& menuManager, int32_t targetId);
    bool (*checkSkipMenuShow)(const RefPtr<AceType>& menuManager, int32_t targetId);
    void (*registerMenuLifeCycleCallback)(const RefPtr<AceType>& menuManager, int32_t targetId,
        const std::function<void(const MenuLifeCycleEvent& menuLifeCycleEvent)>&& callback);
    void (*unRegisterMenuLifeCycleCallback)(const RefPtr<AceType>& menuManager, int32_t targetId);
    std::function<void(const MenuLifeCycleEvent&)>& (*getMenuLifeCycleCallback)(const RefPtr<AceType>& menuManager,
        int32_t targetId);
    RefPtr<AceType> (*getMenuManager)(const RefPtr<UINode>& rootNode);
};

namespace InnerModifier {
const ArkUIMenuManagerInnerModifier* GetMenuManagerInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_BRIDGE_INNER_MODIFIER_MENU_MANAGER_INNER_MODIFIER_H