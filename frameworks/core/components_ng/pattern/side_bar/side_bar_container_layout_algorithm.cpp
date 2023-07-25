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
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"
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
constexpr Dimension CONTROL_BUTTON_PADDING = 12.0_vp;
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
    auto idealSize = CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);

    AdjustMinAndMaxSideBarWidth(layoutWrapper);

    auto parentWidth = idealSize.Width();
    if (needInitRealSideBarWidth_) {
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            GetAllPropertyValue(layoutProperty, parentWidth);
        } else {
            InitRealSideBarWidth(layoutWrapper, parentWidth);
        }
    }

    if (parentWidth >= typeUpdateWidth_) {
        type_ = layoutProperty->GetSideBarContainerType().value_or(SideBarContainerType::EMBED);
    }

    auto type = layoutProperty->GetSideBarContainerType().value_or(SideBarContainerType::EMBED);
    if (type == SideBarContainerType::AUTO) {
        AutoMode(layoutProperty, parentWidth);
    }

    if ((parentWidth < typeUpdateWidth_) && (!layoutProperty->GetShowSideBar().has_value()) &&
        (type_ != SideBarContainerType::OVERLAY)) {
        if (isControlButtonClick_) {
            type_ = SideBarContainerType::OVERLAY;
        } else {
            sideBarStatus_ = SideBarStatus::HIDDEN;
        }
    }
    if (type_ != SideBarContainerType::OVERLAY) {
        AutoChangeSideBarWidth(layoutProperty, parentWidth);
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
    }
}

RefPtr<LayoutWrapper> SideBarContainerLayoutAlgorithm::GetSideBarLayoutWrapper(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        return nullptr;
    }

    int index = 0;
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        index++;
        if (index == INDEX_SIDE_BAR) {
            return (*it);
        }
    }

    return nullptr;
}

void SideBarContainerLayoutAlgorithm::AdjustMinAndMaxSideBarWidth(LayoutWrapper* layoutWrapper)
{
    adjustMinSideBarWidth_ = DEFAULT_MIN_SIDE_BAR_WIDTH;
    adjustMaxSideBarWidth_ = DEFAULT_MAX_SIDE_BAR_WIDTH;
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (pipeline->GetMinPlatformVersion() < PLATFORM_VERSION_TEN) {
        adjustMinSideBarWidth_ = layoutProperty->GetMinSideBarWidth().value_or(DEFAULT_MIN_SIDE_BAR_WIDTH);
        adjustMaxSideBarWidth_ = layoutProperty->GetMaxSideBarWidth().value_or(DEFAULT_MAX_SIDE_BAR_WIDTH);
        if (adjustMinSideBarWidth_ > adjustMaxSideBarWidth_) {
            adjustMinSideBarWidth_ = DEFAULT_MIN_SIDE_BAR_WIDTH;
            adjustMaxSideBarWidth_ = DEFAULT_MAX_SIDE_BAR_WIDTH;
        }
        return;
    }

    auto sideBarLayoutWrapper = GetSideBarLayoutWrapper(layoutWrapper);
    CHECK_NULL_VOID(sideBarLayoutWrapper);

    auto sideBarLayoutProperty = sideBarLayoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(sideBarLayoutProperty);

    auto&& calcConstraint = sideBarLayoutProperty->GetCalcLayoutConstraint();
    if (layoutProperty->GetMinSideBarWidth().has_value()) {
        adjustMinSideBarWidth_ = layoutProperty->GetMinSideBarWidthValue();
    } else if (calcConstraint && calcConstraint->minSize.has_value() &&
               calcConstraint->minSize.value().Width().has_value()) {
        adjustMinSideBarWidth_ = calcConstraint->minSize->Width()->GetDimension();
    }

    if (layoutProperty->GetMaxSideBarWidth().has_value()) {
        adjustMaxSideBarWidth_ = layoutProperty->GetMaxSideBarWidthValue();
    } else if (calcConstraint && calcConstraint->maxSize.has_value() && calcConstraint->maxSize->Width().has_value()) {
        adjustMaxSideBarWidth_ = calcConstraint->maxSize->Width()->GetDimension();
    }

    if (adjustMinSideBarWidth_ > adjustMaxSideBarWidth_) {
        adjustMinSideBarWidth_ = DEFAULT_MIN_SIDE_BAR_WIDTH;
        adjustMaxSideBarWidth_ = DEFAULT_MAX_SIDE_BAR_WIDTH;
    }
}

