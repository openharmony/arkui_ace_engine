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
#include "core/components_ng/pattern/container_modal/container_modal_toolbar.h"

#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/manager/toolbar/toolbar_manager.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_styles.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_algorithm.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float TITLE_ITEM_HEIGT_S = 56.0; // 56vp height of title
constexpr float TITLE_ITEM_HEIGT_M = 64.0; // 64vp height of title
constexpr float TITLE_ITEM_HEIGT_L = 72.0; // 72vp height of title
constexpr float ROW_MARGIN = 4.0;
constexpr float ROW_TOTAL_MARGIN = 8.0;
constexpr uint32_t TITLE_MGR_CALLBACK_ID = 0;
constexpr uint32_t FLOATING_TITLE_MGR_CALLBACK_ID = 1;
} // namespace

void ContainerModalToolBar::InitToolBarManager()
{
    if (!toolbarManager_) {
        auto toolbar = pattern_.Upgrade();
        CHECK_NULL_VOID(toolbar);
        auto pipeline = toolbar->GetContext();
        CHECK_NULL_VOID(pipeline);
        toolbarManager_ = pipeline->GetToolbarManager();
    }
}

void ContainerModalToolBar::SetOnChangeCallback()
{
    CHECK_NULL_VOID(toolbarManager_);
    if (!hasSetOnchangeCallback_) {
        std::function<void()> func = [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnToolBarLayoutChange();
        };
        toolbarManager_->SetToolBarChangeCallback(std::move(func));
        hasSetOnchangeCallback_ = true;
    }
    if (!isFloating_ && !hasSetUpdateSideTitleBgColor_) {
        std::function<void(const Color&, const Color&, const BlurStyle&)> func =
            [wk = WeakClaim(this)](
                const Color& sideBarColor, const Color& sideBarContainerColor, const BlurStyle& sideBarBlurStyle) {
                auto pattern = wk.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->UpdateSideTitleBgColor(sideBarColor, sideBarContainerColor, sideBarBlurStyle);
            };
        toolbarManager_->SetSideBarColorChangeCallback(std::move(func));
        hasSetUpdateSideTitleBgColor_ = true;
    }
    if (!hasSetNavigationModeChangeCallback_) {
        std::function<void()> navigationModefunc = [weak = WeakClaim(this), toolbarMgr = toolbarManager_]() {
            CHECK_NULL_VOID(toolbarMgr);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            NavigationMode navigationMode = toolbarMgr->GetNavigationMode();
            if (navigationMode != NavigationMode::SPLIT) {
                pattern->RemoveAllToolbarItem();
            }
        };
        toolbarManager_->SetNavigationModeChangeCallback(std::move(navigationModefunc));
        hasSetNavigationModeChangeCallback_ = true;
    }
}

void ContainerModalToolBar::SetToolbarBuilder(const RefPtr<FrameNode>& parent, std::function<RefPtr<UINode>()>& builder)
{
    CHECK_NULL_VOID(parent);
    RemoveToolbarItem(parent);
    UpdateTitleLayout();
    CHECK_NULL_VOID(builder);
    auto nodes = builder();
    CHECK_NULL_VOID(nodes);
    auto it = itemsWillOnTree_.find(parent);
    if (it != itemsWillOnTree_.end()) {
        it->second.clear();
    }
    auto children = nodes->GetChildren();
    for (auto& item : children) {
        itemsWillOnTree_[parent].push_back(item);
    }
    auto callback = [weak = WeakClaim(this), frame = WeakClaim(RawPtr(parent))]() {
        auto toolbar = weak.Upgrade();
        CHECK_NULL_VOID(toolbar);
        auto frameNode = frame.Upgrade();
        CHECK_NULL_VOID(frameNode);
        toolbar->RemoveToolbarItem(frameNode);
        toolbar->UpdateTitleLayout();
    };
    parent->SetRemoveToolbarItemCallback(
        isFloating_ ? FLOATING_TITLE_MGR_CALLBACK_ID : TITLE_MGR_CALLBACK_ID, std::move(callback));
    InitToolBarManager();
    SetOnChangeCallback();
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto pipeline = pattern->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterRenderTask([weak = WeakClaim(this), frame = WeakClaim(RawPtr(parent))]() {
        auto toolbar = weak.Upgrade();
        CHECK_NULL_VOID(toolbar);
        auto node = frame.Upgrade();
        CHECK_NULL_VOID(node);
        if (toolbar->GetNavOrSideBarNodes(node)) {
            if (!(toolbar->HasNavOrSideBarNodes())) {
                toolbar->SetHasNavOrSideBarNodes(true);
                toolbar->ToInitNavOrSideBarNode();
            }
        } else {
            return;
        }
        toolbar->ParsePlacementType(node);
    });
}

void ContainerModalToolBar::ParsePlacementType(const RefPtr<FrameNode>& node)
{
    if (!GetNavOrSideBarNodes(node) || !HasNavOrSideBarNodes()) {
        return;
    }

    bool hasItem = false;
    for (auto it = itemsWillOnTree_.begin(); it != itemsWillOnTree_.end();) {
        auto parent = it->first;
        auto& list = it->second;
        if (HandleToolbarItemList(parent, list)) {
            it = itemsWillOnTree_.erase(it);
            hasItem = true;
        } else {
            it++;
        }
    }
    if (hasItem) {
        AddToolbarItemToContainer();
        OnToolBarLayoutChange();
    }
}

