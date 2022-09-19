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

#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
FlexDirection FlipAxis(FlexDirection direction)
{
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return FlexDirection::COLUMN;
    }
    return FlexDirection::ROW;
}

bool IsStartTopLeft(FlexDirection direction, TextDirection textDirection)
{
    switch (direction) {
        case FlexDirection::ROW:
            return textDirection == TextDirection::LTR;
        case FlexDirection::ROW_REVERSE:
            return textDirection == TextDirection::RTL;
        case FlexDirection::COLUMN:
            return true;
        case FlexDirection::COLUMN_REVERSE:
            return false;
        default:
            return true;
    }
}

float GetCrossAxisSizeHelper(const SizeF& size, FlexDirection direction)
{
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return size.Height();
    }
    return size.Width();
}

float GetMainAxisSizeHelper(const SizeF& size, FlexDirection direction)
{
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return size.Width();
    }
    return size.Height();
}

OptionalSizeF GetCalcSizeHelper(float mainAxisSize, float crossAxisSize, FlexDirection direction)
{
    OptionalSizeF size;
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        size.SetWidth(mainAxisSize);
        size.SetHeight(crossAxisSize);
    } else {
        size.SetHeight(mainAxisSize);
        size.SetWidth(crossAxisSize);
    }
    return size;
}
} // namespace

float FlexLayoutAlgorithm::GetMainAxisSize(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    float size = 0.0f;
    if (!layoutWrapper) {
        return size;
    }
    return GetMainAxisSizeHelper(layoutWrapper->GetGeometryNode()->GetFrameSize(), direction_);
}

float FlexLayoutAlgorithm::GetCrossAxisSize(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    if (!layoutWrapper) {
        return 0.0f;
    }
    return GetCrossAxisSizeHelper(layoutWrapper->GetGeometryNode()->GetFrameSize(), direction_);
}

void FlexLayoutAlgorithm::CheckSizeValidity(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    if (!layoutWrapper->GetGeometryNode()->GetFrameSize().IsPositive()) {
        return;
    }
    ++validSizeCount_;
}

void FlexLayoutAlgorithm::CheckBaselineProperties(
    const RefPtr<LayoutWrapper>& layoutWrapper, BaselineProperties& baselineProperties)
{
    /**
     * TODO: Support Layout With baseline.
     */
}

void FlexLayoutAlgorithm::InitFlexProperties(LayoutWrapper* layoutWrapper)
{
    mainSize_ = 0.0f;
    crossAxisSize_ = 0.0f;
    allocatedSize_ = 0.0f;
    layoutMode_ = FlexLayoutMode::FLEX_WEIGHT_MODE;
    totalFlexWeight_ = 0.0f;
    maxDisplayPriority_ = 0;
    layoutWrapper_ = layoutWrapper;
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    direction_ = layoutProperty->GetFlexDirection().value_or(FlexDirection::ROW);
    mainAxisAlign_ = layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START);
    crossAxisAlign_ = layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START);
    TravelChildrenFlexProps(layoutWrapper);
}

void FlexLayoutAlgorithm::TravelChildrenFlexProps(LayoutWrapper* layoutWrapper)
{
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& child : children) {
        const auto& childLayoutProperty = child->GetLayoutProperty();
        const auto& childMagicItemProperty = childLayoutProperty->GetMagicItemProperty();
        MagicLayoutNode node;
        node.layoutWrapper = child;
        int32_t childDisplayPriority = 1;
        float childLayoutWeight = -1.0f;
        if (childMagicItemProperty) {
            childDisplayPriority = childMagicItemProperty->GetDisplayPriority().value_or(1);
            childLayoutWeight = childMagicItemProperty->GetLayoutWeight().value_or(-1);
        }
        if (!magicNodes_.count(childDisplayPriority)) {
            magicNodes_.insert(
                std::map<int32_t, std::list<MagicLayoutNode>>::value_type(childDisplayPriority, { node }));
            if (childLayoutWeight > 0) {
                magicNodeWeights_.insert(std::map<int32_t, float>::value_type(childDisplayPriority, childLayoutWeight));
            }
        } else {
            magicNodes_[childDisplayPriority].emplace_back(node);
            if (childLayoutWeight > 0) {
                magicNodeWeights_[childDisplayPriority] += childLayoutWeight;
            }
        }
        totalFlexWeight_ += GreatOrEqual(childLayoutWeight, 0.0f) ? childLayoutWeight : 0.0f;
        maxDisplayPriority_ = std::max(childDisplayPriority, maxDisplayPriority_);
    }
    layoutMode_ =
        LessOrEqual(totalFlexWeight_, 0.0f) ? FlexLayoutMode::FLEX_ITEM_MODE : FlexLayoutMode::FLEX_WEIGHT_MODE;
}

