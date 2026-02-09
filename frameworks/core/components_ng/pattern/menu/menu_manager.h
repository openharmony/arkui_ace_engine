/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_MANAGER_H

#include <cstdint>
#include <functional>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {
class AnimationOption;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class FrameNode;
enum class HideMenuType;
enum class MenuLifeCycleEvent;
class PipelineContext;
class OverlayManager;
class UINode;

template<typename T>
class OffsetT;
using OffsetF = OffsetT<float>;

template<typename T>
class RectT;
using RectF = RectT<float>;

class ACE_EXPORT MenuManager : public virtual AceType {
    DECLARE_ACE_TYPE(MenuManager, AceType);

public:
    explicit MenuManager(const RefPtr<FrameNode>& rootNode);
    ~MenuManager() override;

    void HideAllMenusWithoutAnimation(const RefPtr<OverlayManager>& overlayManager, bool showInSubwindow = false);
    void ShowMenu(const RefPtr<OverlayManager>& overlayManager, int32_t targetId,
        const NG::OffsetF& offset, RefPtr<FrameNode> menu);
    void HideMenu(const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager,
        int32_t targetId, bool isMenuOnTouch,
        const HideMenuType& reason);
    void DeleteMenu(int32_t targetId, const RefPtr<OverlayManager>& overlayManager);
    void ShowMenuInSubWindow(const RefPtr<OverlayManager>& overlayManager,
        int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu);
    void HideMenuInSubWindow(const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager,
        int32_t targetId);
    RefPtr<FrameNode> GetMenuNodeWithExistContent(const RefPtr<UINode>& node);
    RefPtr<FrameNode> GetMenuNode(int32_t targetId);
    void HideMenuInSubWindow(const RefPtr<OverlayManager>& overlayManager,
        bool showPreviewAnimation = true, bool startDrag = false);
    void CleanMenuInSubWindow(int32_t targetId);
    void CleanPreviewInSubWindow();
    void CleanHoverImagePreviewInSubWindow(const RefPtr<FrameNode>& flexNode);
    void CleanMenuInSubWindowWithAnimation(const RefPtr<OverlayManager>& overlayManager);
    void HideAllMenus(const RefPtr<OverlayManager>& overlayManager);
    bool RemoveMenu(const RefPtr<FrameNode>& overlay);
    bool RemoveMenuInSubWindow(const RefPtr<FrameNode>& menuWrapper, const RefPtr<OverlayManager>& overlayManager);
    void RemoveMenuFilter(const RefPtr<FrameNode>& menuWrapper, bool hasAnimation = true);
    void UpdateContextMenuDisappearPosition(const NG::OffsetF& offset, float menuScale = 1.0f,
        bool isRedragStart = false, int32_t menuWrapperId = -1);
    void ContextMenuSwitchDragPreviewAnimation(const RefPtr<NG::FrameNode>& dragPreviewNode,
        const NG::OffsetF& offset);
    bool GetMenuPreviewCenter(NG::OffsetF& offset);

