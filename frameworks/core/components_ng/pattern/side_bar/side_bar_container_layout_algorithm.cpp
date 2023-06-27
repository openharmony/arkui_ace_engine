/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/side_bar/side_bar_container_layout_algorithm.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t DEFAULT_MIN_CHILDREN_SIZE = 3;
constexpr Dimension DEFAULT_CONTROL_BUTTON_LEFT = 16.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_END_MARGIN = 0.0_vp;

constexpr static int INDEX_CONTRON_BUTTON = 1;
constexpr static int INDEX_DIVIDER = 2;
constexpr static int INDEX_SIDE_BAR = 3;
constexpr static int32_t PLATFORM_VERSION_TEN = 10;
static Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
static Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
static Dimension DEFAULT_MIN_CONTENT_WIDTH = 0.0_vp;
static Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
static Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
} // namespace

void SideBarContainerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    UpdateDefaultValueByVersion();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        LOGE("SideBarContainerLayoutAlgorithm::Measure, children is less than 3.");
        return;
    }
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    const auto& scaleProperty = constraint->scaleProperty;
    auto idealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);

    auto parentWidth = idealSize.Width();
    if (needInitRealSideBarWidth_) {
        InitRealSideBarWidth(layoutWrapper, parentWidth);
    }

    auto minSideBarWidth = layoutProperty->GetMinSideBarWidth().value_or(DEFAULT_MIN_SIDE_BAR_WIDTH);
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);
    auto minSideBarWidthPx = ConvertToPx(minSideBarWidth, scaleProperty, parentWidth).value_or(0);
    auto dividerStrokeWidthPx = ConvertToPx(dividerStrokeWidth, scaleProperty, parentWidth).value_or(1);
    AutoChangeSideBarWidth(layoutWrapper, parentWidth, minSideBarWidthPx, dividerStrokeWidthPx);

    if (type_ == SideBarContainerType::AUTO) {
        AutoMode(layoutWrapper, parentWidth, minSideBarWidthPx, dividerStrokeWidthPx);
    }

    /*
     * child inverted order is: controlbutton, divider, sidebar, contentxxx, ..., content2, content1
     * content only display the first one, use itor from end
     */
    int index = 0;
    RefPtr<LayoutWrapper> dividerLayoutWrapper = nullptr;
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        index++;
        if (index == INDEX_CONTRON_BUTTON) {
            auto imgLayoutWrapper = (*it);
            MeasureControlButton(layoutProperty, imgLayoutWrapper, parentWidth);
        } else if (index == INDEX_DIVIDER) {
            dividerLayoutWrapper = (*it);
        } else if (index == INDEX_SIDE_BAR) {
            auto sideBarLayoutWrapper = (*it);
            MeasureSideBar(layoutProperty, sideBarLayoutWrapper);
        } else { // other break
            continue;
        }
    }

    if (dividerLayoutWrapper) {
        MeasureDivider(layoutProperty, dividerLayoutWrapper, parentWidth);
    }

    if (children.size() > DEFAULT_MIN_CHILDREN_SIZE) { // when sidebar only add one component, content is not display
        auto contentLayoutWrapper = children.front();
        MeasureSideBarContent(layoutProperty, contentLayoutWrapper, parentWidth);
    }
}

void SideBarContainerLayoutAlgorithm::UpdateDefaultValueByVersion()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        DEFAULT_SIDE_BAR_WIDTH = 240.0_vp;
        DEFAULT_MIN_SIDE_BAR_WIDTH = 240.0_vp;
        DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;
        DEFAULT_CONTROL_BUTTON_WIDTH = 24.0_vp;
        DEFAULT_CONTROL_BUTTON_HEIGHT = 24.0_vp;
    }
}