void FlexLayoutAlgorithm::ResizeFlexSizeByItem(const RefPtr<LayoutWrapper>& childLayoutWrapper, float& allocatedSize)
{
    float mainAxisSize = GetMainAxisSize(childLayoutWrapper);
    if (GreatOrEqual(mainAxisSize, Infinity<float>())) {
        mainAxisSize = 0.0f;
        infinityLayoutNodes_.insert(childLayoutWrapper);
    }
    crossAxisSize_ = std::max(crossAxisSize_, GetCrossAxisSize(childLayoutWrapper));
    allocatedSize_ += mainAxisSize;
    allocatedSize_ += space_;
    allocatedSize += mainAxisSize;
    allocatedSize += space_;
}

void FlexLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(realSize_.ConvertToSizeT());
        return;
    }
    InitFlexProperties(layoutWrapper);
    if (layoutMode_ == FlexLayoutMode::FLEX_WEIGHT_MODE) {
        MeasureInWeightMode(layoutWrapper);
    } else if (maxDisplayPriority_ > 1) {
        MeasureInIndexMode(layoutWrapper);
    } else {
        MeasureInItemMode(layoutWrapper);
    }
}

float FlexLayoutAlgorithm::GetStretchCrossAxisLimit() const
{
    float crossAxisLimit = 0.0f;
    if (GreatNotEqual(selfIdealCrossAxisSize_, -1.0f)) {
        crossAxisLimit = selfIdealCrossAxisSize_;
    } else {
        crossAxisLimit = crossAxisSize_;
    }
    return crossAxisLimit;
}

LayoutConstraintF FlexLayoutAlgorithm::MakeLayoutConstraint(
    float mainFlexExtent, const LayoutConstraintF& constraint, bool isStretch, bool supportZero) const
{
    LayoutConstraintF layoutConstraint;
    if (LessNotEqual(mainFlexExtent, 0.0f)) {
        layoutConstraint.UpdateMaxSizeWithCheck(layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint()->maxSize);
    } else if (GreatNotEqual(mainFlexExtent, 0.0f)) {
        layoutConstraint = MakeLayoutConstraintWithLimit(mainFlexExtent, isStretch);
    } else {
        if (supportZero) {
            layoutConstraint = MakeLayoutConstraintWithLimit(mainFlexExtent, isStretch);
        } else {
            layoutConstraint.UpdateMaxSizeWithCheck(
                layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint()->maxSize);
        }
    }
    layoutConstraint.UpdateMaxSizeWithCheck(layoutConstraint.maxSize);
    layoutConstraint.UpdateMinSizeWithCheck(layoutConstraint.minSize);
    return layoutConstraint;
}

LayoutConstraintF FlexLayoutAlgorithm::MakeLayoutConstraintWithLimit(float maxMainAxisLimit, bool isStretch) const
{
    LayoutConstraintF layoutConstraint;
    auto parentLayoutConstraint = layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint();
    float minCrossAxisLimit = 0.0f;
    float maxCrossAxisLimit = (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE)
                                  ? parentLayoutConstraint->maxSize.Height()
                                  : parentLayoutConstraint->maxSize.Width();
    if (isStretch) {
        minCrossAxisLimit = GetStretchCrossAxisLimit();
        maxCrossAxisLimit = minCrossAxisLimit;
    }
    if (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) {
        layoutConstraint.UpdateSelfIdealSizeWithCheck(
            OptionalSizeF(std::optional<float>(maxMainAxisLimit), maxCrossAxisLimit));
    } else {
        layoutConstraint.UpdateSelfIdealSizeWithCheck(
            OptionalSizeF(maxCrossAxisLimit, std::optional<float>(maxMainAxisLimit)));
    }
    return layoutConstraint;
}

