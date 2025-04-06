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

#include "core/components_ng/pattern/bubble/bubble_layout_algorithm.h"

#include <algorithm>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/device_config.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HALF = 2.0;
constexpr double DOUBLE = 2.0;
constexpr Dimension ARROW_RADIUS = 2.0_vp;
constexpr Dimension MARGIN_SPACE = 6.0_vp;
constexpr Dimension TIPS_MARGIN_SPACE = 8.0_vp;
constexpr Dimension DRAW_EDGES_SPACE = 1.0_vp;
constexpr double BUBBLE_ARROW_HALF = 2.0;
constexpr size_t ALIGNMENT_STEP_OFFSET = 1;
constexpr Dimension KEYBOARD_SPACE = 8.0_vp;

// help value to calculate p2 p4 position
constexpr Dimension DEFAULT_BUBBLE_ARROW_WIDTH = 16.0_vp;
constexpr Dimension DEFAULT_BUBBLE_ARROW_HEIGHT = 8.0_vp;
Dimension DEFAULT_P2_HEIGHT = 7.32_vp;
Dimension DEFAULT_P2_WIDTH = 1.5_vp;
Dimension DEFAULT_P4_END_Y = 6.0_vp;
Dimension DEFAULT_P2_END_X = 12.8_vp;
Dimension DEFAULT_P2_END_Y = 7.6_vp;

Dimension BUBBLE_ARROW_WIDTH = 16.0_vp;
Dimension BUBBLE_ARROW_HEIGHT = 8.0_vp;
constexpr double ARROW_OFFSET_START_VALUE = 0.0;
constexpr double ARROW_OFFSET_CENTER_VALUE = 0.5;
constexpr Dimension HORIZON_SPACING_WITH_SCREEN = 8.0_vp;
constexpr Dimension BEZIER_WIDTH_HALF = 8.0_vp;

Dimension ARROW_VERTICAL_P1_OFFSET_X = 8.0_vp;
Dimension ARROW_VERTICAL_P2_OFFSET_X = 1.5_vp;
Dimension ARROW_VERTICAL_P2_OFFSET_Y = 7.32_vp;
Dimension ARROW_VERTICAL_P4_OFFSET_X = 1.5_vp;
Dimension ARROW_VERTICAL_P4_OFFSET_Y = 7.32_vp;
Dimension ARROW_VERTICAL_P5_OFFSET_X = 8.0_vp;

Dimension ARROW_HORIZON_P1_OFFSET_Y = 8.0_vp;
Dimension ARROW_HORIZON_P2_OFFSET_Y = 1.5_vp;
Dimension ARROW_HORIZON_P2_OFFSET_X = 7.32_vp;
Dimension ARROW_HORIZON_P4_OFFSET_Y = 1.5_vp;
Dimension ARROW_HORIZON_P4_OFFSET_X = 7.32_vp;
Dimension ARROW_HORIZON_P5_OFFSET_Y = 8.0_vp;

Dimension ARROW_REPLACE_START_VERTICAL_P1_OFFSET_X = 8.0_vp;
Dimension ARROW_REPLACE_START_VERTICAL_P2_OFFSET_X = 8.0_vp;
Dimension ARROW_REPLACE_START_VERTICAL_P2_OFFSET_Y = 6.0_vp;
Dimension ARROW_REPLACE_START_VERTICAL_P4_OFFSET_X = 4.8_vp;
Dimension ARROW_REPLACE_START_VERTICAL_P4_OFFSET_Y = 7.6_vp;
Dimension ARROW_REPLACE_START_VERTICAL_P5_OFFSET_X = 8.0_vp;

Dimension ARROW_REPLACE_END_VERTICAL_P1_OFFSET_X = 8.0_vp;
Dimension ARROW_REPLACE_END_VERTICAL_P2_OFFSET_X = 4.8_vp;
Dimension ARROW_REPLACE_END_VERTICAL_P2_OFFSET_Y = 7.6_vp;
Dimension ARROW_REPLACE_END_VERTICAL_P4_OFFSET_X = 8.0_vp;
Dimension ARROW_REPLACE_END_VERTICAL_P4_OFFSET_Y = 6.0_vp;
Dimension ARROW_REPLACE_END_VERTICAL_P5_OFFSET_X = 8.0_vp;

Dimension ARROW_REPLACE_START_HORIZON_P1_OFFSET_Y = 8.0_vp;
Dimension ARROW_REPLACE_START_HORIZON_P2_OFFSET_X = 6.0_vp;
Dimension ARROW_REPLACE_START_HORIZON_P2_OFFSET_Y = 8.0_vp;
Dimension ARROW_REPLACE_START_HORIZON_P4_OFFSET_X = 7.6_vp;
Dimension ARROW_REPLACE_START_HORIZON_P4_OFFSET_Y = 4.8_vp;
Dimension ARROW_REPLACE_START_HORIZON_P5_OFFSET_Y = 8.0_vp;

Dimension ARROW_REPLACE_END_HORIZON_P1_OFFSET_Y = 8.0_vp;
Dimension ARROW_REPLACE_END_HORIZON_P2_OFFSET_X = 7.6_vp;
Dimension ARROW_REPLACE_END_HORIZON_P2_OFFSET_Y = 4.8_vp;
Dimension ARROW_REPLACE_END_HORIZON_P4_OFFSET_X = 6.0_vp;
Dimension ARROW_REPLACE_END_HORIZON_P4_OFFSET_Y = 8.0_vp;
Dimension ARROW_REPLACE_END_HORIZON_P5_OFFSET_Y = 8.0_vp;

constexpr Dimension BUBBLE_ARROW_ZERO_PERCENT_VALUE = 0.0_pct;
constexpr Dimension BUBBLE_ARROW_HALF_PERCENT_VALUE = 0.5_pct;
constexpr Dimension BUBBLE_ARROW_ONE_HUNDRED_PERCENT_VALUE = 1.0_pct;
constexpr Dimension OUT_RANGE_SPACE = 40.0_vp;

constexpr int16_t ARROW_OFFSETS_INDEX_ZERO = 0;
constexpr int16_t ARROW_OFFSETS_INDEX_ONE = 1;
constexpr int16_t ARROW_OFFSETS_INDEX_TWO = 2;
constexpr int16_t ARROW_OFFSETS_INDEX_THREE = 3;

void GetEndP2P4(const Dimension& radius)
{
    auto h1 = BUBBLE_ARROW_HEIGHT.ConvertToPx() - radius.ConvertToPx();
    auto w1 = BUBBLE_ARROW_WIDTH.ConvertToPx() - radius.ConvertToPx();
    CHECK_EQUAL_VOID(w1, 0);
    auto theta = std::atan(h1 / w1);
    auto side = w1 /std::cos(theta);
    auto alpha = std::asin(radius.ConvertToPx() / side);
    auto beta = theta + alpha;
    DEFAULT_P4_END_Y = Dimension(h1);
    auto side1 = side * std::cos(alpha);
    DEFAULT_P2_END_X = Dimension(side1 * std::cos(beta));
    DEFAULT_P2_END_Y = Dimension(side1 * std::sin(beta));
}

void GetP2(const Dimension& radius)
{
    auto h1 = BUBBLE_ARROW_HEIGHT.ConvertToPx() - radius.ConvertToPx();
    auto w1 = BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    CHECK_EQUAL_VOID(w1, 0);
    auto theta = std::atan(h1 / w1);
    auto side = w1 /std::cos(theta);
    auto alpha = std::asin(radius.ConvertToPx() / side);
    auto side1 = radius.ConvertToPx() / std::tan(alpha);
    auto beta = alpha + theta;
    DEFAULT_P2_HEIGHT = Dimension(side1 * std::sin(beta));
    DEFAULT_P2_WIDTH = Dimension(w1 - side1 * std::cos(beta));
}

void calculateArrowPoint(Dimension height, Dimension width)
{
    auto rateX = width.ConvertToPx() / BUBBLE_ARROW_WIDTH.ConvertToPx();
    BUBBLE_ARROW_WIDTH = width;
    BUBBLE_ARROW_HEIGHT = height;

    GetEndP2P4(ARROW_RADIUS);
    GetP2(ARROW_RADIUS);

    ARROW_VERTICAL_P1_OFFSET_X = ARROW_VERTICAL_P1_OFFSET_X * rateX;
    ARROW_VERTICAL_P2_OFFSET_Y = DEFAULT_P2_HEIGHT;
    ARROW_VERTICAL_P2_OFFSET_X = DEFAULT_P2_WIDTH;
    ARROW_VERTICAL_P4_OFFSET_Y = DEFAULT_P2_HEIGHT;
    ARROW_VERTICAL_P4_OFFSET_X = DEFAULT_P2_WIDTH;
    ARROW_VERTICAL_P5_OFFSET_X = ARROW_VERTICAL_P5_OFFSET_X * rateX;

    ARROW_HORIZON_P1_OFFSET_Y = ARROW_HORIZON_P1_OFFSET_Y * rateX;
    ARROW_HORIZON_P2_OFFSET_X = DEFAULT_P2_HEIGHT;
    ARROW_HORIZON_P2_OFFSET_Y = DEFAULT_P2_WIDTH;
    ARROW_HORIZON_P4_OFFSET_X = DEFAULT_P2_HEIGHT;
    ARROW_HORIZON_P4_OFFSET_Y = DEFAULT_P2_WIDTH;
    ARROW_HORIZON_P5_OFFSET_Y = ARROW_HORIZON_P5_OFFSET_Y * rateX;

    auto p1x = BUBBLE_ARROW_WIDTH / HALF;
    auto p2x = Dimension(DEFAULT_P2_END_X.ConvertToPx() - p1x.ConvertToPx());
    auto p2y = DEFAULT_P2_END_Y;
    auto p4y = DEFAULT_P4_END_Y;

    ARROW_REPLACE_START_VERTICAL_P1_OFFSET_X = p1x;
    ARROW_REPLACE_START_VERTICAL_P2_OFFSET_X = p1x;
    ARROW_REPLACE_START_VERTICAL_P2_OFFSET_Y = p4y;
    ARROW_REPLACE_START_VERTICAL_P4_OFFSET_X = p2x;
    ARROW_REPLACE_START_VERTICAL_P4_OFFSET_Y = p2y;
    ARROW_REPLACE_START_VERTICAL_P5_OFFSET_X = p1x;

    ARROW_REPLACE_END_VERTICAL_P1_OFFSET_X = p1x;
    ARROW_REPLACE_END_VERTICAL_P2_OFFSET_X = p2x;
    ARROW_REPLACE_END_VERTICAL_P2_OFFSET_Y = p2y;
    ARROW_REPLACE_END_VERTICAL_P4_OFFSET_X = p1x;
    ARROW_REPLACE_END_VERTICAL_P4_OFFSET_Y = p4y;
    ARROW_REPLACE_END_VERTICAL_P5_OFFSET_X = p1x;

    ARROW_REPLACE_START_HORIZON_P1_OFFSET_Y = p1x;
    ARROW_REPLACE_START_HORIZON_P2_OFFSET_X = p4y;
    ARROW_REPLACE_START_HORIZON_P2_OFFSET_Y = p1x;
    ARROW_REPLACE_START_HORIZON_P4_OFFSET_X = p2y;
    ARROW_REPLACE_START_HORIZON_P4_OFFSET_Y = p2x;
    ARROW_REPLACE_START_HORIZON_P5_OFFSET_Y = p1x;

    ARROW_REPLACE_END_HORIZON_P1_OFFSET_Y = p1x;
    ARROW_REPLACE_END_HORIZON_P2_OFFSET_X = p2y;
    ARROW_REPLACE_END_HORIZON_P2_OFFSET_Y = p2x;
    ARROW_REPLACE_END_HORIZON_P4_OFFSET_X = p4y;
    ARROW_REPLACE_END_HORIZON_P4_OFFSET_Y = p1x;
    ARROW_REPLACE_END_HORIZON_P5_OFFSET_Y = p1x;
}

// get main window's pipeline
RefPtr<PipelineContext> GetMainPipelineContext(LayoutWrapper* layoutWrapper)
{
    auto containerId = Container::CurrentId();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, nullptr);
    RefPtr<PipelineContext> context;
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
        CHECK_NULL_RETURN(parentContainer, nullptr);
        context = AceType::DynamicCast<PipelineContext>(parentContainer->GetPipelineContext());
    } else {
        context = host->GetContextRefPtr();
    }
    return context;
}
} // namespace