ItemPlacementType ContainerModalToolBar::GetItemTypeFromTag(const std::string& tag, uint32_t placement)
{
    if (tag == V2::SIDE_BAR_ETS_TAG) {
        return placement ? ItemPlacementType::SIDE_BAR_END : ItemPlacementType::SIDE_BAR_START;
    }
    if (tag == V2::NAVBAR_ETS_TAG) {
        return placement ? ItemPlacementType::NAV_BAR_END : ItemPlacementType::NAV_BAR_START;
    }
    if (tag == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        return placement ? ItemPlacementType::NAVDEST_END : ItemPlacementType::NAVDEST_START;
    }
    return ItemPlacementType::NONE;
}

bool ContainerModalToolBar::HandleToolbarItemList(const RefPtr<FrameNode>& parentNode, std::list<RefPtr<UINode>>& list)
{
    CHECK_NULL_RETURN(parentNode, true);
    std::string tag = GetTagFromNode(parentNode);
    if (tag == "") {
        return false;
    }
    for (auto& item : list) {
        auto frameNode = AceType::DynamicCast<FrameNode>(item);
        itemsOnTree_[parentNode].push_back(item);
        auto pattern = frameNode->GetPattern<ToolBarItemPattern>();
        int32_t placement = 0;
        if (pattern) {
            placement = pattern->GetPlacement();
            auto id = GetItemTypeFromTag(tag, placement);
            itemWillAdd_[id].emplace_back(frameNode);
        }
    }
    return true;
}