void FlexLayoutAlgorithm::MeasureInWeightMode(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& parentIdealSize = layoutConstraint->parentIdealSize;
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    OptionalSizeF realSize;
    /**
     * check selfIdealSize and matchParent.
     */
    do {
        realSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (realSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            realSize.UpdateIllegalSizeWithCheck(parentIdealSize);
        }
    } while (false);
    /**
     * get the user defined main axis size and cross axis size.
     */
    SizeF maxSize;
    maxSize.UpdateSizeWithCheck(layoutConstraint->maxSize);
    maxSize.UpdateSizeWhenSmaller(realSize.ConvertToSizeT());
    float maxMainAxisSize = GetMainAxisSizeHelper(maxSize, direction_);
    mainSize_ = maxMainAxisSize;
    if (NearEqual(maxMainAxisSize, Infinity<float>())) {
        LOGW("not supported infinite size");
        return;
    }
    selfIdealCrossAxisSize_ = GetCrossAxisSizeHelper(realSize.ConvertToSizeT(), direction_);
    BaselineProperties baselineProperties;
    auto childConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    float allocatedSize = allocatedSize_;
    /**
     * measure relative nodes；
     */
    auto iter = magicNodes_.rbegin();
    while (iter != magicNodes_.rend()) {
        auto& layoutList = (*iter).second;
        for (auto& node : layoutList) {
            auto childLayoutWrapper = node.layoutWrapper;
            float childLayoutWeight = 0.0f;
            const auto& magicItemProperty = childLayoutWrapper->GetLayoutProperty()->GetMagicItemProperty();
            if (magicItemProperty) {
                childLayoutWeight = magicItemProperty->GetLayoutWeightValue();
            }
            if (LessOrEqual(childLayoutWeight, 0.0f)) {
                childLayoutWrapper->Measure(childConstraint);
                ResizeFlexSizeByItem(childLayoutWrapper, allocatedSize);
                CheckSizeValidity(childLayoutWrapper);
                CheckBaselineProperties(childLayoutWrapper, baselineProperties);
            }
        }
        iter++;
    }

    /**
     * TODO: Support Measure In Index Mode.
     */
    maxMainAxisSize -= allocatedSize_;
    if (LessOrEqual(maxMainAxisSize, 0)) {
        return;
    }

    /**
     * measure magic nodes
     */
    auto spacePerWeight = maxMainAxisSize / totalFlexWeight_;
    bool isExceed = false;
    iter = magicNodes_.rbegin();
    while (iter != magicNodes_.rend()) {
        auto& layoutList = (*iter).second;
        for (auto& node : layoutList) {
            auto childLayoutWrapper = node.layoutWrapper;
            float childLayoutWeight = 0.0f;
            const auto& childLayoutProperty = childLayoutWrapper->GetLayoutProperty();
            const auto& magicItemProperty = childLayoutProperty->GetMagicItemProperty();
            if (magicItemProperty) {
                childLayoutWeight = magicItemProperty->GetLayoutWeightValue();
            }
            if (LessOrEqual(childLayoutWeight, 0)) {
                continue;
            }
            float childFlexSize = spacePerWeight * childLayoutWeight;
            childConstraint = MakeLayoutConstraint(childFlexSize, childConstraint, false, false);
            isExceed = isExceed || GetMainAxisSizeHelper(childConstraint.minSize, direction_) > childFlexSize;
            node.layoutConstraint = childConstraint;
        }
        if (!isExceed) {
            iter++;
        } else if (magicNodes_.size() <= 1) {
            break;
        } else {
            totalFlexWeight_ -= magicNodeWeights_[magicNodes_.begin()->first];
            spacePerWeight = maxMainAxisSize / totalFlexWeight_;
            isExceed = false;
            magicNodes_.erase(magicNodes_.begin());
            iter = magicNodes_.rbegin();
        }
    }

    MeasureMagicNodes(layoutWrapper, baselineProperties);
    if (crossAxisAlign_ == FlexAlign::STRETCH) {
        RedoLayoutForStretchMagicNode();
    }

    realSize.UpdateIllegalSizeWithCheck(GetCalcSizeHelper(maxMainAxisSize, crossAxisSize_, direction_));
    layoutWrapper->GetGeometryNode()->SetFrameSize(realSize.ConvertToSizeT());
}

void FlexLayoutAlgorithm::MeasureInIndexMode(LayoutWrapper* layoutWrapper) {}