BubbleLayoutAlgorithm::BubbleLayoutAlgorithm(int32_t id, const std::string& tag,
    const std::optional<OffsetF>& targetOffset, const std::optional<SizeF>& targetSize)
    : targetNodeId_(id), targetTag_(tag)
{
    if (targetOffset.has_value()) {
        targetOffset_ = targetOffset.value();
    }
    if (targetSize.has_value()) {
        targetSize_ = targetSize.value();
    }
    placementFuncMap_[Placement::TOP] = &BubbleLayoutAlgorithm::GetPositionWithPlacementTop;
    placementFuncMap_[Placement::TOP_LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementTopLeft;
    placementFuncMap_[Placement::TOP_RIGHT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementTopRight;
    placementFuncMap_[Placement::BOTTOM] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottom;
    placementFuncMap_[Placement::BOTTOM_LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottomLeft;
    placementFuncMap_[Placement::BOTTOM_RIGHT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottomRight;
    placementFuncMap_[Placement::LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementLeft;
    placementFuncMap_[Placement::LEFT_TOP] = &BubbleLayoutAlgorithm::GetPositionWithPlacementLeftTop;
    placementFuncMap_[Placement::LEFT_BOTTOM] = &BubbleLayoutAlgorithm::GetPositionWithPlacementLeftBottom;
    placementFuncMap_[Placement::RIGHT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementRight;
    placementFuncMap_[Placement::RIGHT_TOP] = &BubbleLayoutAlgorithm::GetPositionWithPlacementRightTop;
    placementFuncMap_[Placement::RIGHT_BOTTOM] = &BubbleLayoutAlgorithm::GetPositionWithPlacementRightBottom;

    setHorizontal_ = { Placement::LEFT, Placement::LEFT_BOTTOM, Placement::LEFT_TOP, Placement::RIGHT,
        Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP };
    setVertical_ = { Placement::TOP, Placement::TOP_LEFT, Placement::TOP_RIGHT, Placement::BOTTOM,
        Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT };
}

void BubbleLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto bubbleProp = DynamicCast<BubbleLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(bubbleProp);
    auto bubbleLayoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(bubbleLayoutProperty);
    bool showInSubWindow = bubbleLayoutProperty->GetShowInSubWindowValue(false);
    useCustom_ = bubbleLayoutProperty->GetUseCustom().value_or(false);
    isTips_ = bubbleLayoutProperty->GetIsTips().value_or(false);
    InitProps(bubbleProp, showInSubWindow, layoutWrapper);
    auto bubbleNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(bubbleNode);
    const auto& layoutConstraint = bubbleLayoutProperty->GetLayoutConstraint();
    if (!layoutConstraint) {
        LOGE("fail to measure bubble due to layoutConstraint is nullptr");
        return;
    }
    // bubble size fit screen.
    layoutWrapper->GetGeometryNode()->SetFrameSize(layoutConstraint->maxSize);
    layoutWrapper->GetGeometryNode()->SetContentSize(layoutConstraint->maxSize);
    // update child layout constraint
    LayoutConstraintF childLayoutConstraint = bubbleLayoutProperty->CreateChildConstraint();
    if (avoidKeyboard_) {
        childLayoutConstraint.maxSize.SetHeight(wrapperSize_.Height() - marginTop_ - KEYBOARD_SPACE.ConvertToPx());
        childLayoutConstraint.maxSize.SetWidth(wrapperSize_.Width());
    }
    float minHeight = minHeight_.ConvertToPx();
    if (GreatNotEqual(static_cast<double>(minHeight), 0.0)) {
        childLayoutConstraint.minSize.SetHeight(minHeight);
    }
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto child = children.front();
    CHECK_NULL_VOID(child);
    measureChildSizeBefore_ = child->GetGeometryNode()->GetFrameSize();
    if (isHalfFoldHover_) {
        SizeF size = SizeF(childLayoutConstraint.maxSize.Width(),
            static_cast<float>(std::floor(wrapperRect_.Height())));
        childLayoutConstraint.UpdateMaxSizeWithCheck(size);
    }
    // childSize_ and childOffset_ is used in Layout.
    auto childProp = child->GetLayoutProperty();
    CHECK_NULL_VOID(childProp);
    childProp->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    child->Measure(childLayoutConstraint);
    measureChildSizeAfter_ = child->GetGeometryNode()->GetFrameSize();
    if (!NearEqual(measureChildSizeBefore_, measureChildSizeAfter_)) {
        auto childShowWidth = child->GetGeometryNode()->GetFrameSize().Width() + BUBBLE_ARROW_HEIGHT.ConvertToPx() * 2;
        auto childShowHeight =
            child->GetGeometryNode()->GetFrameSize().Height() + BUBBLE_ARROW_HEIGHT.ConvertToPx() * 2;
        child->GetGeometryNode()->SetFrameSize(SizeF { childShowWidth, childShowHeight });
        measureChildSizeLast_ = child->GetGeometryNode()->GetFrameSize();
    } else {
        measureChildSizeLast_ = child->GetGeometryNode()->GetFrameSize();
    }
    if (useCustom_ && !showInSubWindow) {
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        float rootH = context->GetRootHeight();
        float rootW = context->GetRootWidth();
        auto childHeight = child->GetGeometryNode()->GetMarginFrameSize().Height();
        auto childWidth = child->GetGeometryNode()->GetMarginFrameSize().Width();
        auto scaledBubbleSpacing = scaledBubbleSpacing_ * 2;
        auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
        CHECK_NULL_VOID(targetNode);
        auto geometryNode = targetNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto targetSize = geometryNode->GetFrameSize();
        auto targetOffset = targetNode->GetPaintRectOffset();
        auto constrainHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
        auto constrainWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
        float maxWidth = constrainWidth - targetSecurity_ * DOUBLE;
        auto placement = bubbleLayoutProperty->GetPlacement().value_or(Placement::BOTTOM);
        std::unordered_set<Placement> setHorizontal = { Placement::LEFT, Placement::LEFT_BOTTOM, Placement::LEFT_TOP,
            Placement::RIGHT, Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP };
        std::unordered_set<Placement> setVertical = { Placement::TOP, Placement::TOP_LEFT, Placement::TOP_RIGHT,
            Placement::BOTTOM, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT };
        if (setHorizontal.find(placement) != setHorizontal.end()) {
            if (childWidth + targetOffset.GetX() + targetSize.Width() + scaledBubbleSpacing <= rootW &&
                targetOffset.GetX() - childWidth - scaledBubbleSpacing >= 0) {
                return;
            }
            constrainWidth = rootW - scaledBubbleSpacing;
        }
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            if (setVertical.find(placement) != setVertical.end()) {
                if (childHeight + targetOffset.GetY() + targetSize.Height() + scaledBubbleSpacing <= rootH &&
                    targetOffset.GetY() - childHeight - scaledBubbleSpacing >= 0) {
                    return;
                }
                constrainHeight = std::max(rootH - targetOffset.GetY() - targetSize.Height() - scaledBubbleSpacing,
                    targetOffset.GetY() - scaledBubbleSpacing);
            }
        }
        constrainWidth = std::min(constrainWidth, maxWidth);
        SizeF size = SizeF(constrainWidth, constrainHeight);
        childLayoutConstraint.UpdateMaxSizeWithCheck(size);
        child->Measure(childLayoutConstraint);
    }
}

Dimension GetMaxWith(uint32_t maxColumns)
{
    auto gridColumnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::BUBBLE_TYPE);
    auto parent = gridColumnInfo->GetParent();
    if (parent) {
        parent->BuildColumnWidth();
    }
    auto maxWidth = Dimension(gridColumnInfo->GetMaxWidth());
    if (maxColumns > 0) {
        maxWidth = Dimension(gridColumnInfo->GetWidth(maxColumns));
    }
    return maxWidth;
}

SizeF BubbleLayoutAlgorithm::GetPopupMaxWidthAndHeight(bool showInSubWindow, const RefPtr<FrameNode>& frameNode)
{
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, SizeF());
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();

    CHECK_NULL_RETURN(frameNode, SizeF());
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    auto width = geometryNode->GetMarginFrameSize().Width();

    auto safeAreaInsets = OverlayManager::GetSafeAreaInsets(frameNode);
    // system safeArea(AvoidAreaType.TYPE_SYSTEM) only include status bar, the bottom is 0
    auto bottom = 0.0;
    auto top = safeAreaInsets.top_.Length();
    auto maxHeight = windowGlobalRect.Height();
    if (showInSubWindow) {
        maxHeight = SystemProperties::GetDeviceHeight();
    }
    auto popupMaxWidth = GetMaxWith(maxColumns_).Value();
    if (useCustom_) {
        popupMaxWidth = width;
    }
    auto popupMaxHeight = maxHeight - OUT_RANGE_SPACE.ConvertToPx() - OUT_RANGE_SPACE.ConvertToPx() - bottom - top;
    return SizeF(popupMaxWidth, popupMaxHeight);
}

void BubbleLayoutAlgorithm::SetBubbleRadius()
{
    auto littleSide = childSize_.Height() > childSize_.Width() ? childSize_.Width() : childSize_.Height();
    auto littleSideHalf = littleSide / HALF;
    if (borderRadius_.Unit() == DimensionUnit::PERCENT) {
        auto value = borderRadius_.Value() * littleSideHalf;
        borderRadius_.SetValue(value);
        borderRadius_.SetUnit(DimensionUnit::PX);
        border_.SetBorderRadius(Radius(borderRadius_));
    }
    auto borderRadius = ModifyBorderRadius(border_.BottomLeftRadius().GetY().ConvertToPx(), childSize_.Height() / 2);
    auto borderRadius2 = ModifyBorderRadius(border_.BottomLeftRadius().GetY().ConvertToPx(), childSize_.Width() / 2);
    float radiusPx = borderRadius < borderRadius2 ? borderRadius : borderRadius2;
    borderRadius_.SetValue(radiusPx);
    borderRadius_.SetUnit(DimensionUnit::PX);
    border_.SetBorderRadius(Radius(borderRadius_));
}

void BubbleLayoutAlgorithm::BubbleAvoidanceRule(RefPtr<LayoutWrapper> child, RefPtr<BubbleLayoutProperty> bubbleProp,
    RefPtr<FrameNode> bubbleNode, bool showInSubWindow, LayoutWrapper* layoutWrapper)
{
    enableArrow_ = bubbleProp->GetEnableArrow().value_or(false);
    auto bubblePattern = bubbleNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(bubblePattern);
    auto bubblePaintProperty = bubbleNode->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(bubblePaintProperty);
    bool UseArrowOffset = bubblePaintProperty->GetArrowOffset().has_value();
    if (!bubblePattern->IsExiting()) {
        InitTargetSizeAndPosition(showInSubWindow, layoutWrapper);
        if (isCaretMode_) {
            InitCaretTargetSizeAndPosition();
        }
        // subtract the global offset of the overlay node,
        // because the final node position is set relative to the overlay node.
        auto overlayGlobalOffset = bubbleNode->GetOffsetRelativeToWindow();
        targetOffset_ -= overlayGlobalOffset;
    }
    childSize_ = child->GetGeometryNode()->GetMarginFrameSize(); // bubble's size
    auto childShowWidth = childSize_.Width() - BUBBLE_ARROW_HEIGHT.ConvertToPx() * 2;
    auto childShowHeight = childSize_.Height() - BUBBLE_ARROW_HEIGHT.ConvertToPx() * 2;
    childSize_ = SizeF(childShowWidth, childShowHeight);
    SetBubbleRadius();
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        childOffset_ = GetChildPosition(childSize_, bubbleProp, UseArrowOffset); // bubble's offset
        placement_ = arrowPlacement_;
        UpdateChildPosition(childOffset_);
        if (arrowPlacement_ == Placement::TOP) {
            if (bCaretMode_) {
                arrowPosition_ = OffsetF(targetOffset_.GetX(), targetOffset_.GetY() - scaledBubbleSpacing_);
            }
        }
        if (arrowPlacement_ == Placement::BOTTOM) {
            if (bCaretMode_) {
                arrowPosition_ =
                    OffsetF(targetOffset_.GetX(), targetOffset_.GetY() + targetSize_.Height() + scaledBubbleSpacing_);
            }
        }
    } else {
        UpdateMarginByWidth();
        childOffset_ = GetChildPositionNew(childSize_, bubbleProp); // bubble's offset
        childOffset_ = AddOffset(childOffset_);
        dumpInfo_.finalPlacement = PlacementUtils::ConvertPlacementToString(placement_);
    }
}

void BubbleLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto bubbleProp = DynamicCast<BubbleLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(bubbleProp);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(bubblePattern);
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    selfSize_ = layoutWrapper->GetGeometryNode()->GetFrameSize(); // window's size
    auto childWrapper = children.front();
    CHECK_NULL_VOID(childWrapper);
    bool showInSubWindow = bubbleProp->GetShowInSubWindowValue(false);
    auto layoutChildSize = childWrapper->GetGeometryNode()->GetMarginFrameSize();
    auto childMaxSize = GetPopupMaxWidthAndHeight(showInSubWindow, childWrapper->GetHostNode());
    if (NearEqual(childMaxSize, layoutChildSize) || !NearEqual(measureChildSizeLast_, layoutChildSize)) {
        auto childShowWidth =
            childWrapper->GetGeometryNode()->GetFrameSize().Width() + BUBBLE_ARROW_HEIGHT.ConvertToPx() * 2;
        auto childShowHeight =
            childWrapper->GetGeometryNode()->GetFrameSize().Height() + BUBBLE_ARROW_HEIGHT.ConvertToPx() * 2;
        childWrapper->GetGeometryNode()->SetFrameSize(SizeF { childShowWidth, childShowHeight });
    }
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    if (!targetNode) {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "Popup can not get target node, stop layout");
        return;
    }
    if (bubblePattern->IsExiting()) {
        return;
    }
    BubbleAvoidanceRule(childWrapper, bubbleProp, frameNode, showInSubWindow, layoutWrapper);
    UpdateTouchRegion();
    auto childShowOffset = OffsetF(childOffset_.GetX() - BUBBLE_ARROW_HEIGHT.ConvertToPx(),
        childOffset_.GetY() - BUBBLE_ARROW_HEIGHT.ConvertToPx());
    childWrapper->GetGeometryNode()->SetMarginFrameOffset(childShowOffset);
    childWrapper->Layout();
    auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childLayoutWrapper);
    const auto& columnChild = childLayoutWrapper->GetAllChildrenWithBuild();
    if (columnChild.size() > 1 && !useCustom_) {
        auto buttonRow = columnChild.back();
        buttonRowSize_ = buttonRow->GetGeometryNode()->GetMarginFrameSize();
        buttonRowOffset_ = buttonRow->GetGeometryNode()->GetMarginFrameOffset() + childOffset_;
    }
    targetOffsetForPaint_ = targetOffset_;
    childOffsetForPaint_ = childOffset_;
    arrowPositionForPaint_ = arrowPosition_;
    auto isBlock = bubbleProp->GetBlockEventValue(true);
    dumpInfo_.mask = isBlock;
    UpdateHostWindowRect();
    SetHotAreas(showInSubWindow, isBlock, frameNode, bubblePattern->GetContainerId());
    UpdateClipOffset(frameNode);
}

void BubbleLayoutAlgorithm::UpdateHostWindowRect()
{
    hostWindowRect_ = SubwindowManager::GetInstance()->GetParentWindowRect();
    auto currentId = Container::CurrentId();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer()) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
        container = AceEngine::Get().GetContainer(parentContainerId);
        CHECK_NULL_VOID(container);
    }
    if (container->IsUIExtensionWindow()) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(currentId, SubwindowType::TYPE_POPUP);
        CHECK_NULL_VOID(subwindow);
        hostWindowRect_ = subwindow->GetUIExtensionHostWindowRect();
    }
}

