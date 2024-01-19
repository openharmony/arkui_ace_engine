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

#include "core/components_ng/pattern/relative_container/relative_container_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_property.h"
#include "core/components_ng/property/flex_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HORIZONTAL_DIRECTION_RANGE = 3;
constexpr int32_t VERTICAL_DIRECTION_RANGE = 6;
constexpr float DEFAULT_BIAS = 0.5f;
inline bool IsAnchorContainer(const std::string& anchor)
{
    return anchor == "__container__";
}
} // namespace

float RelativeContainerLayoutAlgorithm::GetVerticalAlignTopValue(
    std::string& anchor, std::optional<float>& marginTop)
{
    auto result = 0.0f;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        result = IsAnchorContainer(anchor) ? 0.0f : recordOffsetMap_[anchor].GetY();
    } else {
        result = IsAnchorContainer(anchor)
                 ? 0.0f
                 : recordOffsetMap_[anchor].GetY() + marginTop.value_or(0);
    }
    return result;
}

float RelativeContainerLayoutAlgorithm::GetVerticalAlignCenterValue(
    std::string& anchor, std::optional<float>& marginTop)
{
    auto result = 0.0f;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Height() / 2.0f
                 : idNodeMap_[anchor]->GetGeometryNode()->GetMarginFrameSize().Height() / 2.0f +
                    recordOffsetMap_[anchor].GetY();
    } else {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Height() / 2.0f
                 : idNodeMap_[anchor]->GetGeometryNode()->GetFrameSize().Height() / 2.0f +
                    recordOffsetMap_[anchor].GetY() + marginTop.value_or(0);
    }
    return result;
}

float RelativeContainerLayoutAlgorithm::GetVerticalAlignBottomValue(
    std::string& anchor, std::optional<float>& marginTop)
{
    auto result = 0.0f;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Height()
                 : idNodeMap_[anchor]->GetGeometryNode()->GetMarginFrameSize().Height() +
                    recordOffsetMap_[anchor].GetY();
    } else {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Height()
                 : idNodeMap_[anchor]->GetGeometryNode()->GetFrameSize().Height() +
                    recordOffsetMap_[anchor].GetY() + marginTop.value_or(0);
    }
    return result;
}

void RelativeContainerLayoutAlgorithm::UpdateVerticalTwoAlignValues(
    TwoAlignedValues& twoAlignedValues, AlignRule alignRule)
{
    if (twoAlignedValues.first.has_value() && twoAlignedValues.second.has_value()) {
        return;
    }
    auto result = 0.0f;
    std::optional<float> marginTop;
    if (!IsAnchorContainer(alignRule.anchor)) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor];
        marginTop = anchorWrapper->GetGeometryNode()->GetMargin()->top;
    }
    switch (alignRule.vertical) {
        case VerticalAlign::TOP:
            result = GetVerticalAlignTopValue(alignRule.anchor, marginTop);
            break;
        case VerticalAlign::CENTER:
            result = GetVerticalAlignCenterValue(alignRule.anchor, marginTop);
            break;
        case VerticalAlign::BOTTOM:
            result = GetVerticalAlignBottomValue(alignRule.anchor, marginTop);
            break;
        default:
            break;
    }
    if (!twoAlignedValues.first.has_value()) {
        twoAlignedValues.first = result;
        return;
    }
    if (!twoAlignedValues.second.has_value()) {
        twoAlignedValues.second = result;
    }
}

float RelativeContainerLayoutAlgorithm::GetHorizontalAlignStartValue(
    std::string& anchor, std::optional<float>& marginLeft)
{
    auto result = 0.0f;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        result = IsAnchorContainer(anchor) ? 0.0f : recordOffsetMap_[anchor].GetX();
    } else {
        result = IsAnchorContainer(anchor)
                 ? 0.0f
                 : recordOffsetMap_[anchor].GetX() + marginLeft.value_or(0);
    }
    return result;
}

float RelativeContainerLayoutAlgorithm::GetHorizontalAlignCenterValue(
    std::string& anchor, std::optional<float>& marginLeft)
{
    auto result = 0.0f;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Width() / 2.0f
                 : idNodeMap_[anchor]->GetGeometryNode()->GetMarginFrameSize().Width() / 2.0f +
                    recordOffsetMap_[anchor].GetX();
    } else {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Width() / 2.0f
                 : idNodeMap_[anchor]->GetGeometryNode()->GetFrameSize().Width() / 2.0f +
                    recordOffsetMap_[anchor].GetX() + marginLeft.value_or(0);
    }
    return result;
}

float RelativeContainerLayoutAlgorithm::GetHorizontalAlignEndValue(
    std::string& anchor, std::optional<float>& marginLeft)
{
    auto result = 0.0f;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Width()
                 : idNodeMap_[anchor]->GetGeometryNode()->GetMarginFrameSize().Width() +
                    recordOffsetMap_[anchor].GetX();
    } else {
        result = IsAnchorContainer(anchor)
                 ? containerSizeWithoutPaddingBorder_.Width()
                 : idNodeMap_[anchor]->GetGeometryNode()->GetFrameSize().Width() +
                    recordOffsetMap_[anchor].GetX() + marginLeft.value_or(0);
    }
    return result;
}