void FlexLayoutAlgorithm::MeasureInItemMode(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& parentIdealSize = layoutConstraint->parentIdealSize;
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    OptionalSizeF realSize;
    /**
     * check selfIdealSize and matchParent.
     */
    do {
        realSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (realSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            realSize.UpdateIllegalSizeWithCheck(parentIdealSize);
        }
    } while (false);
    SizeF maxSize;
    maxSize.UpdateSizeWithCheck(layoutConstraint->maxSize);
    maxSize.UpdateSizeWhenSmaller(realSize.ConvertToSizeT());
    float maxMainAxisSize = GetMainAxisSizeHelper(maxSize, direction_);
    mainSize_ = maxMainAxisSize;
    if (NearEqual(maxMainAxisSize, Infinity<float>())) {
        LOGW("not supported infinite size");
        return;
    }
    selfIdealCrossAxisSize_ = GetCrossAxisSizeHelper(realSize.ConvertToSizeT(), direction_);

    BaselineProperties baselineProperties;
    FlexItemProperties flexItemProperties;
    auto childConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    float allocatedSize = allocatedSize_;
    /**
     * first time measure;
     */
    auto iter = magicNodes_.rbegin();
    while (iter != magicNodes_.rend()) {
        auto& layoutList = (*iter).second;
        for (auto& node : layoutList) {
            auto childLayoutWrapper = node.layoutWrapper;
            float childLayoutWeight = 0.0f;
            const auto& magicItemProperty = childLayoutWrapper->GetLayoutProperty()->GetMagicItemProperty();
            if (magicItemProperty) {
                childLayoutWeight = magicItemProperty->GetLayoutWeightValue();
            }
            if (LessOrEqual(childLayoutWeight, 0.0f)) {
                childLayoutWrapper->Measure(childConstraint);
                ResizeFlexSizeByItem(childLayoutWrapper, allocatedSize);
                CheckSizeValidity(childLayoutWrapper);
                CheckBaselineProperties(childLayoutWrapper, baselineProperties);
            }
            const auto& flexItemProperty = childLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
            if (flexItemProperty) {
                float itemShrink = flexItemProperty->GetFlexShrink().value_or(1.0f);
                float itemGrow = flexItemProperty->GetFlexGrow().value_or(0.0f);
                if (itemGrow > 0) {
                    flexItemProperties.lastGrowChild = childLayoutWrapper;
                }
                if (itemShrink > 0) {
                    flexItemProperties.lastShrinkChild = childLayoutWrapper;
                }
                flexItemProperties.totalShrink += itemShrink * GetMainAxisSize(childLayoutWrapper);
                flexItemProperties.totalGrow += itemGrow;
            }
        }
        iter++;
    }

    /**
     * second time measure;
     */
    ResizeItems(flexItemProperties, baselineProperties);
    auto layoutList = (*magicNodes_.rbegin()).second;
    realSize.UpdateIllegalSizeWithCheck(GetCalcSizeHelper(maxMainAxisSize, crossAxisSize_, direction_));
    layoutWrapper->GetGeometryNode()->SetFrameSize(realSize.ConvertToSizeT());
}

void FlexLayoutAlgorithm::ResizeItems(const FlexItemProperties& flexItemProps, BaselineProperties& baselineProps)
{
    float remainSpace = mainSize_ - allocatedSize_;
    float spacePerFlex = 0;
    float allocatedFlexSpace = 0;
    std::function<float(const RefPtr<LayoutWrapper>&)> getFlex;
    RefPtr<LayoutWrapper> lastChild;
    if (remainSpace > 0.0f) {
        getFlex = [](const RefPtr<LayoutWrapper>& item) -> float {
            const auto& flexItemProperty = item->GetLayoutProperty()->GetFlexItemProperty();
            float ret = 0.0f;
            if (flexItemProperty) {
                ret = flexItemProperty->GetFlexGrow().value_or(0.0f);
            }
            return ret;
        };

        spacePerFlex = NearZero(flexItemProps.totalGrow) ? 0.0f : remainSpace / flexItemProps.totalGrow;
        lastChild = flexItemProps.lastGrowChild;
    } else {
        getFlex = [](const RefPtr<LayoutWrapper>& item) -> float {
            const auto& flexItemProperty = item->GetLayoutProperty()->GetFlexItemProperty();
            float ret = 0.0f;
            if (flexItemProperty) {
                ret = flexItemProperty->GetFlexShrink().value_or(1.0f);
            }
            return ret;
        };
        spacePerFlex = NearZero(flexItemProps.totalShrink) ? 0.0f : remainSpace / flexItemProps.totalShrink;
        lastChild = flexItemProps.lastShrinkChild;
    }
    auto iter = magicNodes_.rbegin();
    while (iter != magicNodes_.rend()) {
        auto& layoutList = (*iter).second;
        for (auto& node : layoutList) {
            float itemFlex = getFlex(node.layoutWrapper);
            float flexSize = node.layoutWrapper == lastChild ? (remainSpace - allocatedFlexSpace)
                             : remainSpace > 0.0f            ? spacePerFlex * itemFlex
                                                  : spacePerFlex * itemFlex * GetMainAxisSize(node.layoutWrapper);
            RedoLayoutFlexItem(node, flexSize, baselineProps, allocatedFlexSpace);
        }
        iter++;
    }
}