void BubbleLayoutAlgorithm::SetHotAreas(bool showInSubWindow, bool isBlock,
    RefPtr<FrameNode> frameNode, int32_t containerId)
{
    if (showInSubWindow) {
        std::vector<Rect> rects;
        if (!isBlock) {
            auto rect = Rect(childOffsetForPaint_.GetX(), childOffsetForPaint_.GetY(),
                childSize_.Width(), childSize_.Height());
            rects.emplace_back(rect);
        } else {
            auto rect = Rect(childOffsetForPaint_.GetX(), childOffsetForPaint_.GetY(),
                childSize_.Width(), childSize_.Height());
            rects.emplace_back(hostWindowRect_);
            rects.emplace_back(rect);
        }
        auto context = frameNode->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [rects, containerId, frameNodeWK = WeakClaim(RawPtr(frameNode))]() {
                auto frameNode = frameNodeWK.Upgrade();
                CHECK_NULL_VOID(frameNode);
                auto subWindowMgr = SubwindowManager::GetInstance();
                subWindowMgr->SetHotAreas(rects, SubwindowType::TYPE_POPUP, frameNode->GetId(), containerId);
            },
            TaskExecutor::TaskType::UI, "ArkUIPopupSetHotAreas");
    }
}

bool BubbleLayoutAlgorithm::IsUIExtensionWindow()
{
    auto currentId = Container::CurrentId();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_RETURN(container, false);
    }
    if (container->IsUIExtensionWindow()) {
        return true;
    }
    return false;
}

bool BubbleLayoutAlgorithm::GetIfNeedArrow(const RefPtr<BubbleLayoutProperty>& bubbleProp, const SizeF& childSize)
{
    auto enableArrow = bubbleProp->GetEnableArrow().value_or(true);
    if (!enableArrow) {
        return false;
    }
    double arrowWidth = BUBBLE_ARROW_WIDTH.ConvertToPx();
    double twoRadiusPx = borderRadius_.ConvertToPx() * 2.0;
    if (setHorizontal_.find(placement_) != setHorizontal_.end()) {
        if (childSize.Height() >= twoRadiusPx + arrowWidth) {
            return true;
        }
    }
    if (setVertical_.find(placement_) != setVertical_.end()) {
        if (childSize.Width() >= twoRadiusPx + arrowWidth) {
            return true;
        }
    }
    return false;
}

void BubbleLayoutAlgorithm::UpdateDumpInfo()
{
    dumpInfo_.targetSpace = targetSpace_;
    dumpInfo_.originPlacement = PlacementUtils::ConvertPlacementToString(placement_);
    dumpInfo_.userOffset = positionOffset_;
    dumpInfo_.enableArrow = enableArrow_;
    dumpInfo_.top = top_;
    dumpInfo_.bottom = bottom_;
    dumpInfo_.targetNode = targetTag_;
    dumpInfo_.targetID = targetNodeId_;
}

void BubbleLayoutAlgorithm::InitProps(const RefPtr<BubbleLayoutProperty>& layoutProp, bool showInSubWindow,
    LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto popupTheme = pipeline->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    padding_ = isTips_ ? popupTheme->GetTipsPadding() : popupTheme->GetPadding();
    CHECK_NULL_VOID(layoutProp);
    userSetTargetSpace_ = layoutProp->GetTargetSpace().value_or(Dimension(0.0f));
    borderRadius_ = layoutProp->GetRadius().value_or(popupTheme->GetRadius().GetX());
    border_.SetBorderRadius(Radius(borderRadius_));
    targetSpace_ = layoutProp->GetTargetSpace().value_or(popupTheme->GetTargetSpace());
    placement_ = layoutProp->GetPlacement().value_or(Placement::BOTTOM);
    isCaretMode_ = layoutProp->GetIsCaretMode().value_or(true);
    auto height = layoutProp->GetArrowHeight().value_or(DEFAULT_BUBBLE_ARROW_HEIGHT);
    auto width = layoutProp->GetArrowWidth().value_or(DEFAULT_BUBBLE_ARROW_WIDTH);
    calculateArrowPoint(height, width);
    arrowHeight_ = height.ConvertToPx();
    scaledBubbleSpacing_ = arrowHeight_;
    realArrowWidth_ = BUBBLE_ARROW_WIDTH.ConvertToPx();
    realArrowHeight_ = BUBBLE_ARROW_HEIGHT.ConvertToPx();
    positionOffset_ = layoutProp->GetPositionOffset().value_or(OffsetF());
    auto constraint = layoutProp->GetLayoutConstraint();
    enableArrow_ = layoutProp->GetEnableArrow().value_or(true);
    followTransformOfTarget_ = layoutProp->GetFollowTransformOfTarget().value_or(false);
    auto wrapperIdealSize =
        CreateIdealSize(constraint.value(), Axis::FREE, layoutProp->GetMeasureType(MeasureType::MATCH_PARENT), true);
    wrapperSize_ = wrapperIdealSize;
    targetSecurity_ = HORIZON_SPACING_WITH_SCREEN.ConvertToPx();
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    CHECK_NULL_VOID(layoutWrapper);
    auto safeAreaInsets = OverlayManager::GetSafeAreaInsets(layoutWrapper->GetHostNode());
    top_ = safeAreaInsets.top_.Length();
    bottom_ = safeAreaInsets.bottom_.Length();
    UpdateDumpInfo();
    marginStart_ = (isTips_ ? TIPS_MARGIN_SPACE : MARGIN_SPACE + DRAW_EDGES_SPACE).ConvertToPx();
    marginEnd_ = (isTips_ ? TIPS_MARGIN_SPACE : MARGIN_SPACE + DRAW_EDGES_SPACE).ConvertToPx();
    marginTop_ = top_ + DRAW_EDGES_SPACE.ConvertToPx();
    marginBottom_ = bottom_ + DRAW_EDGES_SPACE.ConvertToPx();
    HandleKeyboard(layoutWrapper, showInSubWindow);
    showArrow_ = false;
    minHeight_ = popupTheme->GetMinHeight();
    maxColumns_ = popupTheme->GetMaxColumns();
    isHalfFoldHover_ = pipelineContext->IsHalfFoldHoverStatus();
    InitWrapperRect(layoutWrapper);
    if (!useCustom_) {
        UpdateScrollHeight(layoutWrapper, showInSubWindow);
    }
}

void BubbleLayoutAlgorithm::HandleKeyboard(LayoutWrapper* layoutWrapper, bool showInSubWindow)
{
    auto bubbleNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(bubbleNode);
    auto bubblePattern = bubbleNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(bubblePattern);
    avoidKeyboard_ = bubblePattern->GetAvoidKeyboard();
    if (!avoidKeyboard_) {
        return;
    }
    if (IsUIExtensionWindow()) {
        HandleUIExtensionKeyboard(layoutWrapper, showInSubWindow);
        return;
    }
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto keyboardHeight = safeAreaManager->GetKeyboardInset().Length();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (GreatNotEqual(keyboardHeight, 0)) {
        auto wrapperHeight =  container->IsSceneBoardEnabled() ? wrapperSize_.Height() - keyboardHeight :
            wrapperSize_.Height() - keyboardHeight - marginBottom_;
        wrapperSize_.SetHeight(wrapperHeight);
        marginBottom_ = KEYBOARD_SPACE.ConvertToPx();
    } else if (showInSubWindow) {
        auto currentContext = bubbleNode->GetContextRefPtr();
        CHECK_NULL_VOID(currentContext);
        auto currentSafeAreaManager = currentContext->GetSafeAreaManager();
        CHECK_NULL_VOID(currentSafeAreaManager);
        auto currentKeyboardHeight = currentSafeAreaManager->GetKeyboardInset().Length();
        if (GreatNotEqual(currentKeyboardHeight, 0)) {
            auto wrapperHeight =  container->IsSceneBoardEnabled() ? wrapperSize_.Height() - currentKeyboardHeight :
                wrapperSize_.Height() - currentKeyboardHeight - marginBottom_;
            wrapperSize_.SetHeight(wrapperHeight);
            marginBottom_ = KEYBOARD_SPACE.ConvertToPx();
        }
    }
}

void BubbleLayoutAlgorithm::HandleUIExtensionKeyboard(LayoutWrapper* layoutWrapper, bool showInSubWindow)
{
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto keyboardInset = safeAreaManager->GetKeyboardInset();
    auto keyboardHeight = keyboardInset.Length();
    auto wrapperRect = pipelineContext->GetDisplayWindowRectInfo();
    if (showInSubWindow) {
        if (GreatNotEqual(keyboardHeight, 0)) {
            keyboardHeight = wrapperSize_.Height() - wrapperRect.Top() - wrapperRect.Height() + keyboardHeight;
            wrapperSize_.SetHeight(wrapperSize_.Height() - keyboardHeight);
            marginBottom_ = KEYBOARD_SPACE.ConvertToPx();
        } else {
            auto bubbleNode = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(bubbleNode);
            auto currentContext = bubbleNode->GetContextRefPtr();
            CHECK_NULL_VOID(currentContext);
            auto currentSafeAreaManager = currentContext->GetSafeAreaManager();
            CHECK_NULL_VOID(currentSafeAreaManager);
            auto currentKeyboardHeight = currentSafeAreaManager->GetKeyboardInset().Length();
            if (GreatNotEqual(currentKeyboardHeight, 0)) {
                marginBottom_ = KEYBOARD_SPACE.ConvertToPx();
                wrapperSize_.SetHeight(wrapperSize_.Height() - currentKeyboardHeight);
            }
        }
    } else {
        auto topInset = safeAreaManager->GetSafeAreaWithoutProcess().top_;
        auto bottomInset = safeAreaManager->GetSafeAreaWithoutProcess().bottom_;
        marginTop_ = DRAW_EDGES_SPACE.ConvertToPx();
        if (topInset.Length() > 0 && LessNotEqual(wrapperRect.Top(), topInset.end)) {
            marginTop_ = topInset.end - wrapperRect.Top() + marginTop_;
        }
        marginBottom_ = DRAW_EDGES_SPACE.ConvertToPx();
        if (keyboardHeight > 0) {
            marginBottom_ = KEYBOARD_SPACE.ConvertToPx();
            wrapperSize_.SetHeight(wrapperSize_.Height() - keyboardHeight);
        } else if (bottomInset.Length() > 0 && GreatNotEqual(wrapperRect.Top() + wrapperRect.Height(),
            bottomInset.start)) {
            marginBottom_ = wrapperRect.Top() + wrapperRect.Height() - bottomInset.start + marginBottom_;
        }
    }
}

void BubbleLayoutAlgorithm::InitWrapperRect(LayoutWrapper* layoutWrapper)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto displayInfo = container->GetDisplayInfo();
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
    if (!foldCreaseRects.empty()) {
        auto foldCrease = foldCreaseRects.front();
        foldCreaseTop_ = foldCrease.Top();
        foldCreaseBottom_ = foldCrease.Bottom();
    }
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_VOID(targetNode);
    auto targetOffset = targetNode->GetPaintRectOffset();
    float getY = 0;
    getY = targetOffset.GetY();
    auto bubbleNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(bubbleNode);
    auto bubblePattern = bubbleNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(bubblePattern);
    auto enableHoverMode = bubblePattern->GetEnableHoverMode();
    if (!enableHoverMode) {
        isHalfFoldHover_ = false;
    }
    if (isHalfFoldHover_ && enableHoverMode) {
        if (getY < foldCreaseTop_) {
            wrapperRect_.SetRect(marginStart_, marginTop_,
                wrapperSize_.Width() - marginEnd_ - marginStart_, foldCreaseTop_ - marginTop_);
        } else if (getY > foldCreaseBottom_) {
            wrapperRect_.SetRect(marginStart_, foldCreaseBottom_,
                wrapperSize_.Width() - marginEnd_ - marginStart_,
                    wrapperSize_.Height() - foldCreaseBottom_ - marginBottom_);
        } else {
            isHalfFoldHover_ = false;
        }
    }
}

