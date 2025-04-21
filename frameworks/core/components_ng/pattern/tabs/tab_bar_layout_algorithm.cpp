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

#include "core/components_ng/pattern/tabs/tab_bar_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int8_t MASK_COUNT = 2;
constexpr int8_t SM_COLUMN_NUM = 4;
constexpr int8_t MD_COLUMN_NUM = 8;
constexpr int8_t LG_COLUMN_NUM = 12;
constexpr int8_t TWO = 2;
constexpr int8_t FOCUS_BOARD = 2;
} // namespace

void TabBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    axis_ = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabsLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabsLayoutProperty);
    auto tabsDirection = tabsLayoutProperty->GetNonAutoLayoutDirection();
    auto tabBarDirection = layoutProperty->GetLayoutDirection();
    isRTL_ = tabBarDirection == TextDirection::RTL ||
             (tabBarDirection == TextDirection::AUTO && tabsDirection == TextDirection::RTL);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize =
        CreateIdealSize(constraint.value(), axis_, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT));

    childCount_ = layoutWrapper->GetTotalChildCount() - MASK_COUNT;
    if (childCount_ <= 0) {
        return;
    }

    if (axis_ == Axis::VERTICAL && constraint->selfIdealSize.Width().has_value() &&
        constraint->selfIdealSize.Width().value() < constraint->parentIdealSize.Width().value_or(0.0f) &&
        constraint->selfIdealSize.Width().value() > tabTheme->GetHorizontalBottomTabMinWidth().ConvertToPx()) {
        // Vertical tab bar may apply LayoutMode.AUTO
        ApplyLayoutMode(layoutWrapper, constraint->selfIdealSize.Width().value());
    }
    if (constraint->selfIdealSize.Width().has_value() &&
        constraint->selfIdealSize.Width().value() > constraint->parentIdealSize.Width().value_or(0.0f)) {
        idealSize.SetWidth(static_cast<float>(
            axis_ == Axis::HORIZONTAL                         ? constraint->parentIdealSize.Width().value_or(0.0f)
            : tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE ? tabTheme->GetTabBarDefaultWidth().ConvertToPx()
                                                             : tabTheme->GetTabBarDefaultHeight().ConvertToPx()));
    }
    if (constraint->selfIdealSize.Height().has_value() &&
        constraint->selfIdealSize.Height().value() > constraint->parentIdealSize.Height().value_or(0.0f)) {
        float height = axis_ == Axis::HORIZONTAL
                           ? (tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE &&
                                         Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                                     ? tabTheme->GetBottomTabBarDefaultWidth().ConvertToPx()
                                     : tabTheme->GetTabBarDefaultHeight().ConvertToPx())
                           : constraint->parentIdealSize.Height().value_or(0.0f);

        idealSize.SetHeight(static_cast<float>(height));
    }
    if (!constraint->selfIdealSize.Width().has_value()) {
        auto defaultWidth = idealSize.Width().value_or(0.f);
        if (axis_ == Axis::VERTICAL) {
            defaultWidth = static_cast<float>(tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE
                                                  ? tabTheme->GetTabBarDefaultWidth().ConvertToPx()
                                                  : tabTheme->GetTabBarDefaultHeight().ConvertToPx());
        }
        idealSize.SetWidth(std::clamp(defaultWidth, constraint->minSize.Width(), constraint->maxSize.Width()));
    }
    if (!constraint->selfIdealSize.Height().has_value()) {
        if (axis_ == Axis::HORIZONTAL) {
            defaultHeight_ = (tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE &&
                                 Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE))
                                 ? static_cast<float>(tabTheme->GetBottomTabBarDefaultWidth().ConvertToPx())
                                 : static_cast<float>(tabTheme->GetTabBarDefaultHeight().ConvertToPx());
        }
        auto idealHeight = idealSize.Height().value_or(0.f);
        idealSize.SetHeight(std::clamp(idealHeight, constraint->minSize.Height(), constraint->maxSize.Height()));
    }

    auto tabBarFocusNode = host->GetFocusHub();
    if ((axis_ == Axis::VERTICAL && NearZero(idealSize.ConvertToSizeT().Width())) ||
        (axis_ == Axis::HORIZONTAL && NearZero(idealSize.ConvertToSizeT().Height()))) {
        layoutWrapper->SetActive(false);
        geometryNode->SetFrameSize(SizeF());
        if (tabBarFocusNode) {
            tabBarFocusNode->SetFocusable(false, false);
        }
        return;
    } else {
        layoutWrapper->SetActive(true);
        if (tabBarFocusNode) {
            tabBarFocusNode->SetFocusable(true, false);
        }
    }

    auto frameSize = idealSize.ConvertToSizeT();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    verticalPadding_ = padding.Height();
    auto contentSize = frameSize;
    MinusPaddingToNonNegativeSize(padding, contentSize);
    contentMainSize_ = GetContentMainSize(layoutWrapper, contentSize);
    if (layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::FIXED) {
        MeasureFixedMode(layoutWrapper, contentSize);
    } else {
        MeasureScrollableMode(layoutWrapper, contentSize);
    }
    if (visibleItemPosition_.empty()) {
        layoutWrapper->SetActiveChildRange(-1, -1);
    } else {
        layoutWrapper->SetActiveChildRange(visibleItemPosition_.begin()->first, visibleItemPosition_.rbegin()->first);
    }
    if (defaultHeight_ || maxHeight_) {
        auto frameHeight = std::max(defaultHeight_.value_or(0.0f), maxHeight_.value_or(0.0f) + verticalPadding_);
        frameSize.SetHeight(std::clamp(frameHeight, constraint->minSize.Height(), constraint->maxSize.Height()));
    }
    CheckBorderAndPadding(frameSize, padding);
    geometryNode->SetFrameSize(frameSize);
    MeasureMask(layoutWrapper);
}

float TabBarLayoutAlgorithm::GetContentMainSize(LayoutWrapper* layoutWrapper, const SizeF& contentSize)
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    if (axis_ == Axis::HORIZONTAL) {
        // Apply grid column options to the tab bar
        barGridMargin_ = ApplyBarGridAlign(layoutProperty, contentSize);
        return Positive(contentSize.Width() - barGridMargin_ * TWO) ? contentSize.Width() - barGridMargin_ * TWO : 0.0f;
    } else {
        barGridMargin_ = 0.0f;
        return contentSize.Height();
    }
}