void SideBarContainerLayoutAlgorithm::InitRealSideBarWidth(LayoutWrapper* layoutWrapper, float parentWidth)
{
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;
    auto sideBarWidth = layoutProperty->GetSideBarWidth().value_or(DEFAULT_SIDE_BAR_WIDTH);
    auto minSideBarWidth = layoutProperty->GetMinSideBarWidth().value_or(DEFAULT_MIN_SIDE_BAR_WIDTH);
    auto maxSideBarWidth = layoutProperty->GetMaxSideBarWidth().value_or(DEFAULT_MAX_SIDE_BAR_WIDTH);
    auto sideBarWidthPx = ConvertToPx(sideBarWidth, scaleProperty, parentWidth).value_or(0);
    auto minSideBarWidthPx = ConvertToPx(minSideBarWidth, scaleProperty, parentWidth).value_or(0);
    auto maxSideBarWidthPx = ConvertToPx(maxSideBarWidth, scaleProperty, parentWidth).value_or(0);
    if (minSideBarWidthPx > maxSideBarWidthPx) {
        minSideBarWidthPx = ConvertToPx(DEFAULT_MIN_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(0);
        maxSideBarWidthPx = ConvertToPx(DEFAULT_MAX_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(0);
    }

    if (sideBarWidthPx <= minSideBarWidthPx) {
        realSideBarWidth_ = minSideBarWidthPx;
    } else if (sideBarWidthPx >= maxSideBarWidthPx) {
        realSideBarWidth_ = maxSideBarWidthPx;
    } else {
        realSideBarWidth_ = sideBarWidthPx;
    }
}

void SideBarContainerLayoutAlgorithm::AutoChangeSideBarWidth(
    LayoutWrapper* layoutWrapper, float parentWidth, float minSideBarWidthPx, float dividerStrokeWidthPx)
{
    /*
     * When reducing component width, first reduce the width of the content to minContentWidth,
     * and then reduce the width of the sidebar
     */
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    const auto& scaleProperty = constraint->scaleProperty;
    auto minContentWidth = layoutProperty->GetMinContentWidth().value_or(DEFAULT_MIN_CONTENT_WIDTH);
    auto minContentWidthPx = ConvertToPx(minContentWidth, scaleProperty, parentWidth).value_or(0);
    minContentWidth_ = minContentWidthPx;

    if ((realSideBarWidth_ + minContentWidth_ + dividerStrokeWidthPx) >= parentWidth) {
        realSideBarWidth_ = parentWidth - minContentWidth_- dividerStrokeWidthPx;
    }
    if (realSideBarWidth_ <= minSideBarWidthPx) {
        realSideBarWidth_ = minSideBarWidthPx;
    }
}

void SideBarContainerLayoutAlgorithm::AutoMode(
    LayoutWrapper* layoutWrapper, float parentWidth, float minSideBarWidthPx, float dividerStrokeWidthPx)
{
    /*
     * SideBarContainer AUTO mode:
     * When the component width is greater than or equal to minNavBarWidth+minContentWidth,
     * it is displayed in Embed mode;
     * When the component width is smaller than minNavBarWidth+minContentWidth,
     * it is displayed in Overlay mode.
     */
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (parentWidth < (minSideBarWidthPx + minContentWidth_ + dividerStrokeWidthPx)) {
        type_ = SideBarContainerType::OVERLAY;
    } else {
        type_ = SideBarContainerType::EMBED;
    }
}

void SideBarContainerLayoutAlgorithm::MeasureSideBar(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<LayoutWrapper>& sideBarLayoutWrapper)
{
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto sideBarIdealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    sideBarIdealSize.SetWidth(realSideBarWidth_);
    auto sideBarConstraint = layoutProperty->CreateChildConstraint();
    sideBarConstraint.selfIdealSize = OptionalSizeF(sideBarIdealSize);

    realSideBarHeight_ = sideBarIdealSize.Height();
    sideBarLayoutWrapper->Measure(sideBarConstraint);
}

void SideBarContainerLayoutAlgorithm::MeasureDivider(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
    const RefPtr<LayoutWrapper>& dividerLayoutWrapper, float parentWidth)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(dividerLayoutWrapper);
    auto constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto scaleProperty = constraint->scaleProperty;
    auto dividerIdealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);

    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);
    auto dividerStartMargin = layoutProperty->GetDividerStartMargin().value_or(DEFAULT_DIVIDER_START_MARGIN);
    auto dividerEndMargin = layoutProperty->GetDividerEndMargin().value_or(DEFAULT_DIVIDER_END_MARGIN);

    auto dividerStrokeWidthPx = ConvertToPx(dividerStrokeWidth, scaleProperty, parentWidth).value_or(1);
    auto dividerStartMarginPx = ConvertToPx(dividerStartMargin, scaleProperty, parentWidth).value_or(0);
    auto dividerEndMarginPx = ConvertToPx(dividerEndMargin, scaleProperty, parentWidth).value_or(0);

    dividerIdealSize.SetWidth(dividerStrokeWidthPx);
    dividerIdealSize.SetHeight(realSideBarHeight_ - dividerStartMarginPx - dividerEndMarginPx);
    realDividerWidth_ = dividerStrokeWidthPx;

    auto dividerLayoutConstraint = layoutProperty->CreateChildConstraint();
    dividerLayoutConstraint.selfIdealSize = OptionalSizeF(dividerIdealSize);
    dividerLayoutWrapper->Measure(dividerLayoutConstraint);
}