void BubbleLayoutAlgorithm::UpdateScrollHeight(LayoutWrapper* layoutWrapper, bool showInSubWindow)
{
    auto bubbleNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(bubbleNode);
    auto bubblePattern = bubbleNode->GetPattern<BubblePattern>();
    CHECK_NULL_VOID(bubblePattern);
    auto enableHoverMode = bubblePattern->GetEnableHoverMode();
    if (!enableHoverMode) {
        return;
    }

    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto childWrapper = children.front();
    CHECK_NULL_VOID(childWrapper);
    auto childMaxSize = GetPopupMaxWidthAndHeight(showInSubWindow, childWrapper->GetHostNode());

    auto columnNode = AceType::DynamicCast<FrameNode>(bubbleNode->GetLastChild());
    CHECK_NULL_VOID(columnNode);
    auto lastColumnNode = AceType::DynamicCast<FrameNode>(columnNode->GetLastChild());
    CHECK_NULL_VOID(lastColumnNode);
    auto buttonRowNode = AceType::DynamicCast<FrameNode>(lastColumnNode->GetLastChild());
    CHECK_NULL_VOID(buttonRowNode);

    if (buttonRowNode->GetChildren().empty()) {
        return;
    }
    const auto& lastChildren = lastColumnNode->GetChildren();
    buttonRowSize_ = buttonRowNode->GetGeometryNode()->GetFrameSize();
    
    for (const auto& uinode : lastChildren) {
        if (uinode->GetTag() == V2::SCROLL_ETS_TAG) {
            auto scrollNode = AceType::DynamicCast<FrameNode>(uinode);
            CHECK_NULL_VOID(scrollNode);
            
            auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
            CHECK_NULL_VOID(scrollProps);
            if (isHalfFoldHover_) {
                scrollProps->UpdateCalcMaxSize(CalcSize(
                    std::nullopt,
                    CalcLength(Dimension(wrapperRect_.Height() - buttonRowSize_.Height()))));
            } else {
                scrollProps->UpdateCalcMaxSize(CalcSize(
                    std::nullopt,
                    CalcLength(Dimension(childMaxSize.Height() - buttonRowSize_.Height()))));
            }
            scrollNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

OffsetF BubbleLayoutAlgorithm::GetChildPositionNew(
    const SizeF& childSize, const RefPtr<BubbleLayoutProperty>& bubbleProp)
{
    static std::map<Placement, std::vector<Placement>> PLACEMENT_STATES = {
        { Placement::BOTTOM_LEFT,
            {
                Placement::BOTTOM_LEFT,
                Placement::TOP_LEFT,
                Placement::RIGHT_TOP,
                Placement::LEFT_TOP,
                Placement::NONE,
            } },
        { Placement::BOTTOM,
            {
                Placement::BOTTOM,
                Placement::TOP,
                Placement::RIGHT,
                Placement::LEFT,
                Placement::NONE,
            } },
        { Placement::BOTTOM_RIGHT,
            {
                Placement::BOTTOM_RIGHT,
                Placement::TOP_RIGHT,
                Placement::RIGHT_BOTTOM,
                Placement::LEFT_BOTTOM,
                Placement::NONE,
            } },
        { Placement::TOP_LEFT,
            {
                Placement::TOP_LEFT,
                Placement::BOTTOM_LEFT,
                Placement::RIGHT_TOP,
                Placement::LEFT_TOP,
                Placement::NONE,
            } },
        { Placement::TOP,
            {
                Placement::TOP,
                Placement::BOTTOM,
                Placement::RIGHT,
                Placement::LEFT,
                Placement::NONE,
            } },
        { Placement::TOP_RIGHT,
            {
                Placement::TOP_RIGHT,
                Placement::BOTTOM_RIGHT,
                Placement::RIGHT_BOTTOM,
                Placement::LEFT_BOTTOM,
                Placement::NONE,
            } },
        { Placement::LEFT_TOP,
            {
                Placement::LEFT_TOP,
                Placement::RIGHT_TOP,
                Placement::BOTTOM_LEFT,
                Placement::TOP_LEFT,
                Placement::NONE,
            } },
        { Placement::LEFT,
            {
                Placement::LEFT,
                Placement::RIGHT,
                Placement::BOTTOM,
                Placement::TOP,
                Placement::NONE,
            } },
        { Placement::LEFT_BOTTOM,
            {
                Placement::LEFT_BOTTOM,
                Placement::RIGHT_BOTTOM,
                Placement::BOTTOM_RIGHT,
                Placement::TOP_RIGHT,
                Placement::NONE,
            } },
        { Placement::RIGHT_TOP,
            {
                Placement::RIGHT_TOP,
                Placement::LEFT_TOP,
                Placement::BOTTOM_LEFT,
                Placement::TOP_LEFT,
                Placement::NONE,
            } },
        { Placement::RIGHT,
            {
                Placement::RIGHT,
                Placement::LEFT,
                Placement::BOTTOM,
                Placement::TOP,
                Placement::NONE,
            } },
        { Placement::RIGHT_BOTTOM,
            {
                Placement::RIGHT_BOTTOM,
                Placement::LEFT_BOTTOM,
                Placement::BOTTOM_RIGHT,
                Placement::TOP_RIGHT,
                Placement::NONE,
            } },
    };
    OffsetF bottomPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_.ConvertToPx() + arrowHeight_);
    OffsetF topPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() - childSize.Height() - targetSpace_.ConvertToPx() - arrowHeight_);
    OffsetF defaultPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
        targetOffset_.GetY() + (targetSize_.Height() - childSize.Height()) / 2.0);
    OffsetF childPosition;
    OffsetF ArrowOffset;
    OffsetF position = defaultPosition;
    auto positionOffset = positionOffset_;
    auto originPlacement = placement_;
    auto originPosition = GetPositionWithPlacementNew(childSize, topPosition, bottomPosition, ArrowOffset);
    bool didNeedArrow = false;
    std::vector<Placement> currentPlacementStates = PLACEMENT_STATES.find(Placement::BOTTOM)->second;
    if (PLACEMENT_STATES.find(placement_) != PLACEMENT_STATES.end()) {
        currentPlacementStates = PLACEMENT_STATES.find(placement_)->second;
    }
    size_t step = ALIGNMENT_STEP_OFFSET;
    bVertical_ = false;
    bHorizontal_ = false;
    for (size_t i = 0, len = currentPlacementStates.size(); i < len;) {
        placement_ = currentPlacementStates[i];
        if (placement_ == Placement::NONE) {
            break;
        }
        if (bCaretMode_) { // Caret mode
            if ((placement_ != Placement::BOTTOM) && (placement_ != Placement::TOP)) {
                i++;
                continue;
            }
        }
        if (bVertical_) {
            if (setHorizontal_.find(placement_) != setHorizontal_.end()) {
                i++;
                continue;
            }
        }
        if (bHorizontal_) {
            if (setVertical_.find(placement_) != setVertical_.end()) {
                i++;
                continue;
            }
        }
        if (i >= step) {
            positionOffset_ = OffsetF(0.0f, 0.0f);
        }
        childPosition = GetPositionWithPlacementNew(childSize, topPosition, bottomPosition, ArrowOffset);
        UpdateChildPosition(childPosition);
        didNeedArrow = GetIfNeedArrow(bubbleProp, childSize_);
        position = FitToScreenNew(childPosition, step, i, childSize, didNeedArrow);
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            continue;
        }
        break;
    }
    if (placement_ == Placement::NONE) {
        bVertical_ = false;
        bHorizontal_ = false;
        position = GetAdjustPosition(currentPlacementStates, step, childSize, topPosition, bottomPosition, ArrowOffset);
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            showArrow_ = false;
            if (avoidKeyboard_ && !isHalfFoldHover_) {
                placement_ = originPlacement;
                position = AdjustPositionNew(originPosition, childSize.Width(), childSize.Height());
            } else {
                position = AdjustPosition(defaultPosition, childSize.Width(), childSize.Height(), targetSecurity_);
            }
            if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
                auto x = std::clamp(
                    defaultPosition.GetX(), marginStart_, wrapperSize_.Width() - childSize.Width() - marginEnd_);
                auto y = marginTop_;
                position = OffsetF(x, y);
            }
        }
    }
    positionOffset_ = positionOffset;
    arrowPlacement_ = placement_;
    arrowPosition_ = ArrowOffset;
    return position;
}

OffsetF BubbleLayoutAlgorithm::AdjustPositionNew(const OffsetF& position, float width, float height)
{
    OffsetF result = position;
    OffsetF positionEnd = position + OffsetF(width, height);
    if (GreatNotEqual(positionEnd.GetX(), wrapperSize_.Width() - marginEnd_)) {
        result.SetX(wrapperSize_.Width() - marginEnd_ - width);
    }
    if (GreatNotEqual(positionEnd.GetY(), wrapperSize_.Height() - marginBottom_)) {
        result.SetY(wrapperSize_.Height()- marginBottom_ - height);
    }
    if (LessNotEqual(position.GetX(), marginStart_)) {
        result.SetX(marginStart_);
    }
    if (LessNotEqual(position.GetY(), marginTop_)) {
        result.SetY(marginTop_);
    }
    return result;
}

OffsetF BubbleLayoutAlgorithm::GetAdjustPosition(std::vector<Placement>& currentPlacementStates, size_t step,
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    OffsetF position;
    float width = 0.0f;
    float height = 0.0f;
    for (size_t i = 0, len = currentPlacementStates.size(); i < len;) {
        placement_ = currentPlacementStates[i];
        if (placement_ == Placement::NONE) {
            break;
        }
        if (bCaretMode_) { // Caret mode
            if ((placement_ != Placement::BOTTOM) && (placement_ != Placement::TOP)) {
                i++;
                continue;
            }
        }
        if (bVertical_) {
            if (setHorizontal_.find(placement_) != setHorizontal_.end()) {
                i++;
                continue;
            }
        }
        if (bHorizontal_) {
            if (setVertical_.find(placement_) != setVertical_.end()) {
                i++;
                continue;
            }
        }
        childPosition = GetPositionWithPlacementNew(childSize, topPosition, bottomPosition, arrowPosition);
        UpdateChildPosition(childPosition);
        width = childSize.Width();
        height = childSize.Height();
        if (showArrow_) {
            if (setHorizontal_.find(placement_) != setHorizontal_.end()) {
                width += BUBBLE_ARROW_HEIGHT.ConvertToPx();
            }
            if (setVertical_.find(placement_) != setVertical_.end()) {
                height += BUBBLE_ARROW_HEIGHT.ConvertToPx();
            }
        }
        position = AdjustPosition(childPosition, width, height, targetSpace_.ConvertToPx());
        if (NearEqual(position, OffsetF(0.0f, 0.0f))) {
            i += step;
            continue;
        }
        break;
    }
    return position;
}

OffsetF BubbleLayoutAlgorithm::AdjustPosition(const OffsetF& position, float width, float height, float space)
{
    float xMax = 0.0f;
    float yMax = 0.0f;
    float xMin = 1.0f;
    float yMin = 1.0f;
    float yTargetOffset = 0.0f;
    switch (placement_) {
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            xMin = marginStart_;
            xMax = std::min(targetOffset_.GetX() - width - space, wrapperSize_.Width() - marginEnd_ - width);
            yMin = marginTop_;
            yMax = wrapperSize_.Height() - height - marginBottom_;
            if (isHalfFoldHover_) {
                yMin = wrapperRect_.Top();
                yMax = wrapperRect_.Bottom() - height;
            }
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            if (showArrow_) {
                space = space + BUBBLE_ARROW_HEIGHT.ConvertToPx();
            }
            xMin = std::max(targetOffset_.GetX() + targetSize_.Width() + space, marginStart_);
            xMax = wrapperSize_.Width() - width - marginEnd_;
            yMin = marginTop_;
            yMax = wrapperSize_.Height() - height - marginBottom_;
            if (isHalfFoldHover_) {
                yMin = wrapperRect_.Top();
                yMax = wrapperRect_.Bottom() - height;
            }
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            xMin = marginStart_;
            xMax = wrapperSize_.Width() - width - marginEnd_;
            yMin = marginTop_;
            yMax = std::min(targetOffset_.GetY() - height - space, wrapperSize_.Height() - marginBottom_ - height);
            if (isHalfFoldHover_) {
                yMin = wrapperRect_.Top();
                yMax = std::min(targetOffset_.GetY() - height - space,
                    static_cast<float>(wrapperRect_.Bottom()) - height);
            }
            yTargetOffset = targetSecurity_;
            break;
        }
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            if (showArrow_) {
                space = space + BUBBLE_ARROW_HEIGHT.ConvertToPx();
            }
            xMin = marginStart_;
            xMax = wrapperSize_.Width() - width - marginEnd_;
            yMin = std::max(targetOffset_.GetY() + targetSize_.Height() + space, marginTop_);
            yMax = wrapperSize_.Height() - height - marginBottom_;
            if (isHalfFoldHover_) {
                yMin = std::max(targetOffset_.GetY() + targetSize_.Height() + space,
                    static_cast<float>(wrapperRect_.Top()));
                yMax = wrapperRect_.Bottom() - height;
            }
            yTargetOffset = -targetSecurity_;
            break;
        }
        case Placement::NONE: {
            xMin = marginStart_;
            xMax = wrapperSize_.Width() - width - marginEnd_;
            yMin = marginTop_;
            yMax = wrapperSize_.Height() - height - marginBottom_;
            if (isHalfFoldHover_) {
                yMin = wrapperRect_.Top();
                yMax = wrapperRect_.Bottom() - height;
            }
            break;
        }
        default:
            break;
    }
    if ((LessNotEqual(xMax, xMin) && !isGreatWrapperWidth_) || LessNotEqual(yMax, yMin)) {
        if (!CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax)) {
            return OffsetF(0.0f, 0.0f);
        }
    } else if (LessNotEqual(xMax, xMin) && isGreatWrapperWidth_) {
        auto y = std::clamp(position.GetY(), yMin, yMax);
        return OffsetF(0.0f, y + yTargetOffset);
    }
    auto result = GetBubblePosition(position, xMin, xMax, yMin, yMax);
    CheckArrowPosition(result, width, height);
    return result;
}

bool BubbleLayoutAlgorithm::CheckIfNeedRemoveArrow(float& xMin, float& xMax, float& yMin, float& yMax)
{
    if (!showArrow_ || !avoidKeyboard_) {
        return false;
    }
    bool isHorizontal = false;
    if (setHorizontal_.find(placement_) != setHorizontal_.end()) {
        isHorizontal = true;
    }
    if ((isHorizontal && LessNotEqual(yMax, yMin)) || (!isHorizontal && LessNotEqual(xMax, xMin))) {
        return false;
    }
    if (isHorizontal && GreatOrEqual(xMax + BUBBLE_ARROW_HEIGHT.ConvertToPx(), xMin)) {
        xMax += BUBBLE_ARROW_HEIGHT.ConvertToPx();
        showArrow_ = false;
        return true;
    }
    if (!isHorizontal && GreatOrEqual(yMax + BUBBLE_ARROW_HEIGHT.ConvertToPx(), yMin)) {
        yMax += BUBBLE_ARROW_HEIGHT.ConvertToPx();
        showArrow_ = false;
        return true;
    }
    return false;
}

OffsetF BubbleLayoutAlgorithm::GetBubblePosition(const OffsetF& position, float xMin,
    float xMax, float yMin, float yMax)
{
    auto x = std::clamp(position.GetX(), xMin, xMax);
    auto y = std::clamp(position.GetY(), yMin, yMax);
    if (!showArrow_ || !avoidKeyboard_) {
        return OffsetF(x, y);
    }
    bool isHorizontal = false;
    if (setHorizontal_.find(placement_) != setHorizontal_.end()) {
        isHorizontal = true;
    }
    if (isHorizontal) {
        if (GreatNotEqual(position.GetX(), xMax)) {
            showArrow_ = false;
            x += BUBBLE_ARROW_HEIGHT.ConvertToPx();
        } else if (LessNotEqual(position.GetX(), xMin)) {
            showArrow_ = false;
        }
    } else {
        if (GreatNotEqual(position.GetY(), yMax)) {
            showArrow_ = false;
            y += BUBBLE_ARROW_HEIGHT.ConvertToPx();
        } else if (LessNotEqual(position.GetY(), yMin)) {
            showArrow_ = false;
        }
    }
    return OffsetF(x, y);
}

Placement GetSimplePlacement(Placement& placement)
{
    switch (placement) {
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            return Placement::LEFT;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            return Placement::RIGHT;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            return Placement::TOP;
        }
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            return Placement::BOTTOM;
        }
        default:
            return Placement::NONE;
    }
}