void TabBarLayoutAlgorithm::MeasureFixedMode(LayoutWrapper* layoutWrapper, SizeF frameSize)
{
    auto childLayoutConstraint = GetChildConstraint(layoutWrapper, frameSize);
    visibleItemLength_.clear();
    visibleChildrenMainSize_ = 0.0f;
    if (axis_ == Axis::HORIZONTAL) {
        auto allocatedWidth = contentMainSize_ / childCount_;
        ApplyLayoutMode(layoutWrapper, allocatedWidth);

        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto tabBarPattern = host->GetPattern<TabBarPattern>();
        CHECK_NULL_VOID(tabBarPattern);
        auto isApplySymmetricExtensible = false;
        for (int32_t index = 0; index < childCount_ && childCount_ > TWO; index++) {
            if (tabBarPattern->GetTabBarStyle(index) == TabBarStyle::BOTTOMTABBATSTYLE &&
                tabBarPattern->GetBottomTabBarStyle(index).symmetricExtensible) {
                isApplySymmetricExtensible = true;
                break;
            }
        }
        if (!isApplySymmetricExtensible) {
            childLayoutConstraint.selfIdealSize.SetWidth(allocatedWidth);
        }
        for (int32_t index = 0; index < childCount_; index++) {
            MeasureItem(layoutWrapper, childLayoutConstraint, index);
            visibleItemPosition_[index] = { allocatedWidth * index, allocatedWidth * (index + 1) };
        }
        if (isApplySymmetricExtensible) {
            ApplySymmetricExtensible(layoutWrapper, allocatedWidth);
            if (isBarAdaptiveHeight_) {
                MeasureMaxHeight(layoutWrapper, childLayoutConstraint);
            }
        }
        if (isApplySymmetricExtensible || isBarAdaptiveHeight_) {
            MeasureItemSecond(layoutWrapper, childLayoutConstraint, frameSize);
        }
    } else {
        for (int32_t index = 0; index < childCount_; index++) {
            MeasureItem(layoutWrapper, childLayoutConstraint, index);
        }
    }

    visibleItemPosition_.clear();
    auto currentOffset =
        (axis_ == Axis::VERTICAL && tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE) ? contentMainSize_ / 4 : 0.0f;
    for (int32_t index = 0; index < childCount_; index++) {
        visibleItemPosition_[index] = { currentOffset, currentOffset + visibleItemLength_[index] };
        currentOffset += visibleItemLength_[index];
    }
}

void TabBarLayoutAlgorithm::UpdateMaxLines(LayoutWrapper* layoutWrapper, int32_t index)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID((tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) && (NeedAdaptForAging(host)
        && (axis_ == Axis::VERTICAL)));
    CHECK_NULL_VOID(layoutWrapper);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(childWrapper);
    auto textWrapper = childWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(textWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateMaxLines(TWO);
}

void TabBarLayoutAlgorithm::MeasureScrollableMode(LayoutWrapper* layoutWrapper, SizeF frameSize)
{
    auto childLayoutConstraint = GetChildConstraint(layoutWrapper, frameSize);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    ScrollableBarModeOptions layoutStyle;
    if (axis_ == Axis::HORIZONTAL) {
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        CHECK_NULL_VOID(tabTheme);
        ScrollableBarModeOptions defaultOptions;
        defaultOptions.margin = tabTheme->GetTabBarDefaultMargin();
        layoutStyle = layoutProperty->GetScrollableBarModeOptions().value_or(defaultOptions);
        scrollMargin_ = layoutStyle.margin.ConvertToPx();
        MeasureVisibleItems(layoutWrapper, childLayoutConstraint);

        useItemWidth_ = true;
        if (GreatNotEqual(visibleChildrenMainSize_, contentMainSize_) ||
            childCount_ > static_cast<int32_t>(visibleItemPosition_.size())) {
            useItemWidth_ = false;
        } else {
            visibleChildrenMainSize_ -= scrollMargin_ * TWO;
            if (layoutStyle.nonScrollableLayoutStyle.value_or(LayoutStyle::ALWAYS_CENTER) ==
                LayoutStyle::ALWAYS_CENTER) {
                useItemWidth_ = false;
            } else if (layoutStyle.nonScrollableLayoutStyle.value() == LayoutStyle::ALWAYS_AVERAGE_SPLIT) {
                HandleAlwaysAverageSplitLayoutStyle(layoutWrapper);
            } else if (layoutStyle.nonScrollableLayoutStyle.value() == LayoutStyle::SPACE_BETWEEN_OR_CENTER) {
                HandleSpaceBetweenOrCenterLayoutStyle(layoutWrapper);
            }
            scrollMargin_ = 0.0f;
        }

        if (isBarAdaptiveHeight_ || useItemWidth_) {
            MeasureItemSecond(layoutWrapper, childLayoutConstraint, frameSize);
        }
    } else {
        MeasureVisibleItems(layoutWrapper, childLayoutConstraint);
    }

    if (LessOrEqual(visibleChildrenMainSize_, contentMainSize_) &&
        childCount_ == static_cast<int32_t>(visibleItemPosition_.size())) {
        visibleItemPosition_.clear();
        float currentOffset = GetCurrentOffset(layoutProperty, layoutStyle);
        for (int32_t index = 0; index < childCount_; index++) {
            visibleItemPosition_[index] = { currentOffset, currentOffset + visibleItemLength_[index] };
            currentOffset += visibleItemLength_[index];
        }
    }
}

float TabBarLayoutAlgorithm::GetCurrentOffset(
    RefPtr<TabBarLayoutProperty>& layoutProperty, ScrollableBarModeOptions& layoutStyle)
{
    float currentOffset = (contentMainSize_ - visibleChildrenMainSize_) / TWO;
    if (layoutStyle.nonScrollableLayoutStyle.has_value()) {
        return currentOffset;
    }
    Alignment alignment = Alignment::CENTER;
    if (layoutProperty->GetPositionProperty()) {
        alignment = layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
    }
    if (axis_ == Axis::HORIZONTAL) {
        float margin = layoutStyle.margin.ConvertToPx();
        currentOffset = (1.0 + alignment.GetHorizontal()) * (contentMainSize_ - visibleChildrenMainSize_) / TWO;
        currentOffset -= alignment.GetHorizontal() * margin;
    } else {
        currentOffset = (1.0 + alignment.GetVertical()) * (contentMainSize_ - visibleChildrenMainSize_) / TWO;
    }
    return currentOffset;
}

