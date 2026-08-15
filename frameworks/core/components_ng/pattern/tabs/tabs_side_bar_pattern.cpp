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
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
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
        pattern->OnTabListScroll(totalOffset);
    };
    controller->SetObserver(observer);
    // Hide scrollbar for sidebar tab list
    ScrollableModelNG::SetScrollBarMode(AceType::RawPtr(scrollNode), DisplayMode::OFF);
    // clipContent(SAFE_AREA): expand clip rect to include safeAreaPadding area,
    // so scroll content renders behind the header.
    ScrollableModelNG::SetContentClip(AceType::RawPtr(scrollNode),
        ContentClipMode::SAFE_AREA, nullptr);

    // Create ColumnNode (vertical container for tab items)
    auto columnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    CHECK_NULL_VOID(columnNode);
    auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    if (columnLayoutProperty) {
        columnLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
        // Column fills parent (Scroll) width so tab items can be left-aligned
        // within the full width. Height remains content-based for scrolling.
        columnLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
        // Children left-aligned (default, explicit for clarity)
        columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    }
    tabListPattern->SetColumnNode(columnNode);

    // Assemble: Column -> Scroll -> SideBarTabListNode -> SideBarNode(host)
    columnNode->MountToParent(scrollNode);
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
    bool needRecreateSearchNode =
        searchableOptions_.isNull != newOptions.isNull ||
        searchableOptions_.placeholder != newOptions.placeholder;
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
    auto customModifier = NodeModifier::GetSearchCustomModifier();
    CHECK_NULL_VOID(customModifier);
    RefPtr<FrameNode> searchNode = nullptr;
    {
        std::optional<std::string> icon;
        ScopedViewStackProcessor scopedViewStackProcessor;
        customModifier->createNormalSearch(text, placeholder, icon, nullptr);
        searchNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        CHECK_NULL_VOID(searchNode);
    }
    customModifier->setOnChangeEvent(AceType::RawPtr(searchNode),
        [weakPattern = WeakClaim(this)](const std::u16string& newStr) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnSearchChange(newStr);
        });
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
    UpdateSearchNodeIfNeeded();
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
    InitHeaderContainerScrollEffect(isScrollEffectEnabled);
}

RefPtr<FrameNode> TabsSideBarPattern::CreateEffectNode(const std::string& tag)
{
    auto node = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    // Effect nodes don't participate in hit test
    ViewAbstract::SetHitTestMode(AceType::RawPtr(node), HitTestMode::HTMNONE);
    return node;
}

void TabsSideBarPattern::OnTabListScroll(float totalOffset)
{
    auto threshold = static_cast<float>(GRADUAL_BLUR_SCROLL_THRESHOLD.ConvertToPx());
    float scrollScale = (threshold > 0.0f) ? std::clamp(totalOffset / threshold, 0.0f, 1.0f) : 0.0f;
    UpdateHeaderContainerBlurStyle(scrollScale);
}

void TabsSideBarPattern::InitHeaderContainerScrollEffect(bool isScrollEffectEnabled)
{
    if (isScrollEffectEnabled == isScrollEffectEnabled_) {
        return;
    }
    isScrollEffectEnabled_ = isScrollEffectEnabled;
    do {
        CHECK_NULL_BREAK(headerContainerMaskBlurNode_);
        auto property = headerContainerMaskBlurNode_->GetLayoutProperty();
        CHECK_NULL_BREAK(property);
        property->UpdateVisibility(isScrollEffectEnabled_ ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
    } while (false);
    do {
        CHECK_NULL_BREAK(headerContainerMaskNode_);
        auto property = headerContainerMaskNode_->GetLayoutProperty();
        CHECK_NULL_BREAK(property);
        property->UpdateVisibility(isScrollEffectEnabled_ ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
    } while (false);
    if (!isScrollEffectEnabled_) {
        return;
    }
    auto scale = std::clamp(scrollScale_, 0.0f, 1.0f);
    UpdateHeaderContainerBlurStyle(scale);
}

void TabsSideBarPattern::UpdateHeaderContainerBlurStyle(float scrollScale)
{
    if (NearEqual(scrollScale_, scrollScale)) {
        return;
    }
    scrollScale_ = scrollScale;
    if (!isScrollEffectEnabled_) {
        return;
    }
    CHECK_NULL_VOID(headerContainerMaskBlurNode_ && headerContainerMaskNode_);
    auto maskBlurRenderContext = headerContainerMaskBlurNode_->GetRenderContext();
    auto maskRenderContext = headerContainerMaskNode_->GetRenderContext();
    CHECK_NULL_VOID(maskBlurRenderContext && maskRenderContext);
    // Interpolate blur radius: 0 → maxRadius based on scrollScale
    float blurRadius = scrollScale * static_cast<float>(GRADUAL_BLUR_MAX_RADIUS.ConvertToPx());
    // MaskBlur node: apply radius gradient blur with vertical gradient mask
    maskBlurRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    if (NearZero(blurRadius)) {
        maskBlurRenderContext->UpdateBackBlurRadius(Dimension(0.0, DimensionUnit::VP));
        maskBlurRenderContext->ResetRadiusGradientBlur();
    } else {
        maskBlurRenderContext->UpdateBackBlurRadius(Dimension());
        LinearGradientBlurPara gradientBlurPara(
            Dimension(blurRadius, DimensionUnit::PX), MASK_BLUR_STOPS, GradientDirection::BOTTOM);
        maskBlurRenderContext->UpdateRadiusGradientBlur(gradientBlurPara);
    }

    // Mask node: apply fade-out gradient with interpolated opacity
    maskRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    double opacity = scrollScale * GRADUAL_BLUR_MAX_OPACITY;
    if (NearZero(opacity)) {
        // No gradient at scroll position 0 — fully transparent
        Gradient emptyGradient;
        emptyGradient.CreateGradientWithType(GradientType::LINEAR);
        maskRenderContext->UpdateLinearGradient(emptyGradient);
    } else {
        // Use sidebar background color with interpolated opacity for the gradient
        Color blendColor = Color::FromARGB(
            static_cast<uint8_t>(opacity * 255), 0xF1, 0xF3, 0xF5);
        Gradient gradient;
        gradient.CreateGradientWithType(GradientType::LINEAR);
        gradient.SetDirection(GradientDirection::BOTTOM);
        for (const auto& fractionStop : FADE_OUT_GRADIENT_STOPS) {
            GradientColor stepColor(blendColor.BlendOpacity(fractionStop.first));
            stepColor.SetDimension(fractionStop.second * 100.0f, DimensionUnit::PERCENT);
            gradient.AddColor(stepColor);
        }
        maskRenderContext->UpdateLinearGradient(gradient);
    }
}
} // namespace OHOS::Ace::NG