void ContainerModalToolBar::UpdateTitleAfterRemove()
{
    if (navbarRow_) {
        navbarRow_->MarkDirtyNode(
            PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        if (leftNavRow_) {
            leftNavRow_->MarkDirtyNode(
                PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        }
        if (rightNavRow_) {
            rightNavRow_->MarkDirtyNode(
                PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        }
    }
    if (navDestbarRow_) {
        navDestbarRow_->MarkDirtyNode(
            PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        if (leftNavDestRow_) {
            leftNavDestRow_->MarkDirtyNode(
                PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        }
        if (rightNavDestRow_) {
            rightNavDestRow_->MarkDirtyNode(
                PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        }
    }
}

void ContainerModalToolBar::RemoveAllToolbarItem()
{
    for (auto& [_, list] : itemsOnTree_) {
        for (auto& item : list) {
            auto parent = item->GetParent();
            if (parent) {
                parent->RemoveChild(item);
                parent->MarkNeedSyncRenderTree();
                parent->RebuildRenderContextTree();
            }
        }
    }
    itemsOnTree_.clear();
    UpdateTitleLayout();
}

void ContainerModalToolBar::RemoveToolbarItem(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto& list = itemsOnTree_[frameNode];
    for (auto& item : list) {
        auto parent = item->GetParent();
        if (parent) {
            parent->RemoveChild(item);
            parent->MarkNeedSyncRenderTree();
            parent->RebuildRenderContextTree();
        }
    }
    list.clear();
    itemsOnTree_.erase(frameNode);
}

void ContainerModalToolBar::UpdateTitleLayout()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    UpdateTitleAfterRemove();
    toolbarItemMaxHeight_ = 0.0f;
    for (auto it = itemsOnTree_.begin(); it != itemsOnTree_.end(); it++) {
        auto& list = it->second;
        for (auto iit = list.begin(); iit != list.end(); iit++) {
            auto toolbarNode = AceType::DynamicCast<FrameNode>(*iit);
            CHECK_NULL_VOID(toolbarNode);
            LayoutConstraintF Constraint;
            toolbarNode->Measure(Constraint);
            auto toolbarItemHeight = Dimension(toolbarNode->GetGeometryNode()->GetFrameSize().Height()).ConvertToVp();
            if (GreatNotEqual(toolbarItemHeight, toolbarItemMaxHeight_)) {
                toolbarItemMaxHeight_ = toolbarItemHeight;
            }
        }
    }
    if (!isTitleShow_ || customTitleShow_) {
        RemoveToolbarRowContainers();
        OnToolBarLayoutChange();
        AdjustContainerModalTitleHeight();
    }
}

void ContainerModalToolBar::AddToolbarItemToContainer()
{
    for (auto it = itemWillAdd_.begin(); it != itemWillAdd_.end(); it++) {
        auto placementType = it->first;
        if (placementType == ItemPlacementType::NONE) {
            continue;
        }
        auto& list = it->second;
        for (auto iit = list.begin(); iit != list.end();) {
            if (AddToolbarItemToRow(placementType, *iit)) {
                iit = list.erase(iit);
            } else {
                iit++;
            }
        }
    }
}

bool ContainerModalToolBar::AddToolbarItemToRow(ItemPlacementType placeMent, const RefPtr<FrameNode>& frameNode)
{
    if ((!toolbarManager_->HasNavBar() &&
            (placeMent == ItemPlacementType::NAV_BAR_END || placeMent == ItemPlacementType::NAV_BAR_START)) ||
        (!toolbarManager_->HasNavDest() &&
            (placeMent == ItemPlacementType::NAVDEST_START || placeMent == ItemPlacementType::NAVDEST_END))) {
        return false;
    }

    CHECK_NULL_RETURN(frameNode, false);
    LayoutConstraintF Constraint;
    frameNode->Measure(Constraint);
    auto toolbarItemHeight = Dimension(frameNode->GetGeometryNode()->GetFrameSize().Height()).ConvertToVp();
    if (GreatNotEqual(toolbarItemHeight, toolbarItemMaxHeight_)) {
        toolbarItemMaxHeight_ = toolbarItemHeight;
    }

    return AddToolbarItemToSpecificRow(placeMent, frameNode);
}

bool ContainerModalToolBar::AddToolbarItemToSpecificRow(ItemPlacementType placeMent, const RefPtr<FrameNode>& frameNode)
{
    bool ref = false;
    switch (placeMent) {
        case ItemPlacementType::NAV_BAR_START:
            ref = AddToolbarItemToNavBarStart(frameNode);
            break;
        case ItemPlacementType::NAV_BAR_END:
            ref = AddToolbarItemToNavBarEnd(frameNode);
            break;
        case ItemPlacementType::NAVDEST_START:
            ref = AddToolbarItemToNavDestStart(frameNode);
            break;
        case ItemPlacementType::NAVDEST_END:
            ref = AddToolbarItemToNavDestEnd(frameNode);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Unknown placement");
            return false;
    }
    auto containermodal = pattern_.Upgrade();
    CHECK_NULL_RETURN(containermodal, ref);
    containermodal->SetIsHaveToolBar(true);
    if (!isTitleShow_ || customTitleShow_) {
        auto pipeline = containermodal->GetContext();
        CHECK_NULL_RETURN(pipeline, true);
        auto overlayTask = [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->AdjustContainerModalTitleHeight();
        };
        pipeline->AddAfterRenderTask(overlayTask);
    }
    return ref;
}

bool ContainerModalToolBar::AddToolbarItemToNavBarStart(const RefPtr<FrameNode>& frameNode)
{
    if (!navbarRow_) {
        AddNavBarRow();
    }
    if (navbarRow_) {
        if (!leftNavRow_) {
            AddLeftNavRow();
        }
        leftNavRow_->AddChild(frameNode);
        leftNavRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return true;
    }
    return false;
}

bool ContainerModalToolBar::AddToolbarItemToNavBarEnd(const RefPtr<FrameNode>& frameNode)
{
    if (!navbarRow_) {
        AddNavBarRow();
    }

    if (navbarRow_) {
        if (!rightNavRow_) {
            AddLeftNavRow();
            AddRightNavRow();
        }
        rightNavRow_->AddChild(frameNode);
        rightNavRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return true;
    }
    return false;
}

bool ContainerModalToolBar::AddToolbarItemToNavDestStart(const RefPtr<FrameNode>& frameNode)
{
    if (!navDestbarRow_) {
        AddNavDestBarRow();
    }

    if (navDestbarRow_) {
        if (!leftNavDestRow_) {
            AddLeftNavDestRow();
        }
        leftNavDestRow_->AddChild(frameNode);
        leftNavDestRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return true;
    }
    return false;
}

bool ContainerModalToolBar::AddToolbarItemToNavDestEnd(const RefPtr<FrameNode>& frameNode)
{
    if (!navDestbarRow_) {
        AddNavDestBarRow();
    }

    if (navDestbarRow_) {
        if (!rightNavDestRow_) {
            AddLeftNavDestRow();
            AddRightNavDestRow();
        }
        rightNavDestRow_->AddChild(frameNode);
        rightNavDestRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return true;
    }
    return false;
}

void ContainerModalToolBar::AddNavBarRow()
{
    CHECK_NULL_VOID(title_);
    auto navBarInfo = toolbarManager_->GetNavBarInfo();
    if (navBarInfo.isShow) {
        if (!navbarRow_) {
            navbarRow_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                MakeRefPtr<LinearLayoutPattern>(false));
            navbarRow_->UpdateInspectorId("NavBar");
            auto layout = navbarRow_->GetLayoutProperty<LinearLayoutProperty>();
            CHECK_NULL_VOID(layout);
            layout->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
            layout->UpdateCrossAxisAlign(FlexAlign::CENTER);
            auto renderContext = navbarRow_->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->SetClipToFrame(true);
            title_->AddChild(navbarRow_, 1);
            navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
    }
    title_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void ContainerModalToolBar::AddLeftNavRow()
{
    if (navbarRow_) {
        if (!leftNavRow_) {
            leftNavRow_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                MakeRefPtr<LinearLayoutPattern>(false));
            leftNavRow_->UpdateInspectorId("LeftNavRow");
            auto layout = leftNavRow_->GetLayoutProperty<LinearLayoutProperty>();
            CHECK_NULL_VOID(layout);
            MarginProperty margin;
            margin.SetEdges(CalcLength(Dimension(ROW_MARGIN, DimensionUnit::VP)));
            layout->UpdateMargin(margin);
            navbarRow_->AddChild(leftNavRow_, 0);
            leftNavRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
        navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        title_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    AdjustNavbarRowWidth();
}

void ContainerModalToolBar::AddRightNavRow()
{
    if (navbarRow_) {
        if (!rightNavRow_) {
            rightNavRow_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                MakeRefPtr<LinearLayoutPattern>(false));
            rightNavRow_->UpdateInspectorId("RightNavRow");
            navbarRow_->AddChild(rightNavRow_);
            auto layout = rightNavRow_->GetLayoutProperty<LinearLayoutProperty>();
            CHECK_NULL_VOID(layout);
            MarginProperty margin;
            margin.SetEdges(CalcLength(Dimension(ROW_MARGIN, DimensionUnit::VP)));
            layout->UpdateMargin(margin);
            layout->UpdateMainAxisAlign(FlexAlign::FLEX_END);
            rightNavRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
        navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        title_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    AdjustNavbarRowWidth();
}

void ContainerModalToolBar::AddNavDestBarRow()
{
    auto navDestInfo = toolbarManager_->GetNavDestInfo();
    if (navDestInfo.isShow) {
        if (!navDestbarRow_) {
            navDestbarRow_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                MakeRefPtr<LinearLayoutPattern>(false));
            navDestbarRow_->UpdateInspectorId("NavDestBar");
            auto layout = navDestbarRow_->GetLayoutProperty<LinearLayoutProperty>();
            CHECK_NULL_VOID(layout);
            layout->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
            layout->UpdateCrossAxisAlign(FlexAlign::CENTER);
            auto renderContext = navDestbarRow_->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->SetClipToFrame(true);
            title_->AddChild(navDestbarRow_);
            navDestbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
    }
    title_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void ContainerModalToolBar::AddLeftNavDestRow()
{
    if (navDestbarRow_) {
        if (!leftNavDestRow_) {
            leftNavDestRow_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));
            leftNavDestRow_->UpdateInspectorId("LeftNavDest");
            auto layout = leftNavDestRow_->GetLayoutProperty<LinearLayoutProperty>();
            CHECK_NULL_VOID(layout);
            MarginProperty margin;
            margin.SetEdges(CalcLength(Dimension(ROW_MARGIN, DimensionUnit::VP)));
            layout->UpdateMargin(margin);
            navDestbarRow_->AddChild(leftNavDestRow_, 0);
            leftNavDestRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
        navDestbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        title_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    AdjustNavDestRowWidth();
}

void ContainerModalToolBar::AddRightNavDestRow()
{
    if (navDestbarRow_) {
        if (!rightNavDestRow_) {
            rightNavDestRow_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));
            rightNavDestRow_->UpdateInspectorId("RightNavDest");
            navDestbarRow_->AddChild(rightNavDestRow_);
            auto layout = rightNavDestRow_->GetLayoutProperty<LinearLayoutProperty>();
            CHECK_NULL_VOID(layout);
            MarginProperty margin;
            margin.SetEdges(CalcLength(Dimension(ROW_MARGIN, DimensionUnit::VP)));
            layout->UpdateMargin(margin);
            layout->UpdateMainAxisAlign(FlexAlign::FLEX_END);
            rightNavDestRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
        navDestbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        title_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    AdjustNavDestRowWidth();
}

void ContainerModalToolBar::RemoveToolbarRowContainers()
{
    auto RemoveIfEmpty = [this](RefPtr<FrameNode>& container, const RefPtr<FrameNode>& parent) {
        if (container && container->GetChildren().empty()) {
            if (parent) {
                parent->RemoveChild(container);
                parent->MarkDirtyNode(
                    PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
            }
            container = nullptr;
        }
    };
    RemoveIfEmpty(rightNavRow_, navbarRow_);
    RemoveIfEmpty(rightNavDestRow_, navDestbarRow_);
    if (!rightNavRow_ && navbarRow_) {
        RemoveIfEmpty(leftNavRow_, navbarRow_);
    }
    if (!rightNavDestRow_ && navDestbarRow_) {
        RemoveIfEmpty(leftNavDestRow_, navDestbarRow_);
    }
    RemoveIfEmpty(navbarRow_, title_);
    RemoveIfEmpty(navDestbarRow_, title_);
    if (title_) {
        title_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
    if (!navbarRow_ && !navDestbarRow_) {
        auto containermodal = pattern_.Upgrade();
        CHECK_NULL_VOID(containermodal);
        containermodal->SetIsHaveToolBar(false);
    }
}

void ContainerModalToolBar::OnToolBarLayoutChange()
{
    if (!toolbarManager_ || !HasNavOrSideBarNodes()) {
        return;
    }

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto pipeline = pattern->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterRenderTask([weak = WeakClaim(this), toolbarMgr = toolbarManager_]() {
        auto toolbar = weak.Upgrade();
        CHECK_NULL_VOID(toolbar);
        toolbar->AdjustTitleNodeWidth();
        CHECK_NULL_VOID(toolbarMgr);
        if (toolbarMgr->GetNavBarInfo().isShow) {
            toolbar->AdjustNavbarRowWidth();
        }
        if (toolbarMgr->GetNavDestInfo().isShow) {
            toolbar->AdjustNavDestRowWidth();
        }
    });
}

void ContainerModalToolBar::AdjustTitleNodeWidth()
{
    auto sideBarInfo = toolbarManager_->GetSideBarInfo();
    float titleNodeWidth = sideBarInfo.isShow ? sideBarInfo.width : 0;

    auto titleNode = AceType::DynamicCast<FrameNode>(title_->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto titleNodeProperty = titleNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(titleNodeProperty);
    titleNodeProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    if (itemsOnTree_.empty()) {
        titleNodeProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::PERCENT)));
        titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return;
    }

    auto renderContext = titleNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(true);
    titleNodeProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(titleNodeWidth), CalcLength(1.0, DimensionUnit::PERCENT)));
    titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void ContainerModalToolBar::AdjustNavbarRowWidth()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);

    auto sideBarInfo = toolbarManager_->GetSideBarInfo();
    auto sideBarDividerInfo = toolbarManager_->GetSideBarDividerInfo();
    auto navbarInfo = toolbarManager_->GetNavBarInfo();
    auto navbarDividerInfo = toolbarManager_->GetNavBarDividerInfo();
    auto navDestInfo = toolbarManager_->GetNavDestInfo();
    auto controlButtonsWidth = pattern->GetControlButtonRowWidth();
    float navbarRowWidth = 0.0f;

    if (navbarInfo.isShow && navbarRow_) {
        auto navbarRowProperty = navbarRow_->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(navbarRowProperty);
        if (navDestInfo.isShow && LessOrEqual(navDestInfo.width, controlButtonsWidth.GetDimension().ConvertToPx())) {
            navbarRowWidth = navDestInfo.width + navbarInfo.width - controlButtonsWidth.GetDimension().ConvertToPx();
        } else {
            navbarRowWidth = navbarInfo.width;
        }
        navbarRowProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(navbarRowWidth), std::nullopt));
        auto isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        MarginProperty navbarRowMargin;
        if (isRtl) {
            if (navDestInfo.isShow &&
                LessOrEqual(navDestInfo.width, controlButtonsWidth.GetDimension().ConvertToPx())) {
                navbarRowMargin.left = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
                navbarRowMargin.right = sideBarInfo.isShow ? CalcLength(sideBarDividerInfo.width) : CalcLength(0);
            } else {
                navbarRowMargin.left = CalcLength(navbarDividerInfo.width);
                navbarRowMargin.right = sideBarInfo.isShow ? CalcLength(sideBarDividerInfo.width) : CalcLength(0);
            }
        } else {
            if (navDestInfo.isShow &&
                LessOrEqual(navDestInfo.width, controlButtonsWidth.GetDimension().ConvertToPx())) {
                navbarRowMargin.left = sideBarInfo.isShow ? CalcLength(sideBarDividerInfo.width) : CalcLength(0);
                navbarRowMargin.right = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
            } else {
                navbarRowMargin.left = sideBarInfo.isShow ? CalcLength(sideBarDividerInfo.width) : CalcLength(0);
                navbarRowMargin.right = CalcLength(navbarDividerInfo.width);
            }
        }
        navbarRowProperty->UpdateMargin(navbarRowMargin);
        navbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        navbarRowProperty->UpdateVisibility(
            NearEqual(navbarInfo.width, 0.0f) ? VisibleType::INVISIBLE : VisibleType::VISIBLE);
    }
}

void ContainerModalToolBar::AdjustNavDestRowWidth()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);

    CHECK_NULL_VOID(toolbarManager_);
    auto sideBarInfo = toolbarManager_->GetSideBarInfo();
    auto sideBarDividerInfo = toolbarManager_->GetSideBarDividerInfo();
    auto navbarInfo = toolbarManager_->GetNavBarInfo();
    auto navbarDividerInfo = toolbarManager_->GetNavBarDividerInfo();
    auto navDestInfo = toolbarManager_->GetNavDestInfo();
    auto controlButtonsWidth = pattern->GetControlButtonRowWidth();

    if (navDestInfo.isShow && navDestbarRow_) {
        float navDestbarRowAvailableWidth = navDestInfo.width - controlButtonsWidth.GetDimension().ConvertToPx();
        auto navDestbarRowProperty = navDestbarRow_->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(navDestbarRowProperty);
        navDestbarRowProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(navDestbarRowAvailableWidth), std::nullopt));
        float navDestbarRowLeftMargin = 0.0f;
        if (navbarRow_) {
            navDestbarRowLeftMargin = navbarDividerInfo.width;
        } else if (!sideBarInfo.isShow && !navbarInfo.isShow) {
            navDestbarRowLeftMargin = 0.0f;
        } else if (!sideBarInfo.isShow) {
            navDestbarRowLeftMargin = navbarInfo.width + navbarDividerInfo.width;
        } else if (!navbarInfo.isShow) {
            navDestbarRowLeftMargin = sideBarDividerInfo.width;
        } else {
            navDestbarRowLeftMargin = sideBarDividerInfo.width + navbarInfo.width + navbarDividerInfo.width;
        }
        auto isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        MarginProperty navDestbarRowMargin;
        if (isRtl) {
            navDestbarRowMargin.left = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
            navDestbarRowMargin.right = CalcLength(navDestbarRowLeftMargin);
        } else {
            navDestbarRowMargin.left = CalcLength(navDestbarRowLeftMargin);
            navDestbarRowMargin.right = CalcLength(controlButtonsWidth.GetDimension().ConvertToPx());
        }
        navDestbarRowProperty->UpdateMargin(navDestbarRowMargin);
        navDestbarRow_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        navDestbarRowProperty->UpdateVisibility(
            NearEqual(navDestInfo.width, 0.0f) ? VisibleType::INVISIBLE : VisibleType::VISIBLE);
    }
}