void TabBarLayoutAlgorithm::CheckBorderAndPadding(SizeF& frameSize, const PaddingPropertyF& padding)
{
    if (GreatNotEqual(padding.Width(), frameSize.Width())) {
        frameSize.SetWidth(padding.Width());
    }
    if (GreatNotEqual(padding.Height(), frameSize.Height())) {
        frameSize.SetHeight(padding.Height());
    }
}

bool TabBarLayoutAlgorithm::NeedAdaptForAging(RefPtr<FrameNode> host)
{
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, false);

    if (GreatOrEqual(pipeline->GetFontScale(), tabTheme->GetSubTabBarBigFontSizeScale())) {
        return true;
    }
    return false;
}

bool TabBarLayoutAlgorithm::GetBarAdaptiveHeight(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(defaultHeight_, false);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto isBarAdaptiveHeight = layoutProperty->GetBarAdaptiveHeight().value_or(false);

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, isBarAdaptiveHeight);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, isBarAdaptiveHeight);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, isBarAdaptiveHeight);
    if (tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE &&
        GreatOrEqual(pipeline->GetFontScale(), tabTheme->GetsubTabBarThirdLargeFontSizeScale())) {
        isBarAdaptiveHeight = true;
    }
    return isBarAdaptiveHeight;
}

LayoutConstraintF TabBarLayoutAlgorithm::GetChildConstraint(LayoutWrapper* layoutWrapper, SizeF& frameSize)
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, {});
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, {});
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, {});
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, {});
    auto focusBoardPadding = tabTheme->GetBoardFocusPadding().ConvertToPx();
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    if (axis_ == Axis::HORIZONTAL) {
        isBarAdaptiveHeight_ = GetBarAdaptiveHeight(layoutWrapper);
        childLayoutConstraint.maxSize.SetWidth(Infinity<float>());
        if (tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) {
            childLayoutConstraint.minSize.SetWidth(tabTheme->GetSubTabBarMinWidth().ConvertToPx());
        }
        if (!defaultHeight_.has_value()) {
            childLayoutConstraint.parentIdealSize = OptionalSizeF(frameSize);
            childLayoutConstraint.selfIdealSize.SetHeight(frameSize.Height());
        } else if (!isBarAdaptiveHeight_) {
            frameSize.SetHeight(defaultHeight_.value() - verticalPadding_);
            frameSize.MinusHeight(focusBoardPadding * FOCUS_BOARD);
            childLayoutConstraint.parentIdealSize = OptionalSizeF(frameSize);
            childLayoutConstraint.selfIdealSize.SetHeight(frameSize.Height());
        }
    } else {
        childLayoutConstraint.parentIdealSize = OptionalSizeF(frameSize);
        if (layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::FIXED) {
            frameSize.SetHeight(tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE
                                    ? frameSize.Height() / TWO / childCount_
                                    : frameSize.Height() / childCount_);
            childLayoutConstraint.selfIdealSize = OptionalSizeF(frameSize);
        } else {
            frameSize.MinusWidth(focusBoardPadding * FOCUS_BOARD);
            childLayoutConstraint.maxSize.SetHeight(Infinity<float>());
            childLayoutConstraint.selfIdealSize.SetWidth(frameSize.Width());
        }
    }
    return childLayoutConstraint;
}

void TabBarLayoutAlgorithm::MeasureVisibleItems(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint)
{
    visibleItemLength_.clear();
    visibleChildrenMainSize_ = scrollMargin_ * TWO;
    startMainPos_ = 0.0f;
    endMainPos_ = contentMainSize_;

    if (targetIndex_) {
        targetIndex_ = targetIndex_.value() % childCount_;
        MeasureTargetIndex(layoutWrapper, childLayoutConstraint);
    } else if (jumpIndex_) {
        if (jumpIndex_.value() >= childCount_) {
            jumpIndex_ = 0;
        }
        MeasureJumpIndex(layoutWrapper, childLayoutConstraint);
        if (GreatNotEqual(visibleChildrenMainSize_, scrollMargin_ * TWO)) {
            jumpIndex_.reset();
        }
    } else if (focusIndex_) {
        MeasureFocusIndex(layoutWrapper, childLayoutConstraint);
    } else {
        MeasureWithOffset(layoutWrapper, childLayoutConstraint);
    }
}

void TabBarLayoutAlgorithm::MeasureTargetIndex(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint)
{
    MeasureWithOffset(layoutWrapper, childLayoutConstraint);
    if (GreatOrEqual(visibleItemLength_[targetIndex_.value()], endMainPos_ - startMainPos_)) {
        return;
    }

    if (visibleItemPosition_.empty()) {
        return;
    }
    auto iter = visibleItemPosition_.find(targetIndex_.value());
    if (iter == visibleItemPosition_.end()) {
        return;
    }
    auto space = ((endMainPos_ - startMainPos_) - visibleItemLength_[targetIndex_.value()]) / TWO;
    startMainPos_ = std::min(startMainPos_, iter->second.startPos - space);
    endMainPos_ = std::max(endMainPos_, iter->second.endPos + space);
    auto startIndex = visibleItemPosition_.begin()->first - 1;
    auto startPos = visibleItemPosition_.begin()->second.startPos;
    auto endIndex = visibleItemPosition_.rbegin()->first + 1;
    auto endPos = visibleItemPosition_.rbegin()->second.endPos;
    LayoutForward(layoutWrapper, childLayoutConstraint, endIndex, endPos);
    LayoutBackward(layoutWrapper, childLayoutConstraint, startIndex, startPos);

    startMainPos_ = 0.0f;
    endMainPos_ = contentMainSize_;
    AdjustPosition(layoutWrapper, childLayoutConstraint, startIndex, endIndex, startPos, endPos);
}