void SideBarContainerLayoutAlgorithm::GetAllPropertyValue(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, float parentWidth)
{
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    const auto& scaleProperty = constraint->scaleProperty;
    auto realSideBarWidth = layoutProperty->GetSideBarWidth().value_or(-1.0_vp);
    auto minSideBarWidth = layoutProperty->GetMinSideBarWidth().value_or(-1.0_vp);
    auto minContentWidth = layoutProperty->GetMinContentWidth().value_or(-1.0_vp);
    auto maxSideBarWidth = layoutProperty->GetMaxSideBarWidth().value_or(-1.0_vp);

    realSideBarWidth_ = ConvertToPx(realSideBarWidth, scaleProperty, parentWidth).value_or(-1.0f);
    minSideBarWidth_ = ConvertToPx(minSideBarWidth, scaleProperty, parentWidth).value_or(-1.0f);
    minContentWidth_ = ConvertToPx(minContentWidth, scaleProperty, parentWidth).value_or(-1.0f);
    maxSideBarWidth_ = ConvertToPx(maxSideBarWidth, scaleProperty, parentWidth).value_or(-1.0f);

    defaultRealSideBarWidth_ = ConvertToPx(DEFAULT_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);
    defaultMinSideBarWidth_ = ConvertToPx(DEFAULT_MIN_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);
    defaultMaxSideBarWidth_ = ConvertToPx(DEFAULT_MAX_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);
    defaultMinContentWidth_ = ConvertToPx(DEFAULT_MIN_CONTENT_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);

    MeasureTypeUpdateWidth();
    if (minContentWidth_ < 0.0f) {
        minContentWidth_ = 0.0f;
    }
    InitSideBarWidth(parentWidth);
    MeasureRealSideBarWidth(parentWidth);

    auto sideBarContainerPattern = AceType::DynamicCast<SideBarContainerPattern>(pattern_.Upgrade());
    sideBarContainerPattern->SetMinSideBarWidth(minSideBarWidth_);
    sideBarContainerPattern->SetMaxSideBarWidth(maxSideBarWidth_);
    sideBarContainerPattern->SetMinContentWidth(minContentWidth_);
    sideBarContainerPattern->SetTypeUpdateWidth(typeUpdateWidth_);
}

void SideBarContainerLayoutAlgorithm::MeasureTypeUpdateWidth()
{
    if (minSideBarWidth_ >= 0.0f && minContentWidth_ >= 0.0f) {
        typeUpdateWidth_ = minSideBarWidth_ + minContentWidth_;
        return;
    } else if (minSideBarWidth_ >= 0.0f) {
        typeUpdateWidth_ = minSideBarWidth_ + defaultMinContentWidth_;
    } else if (minContentWidth_ >= 0.0f) {
        typeUpdateWidth_ = minContentWidth_ + defaultMinSideBarWidth_;
    } else {
        typeUpdateWidth_ = defaultMinSideBarWidth_ + defaultMinContentWidth_;
    }
    if (typeUpdateWidth_ < defaultMinSideBarWidth_ + defaultMinContentWidth_) {
        typeUpdateWidth_ = defaultMinSideBarWidth_ + defaultMinContentWidth_;
    }
}