void RelativeContainerLayoutAlgorithm::UpdateHorizontalTwoAlignValues(
    TwoAlignedValues& twoAlignedValues, AlignRule alignRule)
{
    if (twoAlignedValues.first.has_value() && twoAlignedValues.second.has_value()) {
        return;
    }
    auto result = 0.0f;
    std::optional<float> marginLeft;
    if (!IsAnchorContainer(alignRule.anchor)) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor];
        marginLeft = anchorWrapper->GetGeometryNode()->GetMargin()->left;
    }
    switch (alignRule.horizontal) {
        case HorizontalAlign::START:
            result = GetHorizontalAlignStartValue(alignRule.anchor, marginLeft);
            break;
        case HorizontalAlign::CENTER:
            result = GetHorizontalAlignCenterValue(alignRule.anchor, marginLeft);
            break;
        case HorizontalAlign::END:
            result = GetHorizontalAlignEndValue(alignRule.anchor, marginLeft);
            break;
        default:
            break;
    }
    if (!twoAlignedValues.first.has_value()) {
        twoAlignedValues.first = result;
        return;
    }
    if (!twoAlignedValues.second.has_value()) {
        twoAlignedValues.second = result;
    }
}

void RelativeContainerLayoutAlgorithm::DetermineTopologicalOrder(LayoutWrapper* layoutWrapper)
{
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    idNodeMap_.clear();
    reliedOnMap_.clear();
    recordOffsetMap_.clear();
    incomingDegreeMap_.clear();
    auto layoutConstraint = relativeContainerLayoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    containerSizeWithoutPaddingBorder_ = idealSize.ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(containerSizeWithoutPaddingBorder_);
    if (relativeContainerLayoutProperty->GetPaddingProperty() ||
        relativeContainerLayoutProperty->GetBorderWidthProperty()) {
        padding_ = relativeContainerLayoutProperty->CreatePaddingAndBorder();
        MinusPaddingToSize(padding_, containerSizeWithoutPaddingBorder_);
    }
    CollectNodesById(layoutWrapper);
    GetDependencyRelationship();
    if (!PreTopologicalLoopDetection()) {
        const auto& childrenWrappers = layoutWrapper->GetAllChildrenWithBuild();
        auto constraint = relativeContainerLayoutProperty->CreateChildConstraint();
        for (const auto& childrenWrapper : childrenWrappers) {
            childrenWrapper->SetActive(false);
            constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
            childrenWrapper->Measure(constraint);
            constraint.Reset();
        }
        return;
    }
    TopologicalSort(renderList_);
}

void RelativeContainerLayoutAlgorithm::UpdateSizeWhenChildrenEmpty(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    const auto& calcLayoutConstraint = relativeContainerLayoutProperty->GetCalcLayoutConstraint();
    if (!calcLayoutConstraint) {
        const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
        CHECK_NULL_VOID(layoutConstraint.has_value());
        auto idealSize = CreateIdealSizeByPercentRef(layoutConstraint.value(), Axis::FREE,
                                                     MeasureType::MATCH_PARENT).ConvertToSizeT();
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize.IsPositive() ? idealSize : SizeF(0.0f, 0.0f));
        return;
    }
    auto selfIdealSize = calcLayoutConstraint->selfIdealSize;
    padding_ = relativeContainerLayoutProperty->CreatePaddingAndBorder();
    if (selfIdealSize->Width()->GetDimension().Unit() == DimensionUnit::AUTO) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(
            SizeF(padding_.Width(), layoutWrapper->GetGeometryNode()->GetFrameSize().Height()));
    }
    if (selfIdealSize->Height()->GetDimension().Unit() == DimensionUnit::AUTO) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(
            SizeF(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), padding_.Height()));
    }
}

void RelativeContainerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    if (layoutWrapper->GetAllChildrenWithBuild().empty()) {
        UpdateSizeWhenChildrenEmpty(layoutWrapper);
        return;
    }

    DetermineTopologicalOrder(layoutWrapper);
    if (SystemProperties::GetDebugEnabled()) {
        std::string result = "[";
        for (const auto& nodeName : renderList_) {
            result += nodeName + ",";
        }
        if (!renderList_.empty()) {
            result = result.substr(0, result.length() - 1);
        }
        result += "]";
    }
    for (const auto& nodeName : renderList_) {
        if (idNodeMap_.find(nodeName) == idNodeMap_.end()) {
            continue;
        }
        auto childWrapper = idNodeMap_[nodeName];
        auto childConstraint = relativeContainerLayoutProperty->CreateChildConstraint();
        if (!childWrapper->IsActive()) {
            childWrapper->Measure(childConstraint);
            continue;
        }
        if (!childWrapper->GetLayoutProperty() || !childWrapper->GetLayoutProperty()->GetFlexItemProperty()) {
            childWrapper->Measure(childConstraint);
            recordOffsetMap_[nodeName] = OffsetF(0.0f, 0.0f);
            continue;
        }
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!flexItem->HasAlignRules()) {
            childWrapper->Measure(childConstraint);
            recordOffsetMap_[nodeName] = OffsetF(0.0f, 0.0f);
            continue;
        }
        flexItem->ClearAlignValue();
        auto alignRules = flexItem->GetAlignRulesValue();
        auto frameNode = childWrapper->GetHostNode();
        if (!alignRules.empty() && frameNode && frameNode->GetLayoutProperty()) {
            // when child has alignRules and position, the position property do not work.
            frameNode->GetLayoutProperty()->SetUsingPosition(false);
        }
        CalcSizeParam(layoutWrapper, nodeName);
        CalcOffsetParam(layoutWrapper, nodeName);
    }
    const auto& calcLayoutConstraint = relativeContainerLayoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(calcLayoutConstraint);
    auto selfIdealSize = calcLayoutConstraint->selfIdealSize;
    CHECK_NULL_VOID(selfIdealSize.has_value());
    if ((selfIdealSize.value().Width().has_value() &&
            selfIdealSize.value().Width().value().GetDimension().Unit() == DimensionUnit::AUTO) ||
        (selfIdealSize.value().Height().has_value() &&
            selfIdealSize.value().Height().value().GetDimension().Unit() == DimensionUnit::AUTO)) {
        MeasureSelf(layoutWrapper);
    }
}

void RelativeContainerLayoutAlgorithm::MeasureSelf(LayoutWrapper* layoutWrapper)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    RectF relativeContainerRect(0, 0, 0, 0);
    auto selfIdealSize = relativeContainerLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    for (const auto& nodeName : renderList_) {
        if (idNodeMap_.find(nodeName) == idNodeMap_.end()) {
            continue;
        }
        auto childWrapper = idNodeMap_[nodeName];
        if (childWrapper->GetLayoutProperty()->GetVisibility() == VisibleType::GONE) {
            continue;
        }
        RectF tempRect(recordOffsetMap_[nodeName].GetX(), recordOffsetMap_[nodeName].GetY(),
            childWrapper->GetGeometryNode()->GetMarginFrameSize().Width(),
            childWrapper->GetGeometryNode()->GetMarginFrameSize().Height());
        relativeContainerRect = relativeContainerRect.CombineRectT(tempRect);
    }

    relativeContainerRect =
        relativeContainerRect.IntersectRectT(RectF(0.0f, 0.0f, Infinity<float>(), Infinity<float>()));
    if (selfIdealSize->Width()->GetDimension().Unit() == DimensionUnit::AUTO && !isHorizontalRelyOnContainer_) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(relativeContainerRect.Width() + padding_.Width(),
            layoutWrapper->GetGeometryNode()->GetFrameSize().Height()));
    }
    if (selfIdealSize->Height()->GetDimension().Unit() == DimensionUnit::AUTO && !isVerticalRelyOnContainer_) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(),
            relativeContainerRect.Height() + padding_.Height()));
    }
}

void RelativeContainerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    const auto& childrenWrapper = layoutWrapper->GetAllChildrenWithBuild();
    auto left = padding_.left.value_or(0);
    auto top = padding_.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    for (const auto& childWrapper : childrenWrapper) {
        if (!childWrapper->GetLayoutProperty()->GetFlexItemProperty()) {
            childWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, 0.0f) + paddingOffset);
            childWrapper->Layout();
            continue;
        }
        if (!childWrapper->GetHostNode()->GetInspectorId().has_value()) {
            childWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, 0.0f) + paddingOffset);
            childWrapper->Layout();
            continue;
        }
        if (recordOffsetMap_.find(childWrapper->GetHostNode()->GetInspectorIdValue()) == recordOffsetMap_.end()) {
            childWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, 0.0f) + paddingOffset);
            childWrapper->Layout();
            continue;
        }
        auto curOffset = recordOffsetMap_[childWrapper->GetHostNode()->GetInspectorIdValue()];
        childWrapper->GetGeometryNode()->SetMarginFrameOffset(curOffset + paddingOffset);
        childWrapper->Layout();
    }
}

