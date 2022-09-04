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

#include "flex_layout_algorithm.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {


float FlexLayoutAlgorithm::GetMainSize(const SizeF& size, FlexDirection direction) const
{
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return size.Width();
    }
    return size.Height();
}

float FlexLayoutAlgorithm::GetMainSize(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    float size = 0.0f;
    if (!layoutWrapper) {
        return size;
    }
    if (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    } else {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
    }
    return size;
}

float FlexLayoutAlgorithm::GetCrossSize(const SizeF& size, FlexDirection direction) const
{
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return size.Height();
    }
    return size.Width();
}

float FlexLayoutAlgorithm::GetCrossSize(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    float size = 0.0f;
    if (!layoutWrapper) {
        return size;
    }
    if (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
    } else {
        size = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    }
    return size;
}

OptionalSizeF FlexLayoutAlgorithm::GetCalcSize(float mainSize, float crossSize)
{
    OptionalSizeF size;
    if (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) {
        size.SetWidth(mainSize);
        size.SetHeight(crossSize);
    } else {
        size.SetHeight(mainSize);
        size.SetWidth(crossSize);
    }
    return size;
}

void FlexLayoutAlgorithm::CheckSizeValidity(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    if (!layoutWrapper->GetGeometryNode()->GetFrameSize().IsPositive()) {
        return;
    }
    ++validSizeCount_;
}

void FlexLayoutAlgorithm::CheckBaselineProperties(const RefPtr<LayoutWrapper>& layoutWrapper, BaselineProperties& baselineProperties)
{
}

void FlexLayoutAlgorithm::InitFlexProperties(LayoutWrapper* layoutWrapper)
{
    mainSize_ = 0.0;
    crossSize_ = 0.0;
    allocatedSize_ = 0.0;
    layoutMode_ = FlexLayoutMode::FLEX_WEIGHT_MODE;
    totalFlexWeight_ = 0.0;
    maxDisplayPriority_ = 0;
    layoutWrapper_ = layoutWrapper;
    direction_ = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty())->GetFlexDirection().value_or(FlexDirection::ROW);
    mainAxisAlign_ = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty())->GetMainAxisAlignValue(FlexAlign::FLEX_START);
    crossAxisAlign_ = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty())->GetCrossAxisAlignValue(FlexAlign::FLEX_START);
    TravelChildrenFlexProps(layoutWrapper);
}

void FlexLayoutAlgorithm::TravelChildrenFlexProps(LayoutWrapper* layoutWrapper)
{
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& child: children) {
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
            magicNodes_.insert(std::map<int32_t, std::list<MagicLayoutNode>>::value_type(childDisplayPriority, {node}));
            if (childLayoutWeight > 0) {
                magicNodeWeights_.insert(std::map<int32_t, float>::value_type(childDisplayPriority, childLayoutWeight));
                totalFlexWeight_ += childLayoutWeight;
            }
        } else {
            magicNodes_[childDisplayPriority].emplace_back(node);
            if (childLayoutWeight > 0) {
                magicNodeWeights_[childDisplayPriority] += childLayoutWeight;
                totalFlexWeight_ += childLayoutWeight;
            }
        }
        maxDisplayPriority_ = std::max(childDisplayPriority, maxDisplayPriority_);
    }
    layoutMode_ = LessOrEqual(totalFlexWeight_, 0.0) ? FlexLayoutMode::FLEX_ITEM_MODE : FlexLayoutMode::FLEX_WEIGHT_MODE;
}

void FlexLayoutAlgorithm::ResizeByItem(const RefPtr<LayoutWrapper>& childLayoutWrapper, float& allocatedSize)
{
    float mainSize = GetMainSize(childLayoutWrapper);
    if (NearEqual(mainSize, Size::INFINITE_SIZE)) {
        mainSize = 0.0;
        infinityLayoutNodes_.insert(childLayoutWrapper);
    }
    crossSize_ = std::max(crossSize_, GetCrossSize(childLayoutWrapper));
    allocatedSize_ +=  mainSize;
    allocatedSize_ += space_;
    allocatedSize += mainSize;
    allocatedSize += space_;
}

void FlexLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        LOGD("FlexLayoutAlgorithm::Measure, children is empty");
        layoutWrapper->GetGeometryNode()->SetFrameSize(realSize_.ConvertToSizeT());
        return;
    }
    InitFlexProperties(layoutWrapper);
    LOGD("FlexLayoutAlgorithm::Measure, layoutMode = %{public}d", layoutMode_);
    if (layoutMode_ == FlexLayoutMode::FLEX_WEIGHT_MODE) {
        MeasureInWeightMode(layoutWrapper);
    } else if (maxDisplayPriority_ > 1) {
        MeasureInIndexMode(layoutWrapper);
    } else {
        MeasureInItemMode(layoutWrapper);
    }

}

float FlexLayoutAlgorithm::GetStretchCrossLimit() const
{
    float crossAxisLimit = 0.0f;
    if (GreatNotEqual(selfIdealCrossSize_, -1.0f)) {
        crossAxisLimit = selfIdealCrossSize_;
    } else {
        crossAxisLimit = crossSize_;
    }
    return crossAxisLimit;
}

LayoutConstraintF FlexLayoutAlgorithm::MakeLayoutConstraint(float mainFlexExtent, const LayoutConstraintF& constraint, bool isStretch, bool supportZero) const
{
    LayoutConstraintF layoutConstraint;
    LOGD("FlexLayoutAlgorithm::MakeLayoutConstraint, mainFlexExtent = %{public}f, isStretch = %{public}s, supportZero = %{public}s", mainFlexExtent, isStretch ? "true" : "false", supportZero ? "true" : "false");
    if (LessNotEqual(mainFlexExtent, 0.0)) {
        layoutConstraint.UpdateMaxSizeWithCheck(layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint()->maxSize);
    } else if (GreatNotEqual(mainFlexExtent, 0.0)) {
        layoutConstraint = MakeLayoutConstraintWithLimit(mainFlexExtent, mainFlexExtent, isStretch);
    } else {
        if (supportZero) {
            layoutConstraint = MakeLayoutConstraintWithLimit(mainFlexExtent, mainFlexExtent, isStretch);
        } else {
            layoutConstraint.UpdateMaxSizeWithCheck(layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint()->maxSize);
        }
    }
    layoutConstraint.UpdateMaxSizeWithCheck(layoutConstraint.maxSize);
    layoutConstraint.UpdateMinSizeWithCheck(layoutConstraint.minSize);
    return layoutConstraint;
}

LayoutConstraintF FlexLayoutAlgorithm::MakeLayoutConstraintWithLimit(float minMainLimit, float maxMainLimit, bool isStretch) const
{
    LayoutConstraintF layoutConstraint;
    auto parentLayoutConstraint = layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint();
    float minCrossLimit = 0.0f;
    float maxCrossLimit = (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) ? parentLayoutConstraint->maxSize.Height() : parentLayoutConstraint->maxSize.Width();
    if (isStretch) {
        minCrossLimit = GetStretchCrossLimit();
        maxCrossLimit = minCrossLimit;
    }
    if (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) {
        layoutConstraint.UpdateMinSizeWithCheck(SizeF(minMainLimit, minCrossLimit));
        layoutConstraint.UpdateMaxSizeWithCheck(SizeF(maxMainLimit, maxCrossLimit));
    } else {
        layoutConstraint.UpdateMinSizeWithCheck(SizeF(minCrossLimit, minMainLimit));
        layoutConstraint.UpdateMaxSizeWithCheck(SizeF(maxCrossLimit, minMainLimit));
    }
    return layoutConstraint;
}