    RefPtr<FrameNode> BuildAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions);
    RefPtr<FrameNode> CreateAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
        const RefPtr<FrameNode>& targetNode);
    bool ShowAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
        const RectF& aiRect, const RefPtr<FrameNode>& targetNode,
        const RefPtr<OverlayManager>& overlayManager);
    void CloseAIEntityMenu(const RefPtr<OverlayManager>& overlayManager, int32_t targetId);

    bool IsGatherWithMenu() const
    {
        return isGatherWithMenu_;
    }
    void SetIsGatherWithMenu(bool isGatherWithMenu)
    {
        isGatherWithMenu_ = isGatherWithMenu;
    }
    void RemoveMenuBadgeNode(const RefPtr<FrameNode>& menuWrapperNode);

    void ShowFilterAnimation(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& menuWrapperNode,
        const RefPtr<OverlayManager>& overlayManager);
    void ExecuteFilterAnimation(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& menuWrapperNode,
        const RefPtr<OverlayManager>& overlayManager);
    void EraseMenuInfo(int32_t targetId)
    {
        if (menuMap_.find(targetId) != menuMap_.end()) {
            menuMap_.erase(targetId);
        }
    }

    bool IsMenuShow() const
    {
        return isMenuShow_;
    }

    void PublishMenuStatus(bool isMenuShow, const RefPtr<FrameNode>& menuNode);
    void SetIsMenuShow(bool isMenuShow, const RefPtr<FrameNode>& menuNode);
    OffsetF CalculateMenuPosition(const RefPtr<FrameNode>& menuWrapperNode,
        const RefPtr<OverlayManager>& overlayManager, const OffsetF& offset);
    void SkipMenuShow(int32_t targetId);
    void ResumeMenuShow(int32_t targetId);
    bool CheckSkipMenuShow(int32_t targetId);

    void RegisterMenuLifeCycleCallback(int32_t targetId,
        const std::function<void(const MenuLifeCycleEvent& menuLifeCycleEvent)>&& callback)
    {
        menuLifeCycleCallbackMap_[targetId] = std::move(callback);
    }

    void UnRegisterMenuLifeCycleCallback(int32_t targetId)
    {
        menuLifeCycleCallbackMap_.erase(targetId);
    }

    std::function<void(const MenuLifeCycleEvent&)>& GetMenuLifeCycleCallback(int32_t targetId)
    {
        return menuLifeCycleCallbackMap_[targetId];
    }

private:
    RefPtr<PipelineContext> GetPipelineContext() const;

    /**  find/register menu node and update menu's display position
     *
     *   @return     true if process is successful
     */
    bool ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset);
    void ResetMenuWrapperVisibility(const RefPtr<FrameNode>& menuWrapper);
    void SetPreviewFirstShow(const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager);
    void ShowMenuAnimation(const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager);
    void SetPatternFirstShow(const RefPtr<FrameNode>& menu);
    void PopMenuAnimation(const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager,
        bool showPreviewAnimation = true, bool startDrag = false);
    void ShowMenuDisappearTransition(const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager);
    void ShowMenuClearAnimation(const RefPtr<FrameNode>& menuWrapper, AnimationOption& option,
        bool showPreviewAnimation, bool startDrag);
    bool IsContextMenuBindedOnOrigNode();
    void OnShowMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<OverlayManager> weak,
        int32_t instanceId);
    void HandleMenuDisappearCallback(const RefPtr<FrameNode>& menu);
    bool CheckSelectSubWindowToClose(
        const RefPtr<FrameNode>& menu, const RefPtr<OverlayManager>& overlayManager, bool expandDisplay);
    void OnPopMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<UINode> rootWeak,
        const WeakPtr<OverlayManager> weak, int32_t instanceId);
    void UpdateMenuVisibility(const RefPtr<FrameNode>& menu);
    void RemoveMenuNotInSubWindow(
        const WeakPtr<FrameNode>& menuWK, const WeakPtr<UINode>& rootWeak, const WeakPtr<OverlayManager>& overlayWeak);
    void SendToAccessibility(const WeakPtr<FrameNode> node, const WeakPtr<OverlayManager> overlayWeak, bool isShow);
    void RemoveMenuWrapperNode(const RefPtr<UINode>& rootNode, const RefPtr<PipelineContext>& pipeline);
    void CallMenuDisappearWithStatus(const RefPtr<FrameNode>& menuWrapperNode);
    void CallMenuDisappearOnlyNewLifeCycle(const RefPtr<FrameNode>& menuWrapperNode);
    void EraseMenuInfoFromWrapper(const RefPtr<FrameNode>& menuWrapperNode);
    void UpdateMenuAnimationOptions(const RefPtr<FrameNode>& menu, AnimationOption& option,
        const RefPtr<OverlayManager>& overlayManager);

private:
    WeakPtr<UINode> rootNodeWeak_;
    WeakPtr<PipelineContext> context_;
    // K: target frameNode ID, V: menuNode
    std::unordered_map<int32_t, RefPtr<FrameNode>> menuMap_;
    bool isGatherWithMenu_ { false };
    bool isMenuShow_ = false;
    std::set<int32_t> skipTargetIds_;
    std::unordered_map<int32_t, std::function<void(const MenuLifeCycleEvent&)>> menuLifeCycleCallbackMap_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_MANAGER_H