void ContainerModalToolBar::UpdateToolbarShow(bool isTitleShow, bool customTitleSettedShow)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    isTitleShow_ = isTitleShow;
    customTitleShow_ = customTitleSettedShow;

    if (!isTitleShow || customTitleSettedShow) {
        UpdateTitleLayout();
    } else if (!customTitleSettedShow) {
        pattern->SetControlButtonsRowHeight(CONTAINER_TITLE_HEIGHT);
    }
}

void ContainerModalToolBar::AdjustContainerModalTitleHeight()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);

    if (itemsOnTree_.empty()) {
        pattern->titleHeight_ = CONTAINER_TITLE_HEIGHT;
        pattern->SetContainerModalTitleHeight(CONTAINER_TITLE_HEIGHT.ConvertToPx());
        ResetExpandStackNode();
        return;
    }

    auto rowHeight = toolbarItemMaxHeight_ + ROW_TOTAL_MARGIN;
    if (NearEqual(toolbarItemMaxHeight_, 0.0f)) {
        pattern->titleHeight_ = CONTAINER_TITLE_HEIGHT;
    } else if (LessOrEqual(rowHeight, TITLE_ITEM_HEIGT_S)) {
        pattern->titleHeight_ = Dimension(TITLE_ITEM_HEIGT_S, DimensionUnit::VP);
    } else if (GreatNotEqual(rowHeight, TITLE_ITEM_HEIGT_S) && LessOrEqual(rowHeight, TITLE_ITEM_HEIGT_M)) {
        pattern->titleHeight_ = Dimension(TITLE_ITEM_HEIGT_M, DimensionUnit::VP);
    } else if (GreatNotEqual(rowHeight, TITLE_ITEM_HEIGT_M)) {
        pattern->titleHeight_ = Dimension(TITLE_ITEM_HEIGT_L, DimensionUnit::VP);
    }
    pattern->SetContainerModalTitleHeight(pattern->titleHeight_.ConvertToPx());
    UpdateTargetNodesBarMargin();
}

