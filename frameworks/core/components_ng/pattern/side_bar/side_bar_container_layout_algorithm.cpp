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

#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"

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
    autoHide_ = false;
    UpdateDefaultValueByVersion();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild(layoutWrapper->IsActive());
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        return;
    }
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto idealSize = pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN ?
    CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL,
        layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT)).ConvertToSizeT() :
    CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);

    AdjustMinAndMaxSideBarWidth(layoutWrapper);

    auto parentWidth = idealSize.Width();
    realSideBarWidth_ = ConvertToPx(realSideBarWidthDimension_, constraint->scaleProperty, parentWidth).value_or(-1.0f);
    if (needInitRealSideBarWidth_ || NearZero(realSideBarWidth_)) {
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
        } else if (layoutProperty->GetAutoHide().value_or(true)) {
            sideBarStatus_ = SideBarStatus::HIDDEN;
            autoHide_ = true;
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

    if (realSideBarWidthDimension_.Unit() == DimensionUnit::PERCENT) {
        realSideBarWidthDimension_ = NearZero(parentWidth)
                                         ? Dimension(0.0, DimensionUnit::PERCENT)
                                         : Dimension(realSideBarWidth_ / parentWidth, DimensionUnit::PERCENT);
    } else {
        realSideBarWidthDimension_ = Dimension(realSideBarWidth_, DimensionUnit::PX);
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
    const auto& children = layoutWrapper->GetAllChildrenWithBuild(layoutWrapper->IsActive());
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
    if (preSideBarWidth_.IsValid()) {
        realSideBarWidth_ = ConvertToPx(preSideBarWidth_, scaleProperty, parentWidth).value_or(-1.0f);
    }

    minSideBarWidth_ = ConvertToPx(minSideBarWidth, scaleProperty, parentWidth).value_or(-1.0f);
    minContentWidth_ = ConvertToPx(minContentWidth, scaleProperty, parentWidth).value_or(-1.0f);
    maxSideBarWidth_ = ConvertToPx(maxSideBarWidth, scaleProperty, parentWidth).value_or(-1.0f);

    defaultRealSideBarWidth_ = ConvertToPx(DEFAULT_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);
    defaultMinSideBarWidth_ = ConvertToPx(DEFAULT_MIN_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);
    defaultMaxSideBarWidth_ = ConvertToPx(DEFAULT_MAX_SIDE_BAR_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);
    defaultMinContentWidth_ = ConvertToPx(DEFAULT_MIN_CONTENT_WIDTH, scaleProperty, parentWidth).value_or(-1.0f);

    MeasureTypeUpdateWidth();
    minContentWidth_ = std::max(0.0f, minContentWidth_);
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
    auto sideBarIdealSize = PipelineContext::GetCurrentContext()->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN ?
        CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL,
        layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT)).ConvertToSizeT():
        CreateIdealSize(constraint.value(), Axis::HORIZONTAL,
        layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    realSideBarHeight_ = sideBarIdealSize.Height() - padding.top.value_or(0) - padding.bottom.value_or(0);
    if (LessNotEqual(realSideBarHeight_, 0.0f)) {
        realSideBarHeight_ = 0.0f;
    }
    sideBarIdealSize.SetWidth(realSideBarWidth_);
    sideBarIdealSize.SetHeight(realSideBarHeight_);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        auto sideBarLayoutProperty = sideBarLayoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(sideBarLayoutProperty);
        auto&& calcConstraint = sideBarLayoutProperty->GetCalcLayoutConstraint();
        if (calcConstraint) {
            if (calcConstraint->maxSize.has_value()) {
                auto maxWidth = CalcLength(realSideBarWidth_);
                auto maxHeight = CalcLength(realSideBarHeight_);
                calcConstraint->UpdateMaxSizeWithCheck(CalcSize(maxWidth, maxHeight));
            }

            if (calcConstraint->minSize.has_value()) {
                auto minWidth = CalcLength(realSideBarWidth_);
                auto minHeight = CalcLength(realSideBarHeight_);
                calcConstraint->UpdateMinSizeWithCheck(CalcSize(minWidth, minHeight));
            }
        }
    }

    auto sideBarConstraint = layoutProperty->CreateChildConstraint();
    sideBarConstraint.selfIdealSize = OptionalSizeF(sideBarIdealSize);

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
    auto dividerIdealSize = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) ?
    CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL,
        layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT)).ConvertToSizeT() :
    CreateIdealSize(
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
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto contentWidth = parentWidth - padding.left.value_or(0) - padding.right.value_or(0);

    if (type_ == SideBarContainerType::EMBED) {
        if (sideBarStatus_ == SideBarStatus::SHOW) {
            contentWidth -= (realSideBarWidth_ + realDividerWidth_);
        } else if (sideBarStatus_ == SideBarStatus::CHANGING) {
            contentWidth = (sideBarPosition == SideBarPosition::START)
                               ? (contentWidth - realSideBarWidth_ - realDividerWidth_ - currentOffset_)
                               : (contentWidth - realDividerWidth_ + currentOffset_);
        }
    }
    contentWidth = std::max(contentWidth, minContentWidth_);

    auto contentIdealSize = PipelineContext::GetCurrentContext()->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN ?
    CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL,
        layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT)).ConvertToSizeT() :
    CreateIdealSize(
        constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    contentIdealSize.SetWidth(contentWidth);
    contentIdealSize.SetHeight(realSideBarHeight_);
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
    const auto& children = layoutWrapper->GetAllChildrenWithBuild(layoutWrapper->IsActive());
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
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
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
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
    controlButtonLeftPx += padding.left.value_or(0);
    controlButtonTopPx += padding.top.value_or(0);
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
        auto defaultControlButtonLeftPx = ConvertToPx(defaultControlButtonLeft, scaleProperty, parentWidth).value_or(0)
            + padding.right.value_or(0);
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
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    float sideBarOffsetX = padding.left.value_or(0);
    float sideBarOffsetY = padding.top.value_or(0);

    switch (sideBarStatus_) {
        case SideBarStatus::SHOW:
            if (sideBarPosition == SideBarPosition::END) {
                sideBarOffsetX = parentWidth - realSideBarWidth_ - padding.right.value_or(0);
            }
            break;
        case SideBarStatus::HIDDEN:
            if (sideBarPosition == SideBarPosition::START) {
                sideBarOffsetX = -(realSideBarWidth_ + realDividerWidth_ - padding.left.value_or(0));
            } else {
                sideBarOffsetX = parentWidth + realDividerWidth_ - padding.right.value_or(0);
            }
            break;
        case SideBarStatus::CHANGING:
            if (sideBarPosition == SideBarPosition::START) {
                sideBarOffsetX = currentOffset_ + padding.left.value_or(0);
            } else {
                sideBarOffsetX = parentWidth - padding.right.value_or(0) + currentOffset_;
            }
            break;
        default:
            break;
    }

    sideBarOffset_ = OffsetF(sideBarOffsetX, sideBarOffsetY);
    sideBarLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(sideBarOffset_);
    sideBarLayoutWrapper->Layout();
}