void BubbleLayoutAlgorithm::CheckArrowPosition(OffsetF& position, float width, float height)
{
    if (!showArrow_ || !avoidKeyboard_) {
        return;
    }
    float xMax = 0.0f;
    float yMax = 0.0f;
    float xMin = 1.0f;
    float yMin = 1.0f;
    float cornerDistance = borderRadius_.ConvertToPx() + BUBBLE_ARROW_WIDTH.ConvertToPx() / DOUBLE;
    auto simplePlacement = GetSimplePlacement(placement_);
    if (simplePlacement == Placement::LEFT) {
        yMin = position.GetY() + cornerDistance;
        yMax = position.GetY() + height - cornerDistance;
        if (GreatNotEqual(yMin, targetOffset_.GetY() + targetSize_.Height()) ||
            LessNotEqual(yMax, targetOffset_.GetY())) {
            showArrow_ = false;
            position.SetX(position.GetX() + BUBBLE_ARROW_HEIGHT.ConvertToPx());
        }
    } else if (simplePlacement == Placement::RIGHT) {
        yMin = position.GetY() + cornerDistance;
        yMax = position.GetY() + height - cornerDistance;
        if (GreatNotEqual(yMin, targetOffset_.GetY() + targetSize_.Height()) ||
            LessNotEqual(yMax, targetOffset_.GetY())) {
            showArrow_ = false;
            position.SetX(position.GetX() - BUBBLE_ARROW_HEIGHT.ConvertToPx());
        }
    } else if (simplePlacement == Placement::TOP) {
        xMin = position.GetX() + cornerDistance;
        xMax = position.GetX() + width - cornerDistance;
        if (GreatNotEqual(xMin, targetOffset_.GetX() + targetSize_.Width()) ||
            LessNotEqual(xMax, targetOffset_.GetX())) {
            showArrow_ = false;
            position.SetY(position.GetY() + BUBBLE_ARROW_HEIGHT.ConvertToPx());
        }
    } else if (simplePlacement == Placement::BOTTOM) {
        xMin = position.GetX() + cornerDistance;
        xMax = position.GetX() + width - cornerDistance;
        if (GreatNotEqual(xMin, targetOffset_.GetX() + targetSize_.Width()) ||
            LessNotEqual(xMax, targetOffset_.GetX())) {
            showArrow_ = false;
            position.SetY(position.GetY() - BUBBLE_ARROW_HEIGHT.ConvertToPx());
        }
    }
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementNew(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    auto func = placementFuncMap_.find(placement_);
    if (func != placementFuncMap_.end()) {
        auto placementFunc = func->second;
        if (placementFunc != nullptr) {
            childPosition = (this->*placementFunc)(childSize, topPosition, bottomPosition, arrowPosition);
        }
    }
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::FitToScreenNew(
    const OffsetF& position, size_t step, size_t& i, const SizeF& childSize, bool didNeedArrow)
{
    if (!CheckPosition(position, childSize, step, i)) {
        return OffsetF(0.0f, 0.0f);
    }
    return position;
}

OffsetF BubbleLayoutAlgorithm::AddTargetSpace(const OffsetF& position)
{
    auto x = position.GetX();
    auto y = position.GetY();
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            y += targetSpace_.ConvertToPx();
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            y -= targetSpace_.ConvertToPx();
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            x += targetSpace_.ConvertToPx();
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            x -= targetSpace_.ConvertToPx();
            break;
        }
        default: {
            y += targetSpace_.ConvertToPx();
            break;
        }
    }
    return OffsetF(x, y);
}

OffsetF BubbleLayoutAlgorithm::AddOffset(const OffsetF& position)
{
    auto x = position.GetX();
    auto y = position.GetY();
    x += positionOffset_.GetX();
    y += positionOffset_.GetY();
    return OffsetF(x, y);
}

void BubbleLayoutAlgorithm::UpdateChildPosition(OffsetF& childOffset)
{
    double arrowWidth = BUBBLE_ARROW_WIDTH.ConvertToPx();
    double twoRadiusPx = borderRadius_.ConvertToPx() * 2.0;
    float movingDistance = BUBBLE_ARROW_HEIGHT.ConvertToPx();
    switch (placement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            showArrow_ = GreatOrEqual(childSize_.Width() - twoRadiusPx, arrowWidth);
            if (!showArrow_ || !enableArrow_) {
                childOffset += OffsetF(0.0, movingDistance);
            }
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            showArrow_ = GreatOrEqual(childSize_.Width() - twoRadiusPx, arrowWidth);
            if (!showArrow_ || !enableArrow_) {
                childOffset += OffsetF(0.0, -(movingDistance));
            }
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            showArrow_ = GreatOrEqual(childSize_.Height() - twoRadiusPx, arrowWidth);
            if (!showArrow_ || !enableArrow_) {
                childOffset += OffsetF(movingDistance, 0.0);
            }
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            showArrow_ = GreatOrEqual(childSize_.Height() - twoRadiusPx, arrowWidth);
            if (!showArrow_ || !enableArrow_) {
                childOffset += OffsetF(-(movingDistance), 0.0);
            }
            break;
        default:
            break;
    }
    if (!enableArrow_) {
        showArrow_ = false;
    }
}

void BubbleLayoutAlgorithm::UpdateTouchRegion()
{
    OffsetF topLeft = childOffset_;
    OffsetF bottomRight = OffsetF(childSize_.Width(), childSize_.Height());
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            if (showArrow_) {
                bottomRight += OffsetF(0.0, BUBBLE_ARROW_HEIGHT.ConvertToPx());
            }
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            if (showArrow_) {
                topLeft += OffsetF(0.0, -BUBBLE_ARROW_HEIGHT.ConvertToPx());
                bottomRight += OffsetF(0.0, BUBBLE_ARROW_HEIGHT.ConvertToPx());
            }
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            if (showArrow_) {
                bottomRight += OffsetF(BUBBLE_ARROW_HEIGHT.ConvertToPx(), 0.0);
            }
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            if (showArrow_) {
                topLeft += OffsetF(-BUBBLE_ARROW_HEIGHT.ConvertToPx(), 0.0);
                bottomRight += OffsetF(BUBBLE_ARROW_HEIGHT.ConvertToPx(), 0.0);
            }
            break;
        default:
            break;
    }
    touchRegion_ = RectF(topLeft, topLeft + bottomRight);
    dumpInfo_.touchRegion = touchRegion_;
}

void BubbleLayoutAlgorithm::InitCaretTargetSizeAndPosition()
{
    static std::vector<std::string> TEXT_STATES = { V2::TEXTAREA_ETS_TAG, V2::TEXTINPUT_ETS_TAG,
        V2::RICH_EDITOR_ETS_TAG, V2::SEARCH_ETS_TAG };
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_VOID(targetNode);
    auto it = std::find(TEXT_STATES.begin(), TEXT_STATES.end(), targetTag_);
    bCaretMode_ = false;
    CaretMetricsF caretMetrics;
    if (it != TEXT_STATES.end()) {
        bCaretMode_ = true;
        positionOffset_ = OffsetF(0.0f, 0.0f);
        if ((placement_ != Placement::BOTTOM) && (placement_ != Placement::TOP)) {
            placement_ = Placement::BOTTOM;
        }
        GetTextCaretMetrics<TextBase>(targetNode, caretMetrics);
        targetOffset_ = caretMetrics.offset;
        targetSize_.SetHeight(caretMetrics.height);
        targetSize_.SetWidth(0.0f);
    }
}

void BubbleLayoutAlgorithm::InitTargetSizeAndPosition(bool showInSubWindow, LayoutWrapper* layoutWrapper)
{
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_VOID(targetNode);
    if (!targetNode->IsOnMainTree() && !targetNode->IsVisible()) {
        return;
    }
    if (followTransformOfTarget_) {
        auto rect = targetNode->GetPaintRectToWindowWithTransform();
        targetSize_ = rect.GetSize();
        targetOffset_ = rect.GetOffset();
    } else {
        auto geometryNode = targetNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        targetSize_ = geometryNode->GetFrameSize();
        targetOffset_ = targetNode->GetPaintRectOffset();
    }

    auto expandDisplay = SubwindowManager::GetInstance()->GetIsExpandDisplay();
    auto pipelineContext = expandDisplay ? targetNode->GetContextRefPtr() : GetMainPipelineContext(layoutWrapper);
    CHECK_NULL_VOID(pipelineContext);

    TAG_LOGD(AceLogTag::ACE_OVERLAY, "popup targetOffset_: %{public}s, targetSize_: %{public}s",
        targetOffset_.ToString().c_str(), targetSize_.ToString().c_str());
    // Show in SubWindow
    if (showInSubWindow) {
        auto displayWindowOffset = OffsetF(pipelineContext->GetDisplayWindowRectInfo().GetOffset().GetX(),
            pipelineContext->GetDisplayWindowRectInfo().GetOffset().GetY());
        targetOffset_ += displayWindowOffset;
        auto currentSubwindow = SubwindowManager::GetInstance()->GetCurrentWindow();
        if (currentSubwindow) {
            auto subwindowRect = currentSubwindow->GetRect();
            targetOffset_ -= subwindowRect.GetOffset();
        }
    }
    dumpInfo_.targetOffset = targetOffset_;
    dumpInfo_.targetSize = targetSize_;
}

bool BubbleLayoutAlgorithm::CheckPositionInPlacementRect(
    const Rect& rect, const OffsetF& position, const SizeF& childSize)
{
    auto x = position.GetX();
    auto y = position.GetY();
    if (LessNotEqual(x, rect.Left()) || GreatNotEqual(x + childSize.Width(), rect.Right()) ||
        LessNotEqual(y, rect.Top()) || GreatNotEqual(y + childSize.Height(), rect.Bottom())) {
        return false;
    }
    return true;
}