std::string ContainerModalToolBar::GetTagFromNode(RefPtr<UINode> node)
{
    std::string tag = "";
    CHECK_NULL_RETURN(node, tag);
    auto navigationNode = navigationNode_.Upgrade();
    while (node && node->GetTag() != V2::ROOT_ETS_TAG) {
        if (node->GetTag() == V2::NAVBAR_ETS_TAG && navigationNode && navigationNode == node->GetParent()) {
            tag = node->GetTag();
            break;
        }
        if (node->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            if (node == navDestNode_) {
                tag = node->GetTag();
                break;
            }
            auto navDestContentNode = node->GetParent();
            if (navDestContentNode && navigationNode && navigationNode == navDestContentNode->GetParent()) {
                tag = node->GetTag();
                break;
            }
        }
        node = node->GetParent();
    }
    return tag;
}

/**
 * @brief This method traverses the node hierarchy to identify and set specific target nodes
 *        (SideBar, Navigation, and Navigation Destination nodes) based on their tags and geometry.
 *
 * @return Returns true if any of the target nodes (SideBar, Navigation, or Navigation Destination)
 *         are found and set; otherwise, returns false.
 *
 * @details The method performs the following steps:
 * - Retrieves the root content node and its geometry content.
 * - Initializes a queue for breadth-first traversal of the node hierarchy.
 * - Iterates through the child nodes to find nodes with specific tags:
 *   - SIDE_BAR_ETS_TAG: Identifies the SideBar node if its width matches the root content width.
 *   - NAVBAR_ETS_TAG: If the SideBar node has not be finded, identifies the Navigation node if its width matches
 * the root content width, else identifies the Navigation node direct
 *   - NAVDESTINATION_VIEW_ETS_TAG: Identifies the Navigation Destination node.
 * - Stops traversal once all required nodes are found or the hierarchy is fully traversed.
 *
 * @note The method uses a queue to perform breadth-first traversal and ensures that
 *       the search stops as soon as the required nodes are identified.
 */