void FlexLayoutAlgorithm::MeasureInWeightMode(LayoutWrapper* layoutWrapper)
{
    LOGD("FlexLayoutAlgorithm::MeasureInWeightMode");
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
    } while(false);
    /**
     * get the user defined main axis size and cross axis size.
     */
    SizeF maxSize;
    maxSize.UpdateSizeWithCheck(layoutConstraint->maxSize);
    maxSize.UpdateSizeWhenSmaller(realSize.ConvertToSizeT());
    float maxMainSize = GetMainSize(maxSize, direction_);
    LOGD("FlexLayoutAlgorithm::MeasureInWeightMode, maxMainSize = %{public}f", maxMainSize);
    if (NearEqual(maxMainSize, Size::INFINITE_SIZE)) {
        LOGW("not supported infinite size");
        return;
    }
    selfIdealCrossSize_ = GetCrossSize(realSize.ConvertToSizeT(), direction_);
    LOGD("selfIdealCrossSize_ = %{public}f", selfIdealCrossSize_);
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
            if (LessOrEqual(childLayoutWeight, 0.0)) {
                childLayoutWrapper->Measure(childConstraint);
                ResizeByItem(childLayoutWrapper, allocatedSize);
                CheckSizeValidity(childLayoutWrapper);
                CheckBaselineProperties(childLayoutWrapper, baselineProperties);
            }
        }
        iter++;
    }

    maxMainSize -= allocatedSize_;
    if (LessOrEqual(maxMainSize, 0)) {
        return;
    }

    /**
     * measure magic nodes
     */
    auto spacePerWeight = maxMainSize / totalFlexWeight_;
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
            isExceed = isExceed || GetMainSize(childConstraint.minSize, direction_) > childFlexSize;
            node.layoutConstraint = childConstraint;
        }
        if (!isExceed) {
            iter++;
        } else if (magicNodes_.size() <= 1) {
            break;
        } else {
            totalFlexWeight_ -= magicNodeWeights_[magicNodes_.begin()->first];
            spacePerWeight = maxMainSize / totalFlexWeight_;
            isExceed = false;
            magicNodes_.erase(magicNodes_.begin());
            iter = magicNodes_.rbegin();
        }
    }

    MeasureMagicNodes(layoutWrapper, baselineProperties);
    if (crossAxisAlign_ == FlexAlign::STRETCH) {
        RelayoutForStretchMagicNode();
    }

    realSize.UpdateIllegalSizeWithCheck(GetCalcSize(maxMainSize, crossSize_));
    LOGD("realSize = %{public}s", realSize.ToString().c_str());
    layoutWrapper->GetGeometryNode()->SetFrameSize(realSize.ConvertToSizeT());
}

void FlexLayoutAlgorithm::MeasureInIndexMode(LayoutWrapper* layoutWrapper)
{
}

void FlexLayoutAlgorithm::MeasureInItemMode(LayoutWrapper* layoutWrapper)
{
}

void FlexLayoutAlgorithm::MeasureMagicNodes(LayoutWrapper* layoutWrapper, BaselineProperties& baselineProperties)
{
    float allocatedSize = allocatedSize_;
    LOGD("FlexLayoutAlgorithm::MeasureMagicNodes");
    for (const auto& magicNode : magicNodes_) {
        auto childList = magicNode.second;
        for (const auto& child : childList) {
            const auto& childLayoutWrapper = child.layoutWrapper;
            const auto& magicItemProperty = childLayoutWrapper->GetLayoutProperty()->GetMagicItemProperty();
            if (!magicItemProperty) {
                continue;
            }
            float childLayoutWeight = magicItemProperty->GetLayoutWeightValue();
            if (LessOrEqual(childLayoutWeight, 0.0)) {
                continue;
            }
            const auto& layoutConstraint = child.layoutConstraint;
            childLayoutWrapper->Measure(layoutConstraint);
            ResizeByItem(childLayoutWrapper, allocatedSize);
            CheckSizeValidity(childLayoutWrapper);
            CheckBaselineProperties(childLayoutWrapper, baselineProperties);
        }
    }
}

void FlexLayoutAlgorithm::RelayoutForStretchMagicNode()
{
    auto childLayoutConstraint = layoutWrapper_->GetLayoutProperty()->CreateChildConstraint();
    for (const auto& magicNodeMap : magicNodes_) {
        auto nodeList = magicNodeMap.second;
        for (const auto& node : nodeList) {
            auto childLayoutWrapper = node.layoutWrapper;
            childLayoutConstraint = MakeLayoutConstraint(GetMainSize(childLayoutWrapper), childLayoutConstraint, true);
            childLayoutWrapper->Measure(childLayoutConstraint);
            crossSize_ = std::max(crossSize_, GetCrossSize(childLayoutWrapper));
        }
    }
}

void FlexLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    LOGD("FlexLayoutAlgorithm::Layout");
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        LOGD("FlexLayoutAlgorithm::Layout, children is empty");
        return;
    }
    BaselineProperties baselineProperties;
    float remainSpace = (mainSize_ - allocatedSize_) > 0.0 ? (mainSize_ - allocatedSize_) : 0.0;
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
            frontSpace = 0.0;
            betweenSpace = 0.0;
            break;
        case FlexAlign::FLEX_END:
            frontSpace = remainSpace;
            betweenSpace = 0.0;
            break;
        case FlexAlign::CENTER:
            frontSpace = remainSpace / 2;
            betweenSpace = 0.0;
            break;
        case FlexAlign::SPACE_BETWEEN:
            frontSpace = 0.0;
            betweenSpace = validSizeCount_ > 1 ? remainSpace / static_cast<float>(validSizeCount_ - 1) : 0;
            break;
        case FlexAlign::SPACE_AROUND:
            betweenSpace = validSizeCount_ > 0 ? remainSpace / static_cast<float>(validSizeCount_) : 0;
            frontSpace = betweenSpace / 2;
            break;
        case FlexAlign::SPACE_EVENLY:
            betweenSpace = validSizeCount_ > 0 ? remainSpace / static_cast<float>(validSizeCount_ + 1) : 0;
            frontSpace = betweenSpace;
            break;
        case FlexAlign::SPACE_CUSTOMIZATION:
            betweenSpace = space_;
            frontSpace = 0.0;
            break;
        default:
            break;
    }
}

void FlexLayoutAlgorithm::PlaceChildren(LayoutWrapper* layoutWrapper, float frontSpace, float betweenSpace, const BaselineProperties& baselineProperties)
{
    float childMainPos = IsStartTopLeft(direction_, TextDirection::LTR) ? frontSpace : mainSize_ - frontSpace;
    float childCrossPos = 0.0f;
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& child : children) {
//        if (child->IsIgnored()) {
//            continue;
//        }
        auto alignItem = GetSelfAlign(child);
        auto textDirection = AdjustTextDirectionByDir();
        switch (alignItem) {
            case FlexAlign::FLEX_START:
            case FlexAlign::FLEX_END:
                childCrossPos = (IsStartTopLeft(FlipAxis(direction_), textDirection) == (alignItem == FlexAlign::FLEX_START)) ? 0 : (crossSize_ - GetCrossSize(child));
                break;
            case FlexAlign::CENTER:
                childCrossPos = (crossSize_ / 2) - (GetCrossSize(child) / 2);
                break;
            case FlexAlign::STRETCH:
                childCrossPos = IsStartTopLeft(FlipAxis(direction_), textDirection) ? 0 : (crossSize_ - GetCrossSize(child));
                break;
            case FlexAlign::BASELINE:
            default:
                break;
        }

        OffsetF offset;
        if (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) {
//            if (item->GetPositionType() == PositionType::SEMI_RELATIVE) {
//                childMainPos = 0.0;
//            }
            offset = OffsetF(childMainPos, childCrossPos);
        } else {
//            offset = Offset((item->GetPositionType() == PositionType::SEMI_RELATIVE) ? 0.0 : childCrossPos, childMainPos);
            offset = OffsetF(childCrossPos, childMainPos);
        }

        if (!IsStartTopLeft(direction_, TextDirection::LTR)) {
            if (direction_ != FlexDirection::COLUMN_REVERSE) {
                offset.SetX(offset.GetX() - GetMainSize(child));
            } else {
                offset.SetY(offset.GetY() - GetMainSize(child));
            }
            child->GetGeometryNode()->SetFrameOffset(offset);
            childMainPos -= GetMainSize(child) + betweenSpace;
        } else {
            child->GetGeometryNode()->SetFrameOffset(offset);
            childMainPos += GetMainSize(child) + betweenSpace;
        }
    }
}

bool FlexLayoutAlgorithm::IsStartTopLeft(FlexDirection direction, TextDirection textDirection) const
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

FlexAlign FlexLayoutAlgorithm::GetSelfAlign(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    const auto& flexItemProperty = layoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    const auto& magicItemProperty = layoutWrapper->GetLayoutProperty()->GetMagicItemProperty();
    if (!magicItemProperty) {
    }
    if (!flexItemProperty) {
        return crossAxisAlign_;
    }
    auto alignSelf = flexItemProperty->GetAlignSelf().value_or(crossAxisAlign_);
    return alignSelf;

}

TextDirection FlexLayoutAlgorithm::AdjustTextDirectionByDir() const
{
    auto textDir = TextDirection::RTL;
    if (direction_ == FlexDirection::ROW_REVERSE) {
        textDir = textDir == TextDirection::RTL ? TextDirection::LTR : TextDirection::RTL;
    }
    return textDir;
}

FlexDirection FlexLayoutAlgorithm::FlipAxis(FlexDirection direction) const
{
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return FlexDirection::COLUMN;
    }
    return FlexDirection::ROW;
}
} // namespace OHOS::Ace::NG