void TabBarLayoutAlgorithm::MeasureJumpIndex(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint)
{
    visibleItemPosition_.clear();
    MeasureItem(layoutWrapper, childLayoutConstraint, jumpIndex_.value());
    if (GreatOrEqual(visibleItemLength_[jumpIndex_.value()], endMainPos_ - startMainPos_)) {
        visibleItemPosition_[jumpIndex_.value()] = { 0.0f, visibleItemLength_[jumpIndex_.value()] };
        return;
    }

    auto startIndex = jumpIndex_.value() - 1;
    auto startPos = ((endMainPos_ - startMainPos_) - visibleItemLength_[jumpIndex_.value()]) / TWO;
    auto endIndex = jumpIndex_.value() + 1;
    auto endPos = ((endMainPos_ - startMainPos_) + visibleItemLength_[jumpIndex_.value()]) / TWO;
    visibleItemPosition_[jumpIndex_.value()] = { startPos, endPos };
    LayoutForward(layoutWrapper, childLayoutConstraint, endIndex, endPos);
    LayoutBackward(layoutWrapper, childLayoutConstraint, startIndex, startPos);

    AdjustPosition(layoutWrapper, childLayoutConstraint, startIndex, endIndex, startPos, endPos);
}

void TabBarLayoutAlgorithm::MeasureFocusIndex(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint)
{
    if (visibleItemPosition_.empty()) {
        return;
    }
    auto startIndex = focusIndex_.value();
    auto startPos = endMainPos_;
    auto endIndex = focusIndex_.value();
    auto endPos = 0.0f;

    auto iter = visibleItemPosition_.find(focusIndex_.value());
    if ((iter != visibleItemPosition_.end() && LessNotEqual(iter->second.startPos, 0.0f)) ||
        focusIndex_.value() < visibleItemPosition_.begin()->first) {
        if (focusIndex_.value() == 0) {
            endPos += scrollMargin_;
        }
        startIndex = endIndex - 1;
        startPos = endPos;
    } else if ((iter != visibleItemPosition_.end() && GreatNotEqual(iter->second.endPos, contentMainSize_)) ||
               focusIndex_.value() > visibleItemPosition_.rbegin()->first) {
        if (focusIndex_.value() == childCount_ - 1) {
            startPos -= scrollMargin_;
        }
        endIndex = startIndex + 1;
        endPos = startPos;
    } else {
        return;
    }
    visibleItemPosition_.clear();
    LayoutForward(layoutWrapper, childLayoutConstraint, endIndex, endPos);
    LayoutBackward(layoutWrapper, childLayoutConstraint, startIndex, startPos);
    if (!canOverScroll_) {
        AdjustPosition(layoutWrapper, childLayoutConstraint, startIndex, endIndex, startPos, endPos);
    }
}

void TabBarLayoutAlgorithm::MeasureWithOffset(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint)
{
    auto startIndex = -1;
    auto startPos = scrollMargin_;
    auto endIndex = 0;
    auto endPos = scrollMargin_;
    if (isRTL_ && axis_ == Axis::HORIZONTAL) {
        currentDelta_ = -currentDelta_;
    }
    if (NonNegative(currentDelta_)) {
        if (!visibleItemPosition_.empty()) {
            endIndex = visibleItemPosition_.begin()->first;
            endPos = visibleItemPosition_.begin()->second.startPos;
        }
        startIndex = endIndex - 1;
        startPos = endPos;
    } else {
        if (!visibleItemPosition_.empty()) {
            startIndex = visibleItemPosition_.rbegin()->first;
            startPos = visibleItemPosition_.rbegin()->second.endPos;
        }
        endIndex = startIndex + 1;
        endPos = startPos;
    }

    startPos += currentDelta_;
    endPos += currentDelta_;
    visibleItemPosition_.clear();
    LayoutForward(layoutWrapper, childLayoutConstraint, endIndex, endPos);
    LayoutBackward(layoutWrapper, childLayoutConstraint, startIndex, startPos);

    if (!canOverScroll_) {
        AdjustPosition(layoutWrapper, childLayoutConstraint, startIndex, endIndex, startPos, endPos);
    }
}

void TabBarLayoutAlgorithm::AdjustPosition(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
    int32_t startIndex, int32_t endIndex, float startPos, float endPos)
{
    if (GreatNotEqual(startPos, startMainPos_ + scrollMargin_)) {
        auto offset = startPos - startMainPos_ - scrollMargin_;
        for (auto& pos : visibleItemPosition_) {
            pos.second.startPos -= offset;
            pos.second.endPos -= offset;
        }
        endPos -= offset;
        LayoutForward(layoutWrapper, childLayoutConstraint, endIndex, endPos);
    } else if (LessNotEqual(endPos, endMainPos_ - scrollMargin_)) {
        auto offset = endMainPos_ - scrollMargin_ - endPos;
        for (auto& pos : visibleItemPosition_) {
            pos.second.startPos += offset;
            pos.second.endPos += offset;
        }
        startPos += offset;
        LayoutBackward(layoutWrapper, childLayoutConstraint, startIndex, startPos);
    }
}

void TabBarLayoutAlgorithm::LayoutForward(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
    int32_t& endIndex, float& endPos)
{
    // 1.When first item is invisible and located to the right or below the tab bar, measure at least one item.
    // 2.When set the height of tab bar to auto, measure all items to find max height of items.
    // 3.If target index exists, measure items from the end index to target index.
    while (endIndex < childCount_ && (endIndex == 0 || LessNotEqual(endPos, endMainPos_) || isBarAdaptiveHeight_ ||
        (targetIndex_ && endIndex <= targetIndex_.value()))) {
        if (endIndex < 0) {
            endIndex = 0;
            continue;
        }
        MeasureItem(layoutWrapper, childLayoutConstraint, endIndex);
        visibleItemPosition_[endIndex] = { endPos, endPos + visibleItemLength_[endIndex] };
        endPos += visibleItemLength_[endIndex];
        if (endIndex < childCount_ - 1 && LessOrEqual(endPos, startMainPos_) && !isBarAdaptiveHeight_ &&
            !targetIndex_.has_value()) {
            visibleChildrenMainSize_ -= visibleItemLength_[endIndex];
            visibleItemLength_.erase(endIndex);
            visibleItemPosition_.erase(endIndex);
        }
        endIndex++;
    }
}