bool ContainerModalToolBar::GetNavOrSideBarNodes(const RefPtr<FrameNode>& node)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto stage = pattern->GetContentNode();
    CHECK_NULL_RETURN(stage, false);
    auto page = GetCurrentPageNode(node);
    CHECK_NULL_RETURN(page, false);
    auto stageGeometryNode = stage->GetGeometryNode();
    CHECK_NULL_RETURN(stageGeometryNode, false);
    auto width = stageGeometryNode->GetFrameSize().Width();
    return GetNavOrSideBarNodesParseChildren(page, width);
}

RefPtr<UINode> ContainerModalToolBar::GetCurrentPageNode(const RefPtr<UINode>& node)
{
    auto tempNode = node;
    while (tempNode) {
        auto parent = tempNode->GetParent();
        if (tempNode->GetTag() == V2::PAGE_ETS_TAG && parent && parent->GetTag() == V2::STAGE_ETS_TAG) {
            return tempNode;
        }
        tempNode = parent;
    }
    return nullptr;
}

bool ContainerModalToolBar::GetNavOrSideBarNodesParseChildren(const RefPtr<UINode>& page, float pageWidth)
{
    std::queue<RefPtr<UINode>> queue {};
    bool isSideBarFound = false;
    bool isNavigationFound = false;
    bool isNavDestFound = false;
    queue.emplace(page);
    RefPtr<UINode> parentNode;
    float sideBarHeight = 0.0f;
    while (!queue.empty()) {
        parentNode = queue.front();
        queue.pop();
        auto children = parentNode->GetChildren();
        if (children.empty()) {
            continue;
        }
        for (auto child : children) {
            queue.emplace(child);
            auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_CONTINUE(childFrameNode)
            if (IsTragetSideBarNodeParse(childFrameNode, pageWidth, sideBarHeight, isSideBarFound)) {
                std::queue<RefPtr<UINode>>().swap(queue);
                queue.emplace(child);
                isSideBarFound = true;
                break;
            } else if (IsTragetNavigationNodeParse(
                childFrameNode, pageWidth, sideBarHeight, isNavigationFound, isSideBarFound)) {
                std::queue<RefPtr<UINode>>().swap(queue);
                queue.emplace(child);
                isSideBarFound = true;
                isNavigationFound = true;
                break;
            } else if ((isNavigationFound && isSideBarFound) || (isNavigationFound &&
                childFrameNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG)) {
                isSideBarFound = true;
                isNavigationFound = true;
                isNavDestFound = true;
                navDestNode_ = childFrameNode;
            }
            if ((isNavigationFound && isSideBarFound) || (isNavigationFound && isNavDestFound)) {
                break;
            }
        }
        if ((isNavigationFound && isSideBarFound) || (isNavigationFound && isNavDestFound)) {
            break;
        }
    }
    if ((isNavigationFound && isSideBarFound) || (isNavigationFound && isNavDestFound)) {
        return true;
    }
    return false;
}