void RelativeContainerLayoutAlgorithm::CollectNodesById(LayoutWrapper* layoutWrapper)
{
    idNodeMap_.clear();
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    auto left = padding_.left.value_or(0);
    auto top = padding_.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto constraint = relativeContainerLayoutProperty->GetLayoutConstraint();
    const auto& childrenWrappers = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& childWrapper : childrenWrappers) {
        auto childLayoutProperty = childWrapper->GetLayoutProperty();
        auto childHostNode = childWrapper->GetHostNode();
        childWrapper->SetActive();
        if (childHostNode && childHostNode->GetInspectorId().has_value()) {
            auto geometryNode = childWrapper->GetGeometryNode();
            auto childConstraint = relativeContainerLayoutProperty->CreateChildConstraint();
            if (childHostNode->GetInspectorId()->empty()) {
                childConstraint.maxSize = SizeF(constraint->maxSize);
                childConstraint.minSize = SizeF(0.0f, 0.0f);
                childWrapper->Measure(childConstraint);
                childWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, 0.0f) + paddingOffset);
                idNodeMap_.emplace(childHostNode->GetInspectorIdValue(), childWrapper);
            }
            idNodeMap_.emplace(childHostNode->GetInspectorIdValue(), childWrapper);
        } else {
            childWrapper->SetActive(false);
        }
    }
}

void RelativeContainerLayoutAlgorithm::GetDependencyRelationship()
{
    for (const auto& node : idNodeMap_) {
        auto childWrapper = node.second;
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        auto childHostNode = childWrapper->GetHostNode();
        if (!flexItem) {
            continue;
        }
        for (const auto& alignRule : flexItem->GetAlignRulesValue()) {
            if (IsAnchorContainer(alignRule.second.anchor) ||
                idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end()) {
                if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE) {
                    isHorizontalRelyOnContainer_ = true;
                } else if (static_cast<uint32_t>(alignRule.first) < VERTICAL_DIRECTION_RANGE) {
                    isVerticalRelyOnContainer_ = true;
                }
                continue;
            }
            auto anchorChildWrapper = idNodeMap_[alignRule.second.anchor];
            auto anchorChildLayoutProp = anchorChildWrapper->GetLayoutProperty();
            auto anchorChildVisibility = anchorChildLayoutProp->GetVisibility();
            if (anchorChildVisibility == VisibleType::GONE) {
                childWrapper->SetActive(false);
            }
            // if a is the anchor of b, then reliedOnMap should place <a, [b]> for the first appearance
            // of key a. Otherwise b will be inserted into the exsiting value list
            if (reliedOnMap_.count(alignRule.second.anchor) == 0) {
                std::set<std::string> reliedList;
                reliedList.insert(childHostNode->GetInspectorIdValue());
                reliedOnMap_[alignRule.second.anchor] = reliedList;
                continue;
            }
            reliedOnMap_[alignRule.second.anchor].insert(childHostNode->GetInspectorIdValue());
        }
    }
}

bool RelativeContainerLayoutAlgorithm::PreTopologicalLoopDetection()
{
    std::queue<std::string> visitedNode;
    std::queue<std::string> layoutQueue;

    for (const auto& node : idNodeMap_) {
        auto childWrapper = node.second;
        auto childHostNode = childWrapper->GetHostNode();
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!flexItem) {
            visitedNode.push(node.first);
            layoutQueue.push(childHostNode->GetInspectorIdValue());
            continue;
        }
        std::set<std::string> anchorSet;
        for (const auto& alignRule : flexItem->GetAlignRulesValue()) {
            if (IsAnchorContainer(alignRule.second.anchor) ||
                idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end()) {
                continue;
            }
            anchorSet.insert(alignRule.second.anchor);
        }
        incomingDegreeMap_[childHostNode->GetInspectorIdValue()] = anchorSet.size();
        if (incomingDegreeMap_[childHostNode->GetInspectorIdValue()] == 0) {
            layoutQueue.push(childHostNode->GetInspectorIdValue());
        }
    }
    std::map<std::string, uint32_t> incomingDegreeMapCopy;
    incomingDegreeMapCopy.insert(incomingDegreeMap_.begin(), incomingDegreeMap_.end());
    while (!layoutQueue.empty()) {
        auto currentNodeInspectorId = layoutQueue.front();
        layoutQueue.pop();
        auto reliedSet = reliedOnMap_[currentNodeInspectorId];
        for (const auto& node : reliedSet) {
            if (incomingDegreeMapCopy.find(node) == incomingDegreeMapCopy.end() || IsAnchorContainer(node)) {
                continue;
            }
            incomingDegreeMapCopy[node] -= 1;
            if (incomingDegreeMapCopy[node] == 0) {
                layoutQueue.push(node);
            }
        }
        incomingDegreeMapCopy.erase(currentNodeInspectorId);
        visitedNode.push(currentNodeInspectorId);
    }
    if (!incomingDegreeMapCopy.empty()) {
        std::string loopDependentNodes;
        for (const auto& node : incomingDegreeMapCopy) {
            loopDependentNodes += node.first + ",";
        }
        return false;
    }
    return true;
}