bool BubbleLayoutAlgorithm::CheckPosition(const OffsetF& position, const SizeF& childSize, size_t step, size_t& i)
{
    float targetOffsetX = targetOffset_.GetX();
    float targetOffsetY = targetOffset_.GetY();
    Rect rect;
    switch (placement_) {
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
        case Placement::BOTTOM: {
            targetOffsetY += (userSetTargetSpace_.ConvertToPx());
            auto y = std::max(targetOffsetY + targetSize_.Height(), marginTop_);
            auto height = std::min(wrapperSize_.Height() - marginBottom_ - targetOffsetY - targetSize_.Height(),
                wrapperSize_.Height() - marginBottom_ - marginTop_);
            rect.SetRect(marginStart_, y, wrapperSize_.Width() - marginEnd_ - marginStart_, height);
            if (isHalfFoldHover_) {
                y = std::max(targetOffsetY + targetSize_.Height(), static_cast<float>(wrapperRect_.Top()));
                height = std::min(static_cast<float>(wrapperRect_.Bottom()) - targetOffsetY - targetSize_.Height(),
                    wrapperSize_.Height() - marginBottom_ - marginTop_);
                rect.SetRect(marginStart_, y, wrapperSize_.Width() - marginEnd_ - marginStart_, height);
            }
            if (childSize.Height() > height) {
                i += step;
                return false;
            } else {
                bVertical_ = true;
            }
            break;
        }
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
        case Placement::TOP: {
            targetOffsetY += (-userSetTargetSpace_.ConvertToPx());
            auto height = std::min(targetOffsetY - marginTop_, wrapperSize_.Height() - marginTop_ - marginBottom_);
            rect.SetRect(marginStart_, marginTop_, wrapperSize_.Width() - marginEnd_ - marginStart_, height);
            if (isHalfFoldHover_) {
                height = std::min(targetOffsetY - static_cast<float>(wrapperRect_.Top()),
                    wrapperSize_.Height() - marginTop_ - marginBottom_);
                rect.SetRect(marginStart_, wrapperRect_.Top(),
                    wrapperSize_.Width() - marginEnd_ - marginStart_, height);
            }
            if (childSize.Height() > height) {
                i += step;
                return false;
            } else {
                bVertical_ = true;
            }
            break;
        }
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT: {
            targetOffsetX += (userSetTargetSpace_.ConvertToPx());
            auto x = std::max(targetOffsetX + targetSize_.Width(), marginStart_);
            auto width = std::min(wrapperSize_.Width() - targetOffsetX - targetSize_.Width() - marginEnd_,
                wrapperSize_.Width() - marginStart_ - marginEnd_);
            rect.SetRect(x, marginTop_, width, wrapperSize_.Height() - marginBottom_ - marginTop_);
            if (isHalfFoldHover_) {
                rect.SetRect(x, wrapperRect_.Top(), width, wrapperRect_.Height());
            }
            if (childSize.Width() > width) {
                i += step;
                return false;
            } else {
                bHorizontal_ = true;
            }
            break;
        }
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT: {
            targetOffsetX += (-userSetTargetSpace_.ConvertToPx());
            auto width = std::min(targetOffsetX - marginStart_, wrapperSize_.Width() - marginEnd_ - marginStart_);
            rect.SetRect(marginStart_, marginTop_, width, wrapperSize_.Height() - marginBottom_ - marginTop_);
            if (isHalfFoldHover_) {
                rect.SetRect(marginStart_, wrapperRect_.Top(), width, wrapperRect_.Height());
            }
            if (childSize.Width() > width) {
                i += step;
                return false;
            } else {
                bHorizontal_ = true;
            }
            break;
        }
        default:
            return false;
    }
    i++;
    return CheckPositionInPlacementRect(rect, position, childSize);
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    arrowPosition = topPosition + OffsetF(radius + arrowHalfWidth, childSize.Height() + bubbleSpacing);
    if (bCaretMode_) {
        arrowPosition = OffsetF(targetOffset_.GetX(), targetOffset_.GetY() - bubbleSpacing);
    }
    return topPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementTopLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginBottom = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition = OffsetF(targetOffset_.GetX() - marginRight,
        targetOffset_.GetY() - childSize.Height() - bubbleSpacing - marginBottom - targetSpace_.ConvertToPx());
    arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, childSize.Height() + bubbleSpacing);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementTopRight(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginBottom = 0.0f;
    float marginLeft = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
        targetOffset_.GetY() - childSize.Height() - targetSpace_.ConvertToPx() - bubbleSpacing - marginBottom);
    arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, childSize.Height() + bubbleSpacing);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    arrowPosition = bottomPosition + OffsetF(radius + arrowHalfWidth, -bubbleSpacing);
    if (bCaretMode_) {
        arrowPosition = OffsetF(targetOffset_.GetX(), targetOffset_.GetY() + targetSize_.Height() + bubbleSpacing);
    }
    return bottomPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementBottomLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginTop = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition = OffsetF(targetOffset_.GetX() - marginRight,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_.ConvertToPx() + bubbleSpacing + marginTop);
    arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, -bubbleSpacing);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementBottomRight(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginTop = 0.0f;
    float marginLeft = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float radius = borderRadius_.ConvertToPx();
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
        targetOffset_.GetY() + targetSize_.Height() + targetSpace_.ConvertToPx() + bubbleSpacing + marginTop);
    arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, -bubbleSpacing);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementLeft(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition =
        OffsetF(targetOffset_.GetX() - targetSpace_.ConvertToPx() - bubbleSpacing - childSize.Width() - marginRight,
            targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
    arrowPosition = childPosition + OffsetF(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementLeftTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginBottom = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition =
        OffsetF(targetOffset_.GetX() - targetSpace_.ConvertToPx() - bubbleSpacing - childSize.Width() - marginRight,
            targetOffset_.GetY() - marginBottom);
    arrowPosition = childPosition + OffsetF(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementLeftBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginRight = 0.0f;
    float marginTop = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition =
        OffsetF(targetOffset_.GetX() - targetSpace_.ConvertToPx() - bubbleSpacing - childSize.Width() - marginRight,
            targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
    arrowPosition = childPosition + OffsetF(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementRight(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginLeft = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition =
        OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_.ConvertToPx() + bubbleSpacing + marginLeft,
            targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0);
    arrowPosition = childPosition + OffsetF(-bubbleSpacing, radius + arrowHalfWidth);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementRightTop(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginBottom = 0.0f;
    float marginLeft = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition =
        OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_.ConvertToPx() + bubbleSpacing + marginLeft,
            targetOffset_.GetY() - marginBottom);
    arrowPosition = childPosition + OffsetF(-bubbleSpacing, radius + arrowHalfWidth);
    return childPosition;
}

OffsetF BubbleLayoutAlgorithm::GetPositionWithPlacementRightBottom(
    const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition)
{
    OffsetF childPosition;
    float marginTop = 0.0f;
    float marginLeft = 0.0f;
    float bubbleSpacing = scaledBubbleSpacing_;
    float arrowHalfWidth = BUBBLE_ARROW_WIDTH.ConvertToPx() / BUBBLE_ARROW_HALF;
    float radius = borderRadius_.ConvertToPx();
    childPosition =
        OffsetF(targetOffset_.GetX() + targetSize_.Width() + targetSpace_.ConvertToPx() + bubbleSpacing + marginLeft,
            targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
    arrowPosition = childPosition + OffsetF(-bubbleSpacing, radius + arrowHalfWidth);
    return childPosition;
}

std::string BubbleLayoutAlgorithm::MoveTo(double x, double y)
{
    return "M" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string BubbleLayoutAlgorithm::LineTo(double x, double y)
{
    return "L" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string BubbleLayoutAlgorithm::ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y)
{
    int32_t sweep_flag = 1;
    return "A" + std::to_string(rx) + " " + std::to_string(ry) + " " + std::to_string(rotation) + " " +
           std::to_string(arc_flag) + " " + std::to_string(sweep_flag) + " " + std::to_string(x) + " " +
           std::to_string(y) + " ";
}

void BubbleLayoutAlgorithm::UpdateClipOffset(const RefPtr<FrameNode>& frameNode)
{
    auto paintProperty = frameNode->GetPaintProperty<BubbleRenderProperty>();
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    if (!bCaretMode_) {
        arrowPosition_ =
            OffsetF(BUBBLE_ARROW_HEIGHT.ConvertToPx() * DOUBLE, BUBBLE_ARROW_HEIGHT.ConvertToPx() * DOUBLE);
        UpdateArrowOffset(paintProperty->GetArrowOffset(), arrowPlacement_);
    } else {
        arrowPosition_ = arrowPosition_ - childOffset_ + OffsetF(BUBBLE_ARROW_HEIGHT.ConvertToPx(), 0.0f);
    }
    targetOffset_ = targetOffset_ - childOffset_;
    childOffset_ = OffsetF(BUBBLE_ARROW_HEIGHT.ConvertToPx(), BUBBLE_ARROW_HEIGHT.ConvertToPx());
    clipFrameNode_ = childNode;
    clipPath_.clear();
    clipPath_ = ClipBubbleWithPath();
}

std::string BubbleLayoutAlgorithm::ClipBubbleWithPath()
{
    std::string path;
    float arrowOffset = 0.0;
    if (!bCaretMode_) {
        arrowOffset = GetArrowOffset(arrowPlacement_);
    }
    float radiusPx = borderRadius_.ConvertToPx();
    Placement arrowBuildplacement = Placement::NONE;
    if (enableArrow_ && showArrow_) {
        GetArrowBuildPlacement(arrowBuildplacement);
        arrowBuildPlacement_ = arrowBuildplacement;
    }
    if ((arrowBuildplacement == Placement::TOP_LEFT) || (arrowBuildplacement == Placement::LEFT_TOP)) {
        path += MoveTo(childOffset_.GetX(), childOffset_.GetY());
    } else {
        path += MoveTo(childOffset_.GetX() + radiusPx, childOffset_.GetY());
    }
    path += BuildTopLinePath(arrowOffset, radiusPx, arrowBuildplacement);
    if ((arrowBuildplacement != Placement::TOP_RIGHT) && (arrowBuildplacement != Placement::RIGHT_TOP)) {
        path += BuildCornerPath(Placement::TOP_RIGHT, radiusPx);
    }
    path += BuildRightLinePath(arrowOffset, radiusPx, arrowBuildplacement);
    if ((arrowBuildplacement != Placement::RIGHT_BOTTOM) && (arrowBuildplacement != Placement::BOTTOM_RIGHT)) {
        path += BuildCornerPath(Placement::BOTTOM_RIGHT, radiusPx);
    }
    path += BuildBottomLinePath(arrowOffset, radiusPx, arrowBuildplacement);
    if ((arrowBuildplacement != Placement::BOTTOM_LEFT) && (arrowBuildplacement != Placement::LEFT_BOTTOM)) {
        path += BuildCornerPath(Placement::BOTTOM_LEFT, radiusPx);
    }
    path += BuildLeftLinePath(arrowOffset, radiusPx, arrowBuildplacement);
    if ((arrowBuildplacement != Placement::LEFT_TOP) && (arrowBuildplacement != Placement::TOP_LEFT)) {
        path += BuildCornerPath(Placement::TOP_LEFT, radiusPx);
    }
    return path + "Z";
}

float BubbleLayoutAlgorithm::GetArrowOffset(const Placement& placement)
{
    Edge edge;
    double arrowOffset;
    double maxMotionRange = 0.0;
    double minMotionRange = 0.0;
    double targetOffsetXOrY = 0.0;
    double childOffsetsetXOrY = 0.0;
    double childSizeWidthOrHeight = 0.0;
    double targetSizeWidthOrHeight = 0.0;
    bool bHorizontal = false;

    InitEdgeSize(edge);
    switch (placement) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            bHorizontal = true;
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            bHorizontal = true;
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            break;
        default:
            break;
    }
    if (bHorizontal) {
        targetOffsetXOrY = targetOffset_.GetX();
        targetSizeWidthOrHeight = targetSize_.Width();
        childOffsetsetXOrY = childOffset_.GetX();
        childSizeWidthOrHeight = childSize_.Width();
    } else {
        targetOffsetXOrY = targetOffset_.GetY();
        targetSizeWidthOrHeight = targetSize_.Height();
        childOffsetsetXOrY = childOffset_.GetY();
        childSizeWidthOrHeight = childSize_.Height();
    }
    maxMotionRange = childSizeWidthOrHeight;
    if (arrowOfTargetOffset_ == ArrowOfTargetOffset::START) {
        arrowOffset = (targetOffsetXOrY + (arrowOffset_.Value() * targetSizeWidthOrHeight)) - childOffsetsetXOrY +
                      BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
        return arrowOffset;
    }
    if (arrowOfTargetOffset_ == ArrowOfTargetOffset::CENTER) {
        arrowOffset = (targetOffsetXOrY + (arrowOffset_.Value() * targetSizeWidthOrHeight)) - childOffsetsetXOrY;
        return arrowOffset;
    }
    if (arrowOfTargetOffset_ == ArrowOfTargetOffset::END) {
        arrowOffset = (targetOffsetXOrY + (arrowOffset_.Value() * targetSizeWidthOrHeight)) - childOffsetsetXOrY -
                      BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
        return arrowOffset;
    }
    return std::clamp(arrowOffset_.Unit() == DimensionUnit::PERCENT ? arrowOffset_.Value() * maxMotionRange
                                                                    : arrowOffset_.ConvertToPx(),
        minMotionRange, maxMotionRange);
}

void BubbleLayoutAlgorithm::UpdateArrowOffset(const std::optional<Dimension>& offset, const Placement& placement)
{
    if (offset.has_value()) {
        arrowOffset_ = offset.value();
        arrowOfTargetOffset_ = ArrowOfTargetOffset::NONE;
        if (arrowOffset_.Unit() == DimensionUnit::PERCENT) {
            if (arrowOffset_.Value() == ARROW_OFFSET_START_VALUE) {
                arrowOfTargetOffset_ = ArrowOfTargetOffset::START;
            } else if (arrowOffset_.Value() == ARROW_OFFSET_CENTER_VALUE) {
                arrowOfTargetOffset_ = ArrowOfTargetOffset::CENTER;
            } else {
                arrowOfTargetOffset_ = ArrowOfTargetOffset::END;
            }
            arrowOffset_.SetValue(std::clamp(arrowOffset_.Value(), 0.0, 1.0));
        }
        return;
    }
    arrowOfTargetOffset_ = ArrowOfTargetOffset::NONE;
    switch (placement) {
        case Placement::LEFT:
        case Placement::RIGHT:
        case Placement::TOP:
        case Placement::BOTTOM:
            arrowOffset_ = BUBBLE_ARROW_HALF_PERCENT_VALUE;
            arrowOfTargetOffset_ = ArrowOfTargetOffset::CENTER;
            break;
        case Placement::TOP_LEFT:
        case Placement::BOTTOM_LEFT:
        case Placement::LEFT_TOP:
        case Placement::RIGHT_TOP:
            arrowOffset_ = BUBBLE_ARROW_ZERO_PERCENT_VALUE;
            arrowOfTargetOffset_ = ArrowOfTargetOffset::START;
            break;
        case Placement::TOP_RIGHT:
        case Placement::BOTTOM_RIGHT:
        case Placement::LEFT_BOTTOM:
        case Placement::RIGHT_BOTTOM:
            arrowOffset_ = BUBBLE_ARROW_ONE_HUNDRED_PERCENT_VALUE;
            arrowOfTargetOffset_ = ArrowOfTargetOffset::END;
            break;
        default:
            break;
    }
}

void BubbleLayoutAlgorithm::InitEdgeSize(Edge& edge)
{
    edge.SetTop(Dimension(std::max(padding_.Left().ConvertToPx(), border_.TopLeftRadius().GetX().ConvertToPx()) +
                          std::max(padding_.Right().ConvertToPx(), border_.TopRightRadius().GetX().ConvertToPx())));
    edge.SetBottom(
        Dimension(std::max(padding_.Left().ConvertToPx(), border_.BottomLeftRadius().GetX().ConvertToPx()) +
                  std::max(padding_.Right().ConvertToPx(), border_.BottomRightRadius().GetX().ConvertToPx())));
    edge.SetLeft(
        Dimension(std::max(padding_.Top().ConvertToPx(), border_.TopRightRadius().GetY().ConvertToPx()) +
                  std::max(padding_.Bottom().ConvertToPx(), border_.BottomRightRadius().GetY().ConvertToPx())));
    edge.SetRight(
        Dimension(std::max(padding_.Top().ConvertToPx(), border_.TopLeftRadius().GetY().ConvertToPx()) +
                  std::max(padding_.Bottom().ConvertToPx(), border_.BottomLeftRadius().GetY().ConvertToPx())));
}

float BubbleLayoutAlgorithm::ModifyBorderRadius(float borderRadius, float halfChildHeight)
{
    return GreatOrEqual(borderRadius, halfChildHeight) ? halfChildHeight : borderRadius;
}

void BubbleLayoutAlgorithm::GetArrowBuildPlacement(Placement& arrowBuildplacement)
{
    auto radius = borderRadius_.ConvertToPx();
    float maxOffset = 0.0;
    switch (arrowPlacement_) {
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT: // TOP
            maxOffset = childOffset_.GetX() + childSize_.Width() - radius -
                        BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
            if ((!bCaretMode_) && (arrowOffset_.Unit() != DimensionUnit::PERCENT)) {
                if ((arrowPosition_.GetX() + arrowOffset_.ConvertToPx()) > maxOffset) {
                    arrowBuildplacement = Placement::TOP_RIGHT;
                    break;
                }
                if ((arrowOffset_.ConvertToPx()) < radius) {
                    arrowBuildplacement = Placement::TOP_LEFT;
                    break;
                }
                arrowBuildplacement = Placement::TOP;
            } else {
                arrowBuildplacement = Placement::TOP;
            }
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM: // Right
            maxOffset = childOffset_.GetY() + childSize_.Height() - radius -
                        BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
            if ((!bCaretMode_) && (arrowOffset_.Unit() != DimensionUnit::PERCENT)) {
                if ((arrowPosition_.GetY() + arrowOffset_.ConvertToPx()) > maxOffset) {
                    arrowBuildplacement = Placement::RIGHT_BOTTOM;
                    break;
                }
                if ((arrowOffset_.ConvertToPx()) < radius) {
                    arrowBuildplacement = Placement::RIGHT_TOP;
                    break;
                }
                arrowBuildplacement = Placement::RIGHT;
            } else {
                arrowBuildplacement = Placement::RIGHT;
            }
            break;
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT: // Bottom
            maxOffset = childOffset_.GetX() + childSize_.Width() - radius -
                        BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
            if ((!bCaretMode_) && (arrowOffset_.Unit() != DimensionUnit::PERCENT)) {
                if ((arrowPosition_.GetX() + arrowOffset_.ConvertToPx()) > maxOffset) {
                    arrowBuildplacement = Placement::BOTTOM_RIGHT; // replace
                    break;
                }
                if ((arrowOffset_.ConvertToPx()) < radius) {
                    arrowBuildplacement = Placement::BOTTOM_LEFT; // replace
                    break;
                }
                arrowBuildplacement = Placement::BOTTOM; // nomal
            } else {
                arrowBuildplacement = Placement::BOTTOM; // nomal
            }
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM: // Left
            maxOffset = childOffset_.GetY() + childSize_.Height() - radius -
                        BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
            if ((!bCaretMode_) && (arrowOffset_.Unit() != DimensionUnit::PERCENT)) {
                if ((arrowPosition_.GetY() + arrowOffset_.ConvertToPx()) > maxOffset) {
                    arrowBuildplacement = Placement::LEFT_BOTTOM;
                    break;
                }
                if ((arrowOffset_.ConvertToPx()) < radius) {
                    arrowBuildplacement = Placement::LEFT_TOP;
                    break;
                }
                arrowBuildplacement = Placement::LEFT;
            } else {
                arrowBuildplacement = Placement::LEFT;
            }
            break;
        default:
            break;
    }
    if (arrowBuildplacement > Placement::BOTTOM) {
        arrowPosition_ += OffsetF(-BUBBLE_ARROW_HEIGHT.ConvertToPx(), -BUBBLE_ARROW_HEIGHT.ConvertToPx());
    }
}

void BubbleLayoutAlgorithm::SetArrowOffsetsFromClip(const int16_t index, const float offsetX, const float offsetY)
{
    arrowOffsetsFromClip_[index] = { offsetX, offsetY };
}

std::string BubbleLayoutAlgorithm::BuildTopLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement)
{
    std::string path;
    float childOffsetY = childOffset_.GetY();
    auto leftOffset =
        childOffset_.GetX() + radius + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto rightOffset = childOffset_.GetX() + childSize_.Width() - radius -
                       BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto arrowTopOffset = std::clamp(
        arrowPosition_.GetX() + arrowOffset, static_cast<float>(leftOffset), static_cast<float>(rightOffset));
    switch (arrowPlacement_) {
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            if (arrowBuildplacement == Placement::TOP_RIGHT) {
                path += ReplaceArrowTopRight(
                    arrowPosition_.GetX() + childSize_.Width() - BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF, childOffsetY);
            }
            if (arrowBuildplacement == Placement::TOP_LEFT) {
                path +=
                    ReplaceArrowTopLeft(arrowPosition_.GetX() + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF, childOffsetY);
            }
            if (arrowBuildplacement == Placement::TOP) {
                path += LineTo(arrowTopOffset - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffsetY); // P1
                path += LineTo(arrowTopOffset - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
                    childOffsetY - ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx()); // P2
                path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
                    arrowTopOffset + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
                    childOffsetY - ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx());                            // P4
                path += LineTo(arrowTopOffset + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffsetY); // P5
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
                    arrowTopOffset - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffsetY);
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
                    arrowTopOffset - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
                    childOffsetY - ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
                    arrowTopOffset + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
                    childOffsetY - ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
                    arrowTopOffset + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffsetY);
            }
            break;
        default:
            break;
    }
    if (arrowBuildplacement != Placement::TOP_RIGHT) {
        path += LineTo(childOffset_.GetX() + childSize_.Width() - radius, childOffsetY);
    }
    return path;
}

std::string BubbleLayoutAlgorithm::BuildRightLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement)
{
    std::string path;
    float childOffsetY = childOffset_.GetY();
    auto topOffset = childOffset_.GetY() + radius + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto bottomOffset = childOffset_.GetY() + childSize_.Height() - radius - BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto arrowRightOffset = std::clamp(
        arrowPosition_.GetY() + arrowOffset, static_cast<float>(topOffset), static_cast<float>(bottomOffset));
    switch (arrowPlacement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            if (arrowBuildplacement == Placement::RIGHT_BOTTOM) {
                path += ReplaceArrowRightBottom(arrowPosition_.GetY() + childSize_.Height()
                    - BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF, childOffset_.GetX() + childSize_.Width());
            }
            if (arrowBuildplacement == Placement::RIGHT_TOP) {
                path += ReplaceArrowRightTop(arrowPosition_.GetY() + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF,
                    childOffset_.GetX() + childSize_.Width());
            }
            if (arrowBuildplacement == Placement::RIGHT) {
                path += LineTo(childOffset_.GetX() + childSize_.Width(),
                    arrowRightOffset - ARROW_HORIZON_P1_OFFSET_Y.ConvertToPx()); // P1
                path += LineTo(childOffset_.GetX() + childSize_.Width() + ARROW_HORIZON_P2_OFFSET_X.ConvertToPx(),
                    arrowRightOffset - ARROW_HORIZON_P2_OFFSET_Y.ConvertToPx()); // P2
                path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
                    childOffset_.GetX() + childSize_.Width() + ARROW_HORIZON_P4_OFFSET_X.ConvertToPx(),
                    arrowRightOffset + ARROW_HORIZON_P4_OFFSET_Y.ConvertToPx()); // P4
                path += LineTo(childOffset_.GetX() + childSize_.Width(),
                    arrowRightOffset + ARROW_HORIZON_P5_OFFSET_Y.ConvertToPx()); // P5
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO, childOffset_.GetX() + childSize_.Width(),
                    arrowRightOffset - ARROW_HORIZON_P1_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
                    childOffset_.GetX() + childSize_.Width() + ARROW_HORIZON_P2_OFFSET_X.ConvertToPx(),
                    arrowRightOffset - ARROW_HORIZON_P2_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
                    childOffset_.GetX() + childSize_.Width() + ARROW_HORIZON_P4_OFFSET_X.ConvertToPx(),
                    arrowRightOffset + ARROW_HORIZON_P4_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE, childOffset_.GetX() + childSize_.Width(),
                    arrowRightOffset + ARROW_HORIZON_P5_OFFSET_Y.ConvertToPx());
            }
            break;
        default:
            break;
    }
    if (arrowBuildplacement != Placement::RIGHT_BOTTOM) {
        path += LineTo(childOffset_.GetX() + childSize_.Width(), childOffsetY + childSize_.Height() - radius);
    }
    return path;
}

