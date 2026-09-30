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

#include "core/components_ng/pattern/tabs/tabs_side_bar_pattern.h"

#include <optional>
#include <string>

#include "interfaces/native/ui_input_event.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/log/ace_checker.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/search/bridge/search_custom_modifier.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_declaration.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_side_bar_tab_list_pattern.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/gestures/gesture_info.h"
#include "core/interfaces/native/node/search_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HEADER_CONTAINER_MASK_BLUR_ZINDEX = 1;
constexpr int32_t HEADER_CONTAINER_MASK_ZINDEX = 2;
constexpr int32_t HEADER_CONTAINER_NODE_ZINDEX = 3;
constexpr int32_t BOTTOM_BAR_CONTAINER_MASK_BLUR_ZINDEX = 1;
constexpr int32_t BOTTOM_BAR_CONTAINER_MASK_ZINDEX = 2;
constexpr int32_t BOTTOM_BAR_CONTAINER_NODE_ZINDEX = 3;
const Dimension DEFAULT_SEARCH_NODE_HEIGHT = 56.0_vp;

// Gradual blur constants (referencing TitleBar's GRADUAL_BLUR parameters)
const Dimension GRADUAL_BLUR_SCROLL_THRESHOLD = 56.0_vp;
const Dimension GRADUAL_BLUR_MAX_RADIUS = 12.0_vp;
constexpr double GRADUAL_BLUR_MAX_OPACITY = 0.8;

const std::vector<std::pair<float, float>> MASK_BLUR_STOPS = {
    { 1.0f, 0.0f }, { 0.6f, 0.6f }, { 0.0f, 1.0f }
};

const std::vector<std::pair<float, float>> FADE_OUT_GRADIENT_STOPS = {
    {1.0f, 0.0f}, {1.0f, 0.3f}, {0.99764f, 0.335f}, {0.99010f, 0.370f},
    {0.97627f, 0.405f}, {0.95574f, 0.440f}, {0.92808f, 0.475f},
    {0.89108f, 0.510f}, {0.84375f, 0.545f}, {0.78547f, 0.580f},
    {0.71344f, 0.615f}, {0.63048f, 0.650f}, {0.53513f, 0.685f},
    {0.43280f, 0.720f}, {0.33021f, 0.755f}, {0.23699f, 0.790f},
    {0.15625f, 0.825f}, {0.09588f, 0.860f}, {0.05096f, 0.895f},
    {0.02089f, 0.930f}, {0.00491f, 0.965f}, {0.0f, 1.0f}
};
}