void SideBarContainerLayoutAlgorithm::LayoutSideBarContent(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& contentLayoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SideBarContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto sideBarPosition = GetSideBarPositionWithRtl(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    float contentOffsetX = padding.left.value_or(0);
    float contentOffsetY = padding.top.value_or(0);

    if (type_ == SideBarContainerType::EMBED && sideBarPosition == SideBarPosition::START) {
        if (sideBarStatus_ == SideBarStatus::SHOW) {
            contentOffsetX = realSideBarWidth_ + realDividerWidth_ + padding.left.value_or(0);
        } else if (sideBarStatus_ == SideBarStatus::CHANGING) {
            contentOffsetX = realSideBarWidth_ + realDividerWidth_ + currentOffset_ + padding.left.value_or(0);
        }
    }

    auto contentOffset = OffsetF(contentOffsetX, contentOffsetY);
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
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    float dividerOffsetX = padding.left.value_or(0);
    float dividerOffsetY = padding.top.value_or(0);

    switch (sideBarStatus_) {
        case SideBarStatus::SHOW:
            if (sideBarPosition == SideBarPosition::START) {
                dividerOffsetX = realSideBarWidth_ + padding.left.value_or(0);
            } else {
                dividerOffsetX = parentWidth - realSideBarWidth_ - realDividerWidth_ - padding.right.value_or(0);
            }
            break;
        case SideBarStatus::HIDDEN:
            if (sideBarPosition == SideBarPosition::START) {
                dividerOffsetX = -realDividerWidth_ + padding.left.value_or(0);
            } else {
                dividerOffsetX = parentWidth - padding.right.value_or(0);
            }
            break;
        case SideBarStatus::CHANGING:
            if (sideBarPosition == SideBarPosition::START) {
                dividerOffsetX = realSideBarWidth_ + currentOffset_ + padding.left.value_or(0);
            } else {
                dividerOffsetX = parentWidth - realDividerWidth_ + currentOffset_ - padding.right.value_or(0);
            }
            break;
        default:
            break;
    }

    auto dividerOffset = OffsetF(dividerOffsetX, dividerStartMarginPx + dividerOffsetY);
    CHECK_NULL_VOID(dividerLayoutWrapper->GetGeometryNode());
    dividerLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(dividerOffset);
    dividerLayoutWrapper->Layout();
}

SideBarPosition SideBarContainerLayoutAlgorithm::GetSideBarPositionWithRtl(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty)
{
    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    if (layoutProperty->GetLayoutDirection() == TextDirection::RTL ||
        AceApplicationInfo::GetInstance().IsRightToLeft()) {
        sideBarPosition = (sideBarPosition == SideBarPosition::START) ? SideBarPosition::END : SideBarPosition::START;
    }
    return sideBarPosition;
}
} // namespace OHOS::Ace::NG