void SideBarContainerLayoutAlgorithm::InitSideBarWidth(float parentWidth)
{
    if (minSideBarWidth_ >= parentWidth) {
        minSideBarWidth_ = parentWidth;
        maxSideBarWidth_ = parentWidth;
        realSideBarWidth_ = parentWidth;
        minContentWidth_ = 0.0f;
        return;
    }

    if (maxSideBarWidth_ >= parentWidth) {
        maxSideBarWidth_ = parentWidth;
        if (realSideBarWidth_ <= minSideBarWidth_) {
            realSideBarWidth_ = minSideBarWidth_;
        } else if (realSideBarWidth_ >= maxSideBarWidth_) {
            realSideBarWidth_ = maxSideBarWidth_;
        }
        return;
    }
    if (minSideBarWidth_ >= 0.0f && maxSideBarWidth_ >= 0.0f) {
        if (minSideBarWidth_ >= maxSideBarWidth_) {
            maxSideBarWidth_ = minSideBarWidth_;
            realSideBarWidth_ = minSideBarWidth_;
            return;
        }
    }

    if (realSideBarWidth_ < 0.0f) {
        return;
    }
    if (realSideBarWidth_ <= minSideBarWidth_) {
        realSideBarWidth_ = minSideBarWidth_;
        return;
    } else if (realSideBarWidth_ >= maxSideBarWidth_ && maxSideBarWidth_ >= 0) {
        realSideBarWidth_ = maxSideBarWidth_;
        return;
    } else if (realSideBarWidth_ >= parentWidth) {
        realSideBarWidth_ = parentWidth;
    }
}

void SideBarContainerLayoutAlgorithm::MeasureRealSideBarWidth(float parentWidth)
{
    if (minSideBarWidth_ < 0.0f) {
        if (realSideBarWidth_ >= 0.0f) {
            minSideBarWidth_ = realSideBarWidth_;
        } else if (maxSideBarWidth_ >= 0.0f) {
            minSideBarWidth_ = maxSideBarWidth_;
        } else {
            minSideBarWidth_ = defaultMinSideBarWidth_;
        }
        if (minSideBarWidth_ >= defaultMinSideBarWidth_) {
            minSideBarWidth_ = defaultMinSideBarWidth_;
        }
        if (minSideBarWidth_ >= parentWidth) {
            minSideBarWidth_ = parentWidth;
            maxSideBarWidth_ = parentWidth;
            realSideBarWidth_ = parentWidth;
            return;
        }
    }

    if (maxSideBarWidth_ < 0.0f) {
        maxSideBarWidth_ = defaultMaxSideBarWidth_;
        if (maxSideBarWidth_ <= realSideBarWidth_) {
            maxSideBarWidth_ = realSideBarWidth_;
        } else if (maxSideBarWidth_ <= minSideBarWidth_) {
            maxSideBarWidth_ = minSideBarWidth_;
            realSideBarWidth_ = minSideBarWidth_;
            return;
        }
    }

    if (realSideBarWidth_ < 0.0f) {
        realSideBarWidth_ = defaultRealSideBarWidth_;
        if (realSideBarWidth_ <= minSideBarWidth_) {
            realSideBarWidth_ = minSideBarWidth_;
        } else if (realSideBarWidth_ >= maxSideBarWidth_) {
            realSideBarWidth_ = maxSideBarWidth_;
        }
    }
}

void SideBarContainerLayoutAlgorithm::InitRealSideBarWidth(LayoutWrapper* layoutWrapper, float parentWidth)
{
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;
    auto sideBarWidth = layoutProperty->GetSideBarWidth().value_or(DEFAULT_SIDE_BAR_WIDTH);
    auto sideBarWidthPx = ConvertToPx(sideBarWidth, scaleProperty, parentWidth).value_or(0);
    auto minSideBarWidthPx = ConvertToPx(adjustMinSideBarWidth_, scaleProperty, parentWidth).value_or(0);
    auto maxSideBarWidthPx = ConvertToPx(adjustMaxSideBarWidth_, scaleProperty, parentWidth).value_or(0);
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
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, float parentWidth)
{
    /*
     * When reducing component width, first reduce the width of the content to minContentWidth,
     * and then reduce the width of the sidebar
     */
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    const auto& scaleProperty = constraint->scaleProperty;
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);
    auto dividerStrokeWidthPx = ConvertToPx(dividerStrokeWidth, scaleProperty, parentWidth).value_or(1);

    if ((realSideBarWidth_ + minContentWidth_ + dividerStrokeWidthPx) >= parentWidth) {
        realSideBarWidth_ = parentWidth - minContentWidth_ - dividerStrokeWidthPx;
    }
    if (realSideBarWidth_ <= minSideBarWidth_) {
        realSideBarWidth_ = minSideBarWidth_;
    }
}