void TabsSideBarPattern::CreateHeaderContainerIfNeeded()
{
    if (headerContainerNode_) {
        return;
    }
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto columnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_VOID(columnNode);
    auto property = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(property);
    property->UpdateFlexDirection(FlexDirection::COLUMN);
    auto renderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(HEADER_CONTAINER_NODE_ZINDEX);
    headerContainerNode_ = columnNode;
    columnNode->MountToParent(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarPattern::CreateBottomBarContainerIfNeeded()
{
    if (bottomBarContainerNode_) {
        return;
    }
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto columnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_VOID(columnNode);
    auto property = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(property);
    property->UpdateFlexDirection(FlexDirection::COLUMN);
    auto renderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(BOTTOM_BAR_CONTAINER_NODE_ZINDEX);
    bottomBarContainerNode_ = columnNode;
    columnNode->MountToParent(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarPattern::CreateMaskNodeIfNeeded()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    do {
        if (headerContainerMaskBlurNode_) {
            break;
        }
        auto maskBlurNode = CreateEffectNode("TabsSideBarHeaderMaskBlur");
        CHECK_NULL_BREAK(maskBlurNode);
        auto property = maskBlurNode->GetLayoutProperty();
        CHECK_NULL_BREAK(property);
        property->UpdateVisibility(VisibleType::INVISIBLE);
        auto maskBlurRenderContext = maskBlurNode->GetRenderContext();
        CHECK_NULL_BREAK(maskBlurRenderContext);
        maskBlurRenderContext->UpdateZIndex(HEADER_CONTAINER_MASK_BLUR_ZINDEX);
        headerContainerMaskBlurNode_ = maskBlurNode;
        maskBlurNode->MountToParent(host);
    } while (false);
    if (headerContainerMaskNode_) {
        return;
    }
    auto maskNode = CreateEffectNode("TabsSideBarHeaderMask");
    CHECK_NULL_VOID(maskNode);
    auto property = maskNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    property->UpdateVisibility(VisibleType::INVISIBLE);
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    maskRenderContext->UpdateZIndex(HEADER_CONTAINER_MASK_ZINDEX);
    headerContainerMaskNode_ = maskNode;
    maskNode->MountToParent(host);
}

void TabsSideBarPattern::CreateBottomBarMaskNodeIfNeeded()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    do {
        if (bottomBarMaskBlurNode_) {
            break;
        }
        auto maskBlurNode = CreateEffectNode("TabsSideBarBottomBarMaskBlur");
        CHECK_NULL_BREAK(maskBlurNode);
        auto property = maskBlurNode->GetLayoutProperty();
        CHECK_NULL_BREAK(property);
        property->UpdateVisibility(VisibleType::INVISIBLE);
        auto maskBlurRenderContext = maskBlurNode->GetRenderContext();
        CHECK_NULL_BREAK(maskBlurRenderContext);
        maskBlurRenderContext->UpdateZIndex(BOTTOM_BAR_CONTAINER_MASK_BLUR_ZINDEX);
        bottomBarMaskBlurNode_ = maskBlurNode;
        maskBlurNode->MountToParent(host);
    } while (false);
    if (bottomBarMaskNode_) {
        return;
    }
    auto maskNode = CreateEffectNode("TabsSideBarBottomBarMask");
    CHECK_NULL_VOID(maskNode);
    auto property = maskNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    property->UpdateVisibility(VisibleType::INVISIBLE);
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    maskRenderContext->UpdateZIndex(BOTTOM_BAR_CONTAINER_MASK_ZINDEX);
    bottomBarMaskNode_ = maskNode;
    maskNode->MountToParent(host);
}

RefPtr<FrameNode> TabsSideBarPattern::CreateSearchContainer()
{
    auto containerNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_RETURN(containerNode, nullptr);
    auto property = containerNode->GetLayoutProperty();
    CHECK_NULL_RETURN(property, nullptr);
    // get previously user defined ideal width
    property->MarkUserDefinedHeightConfigured();
    std::optional<CalcLength> width = std::nullopt;
    auto&& layoutConstraint = property->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        width = layoutConstraint->selfIdealSize->Width();
    }
    std::optional<CalcLength> height = CalcLength(DEFAULT_SEARCH_NODE_HEIGHT);
    property->UpdateUserDefinedIdealSize(CalcSize(width, height));
    property->UpdateAlignment(Alignment::CENTER);
    return containerNode;
}

void TabsSideBarPattern::CreateChildNodeIfNeeded(const RefPtr<FrameNode>& tabsNode)
{
    CreateHeaderContainerIfNeeded();
    CreateMaskNodeIfNeeded();
    CreateTabListIfNeeded(tabsNode);
    CreateBottomBarContainerIfNeeded();
    CreateBottomBarMaskNodeIfNeeded();
}

void TabsSideBarPattern::CreateTabListIfNeeded(const RefPtr<FrameNode>& tabsNode)
{
    if (tabListNode_) {
        return;
    }
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);

    // Create SideBarTabListNode with TabsSideBarTabListPattern (NOT TabBarPattern)
    auto tabListNode = FrameNode::GetOrCreateFrameNode(
        V2::TABS_SIDE_BAR_TAB_LIST_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TabsSideBarTabListPattern>(); });
    CHECK_NULL_VOID(tabListNode);
    auto tabListPattern = tabListNode->GetPattern<TabsSideBarTabListPattern>();
    CHECK_NULL_VOID(tabListPattern);
    tabListPattern->SetTabsNode(tabsNode);
    tabsNode_ = tabsNode;

    // Create ScrollNode (vertical scrolling)
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::ALL);
    scrollPattern->SetNeedFullSafeArea(true);
    auto scrollLayoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    if (scrollLayoutProperty) {
        scrollLayoutProperty->UpdateAxis(Axis::VERTICAL);
        // Align content to top when Column is shorter than Scroll viewport
        // (Scroll defaults to CENTER alignment).
        scrollLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
    }
    auto controller = scrollPattern->GetOrCreatePositionController();
    CHECK_NULL_VOID(controller);
    ScrollerObserver observer;
    observer.onDidScrollEvent = [weakPattern = WeakClaim(this), weakScrollPattern = WeakPtr(scrollPattern)](
        Dimension, ScrollSource, bool, bool) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto scrollPattern = weakScrollPattern.Upgrade();
        CHECK_NULL_VOID(scrollPattern);
        float totalOffset = static_cast<float>(scrollPattern->GetTotalOffset());
        float scrollableDistance = scrollPattern->GetScrollableDistance();
        pattern->OnTabListScroll(totalOffset, scrollableDistance);
    };
    controller->SetObserver(observer);
    // Hide scrollbar for sidebar tab list
    ScrollableModelNG::SetScrollBarMode(AceType::RawPtr(scrollNode), DisplayMode::OFF);
    // clipContent(SAFE_AREA): expand clip rect to include safeAreaPadding area,
    // so scroll content renders behind the header.
    ScrollableModelNG::SetContentClip(AceType::RawPtr(scrollNode),
        ContentClipMode::SAFE_AREA, nullptr);

    // Create content container (parent of item column and footer container, goes inside Scroll)
    auto contentContainer = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_VOID(contentContainer);
    auto contentLayoutProperty = contentContainer->GetLayoutProperty<LinearLayoutProperty>();
    if (contentLayoutProperty) {
        contentLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
        contentLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
        contentLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    }

    // Create ColumnNode (vertical container for tab items)
    auto columnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_VOID(columnNode);
    auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    if (columnLayoutProperty) {
        columnLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
        // Column fills parent width so tab items can be left-aligned
        // within the full width. Height remains content-based for scrolling.
        columnLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
        // Children left-aligned (default, explicit for clarity)
        columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    }
    tabListPattern->SetColumnNode(columnNode);

    // Create footer container (sibling of item column inside content container)
    auto footerContainer = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_VOID(footerContainer);
    auto footerLayoutProperty = footerContainer->GetLayoutProperty<LinearLayoutProperty>();
    if (footerLayoutProperty) {
        footerLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
        footerLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
        footerLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    }
    footerContainerNode_ = footerContainer;

    // Assemble: columnNode + footerContainer -> contentContainer -> Scroll
    //           -> SideBarTabListNode -> SideBarNode(host)
    columnNode->MountToParent(contentContainer);
    footerContainer->MountToParent(contentContainer);
    contentContainer->MountToParent(scrollNode);
    scrollNode->MountToParent(tabListNode);
    tabListNode->MountToParent(host);
    tabListNode_ = tabListNode;
    columnNode->MarkModifyDone();
    scrollNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarPattern::UpdateTabListIfNeeded()
{
    // Bind SwiperController (shared with bottom TabBar)
    CHECK_NULL_VOID(tabListNode_);
    auto tabListPattern = tabListNode_->GetPattern<TabsSideBarTabListPattern>();
    CHECK_NULL_VOID(tabListPattern);
    tabListPattern->SetSwiperController(swiperController_);
}