void TabBarLayoutAlgorithm::LayoutBackward(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
    int32_t& startIndex, float& startPos)
{
    // 1.When last item is invisible and located to the left or above the tab bar, measure at least one item.
    // 2.When set the height of tab bar to auto, measure all items to find max height of items.
    // 3.If target index exists, measure items from the start index to target index.
    while (startIndex >= 0 && (startIndex == childCount_ - 1 || GreatNotEqual(startPos, startMainPos_) ||
        isBarAdaptiveHeight_ || (targetIndex_ && startIndex >= targetIndex_.value()))) {
        if (startIndex >= childCount_) {
            startIndex = childCount_ - 1;
            continue;
        }
        MeasureItem(layoutWrapper, childLayoutConstraint, startIndex);
        visibleItemPosition_[startIndex] = { startPos - visibleItemLength_[startIndex], startPos };
        startPos -= visibleItemLength_[startIndex];
        if (startIndex > 0 && GreatOrEqual(startPos, endMainPos_) && !isBarAdaptiveHeight_ &&
            !targetIndex_.has_value()) {
            visibleChildrenMainSize_ -= visibleItemLength_[startIndex];
            visibleItemLength_.erase(startIndex);
            visibleItemPosition_.erase(startIndex);
        }
        startIndex--;
    }
}

void TabBarLayoutAlgorithm::MeasureItem(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
    int32_t index)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto tabBarPattern = host->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID (childWrapper);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (tabBarPattern->GetTabBarStyle(index) == TabBarStyle::BOTTOMTABBATSTYLE && axis_ == Axis::HORIZONTAL) {
        auto iconWrapper = childWrapper->GetOrCreateChildByIndex(0);
        CHECK_NULL_VOID(iconWrapper);
        if (iconWrapper->GetHostNode()->GetTag() == V2::SYMBOL_ETS_TAG) {
            auto symbolLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(iconWrapper->GetLayoutProperty());
            CHECK_NULL_VOID(symbolLayoutProperty);
            symbolLayoutProperty->UpdateMargin({ CalcLength(0.0_vp), CalcLength(0.0_vp), {}, {}, {}, {} });
        } else {
            auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(iconWrapper->GetLayoutProperty());
            CHECK_NULL_VOID(imageLayoutProperty);
            imageLayoutProperty->UpdateMargin({ CalcLength(0.0_vp), CalcLength(0.0_vp), {}, {}, {}, {} });
        }
        auto textWrapper = childWrapper->GetOrCreateChildByIndex(1);
        CHECK_NULL_VOID(textWrapper);
        auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMargin({ CalcLength(0.0_vp), CalcLength(0.0_vp), {}, {}, {}, {} });
    }
    if (layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
        axis_ == Axis::HORIZONTAL) {
        auto textWrapper = childWrapper->GetOrCreateChildByIndex(1);
        if (textWrapper) {
            auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
            if (textLayoutProperty &&
                textLayoutProperty->GetTextOverflow().value_or(TextOverflow::NONE) == TextOverflow::MARQUEE) {
                textLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
            }
        }
    }
    UpdateMaxLines(layoutWrapper, index);
    SetTabBarMargin(childWrapper, index);
    childWrapper->Measure(childLayoutConstraint);
    auto geometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    visibleItemLength_[index] = geometryNode->GetMarginFrameSize().MainSize(axis_);
    visibleChildrenMainSize_ += visibleItemLength_[index];
    if (isBarAdaptiveHeight_) {
        maxHeight_ = std::max(maxHeight_.value_or(0.0f), geometryNode->GetMarginFrameSize().MainSize(Axis::VERTICAL));
    }
}

void TabBarLayoutAlgorithm::SetTabBarMargin(RefPtr<LayoutWrapper> layoutWrapper, int32_t index)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto tabBarPattern = host->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    CHECK_NULL_VOID(tabBarPattern->GetTabBarStyle(index) == TabBarStyle::SUBTABBATSTYLE);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID (childWrapper);

    auto textWrapper = childWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(textWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    if (NeedAdaptForAging(host)) {
        textLayoutProperty->UpdateMargin({ CalcLength(tabTheme->GetSubTabBarLeftRightMargin()),
            CalcLength(tabTheme->GetSubTabBarLeftRightMargin()), {}, {}, {}, {} });
    } else {
        textLayoutProperty->UpdateMargin({ CalcLength(0.0_vp), CalcLength(0.0_vp), {}, {}, {}, {} });
    }
}

void TabBarLayoutAlgorithm::MeasureItemSecond(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint,
    SizeF& frameSize)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto tabBarPattern = host->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);

    visibleChildrenMainSize_ = scrollMargin_ * TWO;
    if (isBarAdaptiveHeight_) {
        frameSize.SetHeight(std::max(defaultHeight_.value_or(0.0f) - verticalPadding_, maxHeight_.value_or(0.0f)));
        childLayoutConstraint.parentIdealSize = OptionalSizeF(frameSize);
        childLayoutConstraint.selfIdealSize.SetHeight(frameSize.Height());
    }
    for (auto& iter : visibleItemPosition_) {
        childLayoutConstraint.selfIdealSize.SetWidth(visibleItemLength_[iter.first]);
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(iter.first);
        CHECK_NULL_VOID(childWrapper);
        auto iconWrapper = childWrapper->GetOrCreateChildByIndex(0);
        if (iconWrapper && iconWrapper->GetHostNode() && iconWrapper->GetHostNode()->GetTag() == V2::SYMBOL_ETS_TAG) {
            childWrapper->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        }
        childWrapper->Measure(childLayoutConstraint);
        auto geometryNode = childWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        visibleChildrenMainSize_ += geometryNode->GetMarginFrameSize().MainSize(axis_);
        tabBarPattern->UpdateSymbolEffect(iter.first);
    }
}