void FlexLayoutAlgorithm::RedoLayoutFlexItem(
    const MagicLayoutNode& flexItem, float flexSize, BaselineProperties& baselineProps, float& allocatedFlexSpace)
{
    auto mainFlexExtent = flexSize + GetMainAxisSize(flexItem.layoutWrapper);
    // auto childMainContent = GetMainAxisSize(
    //     flexItem.layoutWrapper->GetLayoutProperty()->GetContentLayoutConstraint()->selfIdealSize.ConvertToSizeT(),
    //     direction_);
    allocatedSize_ -= GetMainAxisSize(flexItem.layoutWrapper);
    const auto& layoutConstraint = MakeLayoutConstraint(
        mainFlexExtent, flexItem.layoutConstraint, GetSelfAlign(flexItem.layoutWrapper) == FlexAlign::STRETCH, false);
    flexItem.layoutWrapper->Measure(layoutConstraint);
    allocatedFlexSpace += flexSize;
    allocatedSize_ -= space_;
    ResizeFlexSizeByItem(flexItem.layoutWrapper, allocatedSize_);
    CheckBaselineProperties(flexItem.layoutWrapper, baselineProps);
}

void FlexLayoutAlgorithm::MeasureMagicNodes(LayoutWrapper* layoutWrapper, BaselineProperties& baselineProperties)
{
    float allocatedSize = allocatedSize_;
    for (const auto& magicNode : magicNodes_) {
        auto childList = magicNode.second;
        for (const auto& child : childList) {
            const auto& childLayoutWrapper = child.layoutWrapper;
            const auto& magicItemProperty = childLayoutWrapper->GetLayoutProperty()->GetMagicItemProperty();
            if (!magicItemProperty) {
                continue;
            }
            float childLayoutWeight = magicItemProperty->GetLayoutWeightValue();
            if (LessOrEqual(childLayoutWeight, 0.0f)) {
                continue;
            }
            const auto& layoutConstraint = child.layoutConstraint;
            childLayoutWrapper->Measure(layoutConstraint);
            ResizeFlexSizeByItem(childLayoutWrapper, allocatedSize);
            CheckSizeValidity(childLayoutWrapper);
            CheckBaselineProperties(childLayoutWrapper, baselineProperties);
        }
    }
}

void FlexLayoutAlgorithm::RedoLayoutForStretchMagicNode()
{
    auto childLayoutConstraint = layoutWrapper_->GetLayoutProperty()->CreateChildConstraint();
    for (const auto& magicNodeMap : magicNodes_) {
        auto nodeList = magicNodeMap.second;
        for (const auto& node : nodeList) {
            auto childLayoutWrapper = node.layoutWrapper;
            childLayoutConstraint =
                MakeLayoutConstraint(GetMainAxisSize(childLayoutWrapper), childLayoutConstraint, true);
            childLayoutWrapper->Measure(childLayoutConstraint);
            crossAxisSize_ = std::max(crossAxisSize_, GetCrossAxisSize(childLayoutWrapper));
        }
    }
}

void FlexLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        LOGE("FlexLayoutAlgorithm::Layout, children is empty");
        return;
    }
    BaselineProperties baselineProperties;
    float remainSpace = std::max(mainSize_ - allocatedSize_, 0.0f);
    float frontSpace = 0.0f;
    float betweenSpace = 0.0f;
    CalculateSpace(remainSpace, frontSpace, betweenSpace);
    PlaceChildren(layoutWrapper, frontSpace, betweenSpace, baselineProperties);
}