bool ContainerModalToolBar::IsTragetSideBarNodeParse(
    const RefPtr<FrameNode>& childFrameNode, float pageWidth, float& sideBarHeight, bool isSideBarFound)
{
    CHECK_NULL_RETURN(childFrameNode, false);
    if (!isSideBarFound && childFrameNode->GetTag() == V2::SIDE_BAR_ETS_TAG) {
        auto geometryNode = childFrameNode->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, false);
        auto childWidth = geometryNode->GetFrameSize().Width();
        if (NearEqual(pageWidth, childWidth)) {
            sideBarHeight = geometryNode->GetFrameSize().Height();
            sideBarNode_ = childFrameNode;
            return true;
        }
    }
    return false;
}

bool ContainerModalToolBar::IsTragetNavigationNodeParse(const RefPtr<FrameNode>& childFrameNode, float pageWidth,
    float sideBarHeight, bool isNavigationFound, bool isSideBarFound)
{
    CHECK_NULL_RETURN(childFrameNode, false);
    CHECK_NULL_RETURN(toolbarManager_, false);

    if (!isNavigationFound && childFrameNode->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
        auto navigationPattern = childFrameNode->GetPattern<NavigationPattern>();
        CHECK_NULL_RETURN(navigationPattern, false);
        NavigationMode navigationMode = navigationPattern->GetNavigationMode();
        if (!isSideBarFound) {
            auto geometryNode = childFrameNode->GetGeometryNode();
            CHECK_NULL_RETURN(geometryNode, false);
            auto childWidth = geometryNode->GetFrameSize().Width();
            if (NearEqual(pageWidth, childWidth) && navigationMode == NavigationMode::SPLIT) {
                navigationNode_ = childFrameNode;
                return true;
            }
        } else {
            auto geometryNode = childFrameNode->GetGeometryNode();
            CHECK_NULL_RETURN(geometryNode, false);
            auto childHeight = geometryNode->GetFrameSize().Height();
            if ((NearEqual(sideBarHeight, childHeight) || NearEqual(sideBarHeight, 0.0f)) &&
                navigationMode == NavigationMode::SPLIT) {
                navigationNode_ = childFrameNode;
                return true;
            }
        }
    }
    return false;
}

void ContainerModalToolBar::ToInitNavOrSideBarNode()
{
    auto sideBarNode = sideBarNode_.Upgrade();
    if (sideBarNode) {
        auto sideBarPattern = AceType::DynamicCast<NG::SideBarContainerPattern>(sideBarNode->GetPattern());
        if (sideBarPattern) {
            sideBarPattern->InitToolBarManager();
            sideBarNode->MarkModifyDone();
        }
    }
    auto navigationNode = navigationNode_.Upgrade();
    if (navigationNode) {
        auto navigationPattern = AceType::DynamicCast<NG::NavigationPattern>(navigationNode->GetPattern());
        if (navigationPattern) {
            navigationPattern->InitToolBarManager();
            navigationNode->MarkModifyDone();
        }
    }
    CHECK_NULL_VOID(toolbarManager_);
    std::function<void()> getTypeOfItem = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = pattern->navigationNode_.Upgrade();
        CHECK_NULL_VOID(node);
        pattern->ParsePlacementType(node);
    };
    toolbarManager_->SetModifyDoneCallback(std::move(getTypeOfItem));
}

