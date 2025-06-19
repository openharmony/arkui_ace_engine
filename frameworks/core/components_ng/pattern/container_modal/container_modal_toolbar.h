/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_TOOLBAR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_TOOLBAR_H

#include "base/memory/referenced.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/manager/toolbar/toolbar_manager.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
enum class ItemPlacementType {
    NONE = -1,
    SIDE_BAR_START = 0,
    SIDE_BAR_END,
    NAV_BAR_START,
    NAV_BAR_END,
    NAVDEST_START,
    NAVDEST_END,
};
class ContainerModalPattern;

class ACE_EXPORT ContainerModalToolBar : public AceType {
    DECLARE_ACE_TYPE(ContainerModalToolBar, AceType);

public:
    ContainerModalToolBar(WeakPtr<NG::ContainerModalPattern> pattern, const RefPtr<FrameNode> title, bool isFloating)
        : pattern_(std::move(pattern)), title_(title), isFloating_(isFloating) {};
    ~ContainerModalToolBar() = default;

    void InitToolBarManager();
    void SetOnChangeCallback();
    void SetToolbarBuilder(const RefPtr<FrameNode>& parent, std::function<RefPtr<UINode>()>& builder);
    void OnToolBarLayoutChange();
    void AdjustNavDestRowWidth();
    void UpdateToolbarShow(bool isTitleShow, bool customTitleSettedShow);
    void AdjustContainerModalTitleHeight();

    bool GetNavOrSideBarNodes();
    void ToInitNavOrSideBarNode();

    void UpdateSideTitleBgColor(
        const Color& sideBarColor, const Color& sideBarContainerColor, const BlurStyle& blurStyle);
    void UpdateTargetNodesBarMargin(bool reset = false);
    void ExpandStackNodeLayout(bool reset = false);
    void ResetExpandStackNode();

protected:
    void UpdateTitleAfterRemove();
    void RemoveAllToolbarItem();
    void RemoveToolbarItem(const RefPtr<FrameNode>& frameNode);
    void UpdateTitleLayout();

private:
    void ParsePlacementType();
    bool HandleToolbarItemList(const RefPtr<FrameNode>& parentNode, std::list<RefPtr<UINode>>& list);
    ItemPlacementType GetItemTypeFromTag(const std::string& tag, uint32_t placement);

    void AddToolbarItemToContainer();
    bool AddToolbarItemToRow(ItemPlacementType placeMent, const RefPtr<FrameNode>& node);
    bool AddToolbarItemToSpecificRow(ItemPlacementType placeMent, const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavBarStart(const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavBarEnd(const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavDestStart(const RefPtr<FrameNode>& frameNode);
    bool AddToolbarItemToNavDestEnd(const RefPtr<FrameNode>& frameNode);

    void AddNavBarRow();
    void AddLeftNavRow();
    void AddRightNavRow();
    void AddNavDestBarRow();
    void AddLeftNavDestRow();
    void AddRightNavDestRow();
    void RemoveToolbarRowContainers();

    void AdjustTitleNodeWidth();
    void AdjustNavbarRowWidth();
    void SetCustomTitleRowBlurStyle(BlurStyle& blurStyle);
    void UpdateSidebarMargin();
    void UpdateNavbarTitlebarMargin();
    void UpdateNavDestinationTitlebarMargin();

    bool HasNavOrSideBarNodes()
    {
        return hasNavOrSideBarNodes_;
    }

    void SetHasNavOrSideBarNodes(bool hasNavOrSideBarNodes)
    {
        hasNavOrSideBarNodes_ = hasNavOrSideBarNodes;
    }

    std::string GetTagFromNode(RefPtr<UINode> node);
    bool IsTragetNavigationNodeParse(const RefPtr<FrameNode>& childFrameNode, float pageWidth, float sideBarHeight,
        bool isNavigationFound, bool isSideBarFound);
    bool IsTragetSideBarNodeParse(
        const RefPtr<FrameNode>& childFrameNode, float pageWidth, float& sideBarHeight, bool isSideBarFound);
    bool GetNavOrSideBarNodesParseChildren(const RefPtr<UINode>& page, float pageWidth);
    RefPtr<ToolbarManager> toolbarManager_;
    std::map<ItemPlacementType, std::list<RefPtr<FrameNode>>> itemWillAdd_;
    std::map<RefPtr<FrameNode>, std::list<RefPtr<UINode>>> itemsWillOnTree_;
    std::map<RefPtr<FrameNode>, std::list<RefPtr<UINode>>> itemsOnTree_;
    WeakPtr<ContainerModalPattern> pattern_;

    float toolbarItemMaxHeight_ = 0.0f;

    RefPtr<FrameNode> navbarRow_ = nullptr;
    RefPtr<FrameNode> leftNavRow_ = nullptr;
    RefPtr<FrameNode> rightNavRow_ = nullptr;
    RefPtr<FrameNode> navDestbarRow_ = nullptr;
    RefPtr<FrameNode> leftNavDestRow_ = nullptr;
    RefPtr<FrameNode> rightNavDestRow_ = nullptr;
    const RefPtr<FrameNode> title_;
    bool isFloating_;
    WeakPtr<FrameNode> sideBarNode_;
    WeakPtr<FrameNode> navigationNode_;
    WeakPtr<FrameNode> navDestNode_;
    bool hasNavOrSideBarNodes_ = false;
    bool hasSetOnchangeCallback_ = false;

    bool hasSetNavigationModeChangeCallback_ = false;
    bool hasSetUpdateSideTitleBgColor_ = false;
    bool isUpdateTargetNode_ = false;
    bool isTitleShow_ = true;
    bool customTitleShow_ = true;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_TOOLBAR_H