void FlexLayoutAlgorithm::CalculateSpace(float remainSpace, float& frontSpace, float& betweenSpace) const
{
    if (NearZero(remainSpace) && mainAxisAlign_ != FlexAlign::SPACE_CUSTOMIZATION) {
        return;
    }
    switch (mainAxisAlign_) {
        case FlexAlign::FLEX_START:
            frontSpace = 0.0f;
            betweenSpace = 0.0f;
            break;
        case FlexAlign::FLEX_END:
            frontSpace = remainSpace;
            betweenSpace = 0.0f;
            break;
        case FlexAlign::CENTER:
            frontSpace = remainSpace / 2;
            betweenSpace = 0.0f;
            break;
        case FlexAlign::SPACE_BETWEEN:
            frontSpace = 0.0f;
            betweenSpace = validSizeCount_ > 1 ? remainSpace / static_cast<float>(validSizeCount_ - 1) : 0.0f;
            break;
        case FlexAlign::SPACE_AROUND:
            betweenSpace = validSizeCount_ > 0 ? remainSpace / static_cast<float>(validSizeCount_) : 0.0f;
            frontSpace = betweenSpace / 2;
            break;
        case FlexAlign::SPACE_EVENLY:
            betweenSpace = validSizeCount_ > 0 ? remainSpace / static_cast<float>(validSizeCount_ + 1) : 0.0f;
            frontSpace = betweenSpace;
            break;
        case FlexAlign::SPACE_CUSTOMIZATION:
            betweenSpace = space_;
            frontSpace = 0.0f;
            break;
        default:
            break;
    }
    LOGD("CalculateSpace end front space is %{public}f, between space is %{public}f, remain space is %{public}f",
        frontSpace, betweenSpace, remainSpace);
}

void FlexLayoutAlgorithm::PlaceChildren(
    LayoutWrapper* layoutWrapper, float frontSpace, float betweenSpace, const BaselineProperties& baselineProperties)
{
    LOGD("Place children, direction %{public}d, frontSpace %{public}f, betweenSpace %{public}f", direction_, frontSpace,
        betweenSpace);
    float childMainPos = IsStartTopLeft(direction_, TextDirection::LTR) ? frontSpace : mainSize_ - frontSpace;
    float childCrossPos = 0.0f;
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& child : children) {
        auto alignItem = GetSelfAlign(child);
        auto textDirection = AdjustTextDirectionByDir();
        switch (alignItem) {
            case FlexAlign::FLEX_START:
            case FlexAlign::FLEX_END:
                childCrossPos =
                    (IsStartTopLeft(FlipAxis(direction_), textDirection) == (alignItem == FlexAlign::FLEX_START))
                        ? 0
                        : (crossAxisSize_ - GetCrossAxisSize(child));
                break;
            case FlexAlign::CENTER:
                childCrossPos = (crossAxisSize_ / 2) - (GetCrossAxisSize(child) / 2);
                break;
            case FlexAlign::STRETCH:
                childCrossPos = IsStartTopLeft(FlipAxis(direction_), textDirection)
                                    ? 0
                                    : (crossAxisSize_ - GetCrossAxisSize(child));
                break;
            case FlexAlign::BASELINE:
            default:
                break;
        }
        OffsetF offset;
        if (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) {
            offset = OffsetF(childMainPos, childCrossPos);
        } else {
            offset = OffsetF(childCrossPos, childMainPos);
        }

        if (!IsStartTopLeft(direction_, TextDirection::LTR)) {
            if (direction_ != FlexDirection::COLUMN_REVERSE) {
                offset.SetX(offset.GetX() - GetMainAxisSize(child));
            } else {
                offset.SetY(offset.GetY() - GetMainAxisSize(child));
            }
            child->GetGeometryNode()->SetFrameOffset(offset);
            childMainPos -= GetMainAxisSize(child) + betweenSpace;
        } else {
            child->GetGeometryNode()->SetFrameOffset(offset);
            childMainPos += GetMainAxisSize(child) + betweenSpace;
        }
    }
}

FlexAlign FlexLayoutAlgorithm::GetSelfAlign(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    const auto& flexItemProperty = layoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    const auto& magicItemProperty = layoutWrapper->GetLayoutProperty()->GetMagicItemProperty();
    if (!magicItemProperty) {
    }
    CHECK_NULL_RETURN(flexItemProperty, crossAxisAlign_);
    return flexItemProperty->GetAlignSelf().value_or(crossAxisAlign_);
}

TextDirection FlexLayoutAlgorithm::AdjustTextDirectionByDir() const
{
    auto textDir = TextDirection::RTL;
    if (direction_ == FlexDirection::ROW_REVERSE) {
        textDir = textDir == TextDirection::RTL ? TextDirection::LTR : TextDirection::RTL;
    }
    return textDir;
}

} // namespace OHOS::Ace::NG