void TabBarLayoutAlgorithm::MeasureMask(LayoutWrapper* layoutWrapper) const
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto maskLayoutConstraint = layoutProperty->CreateChildConstraint();
    auto selectedMaskWrapper = layoutWrapper->GetOrCreateChildByIndex(childCount_);
    CHECK_NULL_VOID(selectedMaskWrapper);
    maskLayoutConstraint.selfIdealSize = OptionalSizeF(selectedMaskWrapper->GetGeometryNode()->GetFrameSize());
    selectedMaskWrapper->Measure(maskLayoutConstraint);

    auto unselectedMaskWrapper = layoutWrapper->GetOrCreateChildByIndex(childCount_ + 1);
    CHECK_NULL_VOID(unselectedMaskWrapper);
    maskLayoutConstraint.selfIdealSize = OptionalSizeF(unselectedMaskWrapper->GetGeometryNode()->GetFrameSize());
    unselectedMaskWrapper->Measure(maskLayoutConstraint);
}

void TabBarLayoutAlgorithm::MeasureMaxHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& childLayoutConstraint)
{
    for (int32_t index = 0; index < childCount_; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        if (static_cast<int32_t>(visibleItemLength_.size()) == childCount_) {
            childLayoutConstraint.selfIdealSize.SetWidth(visibleItemLength_[index]);
        }
        childWrapper->Measure(childLayoutConstraint);
        auto geometryNode = childWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        maxHeight_ = std::max(maxHeight_.value_or(0.0f), geometryNode->GetMarginFrameSize().MainSize(Axis::VERTICAL));
    }
}

void TabBarLayoutAlgorithm::HandleAlwaysAverageSplitLayoutStyle(LayoutWrapper* layoutWrapper)
{
    std::map<int32_t, float> originalVisibleItemLength;
    for (int32_t index = 0; index < childCount_; index++) {
        originalVisibleItemLength[index] = visibleItemLength_[index];
        visibleItemLength_[index] = 0.0f;
    }

    bool hasLongItem = false;
    int32_t remainingChildCount = childCount_;
    auto totalWidth = contentMainSize_ - scrollMargin_ * TWO;
    auto allocatedItemWidth = 0.0f;

    /* Calculate the widths of long items. A long item refers to an item whose length is above the average,
        so remainingChildCount can't be zero */
    do {
        allocatedItemWidth = totalWidth / remainingChildCount;
        hasLongItem = false;
        for (int32_t index = 0; index < childCount_; index++) {
            if (NearZero(visibleItemLength_[index]) &&
                GreatNotEqual(originalVisibleItemLength[index], allocatedItemWidth)) {
                visibleItemLength_[index] = originalVisibleItemLength[index];
                hasLongItem = true;
                remainingChildCount--;
                totalWidth -= originalVisibleItemLength[index];
            }
        }
    } while (hasLongItem && remainingChildCount > 0 && Positive(totalWidth));

    // Calculate the widths of other items
    for (int32_t index = 0; index < childCount_; index++) {
        if (NearZero(visibleItemLength_[index])) {
            visibleItemLength_[index] = allocatedItemWidth;
        }
    }
}

void TabBarLayoutAlgorithm::HandleSpaceBetweenOrCenterLayoutStyle(LayoutWrapper* layoutWrapper)
{
    if (GreatNotEqual(visibleChildrenMainSize_, contentMainSize_ / TWO)) {
        useItemWidth_ = false;
        return;
    }
    auto additionalWidth = (contentMainSize_ / TWO - visibleChildrenMainSize_) / childCount_;

    for (int32_t index = 0; index < childCount_; ++index) {
        visibleItemLength_[index] += additionalWidth;
    }
}

void TabBarLayoutAlgorithm::ApplyLayoutMode(LayoutWrapper* layoutWrapper, float allocatedWidth)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto tabBarPattern = host->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);

    bool isVertical = LessOrEqual(allocatedWidth, tabTheme->GetHorizontalBottomTabMinWidth().ConvertToPx());

    // Calculate the initial buffer and initial space request of each item.
    for (int32_t index = 0; index < childCount_; ++index) {
        auto bottomTabBarStyle = tabBarPattern->GetBottomTabBarStyle(index);
        if (tabBarPattern->GetTabBarStyle(index) != TabBarStyle::BOTTOMTABBATSTYLE ||
            bottomTabBarStyle.layoutMode != LayoutMode::AUTO) {
            continue;
        }
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(linearLayoutProperty);
        auto textWrapper = childWrapper->GetOrCreateChildByIndex(1);
        CHECK_NULL_VOID(textWrapper);
        auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(textLayoutProperty);
        if (isVertical) {
            linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
            linearLayoutProperty->UpdateSpace(tabTheme->GetBottomTabBarSpace());
            linearLayoutProperty->UpdateMainAxisAlign(bottomTabBarStyle.verticalAlign);
            linearLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
            linearLayoutProperty->SetIsVertical(true);
            textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        } else {
            linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
            linearLayoutProperty->UpdateSpace(tabTheme->GetHorizontalBottomTabBarSpace());
            linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
            linearLayoutProperty->UpdateCrossAxisAlign(bottomTabBarStyle.verticalAlign);
            linearLayoutProperty->SetIsVertical(false);
            textLayoutProperty->UpdateTextAlign(TextAlign::LEFT);
        }
        auto childNode = childWrapper->GetHostNode();
        CHECK_NULL_VOID(childNode);
        if (!tabBarPattern->GetBottomTabLabelStyle(childNode->GetId()).fontSize.has_value() &&
            Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            textLayoutProperty->UpdateFontSize(
                isVertical ? tabTheme->GetBottomTabTextSize() : tabTheme->GetBottomTabHorizontalTextSize());
        }
    }
}