void RelativeContainerLayoutAlgorithm::TopologicalSort(std::list<std::string>& renderList)
{
    std::queue<std::string> layoutQueue;
    for (const auto& node : idNodeMap_) {
        auto childWrapper = node.second;
        auto childHostNode = childWrapper->GetHostNode();
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!flexItem || incomingDegreeMap_[childHostNode->GetInspectorIdValue()] == 0) {
            layoutQueue.push(childHostNode->GetInspectorIdValue());
        }
    }
    while (!layoutQueue.empty()) {
        auto currentNodeInspectorId = layoutQueue.front();
        layoutQueue.pop();
        // reduce incoming degree of nodes relied on currentNode
        auto reliedList = reliedOnMap_[currentNodeInspectorId];
        for (const auto& node : reliedList) {
            if (incomingDegreeMap_.find(node) == incomingDegreeMap_.end() || IsAnchorContainer(node)) {
                continue;
            }
            incomingDegreeMap_[node] -= 1;
            if (incomingDegreeMap_[node] == 0) {
                layoutQueue.push(node);
            }
        }
        renderList.emplace_back(currentNodeInspectorId);
    }
}

void RelativeContainerLayoutAlgorithm::CalcSizeParam(LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    if (idNodeMap_.find(nodeName) == idNodeMap_.end()) {
        return;
    }
    auto childWrapper = idNodeMap_[nodeName];
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    CHECK_NULL_VOID(childWrapper->GetLayoutProperty()->GetFlexItemProperty());
    CHECK_NULL_VOID(childWrapper->GetLayoutProperty()->GetFlexItemProperty()->HasAlignRules());
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    auto childConstraint = relativeContainerLayoutProperty->CreateChildConstraint();
    auto alignRules = childWrapper->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRulesValue();
    const auto& calcConstraint = childLayoutProperty->GetCalcLayoutConstraint();
    bool horizontalHasIdealSize = false;
    bool verticalHasIdealSize = false;
    if (calcConstraint && calcConstraint->selfIdealSize.has_value() &&
        calcConstraint->selfIdealSize.value().Width().has_value()) {
        horizontalHasIdealSize = true;
    }
    if (calcConstraint && calcConstraint->selfIdealSize.has_value() &&
        calcConstraint->selfIdealSize.value().Height().has_value()) {
        verticalHasIdealSize = true;
    }
    horizontalHasIdealSize =
        horizontalHasIdealSize && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN);
    verticalHasIdealSize =
        verticalHasIdealSize && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN);
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    std::optional<float> childIdealWidth;
    std::optional<float> childIdealHeight;

    for (const auto& alignRule : alignRules) {
        if (idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end() &&
            !IsAnchorContainer(alignRule.second.anchor)) {
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE) {
            if (!childFlexItemProperty->GetTwoHorizontalDirectionAligned()) {
                CalcHorizontalLayoutParam(alignRule.first, alignRule.second, layoutWrapper, nodeName);
            }
        } else {
            if (!childFlexItemProperty->GetTwoVerticalDirectionAligned()) {
                CalcVerticalLayoutParam(alignRule.first, alignRule.second, layoutWrapper, nodeName);
            }
        }
    }
    if (childFlexItemProperty->GetTwoHorizontalDirectionAligned()) {
        auto checkAlign = AlignDirection::MIDDLE;
        if (childFlexItemProperty->GetAligned(checkAlign)) {
            auto middleValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::LEFT;
            if (childFlexItemProperty->GetAligned(checkAlign)) {
                childIdealWidth = 2.0f * std::max(middleValue - childFlexItemProperty->GetAlignValue(checkAlign), 0.0f);
            } else {
                checkAlign = AlignDirection::RIGHT;
                childIdealWidth = 2.0f * std::max(childFlexItemProperty->GetAlignValue(checkAlign) - middleValue, 0.0f);
            }
        } else {
            childIdealWidth = std::max(childFlexItemProperty->GetAlignValue(AlignDirection::RIGHT) -
                                           childFlexItemProperty->GetAlignValue(AlignDirection::LEFT),
                0.0f);
        }
        if (childIdealWidth.has_value() && LessOrEqual(childIdealWidth.value(), 0.0f)) {
            childConstraint.selfIdealSize.SetWidth(0.0f);
            childConstraint.selfIdealSize.SetHeight(0.0f);
            childWrapper->Measure(childConstraint);
            return;
        }
    }
    if (childFlexItemProperty->GetTwoVerticalDirectionAligned()) {
        auto checkAlign = AlignDirection::CENTER;
        if (childFlexItemProperty->GetAligned(checkAlign)) {
            auto centerValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::TOP;
            if (childFlexItemProperty->GetAligned(checkAlign)) {
                childIdealHeight =
                    2.0f * std::max(centerValue - childFlexItemProperty->GetAlignValue(checkAlign), 0.0f);
            } else {
                checkAlign = AlignDirection::BOTTOM;
                childIdealHeight =
                    2.0f * std::max(childFlexItemProperty->GetAlignValue(checkAlign) - centerValue, 0.0f);
            }
        } else {
            childIdealHeight = std::max(childFlexItemProperty->GetAlignValue(AlignDirection::BOTTOM) -
                                            childFlexItemProperty->GetAlignValue(AlignDirection::TOP),
                0.0f);
        }
        if (childIdealHeight.has_value() && LessOrEqual(childIdealHeight.value(), 0.0f)) {
            childConstraint.selfIdealSize.SetWidth(0.0f);
            childConstraint.selfIdealSize.SetHeight(0.0f);
            childWrapper->Measure(childConstraint);
            return;
        }
    }

    // for api 11 or larger, alignRules will not effect child component size as described in doc
    if (horizontalHasIdealSize && verticalHasIdealSize) {
        childWrapper->Measure(childConstraint);
        return;
    }

    if (childIdealWidth.has_value() && !horizontalHasIdealSize) {
        childConstraint.selfIdealSize.SetWidth(childIdealWidth.value());
    }
    if (childIdealHeight.has_value() && !verticalHasIdealSize) {
        childConstraint.selfIdealSize.SetHeight(childIdealHeight.value());
    }
    childWrapper->Measure(childConstraint);
}