void SideBarContainerLayoutAlgorithm::MeasureSideBarContent(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<LayoutWrapper>& contentLayoutWrapper,
    float parentWidth)
{
    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto contentWidth = parentWidth;

    if (type_ == SideBarContainerType::EMBED) {
        if (sideBarStatus_ == SideBarStatus::SHOW) {
            contentWidth -= (realSideBarWidth_ + realDividerWidth_);
        } else if (sideBarStatus_ == SideBarStatus::CHANGING) {
            contentWidth = (sideBarPosition == SideBarPosition::START)
                               ? (parentWidth - realSideBarWidth_ - realDividerWidth_ - currentOffset_)
                               : (parentWidth - realDividerWidth_ + currentOffset_);
        }
    }

    auto contentIdealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    contentIdealSize.SetWidth(contentWidth);
    auto contentConstraint = layoutProperty->CreateChildConstraint();
    contentConstraint.selfIdealSize = OptionalSizeF(contentIdealSize);
    contentLayoutWrapper->Measure(contentConstraint);
}

void SideBarContainerLayoutAlgorithm::MeasureControlButton(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
    const RefPtr<LayoutWrapper>& buttonLayoutWrapper, float parentWidth)
{
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;

    auto controlButtonWidth = layoutProperty->GetControlButtonWidth().value_or(DEFAULT_CONTROL_BUTTON_WIDTH);
    auto controlButtonHeight = layoutProperty->GetControlButtonHeight().value_or(DEFAULT_CONTROL_BUTTON_HEIGHT);
    auto controlButtonWidthPx = ConvertToPx(controlButtonWidth, scaleProperty, parentWidth).value_or(0);
    auto controlButtonHeightPx = ConvertToPx(controlButtonHeight, scaleProperty, parentWidth).value_or(0);

    auto controlButtonLayoutConstraint = layoutProperty->CreateChildConstraint();
    controlButtonLayoutConstraint.selfIdealSize.SetWidth(controlButtonWidthPx);
    controlButtonLayoutConstraint.selfIdealSize.SetHeight(controlButtonHeightPx);
    buttonLayoutWrapper->Measure(controlButtonLayoutConstraint);
}

void SideBarContainerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        LOGE("SideBarContainerLayoutAlgorithm::Measure, children is less than 3.");
        return;
    }

    int index = 0;
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        index++;
        if (index == INDEX_CONTRON_BUTTON) {
            auto controlButtonLayoutWrapper = (*it);
            LayoutControlButton(layoutWrapper, controlButtonLayoutWrapper);
        } else if (index == INDEX_DIVIDER) {
            auto dividerLayoutWrapper = (*it);
            LayoutDivider(layoutWrapper, dividerLayoutWrapper);
        } else if (index == INDEX_SIDE_BAR) {
            auto sideBarLayoutWrapper = (*it);
            LayoutSideBar(layoutWrapper, sideBarLayoutWrapper);
        } else { // other break
            break;
        }
    }

    if (children.size() > DEFAULT_MIN_CHILDREN_SIZE) { // when sidebar only add one component, content is not display
        auto contentLayoutWrapper = children.front();
        LayoutSideBarContent(layoutWrapper, contentLayoutWrapper);
    }
}

void SideBarContainerLayoutAlgorithm::LayoutControlButton(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& buttonLayoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    CHECK_NULL_VOID (layoutWrapper->GetGeometryNode());
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;

    auto controlButtonLeft = layoutProperty->GetControlButtonLeft().value_or(DEFAULT_CONTROL_BUTTON_LEFT);
    auto controlButtonTop = layoutProperty->GetControlButtonTop().value_or(DEFAULT_CONTROL_BUTTON_TOP);
    if (LessNotEqual(controlButtonLeft.Value(), 0.0)) {
        controlButtonLeft = DEFAULT_CONTROL_BUTTON_LEFT;
    }

    if (LessNotEqual(controlButtonTop.Value(), 0.0)) {
        controlButtonTop = DEFAULT_CONTROL_BUTTON_TOP;
    }

    auto controlButtonLeftPx = ConvertToPx(controlButtonLeft, scaleProperty, parentWidth).value_or(0);
    auto controlButtonTopPx = ConvertToPx(controlButtonTop, scaleProperty, parentWidth).value_or(0);

    /*
     * Control buttion left position need to special handle:
     *   1. when sideBarPosition set to END and controlButtonLeft do not set in ButtonStyle
     *   control button need to move follow the sidebar to the right
     *   2. when sideBarPosition set to START or controlButtonLeft has set by user
     *   control button keep before handle
     *   3. if the controlButtonLeft has set, whether sideBarPosition set to START or END
     *   control button offset the left, if value invalid set to default 16vp
     */
    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);
    auto controlButtonWidth = layoutProperty->GetControlButtonWidth().value_or(DEFAULT_CONTROL_BUTTON_WIDTH);

    if ((sideBarPosition == SideBarPosition::END) && // sideBarPosition is End, other pass
        (!layoutProperty->GetControlButtonLeft().has_value())) { // origin value has not set
        auto defaultControlButtonLeftPx = ConvertToPx(DEFAULT_CONTROL_BUTTON_LEFT,
            scaleProperty, parentWidth).value_or(0);
        auto controlButtonWidthPx = ConvertToPx(controlButtonWidth, scaleProperty, parentWidth).value_or(0);
        controlButtonLeftPx = parentWidth - defaultControlButtonLeftPx - controlButtonWidthPx;
    }

    auto imgOffset = OffsetF(controlButtonLeftPx, controlButtonTopPx);
    buttonLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(imgOffset);
    buttonLayoutWrapper->Layout();
}