void TabBarLayoutAlgorithm::ApplySymmetricExtensible(LayoutWrapper* layoutWrapper, float allocatedWidth)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto tabBarPattern = host->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);

    if (childCount_ <= TWO || childCount_ > static_cast<int32_t>(visibleItemLength_.size())) {
        for (int32_t index = 0; index < static_cast<int32_t>(visibleItemLength_.size()); ++index) {
            visibleItemLength_[index] = allocatedWidth;
        }
        return;
    }

    std::vector<float> leftBuffers(childCount_);
    std::vector<float> rightBuffers(childCount_);
    std::vector<float> spaceRequests(childCount_);

    // Calculate the initial buffer and initial space request of each item.
    for (int32_t index = 0; index < childCount_; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(childWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(linearLayoutProperty);
        if (GreatNotEqual(visibleItemLength_[index], allocatedWidth)) {
            if (tabBarPattern->GetTabBarStyle(index) == TabBarStyle::BOTTOMTABBATSTYLE &&
                tabBarPattern->GetBottomTabBarStyle(index).symmetricExtensible && index > 0 &&
                index < childCount_ - 1) {
                spaceRequests[index] = (visibleItemLength_[index] - allocatedWidth) / TWO;
            }
        } else {
            if (tabBarPattern->GetTabBarStyle(index) == TabBarStyle::BOTTOMTABBATSTYLE) {
                leftBuffers[index] = index == 0 ? 0.0f : (allocatedWidth - visibleItemLength_[index]) / TWO;
                rightBuffers[index] =
                    index == childCount_ - 1 ? 0.0f : (allocatedWidth - visibleItemLength_[index]) / TWO;
            }
        }
    }

    // Decide the used buffer and used space request of each item.
    for (int32_t index = 1; index < childCount_ - 1; ++index) {
        auto actualRequest = std::min(std::min(rightBuffers[index - 1], leftBuffers[index + 1]), spaceRequests[index]);
        spaceRequests[index] = actualRequest;
        rightBuffers[index - 1] = actualRequest;
        leftBuffers[index + 1] = actualRequest;
    }

    spaceRequests[0] = 0.0f;
    spaceRequests[childCount_ - 1] = 0.0f;

    leftBuffers[1] = 0.0f;
    rightBuffers[childCount_ - TWO] = 0.0f;

    CalculateItemWidthsForSymmetricExtensible(layoutWrapper, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
}

void TabBarLayoutAlgorithm::CalculateItemWidthsForSymmetricExtensible(LayoutWrapper* layoutWrapper,
    const std::vector<float>& spaceRequests, const std::vector<float>& leftBuffers,
    const std::vector<float>& rightBuffers, float allocatedWidth)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto tabBarPattern = host->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);

    if ((static_cast<int32_t>(spaceRequests.size()) != childCount_) ||
        (static_cast<int32_t>(leftBuffers.size()) != childCount_) ||
        (static_cast<int32_t>(rightBuffers.size()) != childCount_) ||
        (static_cast<int32_t>(visibleItemLength_.size()) != childCount_)) {
        return;
    }

    for (int32_t index = 0; index < childCount_; ++index) {
        if (tabBarPattern->GetTabBarStyle(index) != TabBarStyle::BOTTOMTABBATSTYLE) {
            visibleItemLength_[index] = allocatedWidth;
            continue;
        }
        if (!NearZero(spaceRequests[index])) {
            visibleItemLength_[index] = allocatedWidth + spaceRequests[index] * TWO;
        } else if (!NearZero(leftBuffers[index]) || !NearZero(rightBuffers[index])) {
            visibleItemLength_[index] = allocatedWidth - leftBuffers[index] - rightBuffers[index];
            auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
            CHECK_NULL_VOID(childWrapper);
            // Adjust margin to keep the position of current item.
            auto leftMargin = rightBuffers[index];
            auto rightMargin = leftBuffers[index];
            if (GreatNotEqual(leftMargin, rightMargin)) {
                leftMargin -= rightMargin;
                rightMargin = 0.0f;
            } else {
                rightMargin -= leftMargin;
                leftMargin = 0.0f;
            }
            UpdateChildMarginProperty(rightMargin, leftMargin, childWrapper);
        } else {
            visibleItemLength_[index] = allocatedWidth;
        }
    }
}