std::string BubbleLayoutAlgorithm::BuildBottomLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement)
{
    std::string path;
    float childOffsetY = childOffset_.GetY();
    auto leftOffset = childOffset_.GetX() + radius + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto rightOffset = childOffset_.GetX() + childSize_.Width() - radius - BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto arrowBottomOffset = std::clamp(
        arrowPosition_.GetX() + arrowOffset, static_cast<float>(leftOffset), static_cast<float>(rightOffset));
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            if (arrowBuildplacement == Placement::BOTTOM_RIGHT) {
                path += ReplaceArrowBottomRight(arrowPosition_.GetX() + childSize_.Width()
                    - BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF, childOffsetY + childSize_.Height());
            }
            if (arrowBuildplacement == Placement::BOTTOM_LEFT) {
                path += ReplaceArrowBottomLeft(arrowPosition_.GetX() + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF,
                    childOffsetY + childSize_.Height());
            }
            if (arrowBuildplacement == Placement::BOTTOM) {
                path += LineTo(arrowBottomOffset + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
                    childOffsetY + childSize_.Height()); // P1
                path += LineTo(arrowBottomOffset + ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
                    childOffsetY + childSize_.Height() + ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx()); // P2
                path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
                    arrowBottomOffset - ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
                    childOffsetY + childSize_.Height() + ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx()); // P4
                path += LineTo(arrowBottomOffset - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
                    childOffsetY + childSize_.Height()); // P5
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
                    arrowBottomOffset + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffsetY + childSize_.Height());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
                    arrowBottomOffset + ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
                    childOffsetY + childSize_.Height() + ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
                    arrowBottomOffset - ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
                    childOffsetY + childSize_.Height() + ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE, arrowBottomOffset
                    - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffsetY + childSize_.Height());
            }
            break;
        default:
            break;
    }
    if (arrowBuildplacement != Placement::BOTTOM_LEFT) {
        path += LineTo(childOffset_.GetX() + radius, childOffsetY + childSize_.Height());
    }
    return path;
}