void SideBarContainerLayoutAlgorithm::LayoutSideBar(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& sideBarLayoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    CHECK_NULL_VOID (layoutWrapper->GetGeometryNode());
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);
    float sideBarOffsetX = 0.0f;

    switch (sideBarStatus_) {
        case SideBarStatus::SHOW:
            if (sideBarPosition == SideBarPosition::END) {
                sideBarOffsetX = parentWidth - realSideBarWidth_;
            }
            break;
        case SideBarStatus::HIDDEN:
            if (sideBarPosition == SideBarPosition::START) {
                sideBarOffsetX = -(realSideBarWidth_ + realDividerWidth_);
            } else {
                sideBarOffsetX = parentWidth;
            }
            break;
        case SideBarStatus::CHANGING:
            if (sideBarPosition == SideBarPosition::START) {
                sideBarOffsetX = currentOffset_;
            } else {
                sideBarOffsetX = parentWidth + currentOffset_;
            }
            break;
        default:
            break;
    }

    sideBarOffset_ = OffsetF(sideBarOffsetX, 0.0f);
    sideBarLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(sideBarOffset_);
    sideBarLayoutWrapper->Layout();
}

void SideBarContainerLayoutAlgorithm::LayoutSideBarContent(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& contentLayoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);

    float contentOffsetX = 0.0f;
    if (type_ == SideBarContainerType::EMBED && sideBarPosition == SideBarPosition::START) {
        if (sideBarStatus_ == SideBarStatus::SHOW) {
            contentOffsetX = realSideBarWidth_ + realDividerWidth_;
        } else if (sideBarStatus_ == SideBarStatus::CHANGING) {
            contentOffsetX = realSideBarWidth_ + realDividerWidth_ + currentOffset_;
        }
    }

    auto contentOffset = OffsetF(contentOffsetX, 0.0f);
    contentLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(contentOffset);
    contentLayoutWrapper->Layout();
}

void SideBarContainerLayoutAlgorithm::LayoutDivider(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& dividerLayoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(dividerLayoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);

    CHECK_NULL_VOID(layoutWrapper->GetGeometryNode());
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto scaleProperty = constraint->scaleProperty;

    auto dividerStartMargin = layoutProperty->GetDividerStartMargin().value_or(DEFAULT_DIVIDER_START_MARGIN);
    auto dividerStartMarginPx = ConvertToPx(dividerStartMargin, scaleProperty, parentWidth).value_or(0);

    float dividerOffsetX = 0.0f;
    switch (sideBarStatus_) {
        case SideBarStatus::SHOW:
            if (sideBarPosition == SideBarPosition::START) {
                dividerOffsetX = realSideBarWidth_;
            } else {
                dividerOffsetX = parentWidth - realSideBarWidth_ - realDividerWidth_;
            }
            break;
        case SideBarStatus::HIDDEN:
            if (sideBarPosition == SideBarPosition::START) {
                dividerOffsetX = -realDividerWidth_;
            } else {
                dividerOffsetX = parentWidth + realSideBarWidth_;
            }
            break;
        case SideBarStatus::CHANGING:
            if (sideBarPosition == SideBarPosition::START) {
                dividerOffsetX = realSideBarWidth_ + currentOffset_;
            } else {
                dividerOffsetX = parentWidth - realDividerWidth_ + currentOffset_ ;
            }
            break;
        default:
            break;
    }

    auto dividerOffset = OffsetF(dividerOffsetX, dividerStartMarginPx);
    CHECK_NULL_VOID(dividerLayoutWrapper->GetGeometryNode());
    dividerLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(dividerOffset);
    dividerLayoutWrapper->Layout();
}

SideBarPosition SideBarContainerLayoutAlgorithm::GetSideBarPositionWithRtl(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty)
{
    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    if (layoutProperty->GetLayoutDirection() == TextDirection::RTL) {
        sideBarPosition = (sideBarPosition == SideBarPosition::START)
                            ? SideBarPosition::END : SideBarPosition::START;
    }
    return sideBarPosition;
}
} // namespace OHOS::Ace::NG
