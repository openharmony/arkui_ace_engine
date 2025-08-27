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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_NODE_H

#include <cstdint>
#include <memory>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

struct OptionParam;

const std::string SelectOverlayRrightClickMenuWrapper = "select_overlay_right_click_menuWrapper";

enum class FrameNodeType {
    SELECTMENU,
    EXTENSIONMENU,
    BACKBUTTON,
    MENUONLY
};

enum class FrameNodeStatus {
    VISIBLE,
    VISIBLETOGONE,
    GONE,
    GONETOVISIBLE
};

enum class FrameNodeTrigger {
    SHOW,
    SHOWN,
    HIDE,
    HIDDEN
};

class ACE_EXPORT SelectOverlayNode : public FrameNode {
    DECLARE_ACE_TYPE(SelectOverlayNode, FrameNode);
public:
    explicit SelectOverlayNode(const RefPtr<Pattern>& pattern);
    ~SelectOverlayNode() override = default;

    static RefPtr<FrameNode> CreateSelectOverlayNode(
        const std::shared_ptr<SelectOverlayInfo>& info, SelectOverlayMode mode = SelectOverlayMode::ALL);
    RefPtr<FrameNode> CreateMoreSelectOverlayNode(const std::vector<MenuOptionsParam>& menuOptionItems, int32_t index);

    void UpdateToolBar(bool menuItemChanged, bool noAnimation = false);

    void UpdateMenuOptions(const std::shared_ptr<SelectOverlayInfo>& info);

    void UpdateMenuInner(const std::shared_ptr<SelectOverlayInfo>& info, bool noAnimation = false);

    void SetSelectInfo(const std::string& selectInfo)
    {
        selectInfo_ = selectInfo;
    }

    const std::string& GetSelectInfo() const
    {
        return selectInfo_;
    }

    void ChangeToolBar(bool isUseExtensionMenu);

    void MoreOrBackAnimation(bool isMore, bool noAnimation = false);

    bool IsInSelectedOrSelectOverlayArea(const PointF& point);

    void SetClosedByGlobalEvent(bool closedByGlobalEvent);

    bool GetAnimationStatus()
    {
        return isDoingAnimation_;
    }

    bool GetIsExtensionMenu()
    {
        return isExtensionMenu_;
    }

    void ShowSelectOverlay(bool animation);

    void HideSelectOverlay(const std::function<void()>& callback);
    void HideOrShowCirclesAndBackArrow(FrameNodeType type, float value);