std::string BubbleLayoutAlgorithm::BuildLeftLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement)
{
    std::string path;
    float childOffsetY = childOffset_.GetY();
    auto topOffset =
        childOffset_.GetY() + radius + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto bottomOffset = childOffset_.GetY() + childSize_.Height() - radius -
                        BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF;
    auto arrowLeftOffset = std::clamp(
        arrowPosition_.GetY() + arrowOffset, static_cast<float>(topOffset), static_cast<float>(bottomOffset));
    switch (arrowPlacement_) {
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            if (arrowBuildplacement == Placement::LEFT_BOTTOM) {
                path += ReplaceArrowLeftBottom(
                    arrowPosition_.GetY() + childSize_.Height() - BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF,
                    childOffset_.GetX());
            }
            if (arrowBuildplacement == Placement::LEFT_TOP) {
                path += ReplaceArrowLeftTop(
                    arrowPosition_.GetY() + BUBBLE_ARROW_WIDTH.ConvertToPx() / HALF, childOffset_.GetX());
            }
            if (arrowBuildplacement == Placement::LEFT) {
                path += LineTo(childOffset_.GetX(), arrowLeftOffset + ARROW_HORIZON_P1_OFFSET_Y.ConvertToPx()); // P1
                path += LineTo(childOffset_.GetX() - ARROW_HORIZON_P2_OFFSET_X.ConvertToPx(),
                    arrowLeftOffset + ARROW_HORIZON_P2_OFFSET_Y.ConvertToPx()); // P2
                path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
                    childOffset_.GetX() - ARROW_HORIZON_P4_OFFSET_X.ConvertToPx(),
                    arrowLeftOffset - ARROW_HORIZON_P4_OFFSET_Y.ConvertToPx());                                 // P4
                path += LineTo(childOffset_.GetX(), arrowLeftOffset - ARROW_HORIZON_P5_OFFSET_Y.ConvertToPx()); // P5
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
                    childOffset_.GetX(), arrowLeftOffset + ARROW_HORIZON_P1_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
                    childOffset_.GetX() - ARROW_HORIZON_P2_OFFSET_X.ConvertToPx(),
                    arrowLeftOffset + ARROW_HORIZON_P2_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
                    childOffset_.GetX() - ARROW_HORIZON_P4_OFFSET_X.ConvertToPx(),
                    arrowLeftOffset - ARROW_HORIZON_P4_OFFSET_Y.ConvertToPx());
                SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
                    childOffset_.GetX(), arrowLeftOffset - ARROW_HORIZON_P5_OFFSET_Y.ConvertToPx());
            }
            break;
        default:
            break;
    }
    if (arrowBuildplacement != Placement::LEFT_TOP) {
        path += LineTo(childOffset_.GetX(), childOffsetY + radius);
    }
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowTopLeft(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo(arrowOffset - ARROW_REPLACE_START_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset); // P1
    path += LineTo(arrowOffset - ARROW_REPLACE_START_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_START_VERTICAL_P2_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_START_VERTICAL_P4_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(arrowOffset + ARROW_REPLACE_START_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset);
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_START_VERTICAL_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_START_VERTICAL_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        arrowOffset + ARROW_REPLACE_START_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset);
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowTopRight(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo((arrowOffset - ARROW_REPLACE_END_VERTICAL_P1_OFFSET_X.ConvertToPx()) / HALF, childOffset); // P1
    path += LineTo(arrowOffset - ARROW_REPLACE_END_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset);          // P1
    path += LineTo(arrowOffset + ARROW_REPLACE_END_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_END_VERTICAL_P2_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_END_VERTICAL_P4_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(arrowOffset + ARROW_REPLACE_END_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
        arrowOffset - ARROW_REPLACE_END_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset);
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_END_VERTICAL_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset - ARROW_REPLACE_END_VERTICAL_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset);
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowRightTop(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo(childOffset, arrowOffset - ARROW_REPLACE_START_HORIZON_P1_OFFSET_Y.ConvertToPx()); // P1
    path += LineTo(childOffset + ARROW_REPLACE_START_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P2_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        childOffset + ARROW_REPLACE_START_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P4_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(childOffset, arrowOffset + ARROW_REPLACE_START_HORIZON_P5_OFFSET_Y.ConvertToPx()); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO, childOffset,
        arrowOffset - ARROW_REPLACE_START_HORIZON_P1_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        childOffset + ARROW_REPLACE_START_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        childOffset + ARROW_REPLACE_START_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        childOffset, arrowOffset + ARROW_REPLACE_START_HORIZON_P5_OFFSET_Y.ConvertToPx());
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowRightBottom(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo(childOffset, arrowOffset - ARROW_REPLACE_END_HORIZON_P1_OFFSET_Y.ConvertToPx()); // P1
    path += LineTo(childOffset + ARROW_REPLACE_END_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P2_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        childOffset + ARROW_REPLACE_END_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P4_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(childOffset, arrowOffset + ARROW_REPLACE_END_HORIZON_P5_OFFSET_Y.ConvertToPx()); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO, childOffset,
        arrowOffset - ARROW_REPLACE_END_HORIZON_P1_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        childOffset + ARROW_REPLACE_END_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        childOffset + ARROW_REPLACE_END_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        childOffset, arrowOffset + ARROW_REPLACE_END_HORIZON_P5_OFFSET_Y.ConvertToPx());
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowBottomLeft(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo(arrowOffset + ARROW_REPLACE_START_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset); // P1
    path += LineTo(arrowOffset - ARROW_REPLACE_START_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_START_VERTICAL_P4_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_START_VERTICAL_P2_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(arrowOffset - ARROW_REPLACE_START_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
        arrowOffset + ARROW_REPLACE_START_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset);
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_START_VERTICAL_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_START_VERTICAL_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        arrowOffset - ARROW_REPLACE_START_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset);
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowBottomRight(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo(arrowOffset + ARROW_REPLACE_END_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset); // P1
    path += LineTo(arrowOffset + ARROW_REPLACE_END_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_END_VERTICAL_P4_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_END_VERTICAL_P2_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(arrowOffset - ARROW_REPLACE_END_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P1_OFFSET_X.ConvertToPx(), childOffset);
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_END_VERTICAL_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        arrowOffset + ARROW_REPLACE_END_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        childOffset + ARROW_REPLACE_END_VERTICAL_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        arrowOffset - ARROW_REPLACE_END_VERTICAL_P5_OFFSET_X.ConvertToPx(), childOffset);
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowLeftTop(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo(childOffset, arrowOffset + ARROW_REPLACE_START_HORIZON_P1_OFFSET_Y.ConvertToPx()); // P1
    path += LineTo(childOffset - ARROW_REPLACE_START_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P4_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        childOffset - ARROW_REPLACE_START_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P2_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(childOffset, arrowOffset - ARROW_REPLACE_START_HORIZON_P5_OFFSET_Y.ConvertToPx()); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
        childOffset, arrowOffset + ARROW_REPLACE_START_HORIZON_P1_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        childOffset - ARROW_REPLACE_START_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        childOffset - ARROW_REPLACE_START_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset - ARROW_REPLACE_START_HORIZON_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        childOffset, arrowOffset - ARROW_REPLACE_START_HORIZON_P5_OFFSET_Y.ConvertToPx());
    return path;
}

std::string BubbleLayoutAlgorithm::ReplaceArrowLeftBottom(const float arrowOffset, const float childOffset)
{
    std::string path;
    path += LineTo(childOffset, arrowOffset + ARROW_REPLACE_END_HORIZON_P1_OFFSET_Y.ConvertToPx()); // P1
    path += LineTo(childOffset - ARROW_REPLACE_END_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P4_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        childOffset - ARROW_REPLACE_END_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P2_OFFSET_Y.ConvertToPx());                         // P4
    path += LineTo(childOffset, arrowOffset - ARROW_REPLACE_END_HORIZON_P5_OFFSET_Y.ConvertToPx()); // P5
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ZERO,
        childOffset, arrowOffset + ARROW_REPLACE_END_HORIZON_P1_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_ONE,
        childOffset - ARROW_REPLACE_END_HORIZON_P4_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P4_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_TWO,
        childOffset - ARROW_REPLACE_END_HORIZON_P2_OFFSET_X.ConvertToPx(),
        arrowOffset + ARROW_REPLACE_END_HORIZON_P2_OFFSET_Y.ConvertToPx());
    SetArrowOffsetsFromClip(ARROW_OFFSETS_INDEX_THREE,
        childOffset, arrowOffset - ARROW_REPLACE_END_HORIZON_P5_OFFSET_Y.ConvertToPx());
    return path;
}

std::string BubbleLayoutAlgorithm::BuildCornerPath(const Placement& placement, float radius)
{
    std::string path;
    float childOffsetY = childOffset_.GetY();
    switch (placement) {
        case Placement::TOP_LEFT:
            path += ArcTo(radius, radius, 0.0f, 0, childOffset_.GetX() + radius, childOffsetY);
            break;
        case Placement::TOP_RIGHT:
            path += ArcTo(radius, radius, 0.0f, 0, childOffset_.GetX() + childSize_.Width(), childOffsetY + radius);
            break;
        case Placement::BOTTOM_RIGHT:
            path += ArcTo(radius, radius, 0.0f, 0, childOffset_.GetX() + childSize_.Width() - radius,
                childOffsetY + childSize_.Height());
            break;
        case Placement::BOTTOM_LEFT:
            path += ArcTo(radius, radius, 0.0f, 0, childOffset_.GetX(), childOffsetY + childSize_.Height() - radius);
            break;
        default:
            break;
    }
    return path;
}

OffsetF BubbleLayoutAlgorithm::GetChildPosition(
    const SizeF& childSize, const RefPtr<BubbleLayoutProperty>& layoutProp, bool UseArrowOffset)
{
    OffsetF bottomPosition;
    OffsetF topPosition;
    OffsetF topArrowPosition;
    OffsetF bottomArrowPosition;
    OffsetF fitPosition;
    OffsetF originOffset;
    OffsetF originArrowOffset;
    OffsetF childPosition;

    InitArrowTopAndBottomPosition(topArrowPosition, bottomArrowPosition, topPosition, bottomPosition, childSize);
    GetPositionWithPlacement(originOffset, originArrowOffset, childSize, placement_);
    originOffset = originOffset + positionOffset_;
    originArrowOffset += positionOffset_;
    arrowPlacement_ = placement_;

    // Fit popup to screen range.
    ErrorPositionType errorType = GetErrorPositionType(originOffset, childSize);
    if (errorType == ErrorPositionType::NORMAL) {
        arrowPosition_ = originArrowOffset;
        return originOffset;
    }

    if (placement_ == Placement::TOP || placement_ == Placement::TOP_LEFT || placement_ == Placement::TOP_RIGHT) {
        fitPosition = topPosition;
        arrowPosition_ = topArrowPosition;
        arrowPlacement_ = Placement::TOP;
    } else {
        placement_ = Placement::BOTTOM;
        fitPosition = bottomPosition;
        arrowPosition_ = bottomArrowPosition;
        arrowPlacement_ = Placement::BOTTOM;
    }

    childPosition = FitToScreen(fitPosition, childSize);
    if (UseArrowOffset) {
        arrowPosition_.SetX(
            childPosition.GetX() + border_.TopLeftRadius().GetX().ConvertToPx() + BEZIER_WIDTH_HALF.ConvertToPx());
    }

    if (GetErrorPositionType(childPosition, childSize) == ErrorPositionType::NORMAL) {
        return childPosition;
    }

    // Fit popup to opposite position
    fitPosition = fitPosition == topPosition ? bottomPosition : topPosition;
    arrowPosition_ = arrowPlacement_ == Placement::TOP ? bottomArrowPosition : topArrowPosition;
    arrowPlacement_ = arrowPlacement_ == Placement::TOP ? Placement::BOTTOM : Placement::TOP;
    placement_ = arrowPlacement_ == Placement::TOP ? Placement::BOTTOM : Placement::TOP;

    childPosition = FitToScreen(fitPosition, childSize);
    if (UseArrowOffset) {
        arrowPosition_.SetX(
            childPosition.GetX() + border_.TopLeftRadius().GetX().ConvertToPx() + BEZIER_WIDTH_HALF.ConvertToPx());
    }

    if (GetErrorPositionType(childPosition, childSize) == ErrorPositionType::NORMAL) {
        return childPosition;
    }

    // If childPosition is error, adjust bubble to origin position.
    arrowPlacement_ = placement_;
    arrowPosition_ = originArrowOffset;

    return originOffset;
}

void BubbleLayoutAlgorithm::InitArrowTopAndBottomPosition(OffsetF& topArrowPosition, OffsetF& bottomArrowPosition,
    OffsetF& topPosition, OffsetF& bottomPosition, const SizeF& childSize)
{
    auto arrowCenter = targetOffset_.GetX() + targetSize_.Width() / 2.0;
    auto horizonSpacing = static_cast<float>(HORIZON_SPACING_WITH_SCREEN.ConvertToPx());
    double arrowWidth = ARROW_WIDTH.ConvertToPx();
    float radius = borderRadius_.ConvertToPx();
    auto safePosition = horizonSpacing + radius + arrowWidth / 2.0;

    GetPositionWithPlacement(topPosition, topArrowPosition, childSize, Placement::TOP);
    GetPositionWithPlacement(bottomPosition, bottomArrowPosition, childSize, Placement::BOTTOM);

    // move the arrow to safe position while arrow too close to window
    // In order not to separate the bubble from the arrow
    // If ArrowOffset is not set, arrow always point to the middle of the targetNode
    if (arrowCenter < safePosition) {
        topArrowPosition = topArrowPosition + OffsetF(safePosition - arrowCenter, 0);
        bottomArrowPosition = bottomArrowPosition + OffsetF(safePosition - arrowCenter, 0);
    }
    if (arrowCenter > selfSize_.Width() - safePosition) {
        topArrowPosition = topArrowPosition - OffsetF(arrowCenter + safePosition - selfSize_.Width(), 0);
        bottomArrowPosition = bottomArrowPosition - OffsetF(arrowCenter + safePosition - selfSize_.Width(), 0);
    }
}

void BubbleLayoutAlgorithm::GetPositionWithPlacement(
    OffsetF& childPosition, OffsetF& arrowPosition, const SizeF& childSize, Placement placement)
{
    float bubbleSpacing = scaledBubbleSpacing_;
    float marginRight = 0.0f;
    float marginBottom = 0.0f;
    float marginTop = 0.0f;
    float marginLeft = 0.0f;
    float arrowHalfWidth = ARROW_WIDTH.ConvertToPx() / 2.0;
    float radius = borderRadius_.ConvertToPx();
    float targetSpace = targetSpace_.ConvertToPx();
    switch (placement) {
        case Placement::TOP:
            childPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
                targetOffset_.GetY() - childSize.Height() - targetSpace - arrowHeight_);
            arrowPosition = childPosition + OffsetF(std::max(padding_.Left().ConvertToPx(),
            border_.TopLeftRadius().GetX().ConvertToPx()) +
            BEZIER_WIDTH_HALF.ConvertToPx(), childSize.Height() + arrowHeight_);
            break;
        case Placement::TOP_LEFT:
            childPosition = OffsetF(targetOffset_.GetX() - marginRight,
                targetOffset_.GetY() - childSize.Height() - bubbleSpacing - marginBottom - targetSpace - arrowHeight_);
            arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, childSize.Height() + bubbleSpacing);
            break;
        case Placement::TOP_RIGHT:
            childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
                targetOffset_.GetY() - childSize.Height() - targetSpace - bubbleSpacing - marginBottom - arrowHeight_);
            arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, childSize.Height() + bubbleSpacing);
            break;
        case Placement::BOTTOM:
            childPosition = OffsetF(targetOffset_.GetX() + (targetSize_.Width() - childSize.Width()) / 2.0,
                targetOffset_.GetY() + targetSize_.Height() + targetSpace + arrowHeight_);
            arrowPosition = childPosition + OffsetF(std::max(padding_.Left().ConvertToPx(),
            border_.BottomLeftRadius().GetX().ConvertToPx()) +
            BEZIER_WIDTH_HALF.ConvertToPx(), -arrowHeight_);
            break;
        case Placement::BOTTOM_LEFT:
            childPosition = OffsetF(targetOffset_.GetX() - marginRight,
                targetOffset_.GetY() + targetSize_.Height() + targetSpace + bubbleSpacing + marginTop + arrowHeight_);
            arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, -bubbleSpacing);
            break;
        case Placement::BOTTOM_RIGHT:
            childPosition = OffsetF(targetOffset_.GetX() + targetSize_.Width() - childSize.Width() + marginLeft,
                targetOffset_.GetY() + targetSize_.Height() + targetSpace + bubbleSpacing + marginTop + arrowHeight_);
            arrowPosition = childPosition + OffsetF(radius + arrowHalfWidth, -bubbleSpacing);
            break;
        case Placement::LEFT:
            childPosition = OffsetF(
                targetOffset_.GetX() - targetSpace - bubbleSpacing - childSize.Width() - marginRight - arrowHeight_,
                targetOffset_.GetY() + targetSize_.Height() / HALF - childSize.Height() / HALF);
            arrowPosition = childPosition + OffsetF(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::LEFT_TOP:
            childPosition = OffsetF(
                targetOffset_.GetX() - targetSpace - bubbleSpacing - childSize.Width() - marginRight - arrowHeight_,
                targetOffset_.GetY() - marginBottom);
            arrowPosition = childPosition + OffsetF(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::LEFT_BOTTOM:
            childPosition = OffsetF(
                targetOffset_.GetX() - targetSpace - bubbleSpacing - childSize.Width() - marginRight - arrowHeight_,
                targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
            arrowPosition = childPosition + OffsetF(childSize_.Width() + bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::RIGHT:
            childPosition = OffsetF(
                targetOffset_.GetX() + targetSize_.Width() + targetSpace + bubbleSpacing + marginLeft + arrowHeight_,
                targetOffset_.GetY() + targetSize_.Height() / HALF - childSize.Height() / HALF);
            arrowPosition = childPosition + OffsetF(-bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::RIGHT_TOP:
            childPosition = OffsetF(
                targetOffset_.GetX() + targetSize_.Width() + targetSpace + bubbleSpacing + marginLeft + arrowHeight_,
                targetOffset_.GetY() - marginBottom);
            arrowPosition = childPosition + OffsetF(-bubbleSpacing, radius + arrowHalfWidth);
            break;
        case Placement::RIGHT_BOTTOM:
            childPosition = OffsetF(
                targetOffset_.GetX() + targetSize_.Width() + targetSpace + bubbleSpacing + marginLeft + arrowHeight_,
                targetOffset_.GetY() + targetSize_.Height() - childSize.Height() - marginTop);
            arrowPosition = childPosition + OffsetF(-bubbleSpacing, radius + arrowHalfWidth);
            break;
        default:
            break;
    }
}

BubbleLayoutAlgorithm::ErrorPositionType BubbleLayoutAlgorithm::GetErrorPositionType(
    const OffsetF& childOffset, const SizeF& childSize)
{
    auto horizonSpacing = static_cast<float>(HORIZON_SPACING_WITH_SCREEN.ConvertToPx());
    RectF validRegion =
        RectF(OffsetF(horizonSpacing, top_), OffsetF(selfSize_.Width() - horizonSpacing, selfSize_.Height() - bottom_));
    PointF childPoint(childOffset.GetX(), childOffset.GetY());
    if (!validRegion.IsInRegion(childPoint)) {
        return ErrorPositionType::TOP_LEFT_ERROR;
    }
    if (!validRegion.IsInRegion(
            PointF(childOffset.GetX() + childSize.Width(), childOffset.GetY() + childSize.Height()))) {
        return ErrorPositionType::BOTTOM_RIGHT_ERROR;
    }
    return ErrorPositionType::NORMAL;
}

OffsetF BubbleLayoutAlgorithm::FitToScreen(const OffsetF& fitPosition, const SizeF& childSize)
{
    auto validation = GetErrorPositionType(fitPosition, childSize);
    if (validation == ErrorPositionType::NORMAL) {
        return fitPosition;
    }
    OffsetF childPosition = fitPosition;
    auto horizonSpacing = static_cast<float>(HORIZON_SPACING_WITH_SCREEN.ConvertToPx());
    if (validation == ErrorPositionType::TOP_LEFT_ERROR) {
        childPosition.SetX(horizonSpacing);
    } else {
        childPosition.SetX(selfSize_.Width() - childSize.Width() - horizonSpacing);
    }
    return childPosition;
}

void BubbleLayoutAlgorithm::UpdateMarginByWidth()
{
    isGreatWrapperWidth_ = GreatOrEqual(childSize_.Width(), wrapperSize_.Width() - marginStart_ - marginEnd_);
    marginStart_ = isGreatWrapperWidth_ ? 0.0f : marginStart_;
    marginEnd_ = isGreatWrapperWidth_ ? 0.0f : marginEnd_;
}

} // namespace OHOS::Ace::NG