void RelativeContainerLayoutAlgorithm::CalcOffsetParam(LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto childWrapper = idNodeMap_[nodeName];
    auto alignRules = childWrapper->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRulesValue();
    float offsetX = 0.0f;
    bool offsetXCalculated = false;
    float offsetY = 0.0f;
    bool offsetYCalculated = false;
    for (const auto& alignRule : alignRules) {
        if (idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end() &&
            !IsAnchorContainer(alignRule.second.anchor)) {
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE) {
            if (!offsetXCalculated) {
                offsetX = CalcHorizontalOffset(
                    alignRule.first, alignRule.second, containerSizeWithoutPaddingBorder_.Width(), nodeName);
                offsetXCalculated = true;
            }
        } else {
            if (!offsetYCalculated) {
                offsetY = CalcVerticalOffset(
                    alignRule.first, alignRule.second, containerSizeWithoutPaddingBorder_.Height(), nodeName);
                offsetYCalculated = true;
            }
        }
    }
    recordOffsetMap_[nodeName] = OffsetF(offsetX, offsetY) + CalcBias(childWrapper);
}

bool RelativeContainerLayoutAlgorithm::IsValidBias(float bias)
{
    return GreatOrEqual(bias, 0.0f);
}

OffsetF RelativeContainerLayoutAlgorithm::CalcBias(const RefPtr<LayoutWrapper>& childWrapper)
{
    OffsetF emptyBiasOffset;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return emptyBiasOffset;
    }
    auto layoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, emptyBiasOffset);
    const auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
    CHECK_NULL_RETURN(flexItemProperty, emptyBiasOffset);
    CHECK_NULL_RETURN(flexItemProperty->HasBias(), emptyBiasOffset);
    auto biasX = flexItemProperty->GetBiasValue().first;
    auto biasY = flexItemProperty->GetBiasValue().second;
    CHECK_NULL_RETURN(flexItemProperty->HasAlignRules(), emptyBiasOffset);
    auto alignRules = flexItemProperty->GetAlignRulesValue();
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ChildIdealSize childIdealSize;
    if (calcLayoutConstraint && calcLayoutConstraint->selfIdealSize.has_value() &&
        calcLayoutConstraint->selfIdealSize.value().Width().has_value()) {
        childIdealSize.first = childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    }

    if (calcLayoutConstraint && calcLayoutConstraint->selfIdealSize.has_value() &&
        calcLayoutConstraint->selfIdealSize.value().Height().has_value()) {
        childIdealSize.second = childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    }
    if (!childIdealSize.first.has_value() && !childIdealSize.second.has_value()) {
        return OffsetF(0.0f, 0.0f);
    }
    auto alignedValuesOnTwoDirections = GetFirstTwoAlignValues(childWrapper, flexItemProperty, childIdealSize);
    auto horizontalOffset = 0.0f;
    auto verticalOffset = 0.0f;
    auto horizontalValues = alignedValuesOnTwoDirections.first;
    auto verticalValues = alignedValuesOnTwoDirections.second;
    if (horizontalValues.first.has_value() && horizontalValues.second.has_value() && childIdealSize.first.has_value()) {
        auto alignDiff = std::abs(horizontalValues.first.value() - horizontalValues.second.value());
        horizontalOffset = (alignDiff - childIdealSize.first.value()) * (IsValidBias(biasX) ? biasX : DEFAULT_BIAS);
    }
    if (verticalValues.first.has_value() && verticalValues.second.has_value() && childIdealSize.second.has_value()) {
        auto alignDiff = std::abs(verticalValues.first.value() - verticalValues.second.value());
        verticalOffset = (alignDiff - childIdealSize.second.value()) * (IsValidBias(biasY) ? biasY : DEFAULT_BIAS);
    }
    return OffsetF(horizontalOffset, verticalOffset);
}