void SideBarContainerLayoutAlgorithm::AutoMode(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, float parentWidth)
{
    /*
     * SideBarContainer AUTO mode:
     * When the component width is greater or equal to minNavBarWidth+minContentWidth,
     * it is displayed in Embed mode;
     * When the component width is smaller than minNavBarWidth+minContentWidth,
     * it is displayed in Overlay mode.
     */
    if (parentWidth < typeUpdateWidth_) {
        type_ = SideBarContainerType::OVERLAY;
    } else {
        type_ = SideBarContainerType::EMBED;
    }
}

void SideBarContainerLayoutAlgorithm::MeasureSideBar(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<LayoutWrapper>& sideBarLayoutWrapper)
{
    auto constraint = layoutProperty->GetLayoutConstraint();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        auto sideBarLayoutProperty = sideBarLayoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(sideBarLayoutProperty);
        auto&& calcConstraint = sideBarLayoutProperty->GetCalcLayoutConstraint();
        if (calcConstraint) {
            if (layoutProperty->GetMaxSideBarWidth().has_value() && calcConstraint->maxSize.has_value()) {
                auto maxWidth = adjustMaxSideBarWidth_.ConvertToPx();
                auto maxHeight = calcConstraint->maxSize->Height();
                calcConstraint->UpdateMaxSizeWithCheck(CalcSize(CalcLength(maxWidth), maxHeight));
            }

            if (layoutProperty->GetMinSideBarWidth().has_value() && calcConstraint->minSize.has_value()) {
                auto minWidth = adjustMinSideBarWidth_.ConvertToPx();
                auto minHeight = calcConstraint->minSize->Height();
                calcConstraint->UpdateMinSizeWithCheck(CalcSize(CalcLength(minWidth), minHeight));
            }
        }
    }

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
    if (contentWidth < minContentWidth_) {
        contentWidth = minContentWidth_;
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

    auto controlButtonWidth = controlImageWidth_ + CONTROL_BUTTON_PADDING * 2;
    auto controlButtonHeight = controlImageHeight_ + CONTROL_BUTTON_PADDING * 2;
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

    CHECK_NULL_VOID(layoutWrapper->GetGeometryNode());
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;

    auto controlImageLeft = layoutProperty->GetControlButtonLeft().value_or(DEFAULT_CONTROL_BUTTON_LEFT);
    auto controlImageTop = layoutProperty->GetControlButtonTop().value_or(DEFAULT_CONTROL_BUTTON_TOP);

    if (LessNotEqual(controlImageLeft.Value(), 0.0)) {
        controlImageLeft = DEFAULT_CONTROL_BUTTON_LEFT;
    }

    if (LessNotEqual(controlImageTop.Value(), 0.0)) {
        controlImageTop = DEFAULT_CONTROL_BUTTON_TOP;
    }
    auto controlButtonLeft = controlImageLeft - CONTROL_BUTTON_PADDING;
    auto controlButtonTop = controlImageTop - CONTROL_BUTTON_PADDING;

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
    auto controlButtonWidth = controlImageWidth_ + CONTROL_BUTTON_PADDING * 2;

    if ((sideBarPosition == SideBarPosition::END) &&             // sideBarPosition is End, other pass
        (!layoutProperty->GetControlButtonLeft().has_value())) { // origin value has not set
        auto defaultControlButtonLeft = DEFAULT_CONTROL_BUTTON_LEFT - CONTROL_BUTTON_PADDING;
        auto defaultControlButtonLeftPx = ConvertToPx(defaultControlButtonLeft, scaleProperty, parentWidth).value_or(0);
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

    CHECK_NULL_VOID(layoutWrapper->GetGeometryNode());
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
                dividerOffsetX = parentWidth;
            }
            break;
        case SideBarStatus::CHANGING:
            if (sideBarPosition == SideBarPosition::START) {
                dividerOffsetX = realSideBarWidth_ + currentOffset_;
            } else {
                dividerOffsetX = parentWidth - realDividerWidth_ + currentOffset_;
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
        sideBarPosition = (sideBarPosition == SideBarPosition::START) ? SideBarPosition::END : SideBarPosition::START;
    }
    return sideBarPosition;
}
} // namespace OHOS::Ace::NG