void ContainerModalToolBar::UpdateSideTitleBgColor(
    const Color& sideBarColor, const Color& sideBarContainerColor, const BlurStyle& blurStyle)
{
    CHECK_NULL_VOID(title_);
    auto titleNode = AceType::DynamicCast<FrameNode>(title_->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto ctx = titleNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    Color color = sideBarContainerColor.BlendColorWithAlpha(sideBarColor);
    ctx->UpdateBackgroundColor(color);
    BlurStyleOption option;
    option.blurStyle = blurStyle;
    ctx->UpdateBackBlurStyle(option);
}

void ContainerModalToolBar::SetCustomTitleRowBlurStyle(BlurStyle& blurStyle)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto customTitleRow = pattern->GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto renderContext = customTitleRow->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BlurStyleOption styleOption;
    styleOption.blurStyle = blurStyle;
    renderContext->UpdateBackBlurStyle(styleOption);
}
void ContainerModalToolBar::UpdateSidebarMargin()
{
    CHECK_NULL_VOID(toolbarManager_);
    if (toolbarManager_->GetIsMoveUp()) {
        auto sideBarContainerModelNode = toolbarManager_->GetSideBarContainerModel().Upgrade();
        CHECK_NULL_VOID(sideBarContainerModelNode);
        sideBarContainerModelNode->MarkDirtyNode(
            PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        sideBarContainerModelNode->MarkModifyDone();
        isUpdateTargetNode_ = true;
    }
}

void ContainerModalToolBar::UpdateNavbarTitlebarMargin()
{
    CHECK_NULL_VOID(toolbarManager_);
    if (toolbarManager_->GetIsMoveUp()) {
        auto navBarNode = toolbarManager_->GetNavBar().Upgrade();
        CHECK_NULL_VOID(navBarNode);
        auto navigation = navBarNode->GetParent();
        CHECK_NULL_VOID(navigation);
        auto navigationFrameNode = AceType::DynamicCast<FrameNode>(navigation);
        CHECK_NULL_VOID(navigationFrameNode);
        navigationFrameNode->MarkDirtyNode(
            PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        navigationFrameNode->MarkModifyDone();
        isUpdateTargetNode_ = true;
    }
}

void ContainerModalToolBar::UpdateNavDestinationTitlebarMargin()
{
    CHECK_NULL_VOID(toolbarManager_);
    if (toolbarManager_->GetIsMoveUp()) {
        auto navigationContentNode = toolbarManager_->GetNavDest().Upgrade();
        CHECK_NULL_VOID(navigationContentNode);
        auto navigationFrameNode = AceType::DynamicCast<FrameNode>(navigationContentNode->GetParent());
        CHECK_NULL_VOID(navigationFrameNode);
        auto navigationPattern = navigationFrameNode->GetPattern<NG::NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        auto navigationStack = navigationPattern->GetNavigationStack();
        CHECK_NULL_VOID(navigationStack);
        auto topNavDestinationNode = navigationStack->GetTopNavPath();
        if (!topNavDestinationNode.has_value()) {
            return;
        }
        auto navDestinationNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(
            NG::NavigationGroupNode::GetNavDestinationNode(topNavDestinationNode->second));
        CHECK_NULL_VOID(navDestinationNode);
        navDestinationNode->MarkDirtyNode(
            PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        navDestinationNode->MarkModifyDone();
        isUpdateTargetNode_ = true;
    }
}

void ContainerModalToolBar::UpdateTargetNodesBarMargin(bool reset)
{
    if (!toolbarManager_ || isFloating_) {
        return;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (reset) {
        if (!isUpdateTargetNode_) {
            return;
        }
        toolbarManager_->SetTitleHeight(Dimension(0.0f));
    } else {
        if (!isUpdateTargetNode_ && pattern->GetIsHaveToolBar() && pattern->IsExpandStackNode()) {
            ExpandStackNodeLayout();
            BlurStyle blurStyle = BlurStyle::THIN;
            SetCustomTitleRowBlurStyle(blurStyle);
            toolbarManager_->SetIsMoveUp(true);
        }
        toolbarManager_->SetTitleHeight(pattern->titleHeight_);
    }

    UpdateNavDestinationTitlebarMargin();
    UpdateNavbarTitlebarMargin();
    UpdateSidebarMargin();
}

void ContainerModalToolBar::ExpandStackNodeLayout(bool reset)
{
    CHECK_NULL_VOID(title_);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto stackNode = pattern->GetStackNode();
    CHECK_NULL_VOID(stackNode);
    auto renderContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto stackLayoutProperty = stackNode->GetLayoutProperty<StackLayoutProperty>();
    CHECK_NULL_VOID(stackLayoutProperty);
    if (reset) {
        auto titleRenderContext = title_->GetRenderContext();
        CHECK_NULL_VOID(titleRenderContext);
        titleRenderContext->ResetBackBlurStyle();
        renderContext->ResetPosition();
        renderContext->ResetZIndex();
        auto titleNode = AceType::DynamicCast<FrameNode>(title_->GetChildren().front());
        CHECK_NULL_VOID(titleNode);
        auto titleNodeCtx = titleNode->GetRenderContext();
        CHECK_NULL_VOID(titleNodeCtx);
        titleNodeCtx->ResetBackBlurStyle();
        titleNodeCtx->UpdateBackgroundColor(Color::TRANSPARENT);
    } else {
        renderContext->UpdatePosition(OffsetT(Dimension(0.0f), Dimension(0.0f)));
        renderContext->UpdateZIndex(-1);
    }
    auto columnNode = pattern->GetColumnNode();
    CHECK_NULL_VOID(columnNode);
    columnNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    columnNode->MarkModifyDone();
}

void ContainerModalToolBar::ResetExpandStackNode()
{
    if (!isUpdateTargetNode_ || isFloating_ || !toolbarManager_) {
        return;
    }
    UpdateTargetNodesBarMargin(true);
    isUpdateTargetNode_ = false;
    toolbarManager_->SetIsMoveUp(false);
    ExpandStackNodeLayout(true);
}
} // namespace OHOS::Ace::NG