std::pair<TwoAlignedValues, TwoAlignedValues> RelativeContainerLayoutAlgorithm::GetFirstTwoAlignValues(
    const RefPtr<LayoutWrapper>& childWrapper, const std::unique_ptr<FlexItemProperty>& flexItemProperty,
    const ChildIdealSize& childIdealSize)
{
    CHECK_NULL_RETURN(flexItemProperty, {});
    CHECK_NULL_RETURN(flexItemProperty->HasAlignRules(), {});
    auto alignRules = flexItemProperty->GetAlignRulesValue();
    TwoAlignedValues horizontalValues;
    TwoAlignedValues verticalValues;
    for (const auto& alignRule : alignRules) {
        bool horizontalCheckTwoSidesAligned = horizontalValues.first.has_value() && horizontalValues.second.has_value();
        bool verticalCheckTwoSidesAligned = verticalValues.second.has_value() && verticalValues.second.has_value();
        if (horizontalCheckTwoSidesAligned && verticalCheckTwoSidesAligned) {
            break;
        }
        if (idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end() &&
            !IsAnchorContainer(alignRule.second.anchor)) {
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE && !horizontalCheckTwoSidesAligned &&
            childIdealSize.first.has_value()) {
            UpdateHorizontalTwoAlignValues(horizontalValues, alignRule.second);
        } else if (static_cast<uint32_t>(alignRule.first) >= HORIZONTAL_DIRECTION_RANGE &&
                   !verticalCheckTwoSidesAligned && childIdealSize.second.has_value()) {
            UpdateVerticalTwoAlignValues(verticalValues, alignRule.second);
        }
    }
    return { horizontalValues, verticalValues };
}

void RelativeContainerLayoutAlgorithm::CalcHorizontalLayoutParam(AlignDirection alignDirection,
    const AlignRule& alignRule, LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    if (idNodeMap_.find(nodeName) == idNodeMap_.end()) {
        return;
    }
    auto childWrapper = idNodeMap_[nodeName];
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    switch (alignRule.horizontal) {
        case HorizontalAlign::START:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX());
            break;
        case HorizontalAlign::CENTER:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? containerSizeWithoutPaddingBorder_.Width() / 2.0f
                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Width() / 2.0f +
                          recordOffsetMap_[alignRule.anchor].GetX());
            break;
        case HorizontalAlign::END:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor)
                                    ? containerSizeWithoutPaddingBorder_.Width()
                                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Width() +
                                          recordOffsetMap_[alignRule.anchor].GetX());
            break;
        default:
            break;
    }
}