    void SwitchToOverlayMode();
    void UpdateSelectMenuBg();
    void AddCustomMenuCallbacks(const std::shared_ptr<SelectOverlayInfo>& info);
    void OnCustomSelectMenuAppear();
    void FireCustomMenuChangeEvent(bool isMenuShow);
    void OnDetachFromMainTree(bool recursive, PipelineContext* context) override;
    void UpdateToolBarFromMainWindow(bool menuItemChanged, bool noAnimation = false);

private:
    void CreateToolBar();
    void SelectMenuAndInnerInitProperty();
    void AddMenuItemByCreateMenuCallback(const std::shared_ptr<SelectOverlayInfo>& info, float maxWidth);
    static const std::vector<MenuItemParam> GetSystemMenuItemParams(const std::shared_ptr<SelectOverlayInfo>& info);
    static void AddMenuItemParamIf(
        bool condition, const std::string& menuId, const std::string& menuButton, std::vector<MenuItemParam>& items);
    int32_t AddCreateMenuItems(const std::vector<NG::MenuOptionsParam>& menuItems,
        const std::shared_ptr<SelectOverlayInfo>& info, float maxWidth);
    bool AddSystemDefaultOptions(float maxWidth, float& allocatedSize);
    void LandscapeMenuAddMenuOptions(bool isDefaultOverMaxWidth, float maxWidth, float allocatedSize,
        int32_t& extensionOptionStartIndex, const std::shared_ptr<SelectOverlayInfo>& info);
    void ShowCut(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowCopy(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowPaste(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowCopyAll(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowTranslate(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowSearch(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowShare(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowCamera(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowAIWrite(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    void ShowAIMenuOptions(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);
    bool IsShowOnTargetAPIVersion();
    bool IsShowTranslateOnTargetAPIVersion();
    std::function<void()> GetDefaultOptionCallback();
    std::function<void(WeakPtr<NG::FrameNode>)> GetSymbolFunc(const std::string& symbolId);
    std::vector<OptionParam> GetDefaultOptionsParams(const std::shared_ptr<SelectOverlayInfo>& info);
    void GetFlexibleOptionsParams(
        const std::shared_ptr<SelectOverlayInfo>& info, std::vector<OptionParam>& params);
    void addMenuOptionItemsParams(
        std::vector<OptionParam>& params, const std::shared_ptr<SelectOverlayInfo>& info, int32_t index);
    void AddExtensionMenuOptions(const std::shared_ptr<SelectOverlayInfo>& info, int32_t index);
    void AddCreateMenuExtensionMenuOptions(const std::vector<MenuOptionsParam>& menuOptionItems,
        const std::shared_ptr<SelectOverlayInfo>& info, int32_t startIndex);
    void AddCreateMenuExtensionMenuParams(const std::vector<MenuOptionsParam>& menuOptionItems,
        const std::shared_ptr<SelectOverlayInfo>& info, int32_t startIndex, std::vector<OptionParam>& params);
    std::function<void()> CreateExtensionMenuOptionCallback(int32_t id, const OnMenuItemCallback& onCreateCallback,
        const std::function<void()>& systemEvent, const MenuOptionsParam& item);
    void CreatExtensionMenu(std::vector<OptionParam>&& params);
    void GetDefaultButtonAndMenuWidth(float& maxWidth);

    void MoreAnimation(bool noAnimation);
    void BackAnimation(bool noAnimation);

    void DispatchVisibleState(FrameNodeType type, FrameNodeTrigger trigger);
    void DispatchVisibleToGoneState(FrameNodeType type, FrameNodeTrigger trigger);
    void DispatchGoneState(FrameNodeType type, FrameNodeTrigger trigger);
    void DispatchGoneToVisibleState(FrameNodeType type, FrameNodeTrigger trigger);
    void ExecuteOverlayStatus(FrameNodeType type, FrameNodeTrigger trigger);
    void SetFrameNodeStatus(FrameNodeType type, FrameNodeStatus status);
    void SetFrameNodeVisibility(FrameNodeType type, VisibleType visibleType);
    void SetFrameNodeOpacity(FrameNodeType type, float opacity);
    void SetSelectMenuOpacity(float value);
    void SetExtensionMenuOpacity(float value);
    void SetBackButtonOpacity(float value);
    void HideFrameNodeImmediately(FrameNodeType type);
    void CreateCustomSelectOverlay(const std::shared_ptr<SelectOverlayInfo>& info);
    void UpdateMoreOrBackSymbolOptions(bool isMoreButton, bool isReplaceEffectEnable);
    void UpdateMoreOrBackSymbolOptionsWithDelay();
    void MenuOnlyStatusChange(const std::shared_ptr<SelectOverlayInfo>& info, bool noAnimation);
    void HideMenuOnlyImmediately();
    void InitSelectMenuStatus(
        SelectOverlayMode mode, const std::shared_ptr<SelectOverlayInfo>& info, bool changeOpacity = true);

    void SetAnimationStatus(bool toDoAnimation)
    {
        isDoingAnimation_ = toDoAnimation;
    }

    void SetIsMoreOrBackSymbolIcon(bool isMoreOrBackSymbol)
    {
        isMoreOrBackSymbolIcon_ = isMoreOrBackSymbol;
    }

    static RefPtr<FrameNode> CreateMenuNode(const std::shared_ptr<SelectOverlayInfo>& info);
    static std::pair<std::vector<MenuOptionsParam>, bool> HandleCollaborationMenuItem(
        const std::vector<MenuOptionsParam>& params);

    void NotifyUpdateToolBar(bool itemChanged, bool withoutAnimation);
    void SetSelectMenuInnerSize();
    void ShowAskCelia(
        float maxWidth, float& allocatedSize, std::shared_ptr<SelectOverlayInfo>& info, const std::string& label);

    using ExecuteStateFunc = void (SelectOverlayNode::*)(FrameNodeType type, FrameNodeTrigger trigger);

    /* Text selection menu node structure.
        -rootNode
            -selectOverlay
                -selectMenu_
                    -selectMenuInner_
                -backButton_
                -extensionMenu_
       Attention:
        If the user-defined selection menu is bound by bindSelectionMenu, there will be only the selectMenu_.
        Then, selectMenuInner_, backButton_, extensionMenu_ will be null.
        Text selection menu node structure whill be like bellow:
        -rootNode
            -selectOverlay(menuWrapper)
                -selectMenu_(menu)
                    -scroller
                        -customBuilderMenu
    */
    RefPtr<FrameNode> selectMenu_;
    RefPtr<FrameNode> selectMenuInner_;
    RefPtr<FrameNode> extensionMenu_;
    RefPtr<FrameNode> backButton_;
    RefPtr<FrameNode> moreOrBackSymbol_;
    RefPtr<FrameNode> moreButton_;

    FrameNodeStatus selectMenuStatus_ = FrameNodeStatus::VISIBLE;
    FrameNodeStatus extensionMenuStatus_ = FrameNodeStatus::GONE;
    FrameNodeStatus backButtonStatus_ = FrameNodeStatus::GONE;
    FrameNodeStatus menuOnlyStatus_ = FrameNodeStatus::VISIBLE;

    std::map<FrameNodeStatus, ExecuteStateFunc> stateFuncs_;

    std::string selectInfo_;

    // Marks whether it is currently in the animated state.
    bool isDoingAnimation_ = false;

    // Controls that only default menus can be converted to extended menus, and extended menus can be converted to
    // default menus.
    bool isExtensionMenu_ = false;

    // Label whether the menu default button needs to appear within the extended menu
    bool isShowInDefaultMenu_[11] = { false }; // OPTION_INDEX_ASK_CELIA + 1

    bool isDefaultBtnOverMaxWidth_ = false;

    bool isMoreOrBackSymbolIcon_ = false;
    bool isCustomMenuAppear_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_NODE_H