void TabsSideBarPattern::UpdateHeaderNodeIfNeeded()
{
    CHECK_NULL_VOID(headerContainerNode_);
    if (headerNode_ == curHeaderNode_) {
        return;
    }

    // Remove old header
    if (curHeaderNode_) {
        headerContainerNode_->RemoveChild(curHeaderNode_);
        headerContainerNode_->MarkNeedSyncRenderTree();
        curHeaderNode_ = nullptr;
    }

    // Mount new header to index 0
    if (headerNode_) {
        headerNode_->MountToParent(headerContainerNode_, 0);
        curHeaderNode_ = headerNode_;
    }
    headerContainerNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarPattern::UpdateFooterNodeIfNeeded()
{
    CHECK_NULL_VOID(footerContainerNode_);

    if (footerNode_ == curFooterNode_) {
        return;
    }
    // Remove old footer
    if (curFooterNode_) {
        footerContainerNode_->RemoveChild(curFooterNode_);
        footerContainerNode_->MarkNeedSyncRenderTree();
        curFooterNode_ = nullptr;
    }
    // Mount new footer to footer container
    if (footerNode_) {
        footerNode_->MountToParent(footerContainerNode_);
        curFooterNode_ = footerNode_;
    }
    footerContainerNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarPattern::UpdateBottomBarNodeIfNeeded()
{
    CHECK_NULL_VOID(bottomBarContainerNode_);
    if (bottomBarNode_ == curBottomBarNode_) {
        return;
    }
    // Remove old bottomBar
    if (curBottomBarNode_) {
        bottomBarContainerNode_->RemoveChild(curBottomBarNode_);
        bottomBarContainerNode_->MarkNeedSyncRenderTree();
        curBottomBarNode_ = nullptr;
    }
    // Mount new bottomBar
    if (bottomBarNode_) {
        bottomBarNode_->MountToParent(bottomBarContainerNode_);
        curBottomBarNode_ = bottomBarNode_;
    }
    bottomBarContainerNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarPattern::UpdateSearchNodeIfNeeded()
{
    CHECK_NULL_VOID(headerContainerNode_);
    if (!incommingOptions_.has_value()) {
        return;
    }
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto newOptions = incommingOptions_.value();
    incommingOptions_ = std::nullopt;

    if (newOptions.isNull) {
        if (searchContainerNode_) {
            headerContainerNode_->RemoveChild(searchContainerNode_);
            searchContainerNode_ = nullptr;
            headerContainerNode_->MarkNeedSyncRenderTree();
            headerContainerNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        searchableOptions_ = newOptions;
        return;
    }
    bool needRecreateSearchNode = searchableOptions_ != newOptions;
    searchableOptions_ = newOptions;
    if (!needRecreateSearchNode) {
        return;
    }

    std::optional<std::u16string> text;
    if (newOptions.searchText.has_value()) {
        text = UtfUtils::Str8DebugToStr16(newOptions.searchText.value());
    }
    std::optional<std::u16string> placeholder;
    if (newOptions.placeholder.has_value()) {
        placeholder = UtfUtils::Str8DebugToStr16(newOptions.placeholder.value());
    }
    ArkUISearchCreateResourceParams searchResParams;
    searchResParams.stringValueRawPtr = AceType::RawPtr(newOptions.searchTextResObj);
    searchResParams.placeholderRawPtr = AceType::RawPtr(newOptions.placeholderResObj);
    searchResParams.parseValueResult = newOptions.searchTextResObj != nullptr;
    searchResParams.parsePlaceholderResult = newOptions.placeholderResObj != nullptr;
    auto customModifier = NodeModifier::GetSearchCustomModifier();
    CHECK_NULL_VOID(customModifier);
    RefPtr<FrameNode> searchNode = nullptr;
    {
        std::optional<std::string> icon;
        ScopedViewStackProcessor scopedViewStackProcessor;
        customModifier->createNormalSearch(text, placeholder, icon, &searchResParams);
        searchNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        CHECK_NULL_VOID(searchNode);
    }
    customModifier->setOnChangeEvent(AceType::RawPtr(searchNode),
        [weakPattern = WeakClaim(this)](const std::u16string& newStr) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnSearchChange(newStr);
        });
    // Remove old search container before creating new one
    if (searchContainerNode_) {
        headerContainerNode_->RemoveChild(searchContainerNode_);
        searchContainerNode_ = nullptr;
        headerContainerNode_->MarkNeedSyncRenderTree();
    }
    auto searchContainerNode = CreateSearchContainer();
    CHECK_NULL_VOID(searchContainerNode);
    searchNode->MountToParent(searchContainerNode);
    searchContainerNode->MountToParent(headerContainerNode_);
    searchContainerNode_ = searchContainerNode;
    headerContainerNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarPattern::OnSearchChange(const std::u16string& newText)
{
    CHECK_NULL_VOID(searchContainerNode_);
    if (searchableOptions_.isNull) {
        return;
    }
    auto text = UtfUtils::Str16ToStr8(newText);
    auto onChangeCallback = searchableOptions_.searchCallback;
    auto searchFilter = searchableOptions_.searchFilter;
    if (onChangeCallback) {
        onChangeCallback(text);
    }
    CHECK_NULL_VOID(tabListNode_);
    auto tabListPattern = tabListNode_->GetPattern<TabsSideBarTabListPattern>();
    CHECK_NULL_VOID(tabListPattern);
    tabListPattern->ApplySearchFilter(searchFilter, newText);
}

void TabsSideBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();

    UpdateTabListIfNeeded();
    UpdateHeaderNodeIfNeeded();
    UpdateFooterNodeIfNeeded();
    UpdateSearchNodeIfNeeded();
    UpdateBottomBarNodeIfNeeded();
    bool isHeaderContainerVisible;
    bool isScrollEffectEnabled;
    if (!curHeaderNode_ && !searchContainerNode_) {
        isScrollEffectEnabled = false;
        isHeaderContainerVisible = false;
    } else {
        isScrollEffectEnabled = true;
        isHeaderContainerVisible = true;
    }
    if (headerContainerNode_) {
        auto headerContainerProperty = headerContainerNode_->GetLayoutProperty();
        if (headerContainerProperty) {
            headerContainerProperty->UpdateVisibility(
                isHeaderContainerVisible ? VisibleType::VISIBLE : VisibleType::GONE);
        }
    }
    if (bottomBarContainerNode_) {
        auto bottomBarProperty = bottomBarContainerNode_->GetLayoutProperty();
        if (bottomBarProperty) {
            bool isBottomBarVisible = curBottomBarNode_ != nullptr;
            bottomBarProperty->UpdateVisibility(
                isBottomBarVisible ? VisibleType::VISIBLE : VisibleType::GONE);
        }
    }
    InitHeaderContainerScrollEffect(isScrollEffectEnabled);

    bool isBottomBarScrollEffect = curBottomBarNode_ != nullptr;
    InitBottomBarScrollEffect(isBottomBarScrollEffect);
}

RefPtr<FrameNode> TabsSideBarPattern::CreateEffectNode(const std::string& tag)
{
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    // Effect nodes don't participate in hit test
    CHECK_NULL_RETURN(node, nullptr);
    auto gestureHub = node->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    gestureHub->SetHitTestMode(HitTestMode::HTMNONE);
    return node;
}

void TabsSideBarPattern::OnTabListScroll(float totalOffset, float scrollableDistance)
{
    auto threshold = static_cast<float>(GRADUAL_BLUR_SCROLL_THRESHOLD.ConvertToPx());
    float scrollScale = (threshold > 0.0f) ? std::clamp(totalOffset / threshold, 0.0f, 1.0f) : 0.0f;
    UpdateHeaderContainerBlurStyle(scrollScale);

    float exceed = scrollableDistance - totalOffset;
    float bottomScrollScale = (threshold > 0.0f && exceed > 0.0f)
        ? std::clamp(exceed / threshold, 0.0f, 1.0f)
        : 0.0f;
    UpdateBottomBarBlurStyle(bottomScrollScale);
}

void TabsSideBarPattern::InitHeaderContainerScrollEffect(bool isScrollEffectEnabled)
{
    InitScrollEffectImpl(isScrollEffectEnabled, isScrollEffectEnabled_, scrollScale_,
        headerContainerMaskBlurNode_, headerContainerMaskNode_, GradientDirection::BOTTOM);
}

void TabsSideBarPattern::InitBottomBarScrollEffect(bool isScrollEffectEnabled)
{
    InitScrollEffectImpl(isScrollEffectEnabled, isBottomBarScrollEffectEnabled_, bottomBarScrollScale_,
        bottomBarMaskBlurNode_, bottomBarMaskNode_, GradientDirection::TOP);
}

void TabsSideBarPattern::InitScrollEffectImpl(bool isScrollEffectEnabled, bool& isEnabledFlag,
    float& cachedScale, const RefPtr<FrameNode>& maskBlurNode, const RefPtr<FrameNode>& maskNode,
    GradientDirection direction)
{
    if (isScrollEffectEnabled == isEnabledFlag) {
        return;
    }
    isEnabledFlag = isScrollEffectEnabled;
    do {
        CHECK_NULL_BREAK(maskBlurNode);
        auto property = maskBlurNode->GetLayoutProperty();
        CHECK_NULL_BREAK(property);
        property->UpdateVisibility(isEnabledFlag ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
    } while (false);
    do {
        CHECK_NULL_BREAK(maskNode);
        auto property = maskNode->GetLayoutProperty();
        CHECK_NULL_BREAK(property);
        property->UpdateVisibility(isEnabledFlag ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
    } while (false);
    if (!isEnabledFlag) {
        return;
    }
    auto scale = std::clamp(cachedScale, 0.0f, 1.0f);
    UpdateBlurStyleImpl(scale, cachedScale, isEnabledFlag, maskBlurNode, maskNode, direction);
}

void TabsSideBarPattern::UpdateHeaderContainerBlurStyle(float scrollScale)
{
    UpdateBlurStyleImpl(scrollScale, scrollScale_, isScrollEffectEnabled_,
        headerContainerMaskBlurNode_, headerContainerMaskNode_, GradientDirection::BOTTOM);
}

void TabsSideBarPattern::UpdateBottomBarBlurStyle(float scrollScale)
{
    UpdateBlurStyleImpl(scrollScale, bottomBarScrollScale_, isBottomBarScrollEffectEnabled_,
        bottomBarMaskBlurNode_, bottomBarMaskNode_, GradientDirection::TOP);
}

void TabsSideBarPattern::UpdateBlurStyleImpl(float scrollScale, float& cachedScale, bool isEnabled,
    const RefPtr<FrameNode>& maskBlurNode, const RefPtr<FrameNode>& maskNode,
    GradientDirection direction)
{
    if (NearEqual(cachedScale, scrollScale)) {
        return;
    }
    cachedScale = scrollScale;
    if (!isEnabled) {
        return;
    }
    CHECK_NULL_VOID(maskBlurNode && maskNode);
    auto maskBlurRenderContext = maskBlurNode->GetRenderContext();
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskBlurRenderContext && maskRenderContext);

    float blurRadius = scrollScale * static_cast<float>(GRADUAL_BLUR_MAX_RADIUS.ConvertToPx());
    maskBlurRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    if (NearZero(blurRadius)) {
        maskBlurRenderContext->UpdateBackBlurRadius(Dimension(0.0, DimensionUnit::VP));
        maskBlurRenderContext->ResetRadiusGradientBlur();
    } else {
        maskBlurRenderContext->UpdateBackBlurRadius(Dimension());
        LinearGradientBlurPara gradientBlurPara(
            Dimension(blurRadius, DimensionUnit::PX), MASK_BLUR_STOPS, direction);
        maskBlurRenderContext->UpdateRadiusGradientBlur(gradientBlurPara);
    }

    maskRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    double opacity = scrollScale * GRADUAL_BLUR_MAX_OPACITY;
    if (NearZero(opacity)) {
        Gradient emptyGradient;
        emptyGradient.CreateGradientWithType(GradientType::LINEAR);
        maskRenderContext->UpdateLinearGradient(emptyGradient);
    } else {
        Color blendColor = Color::FromARGB(
            static_cast<uint8_t>(opacity * 255), 0xF1, 0xF3, 0xF5);
        Gradient gradient;
        gradient.CreateGradientWithType(GradientType::LINEAR);
        gradient.SetDirection(direction);
        for (const auto& fractionStop : FADE_OUT_GRADIENT_STOPS) {
            GradientColor stepColor(blendColor.BlendOpacity(fractionStop.first));
            stepColor.SetDimension(fractionStop.second * 100.0f, DimensionUnit::PERCENT);
            gradient.AddColor(stepColor);
        }
        maskRenderContext->UpdateLinearGradient(gradient);
    }
}
} // namespace OHOS::Ace::NG