void TabBarLayoutAlgorithm::UpdateChildMarginProperty(
    float rightMargin, float leftMargin, const RefPtr<LayoutWrapper>& childWrapper)
{
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(childWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(linearLayoutProperty);
    auto textWrapper = childWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(textWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateMargin(
        { CalcLength(Dimension(leftMargin)), CalcLength(Dimension(rightMargin)), {}, {}, {}, {} });
    auto iconWrapper = childWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(iconWrapper);
    if (iconWrapper->GetHostNode()->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(iconWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(symbolLayoutProperty);
        symbolLayoutProperty->UpdateMargin(
            { CalcLength(Dimension(leftMargin)), CalcLength(Dimension(rightMargin)), {}, {}, {}, {} });
        if (linearLayoutProperty->GetFlexDirection().value_or(FlexDirection::COLUMN) == FlexDirection::ROW) {
            symbolLayoutProperty->UpdateMargin({ CalcLength(Dimension(leftMargin)), {}, {}, {}, {}, {} });
            textLayoutProperty->UpdateMargin({ {}, CalcLength(Dimension(rightMargin)), {}, {}, {}, {} });
        }
    } else {
        auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(iconWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateMargin(
            { CalcLength(Dimension(leftMargin)), CalcLength(Dimension(rightMargin)), {}, {}, {}, {} });
        if (linearLayoutProperty->GetFlexDirection().value_or(FlexDirection::COLUMN) == FlexDirection::ROW) {
            imageLayoutProperty->UpdateMargin({ CalcLength(Dimension(leftMargin)), {}, {}, {}, {}, {} });
            textLayoutProperty->UpdateMargin({ {}, CalcLength(Dimension(rightMargin)), {}, {}, {}, {} });
        }
    }
}

float TabBarLayoutAlgorithm::ApplyBarGridAlign(
    const RefPtr<TabBarLayoutProperty>& layoutProperty, const SizeF& contentSize) const
{
    if (!layoutProperty->GetBarGridAlign()) {
        return 0.0f;
    }
    auto option = layoutProperty->GetBarGridAlign().value();
    auto gridSizeType = GetGridSizeType(contentSize);
    int32_t columnNum = -1;
    if (gridSizeType == GridSizeType::SM) {
        columnNum = option.sm;
        if (columnNum > SM_COLUMN_NUM) {
            return 0.0f;
        }
    } else if (gridSizeType == GridSizeType::MD) {
        columnNum = option.md;
        if (columnNum > MD_COLUMN_NUM) {
            return 0.0f;
        }
    } else if (gridSizeType == GridSizeType::LG) {
        columnNum = option.lg;
        if (columnNum > LG_COLUMN_NUM) {
            return 0.0f;
        }
    } else {
        return 0.0f;
    }
    if (columnNum < 0 || columnNum % 2) {
        return 0.0f;
    }
    auto gridWidth = GetGridWidth(option, contentSize, columnNum);
    return (contentSize.Width() - gridWidth) / TWO;
}

void TabBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    axis_ = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    if ((axis_ == Axis::VERTICAL && NearZero(geometryNode->GetFrameSize().Width())) ||
        (axis_ == Axis::HORIZONTAL && NearZero(geometryNode->GetFrameSize().Height()))) {
        return;
    }
    childCount_ = layoutWrapper->GetTotalChildCount() - MASK_COUNT;
    if (childCount_ <= 0) {
        return;
    }
    if (visibleItemPosition_.empty()) {
        return;
    }

    auto contentSize = geometryNode->GetPaddingSize();
    auto childOffset = OffsetF(0.0f, 0.0f);
    if (geometryNode->GetPadding()) {
        auto left = geometryNode->GetPadding()->left.value_or(0.0f);
        auto top = geometryNode->GetPadding()->top.value_or(0.0f);
        childOffset += OffsetF(left, top);
    }
    if (isRTL_ && axis_ == Axis::HORIZONTAL) {
        childOffset +=
            OffsetF(0.0f, contentSize.Width() - visibleItemPosition_.begin()->second.startPos - barGridMargin_, axis_);
    } else {
        childOffset += OffsetF(barGridMargin_, 0.0f);
        childOffset += OffsetF(0.0f, visibleItemPosition_.begin()->second.startPos, axis_);
    }
    LayoutChildren(layoutWrapper, contentSize, childOffset);
}

void TabBarLayoutAlgorithm::LayoutChildren(LayoutWrapper* layoutWrapper, const SizeF& contentSize, OffsetF& childOffset)
{
    std::map<int32_t, OffsetF> childOffsetDelta;
    for (auto& iter : visibleItemPosition_) {
        auto pos = iter.first;
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(pos);
        if (!childWrapper) {
            continue;
        }
        auto childGeometryNode = childWrapper->GetGeometryNode();
        auto childFrameSize = childGeometryNode->GetMarginFrameSize();
        if (isRTL_ && axis_ == Axis::HORIZONTAL) {
            childOffset -= OffsetF(0.0f, childFrameSize.MainSize(axis_), axis_);
        }
        OffsetF centerOffset =
            OffsetF((contentSize.CrossSize(axis_) - childFrameSize.CrossSize(axis_)) / 2.0, 0.0f, axis_);
        childOffsetDelta[pos] = childOffset + centerOffset - childGeometryNode->GetMarginFrameOffset();
        childGeometryNode->SetMarginFrameOffset(childOffset + centerOffset);
        childWrapper->Layout();
        if (!isRTL_ || axis_ != Axis::HORIZONTAL) {
            childOffset += OffsetF(0.0f, childFrameSize.MainSize(axis_), axis_);
        }
    }
    LayoutMask(layoutWrapper, childOffsetDelta);
}

void TabBarLayoutAlgorithm::LayoutMask(LayoutWrapper* layoutWrapper,
    const std::map<int32_t, OffsetF>& childOffsetDelta)
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto selectedMaskWrapper = layoutWrapper->GetOrCreateChildByIndex(childCount_);
    CHECK_NULL_VOID(selectedMaskWrapper);
    auto unselectedMaskWrapper = layoutWrapper->GetOrCreateChildByIndex(childCount_ + 1);
    CHECK_NULL_VOID(unselectedMaskWrapper);
    for (int32_t i = 0; i < MASK_COUNT; i++) {
        auto currentWrapper = (i == 0 ? selectedMaskWrapper : unselectedMaskWrapper);
        auto currentMask = (i == 0 ? layoutProperty->GetSelectedMask().value_or(-1)
                                   : layoutProperty->GetUnselectedMask().value_or(-1));
        if (currentMask < 0) {
            currentWrapper->GetGeometryNode()->SetFrameSize(SizeF());
            currentWrapper->Layout();
            currentWrapper->SetActive(false);
        } else {
            auto offset = currentWrapper->GetGeometryNode()->GetMarginFrameOffset();
            auto iter = childOffsetDelta.find(currentMask);
            if (iter != childOffsetDelta.end()) {
                offset += iter->second;
            }
            currentWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
            auto imageWrapper = currentWrapper->GetOrCreateChildByIndex(0);
            CHECK_NULL_VOID(imageWrapper);
            auto imageNode = imageWrapper->GetHostNode();
            CHECK_NULL_VOID(imageNode);
            auto imageRenderContext = imageNode->GetRenderContext();
            CHECK_NULL_VOID(imageRenderContext);
            imageRenderContext->SetVisible(true);
            currentWrapper->Layout();
            currentWrapper->SetActive(true);
        }
    }
}

GridSizeType TabBarLayoutAlgorithm::GetGridSizeType(const SizeF& frameSize) const
{
    auto gridColumnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::TAB_BAR);
    CHECK_NULL_RETURN(gridColumnInfo, GridSizeType::UNDEFINED);
    auto parent = gridColumnInfo->GetParent();
    CHECK_NULL_RETURN(parent, GridSizeType::UNDEFINED);
    parent->BuildColumnWidth(frameSize.Width());
    return parent->GetSizeType();
}

float TabBarLayoutAlgorithm::GetGridWidth(
    const BarGridColumnOptions& option, const SizeF& frameSize, int32_t columns) const
{
    auto gridColumnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::TAB_BAR);
    CHECK_NULL_RETURN(gridColumnInfo, 0.0f);
    auto parent = gridColumnInfo->GetParent();
    CHECK_NULL_RETURN(parent, 0.0f);
    parent->SetGutterWidth(option.gutter);
    parent->SetMarginLeft(option.margin);
    parent->SetMarginRight(option.margin);
    parent->BuildColumnWidth(frameSize.Width());
    if (columns < 0) {
        return gridColumnInfo->GetMaxWidth();
    }
    return gridColumnInfo->GetWidth(columns);
}
} // namespace OHOS::Ace::NG