void RelativeContainerLayoutAlgorithm::CalcVerticalLayoutParam(AlignDirection alignDirection,
    const AlignRule& alignRule, LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    if (idNodeMap_.find(nodeName) == idNodeMap_.end()) {
        return;
    }
    auto childWrapper = idNodeMap_[nodeName];
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    switch (alignRule.vertical) {
        case VerticalAlign::TOP:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY());
            break;
        case VerticalAlign::CENTER:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? containerSizeWithoutPaddingBorder_.Height() / 2.0f
                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Height() / 2.0f +
                          recordOffsetMap_[alignRule.anchor].GetY());
            break;
        case VerticalAlign::BOTTOM:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor)
                                    ? containerSizeWithoutPaddingBorder_.Height()
                                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Height() +
                                          recordOffsetMap_[alignRule.anchor].GetY());
            break;
        default:
            break;
    }
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffsetAlignLeft(
    const HorizontalAlign& alignRule, float& anchorWidth)
{
    float offsetX = 0.0f;
    switch (alignRule) {
        case HorizontalAlign::START:
            offsetX = 0.0f;
            break;
        case HorizontalAlign::CENTER:
            offsetX = anchorWidth / 2.0f;
            break;
        case HorizontalAlign::END:
            offsetX = anchorWidth;
            break;
        default:
            break;
    }
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffsetAlignMiddle(
    const HorizontalAlign& alignRule, float& anchorWidth, float& flexItemWidth)
{
    float offsetX = 0.0f;
    switch (alignRule) {
        case HorizontalAlign::START:
            offsetX = (-1) * flexItemWidth / 2.0f;
            break;
        case HorizontalAlign::CENTER:
            offsetX = (anchorWidth - flexItemWidth) / 2.0f;
            break;
        case HorizontalAlign::END:
            offsetX = anchorWidth - flexItemWidth / 2.0f;
            break;
        default:
            break;
    }
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffsetAlignRight(
    const HorizontalAlign& alignRule, float& anchorWidth, float& flexItemWidth)
{
    float offsetX = 0.0f;
    switch (alignRule) {
        case HorizontalAlign::START:
            offsetX = (-1) * flexItemWidth;
            break;
        case HorizontalAlign::CENTER:
            offsetX = anchorWidth / 2.0f - flexItemWidth;
            break;
        case HorizontalAlign::END:
            offsetX = anchorWidth - flexItemWidth;
            break;
        default:
            break;
    }
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffset(
    AlignDirection alignDirection, const AlignRule& alignRule, float containerWidth, const std::string& nodeName)
{
    float offsetX = 0.0f;
    auto childWrapper = idNodeMap_[nodeName];

    float flexItemWidth = childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    float anchorWidth;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        anchorWidth = IsAnchorContainer(alignRule.anchor)
                            ? containerWidth
                            : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Width();
    } else {
        anchorWidth = IsAnchorContainer(alignRule.anchor)
                            ? containerWidth
                            : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetFrameSize().Width();
    }
    std::optional<float> marginLeft;
    if (!IsAnchorContainer(alignRule.anchor)) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor];
        marginLeft = anchorWrapper->GetGeometryNode()->GetMargin()->left;
    }
    switch (alignDirection) {
        case AlignDirection::LEFT:
            offsetX = CalcHorizontalOffsetAlignLeft(alignRule.horizontal, anchorWidth);
            break;
        case AlignDirection::MIDDLE:
            offsetX = CalcHorizontalOffsetAlignMiddle(alignRule.horizontal, anchorWidth, flexItemWidth);
            break;
        case AlignDirection::RIGHT:
            offsetX = CalcHorizontalOffsetAlignRight(alignRule.horizontal, anchorWidth, flexItemWidth);
            break;
        default:
            break;
    }

    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        offsetX += IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX();
    } else {
        offsetX += IsAnchorContainer(alignRule.anchor)
                    ? 0.0f
                    : recordOffsetMap_[alignRule.anchor].GetX() + marginLeft.value_or(0);
    }
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffsetAlignTop(const VerticalAlign& alignRule, float& anchorHeight)
{
    float offsetY = 0.0f;
    switch (alignRule) {
        case VerticalAlign::TOP:
            offsetY = 0.0f;
            break;
        case VerticalAlign::CENTER:
            offsetY = anchorHeight / 2.0f;
            break;
        case VerticalAlign::BOTTOM:
            offsetY = anchorHeight;
            break;
        default:
            break;
    }
    return offsetY;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffsetAlignCenter(
    const VerticalAlign& alignRule, float& anchorHeight, float& flexItemHeight)
{
    float offsetY = 0.0f;
    switch (alignRule) {
        case VerticalAlign::TOP:
            offsetY = (-1) * flexItemHeight / 2.0f;
            break;
        case VerticalAlign::CENTER:
            offsetY = (anchorHeight - flexItemHeight) / 2.0f;
            break;
        case VerticalAlign::BOTTOM:
            offsetY = anchorHeight - flexItemHeight / 2.0f;
            break;
        default:
            break;
    }
    return offsetY;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffsetAlignBottom(
    const VerticalAlign& alignRule, float& anchorHeight, float& flexItemHeight)
{
    float offsetY = 0.0f;
    switch (alignRule) {
        case VerticalAlign::TOP:
            offsetY = (-1) * flexItemHeight;
            break;
        case VerticalAlign::CENTER:
            offsetY = anchorHeight / 2.0f - flexItemHeight;
            break;
        case VerticalAlign::BOTTOM:
            offsetY = anchorHeight - flexItemHeight;
            break;
        default:
            break;
    }
    return offsetY;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffset(
    AlignDirection alignDirection, const AlignRule& alignRule, float containerHeight, const std::string& nodeName)
{
    float offsetY = 0.0f;
    auto childWrapper = idNodeMap_[nodeName];

    float flexItemHeight = childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    float anchorHeight;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        anchorHeight = IsAnchorContainer(alignRule.anchor)
                             ? containerHeight
                             : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Height();
    } else {
        anchorHeight = IsAnchorContainer(alignRule.anchor)
                             ? containerHeight
                             : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetFrameSize().Height();
    }
    std::optional<float> marginTop;
    if (!IsAnchorContainer(alignRule.anchor)) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor];
        marginTop = anchorWrapper->GetGeometryNode()->GetMargin()->top;
    }
    switch (alignDirection) {
        case AlignDirection::TOP:
            offsetY = CalcVerticalOffsetAlignTop(alignRule.vertical, anchorHeight);
            break;
        case AlignDirection::CENTER:
            offsetY = CalcVerticalOffsetAlignCenter(alignRule.vertical, anchorHeight, flexItemHeight);
            break;
        case AlignDirection::BOTTOM:
            offsetY = CalcVerticalOffsetAlignBottom(alignRule.vertical, anchorHeight, flexItemHeight);
            break;
        default:
            break;
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        offsetY += IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY();
    } else {
        offsetY += IsAnchorContainer(alignRule.anchor)
                    ? 0.0f
                    : recordOffsetMap_[alignRule.anchor].GetY() + marginTop.value_or(0);
    }
    return offsetY;
}

} // namespace OHOS::Ace::NG
