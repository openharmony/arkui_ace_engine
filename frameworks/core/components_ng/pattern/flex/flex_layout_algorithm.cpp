//
// Created by 陆泽辉 on 2022/8/8.
//

#include "flex_layout_algorithm.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {


float FlexLayoutAlgorithm::GetMainSize(const SizeF& size, FlexDirection direction) const {
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return size.Width();
    }
    return size.Height();
}

float FlexLayoutAlgorithm::GetMainSize(const RefPtr<LayoutWrapper>& layoutWrapper) const {
    float size = 0.0;
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

float FlexLayoutAlgorithm::GetCrossSize(const SizeF& size, FlexDirection direction) const {
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return size.Height();
    }
    return size.Width();
}

float FlexLayoutAlgorithm::GetCrossSize(const RefPtr<LayoutWrapper>& layoutWrapper) const {
    float size = 0.0;
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

void FlexLayoutAlgorithm::CheckSizeValidity(const RefPtr<LayoutWrapper>& layoutWrapper) {
//    if (item->IsIgnored() || IsNonRelativePosition(item->GetPositionType())) {
//        return;
//    }
    if (!layoutWrapper->GetGeometryNode()->GetFrameSize().IsValid()) {
        return;
    }
    ++validSizeCount_;
}

void FlexLayoutAlgorithm::CheckBaselineProperties(const RefPtr<LayoutWrapper>& layoutWrapper, BaselineProperties& baselineProperties) {
}

void FlexLayoutAlgorithm::InitFlexProperties(LayoutWrapper* layoutWrapper) {
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

void FlexLayoutAlgorithm::TravelChildrenFlexProps(LayoutWrapper* layoutWrapper) {
    std::list<RefPtr<LayoutWrapper>> children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& child: children) {
        /**
         * FIXME: no handle absolute child.
         */
//        if (IsNonRelativePosition(child->GetPositionType())) {
//            absoluteNodes_.insert(child);
//            continue;
//        }
        relativeNodes_.emplace_back(child);
        const auto& childLayoutProperty = child->GetLayoutProperty();
        const auto& childMagicItemProperty = childLayoutProperty->GetMagicItemProperty();
        MagicLayoutNode node;
        node.layoutWrapper = child;
        int32_t childDisplayPriority = 1;
        float childLayoutWeight = -1.0;
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
    /**
     * FIXME: no handle absolute node.
     */
//    if (relativeNodes_.empty() && !absoluteNodes_.empty()) {
//        layoutMode_ = FlexLayoutMode::FLEX_ITEM_MODE;
//    }
}

void FlexLayoutAlgorithm::ResizeByItem(const RefPtr<LayoutWrapper>& childLayoutWrapper, float& allocatedSize) {
    float mainSize = GetMainSize(childLayoutWrapper);
    if (NearEqual(mainSize, Size::INFINITE_SIZE)) {
        mainSize = 0.0;
        infinityLayoutNodes_.insert(childLayoutWrapper);
    }
    /**
     * FIXME: no handle absolute node;
     */
//    if (IsNonRelativePosition(item->GetPositionType())) {
//        return;
//    }
    /**
     * SEMI_Relative 指的是x轴基于父容器，y轴基于自身；
     */
    crossSize_ = std::max(crossSize_, GetCrossSize(childLayoutWrapper));
    allocatedSize_ +=  mainSize;
    allocatedSize_ += space_;
    allocatedSize += mainSize;
    allocatedSize += space_;
}

void FlexLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper) {
    LOGD("FlexLayoutAlgorithm::Measure");
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        LOGD("FlexLayoutAlgorithm::Measure, children is empty");
        layoutWrapper->GetGeometryNode()->SetFrameSize(realSize_);
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

float FlexLayoutAlgorithm::GetStretchCrossLimit() const {
    SizeF maxLayoutConstraint = layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint()->maxSize;
    float crossAxisLimit = 0.0;
    if (!stretchToParent_) {
        crossAxisLimit = crossSize_;
    } else if (!isCrossInfinite_ || !useViewPort_) {
        crossAxisLimit = (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) ? maxLayoutConstraint.Height() : maxLayoutConstraint.Width();
    } else {
        /**
         * FIXME: no handle viewport size;
         */
//        crossAxisLimit = (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) ? viewPort_.Height() : viewPort_.Width();
    }
    return crossAxisLimit;
}

LayoutConstraintF FlexLayoutAlgorithm::MakeLayoutConstraint(float mainFlexExtent, const LayoutConstraintF& constraint, bool isStretch, bool supportZero) const {
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

LayoutConstraintF FlexLayoutAlgorithm::MakeLayoutConstraintWithLimit(float minMainLimit, float maxMainLimit, bool isStretch) const {
    LayoutConstraintF layoutConstraint;
    auto parentLayoutConstraint = layoutWrapper_->GetLayoutProperty()->GetLayoutConstraint();
    float minCrossLimit = 0.0;
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

void FlexLayoutAlgorithm::MeasureInWeightMode(LayoutWrapper* layoutWrapper) {
    LOGD("FlexLayoutAlgorithm::MeasureInWeightMode");
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    float maxMainSize = GetMainSize(layoutConstraint->maxSize, direction_);
    LOGD("FlexLayoutAlgorithm::MeasureInWeightMode, maxMainSize = %{public}f", maxMainSize);
    if (NearEqual(maxMainSize, Size::INFINITE_SIZE)) {
        LOGW("not supported infinite size");
        return;
    }
    if (!relativeNodes_.empty()) {
        maxMainSize -= space_ * static_cast<float>((relativeNodes_.size() - 1));
    }
    BaselineProperties baselineProperties;
    auto childConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint().value();
    float allocatedSize = allocatedSize_;
    for (const auto& child : relativeNodes_) {
        const auto& magicItemProperty = child->GetLayoutProperty()->GetMagicItemProperty();
        float childLayoutWeight = -1.0;
        if (magicItemProperty) {
            childLayoutWeight = magicItemProperty->GetLayoutWeight().value_or(-1);
        }
        if (LessOrEqual(childLayoutWeight, 0.0)) {
            child->Measure(childConstraint);
            ResizeByItem(child, allocatedSize);
            CheckSizeValidity(child);
            CheckBaselineProperties(child, baselineProperties);
        }
    }
    maxMainSize -= allocatedSize_;
    // if remain size less than zero, adjust it to zero
//    if (!useOldLayoutVersion_ && LessNotEqual(maxMainSize, 0.0)) {
//        maxMainSize = 0.0;
//    }

    auto spacePerWeight = maxMainSize / totalFlexWeight_;
    bool isExceed = false;
    auto iter = magicNodes_.rbegin();
    while (iter != magicNodes_.rend()) {
        auto& layoutList = (*iter).second;
        for (auto& node : layoutList) {
            auto childLayoutWrapper = node.layoutWrapper;
            const auto& childLayoutProperty = childLayoutWrapper->GetLayoutProperty();
            const auto& magicItemProperty = childLayoutProperty->GetMagicItemProperty();
            if (!magicItemProperty) {
                continue;
            }
            float childLayoutWeight = magicItemProperty->GetLayoutWeightValue();
            if (LessOrEqual(childLayoutWeight, 0.0)) {
                continue;
            }
            float childFlexSize = spacePerWeight * childLayoutWeight;
//            isExceed = isExceed || GetMainSize() > childFlexSize;
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
    /**
     * FIXME: no handle absolute children and hidden nodes;
     */
//    LayoutAbsoluteChildren();
//    LayoutHiddenNodes();

    SizeF idealSize = {-1, -1};
    const auto& parentIdealSize = layoutConstraint->parentIdealSize;
//    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    if (layoutConstraint->selfIdealSize.has_value()) {
        const auto& selfIdealSize = layoutConstraint->selfIdealSize.value();
        idealSize.UpdateSizeWithCheck(selfIdealSize);
    } else if (measureType == MeasureType::MATCH_PARENT && parentIdealSize.has_value()) {
        idealSize.UpdateIllegalSizeWithCheck(*parentIdealSize);
    }
    realSize_ = idealSize;
    idealSize.UpdateIllegalSizeWithCheck(maxSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(realSize_);
    mainSize_ = GetMainSize(realSize_, direction_);
    crossSize_ = (direction_ == FlexDirection::ROW || direction_ == FlexDirection::ROW_REVERSE) ? realSize_.Height() : realSize_.Width();
}

void FlexLayoutAlgorithm::MeasureInIndexMode(LayoutWrapper* layoutWrapper) {
}

void FlexLayoutAlgorithm::MeasureInItemMode(LayoutWrapper* layoutWrapper) {
}

void FlexLayoutAlgorithm::MeasureMagicNodes(LayoutWrapper* layoutWrapper, BaselineProperties& baselineProperties) {
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

void FlexLayoutAlgorithm::RelayoutForStretchMagicNode() {
    auto childLayoutConstraint = layoutWrapper_->GetLayoutProperty()->CreateChildConstraint().value();
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

void FlexLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper) {
    LOGD("FlexLayoutAlgorithm::Layout");
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        LOGD("FlexLayoutAlgorithm::Layout, children is empty");
        return;
    }
    BaselineProperties baselineProperties;
    float remainSpace = (mainSize_ - allocatedSize_) > 0.0 ? (mainSize_ - allocatedSize_) : 0.0;
    float frontSpace = 0.0;
    float betweenSpace = 0.0;
    CalculateSpace(remainSpace, frontSpace, betweenSpace);
    PlaceChildren(layoutWrapper, frontSpace, betweenSpace, baselineProperties);
}

void FlexLayoutAlgorithm::CalculateSpace(float remainSpace, float& frontSpace, float& betweenSpace) const {
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
            frontSpace = betweenSpace / 2.0;
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

void FlexLayoutAlgorithm::PlaceChildren(LayoutWrapper* layoutWrapper, float frontSpace, float betweenSpace, const BaselineProperties& baselineProperties) {
    float childMainPos = IsStartTopLeft(direction_, TextDirection::LTR) ? frontSpace : mainSize_ - frontSpace;
    float childCrossPos = 0.0;
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& child : children) {
//        if (child->IsIgnored()) {
//            continue;
//        }
//        auto flexItem = AceType::DynamicCast<RenderFlexItem>(item);
//        if (flexItem && flexItem->IsHidden() && !flexItem->GetLayoutSize().IsValid()) {
//            continue;
//        }
//        if (IsNonRelativePosition(item->GetPositionType())) {
//            Offset absoluteOffset = PositionLayoutUtils::GetAbsoluteOffset(Claim(this), item);
//            item->SetAbsolutePosition(absoluteOffset);
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

bool FlexLayoutAlgorithm::IsStartTopLeft(FlexDirection direction, TextDirection textDirection) const {
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

FlexAlign FlexLayoutAlgorithm::GetSelfAlign(const RefPtr<LayoutWrapper>& layoutWrapper) const {
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

TextDirection FlexLayoutAlgorithm::AdjustTextDirectionByDir() const {
    auto textDir = TextDirection::RTL;
    if (direction_ == FlexDirection::ROW_REVERSE) {
        textDir = textDir == TextDirection::RTL ? TextDirection::LTR : TextDirection::RTL;
    }
    return textDir;
}

FlexDirection FlexLayoutAlgorithm::FlipAxis(FlexDirection direction) const {
    if (direction == FlexDirection::ROW || direction == FlexDirection::ROW_REVERSE) {
        return FlexDirection::COLUMN;
    }
    return FlexDirection::ROW;
}
} // namespace OHOS::Ace::NG
