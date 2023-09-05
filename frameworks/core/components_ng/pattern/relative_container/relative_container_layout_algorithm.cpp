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

inline bool IsAnchorContainer(const std::string& anchor)
{
    return anchor == "__container__";
}

} // namespace

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
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize.ConvertToSizeT());
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

void RelativeContainerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (layoutWrapper->GetAllChildrenWithBuild().empty()) {
        LOGD("RelativeContainerLayoutAlgorithm: No child in Relative container");
        return;
    }
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
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
        LOGD("RelativeContainer layout order %{public}s", result.c_str());
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
        // if child has no align rules, measure it with container constraint and place it at top left corner
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
            continue;
        }
        if (!childWrapper->GetHostNode()->GetInspectorId().has_value()) {
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
                // Component who does not have align Rules will have default offset and layout param
                childConstraint.maxSize = SizeF(constraint->maxSize);
                childConstraint.minSize = SizeF(0.0f, 0.0f);
                childWrapper->Measure(childConstraint);
                childWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, 0.0f) + paddingOffset);
                idNodeMap_.emplace(childHostNode->GetInspectorIdValue(), childWrapper);
            }
            if (idNodeMap_.find(childHostNode->GetInspectorIdValue()) != idNodeMap_.end()) {
                LOGW("Component %{public}s ID is duplicated", childHostNode->GetInspectorIdValue().c_str());
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
            LOGD("Componemt %{public}s has no alignRules", node.first.c_str());
            continue;
        }
        for (const auto& alignRule : flexItem->GetAlignRulesValue()) {
            // if anchor is not other children components,
            // then we don't need to put current align rule in dependency map
            if (IsAnchorContainer(alignRule.second.anchor) ||
                idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end()) {
                continue;
            }
            auto anchorChildWrapper = idNodeMap_[alignRule.second.anchor];
            auto anchorChildLayoutProp = anchorChildWrapper->GetLayoutProperty();
            auto anchorChildVisibility = anchorChildLayoutProp->GetVisibility();
            // when anchor component set VisibleType::GONE, the current component is not displayed.
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
            if (alignRule.second.anchor == node.first) {
                LOGE("Component %{public}s has dependency on itself", node.first.c_str());
            }
        }
        incomingDegreeMap_[childHostNode->GetInspectorIdValue()] = anchorSet.size();
        if (incomingDegreeMap_[childHostNode->GetInspectorIdValue()] == 0) {
            layoutQueue.push(childHostNode->GetInspectorIdValue());
        }
    }
    std::map<std::string, uint32_t> incomingDegreeMapCopy;
    incomingDegreeMapCopy.insert(incomingDegreeMap_.begin(), incomingDegreeMap_.end());
    while (!layoutQueue.empty()) {
        auto currentNodeName = layoutQueue.front();
        layoutQueue.pop();
        auto reliedSet = reliedOnMap_[currentNodeName];
        for (const auto& node : reliedSet) {
            if (incomingDegreeMapCopy.find(node) == incomingDegreeMapCopy.end() || IsAnchorContainer(node)) {
                continue;
            }
            incomingDegreeMapCopy[node] -= 1;
            if (incomingDegreeMapCopy[node] == 0) {
                layoutQueue.push(node);
            }
        }
        incomingDegreeMapCopy.erase(currentNodeName);
        visitedNode.push(currentNodeName);
    }
    if (!incomingDegreeMapCopy.empty()) {
        std::string loopDependentNodes;
        for (const auto& node : incomingDegreeMapCopy) {
            loopDependentNodes += node.first + ",";
        }
        LOGE("Perform Layout failed, components [%{public}s] has loop dependency",
            loopDependentNodes.substr(0, loopDependentNodes.size() - 1).c_str());
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
        if (!flexItem) {
            renderList.emplace_back(node.first);
            continue;
        }
        if (incomingDegreeMap_[childHostNode->GetInspectorIdValue()] == 0) {
            layoutQueue.push(childHostNode->GetInspectorIdValue());
        }
    }
    while (!layoutQueue.empty()) {
        auto currentNodeName = layoutQueue.front();
        layoutQueue.pop();
        // reduce incoming degree of nodes relied on currentNode
        auto reliedList = reliedOnMap_[currentNodeName];
        for (const auto& node : reliedList) {
            if (incomingDegreeMap_.find(node) == incomingDegreeMap_.end() || IsAnchorContainer(node)) {
                continue;
            }
            incomingDegreeMap_[node] -= 1;
            if (incomingDegreeMap_[node] == 0) {
                layoutQueue.push(node);
            }
        }
        renderList.emplace_back(currentNodeName);
    }
}

void RelativeContainerLayoutAlgorithm::CalcSizeParam(LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto childWrapper = idNodeMap_[nodeName];
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    auto childConstraint = relativeContainerLayoutProperty->CreateChildConstraint();
    auto alignRules = childWrapper->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRulesValue();
    auto geometryNode = childWrapper->GetGeometryNode();
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    float itemMaxWidth = 0.0f;
    float itemMaxHeight = 0.0f;
    float itemMinWidth = 0.0f;
    float itemMinHeight = 0.0f;
    padding_ = relativeContainerLayoutProperty->CreatePaddingAndBorder();
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    MinusPaddingToSize(padding_, frameSize);
    childConstraint.maxSize = frameSize;
    childConstraint.minSize = SizeF(0.0f, 0.0f);
    // set first two boundaries of each direction
    for (const auto& alignRule : alignRules) {
        if (idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end() &&
            !IsAnchorContainer(alignRule.second.anchor)) {
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < DIRECTION_RANGE) {
            if (!childFlexItemProperty->GetTwoHorizontalDirectionAligned()) {
                CalcHorizontalLayoutParam(alignRule.first, alignRule.second, layoutWrapper, nodeName);
            }
        } else {
            if (!childFlexItemProperty->GetTwoVerticalDirectionAligned()) {
                CalcVerticalLayoutParam(alignRule.first, alignRule.second, layoutWrapper, nodeName);
            }
        }
    }
    // If less than two boundaries have been set, width will use container's width
    if (!childFlexItemProperty->GetTwoHorizontalDirectionAligned()) {
        itemMaxWidth = childConstraint.maxSize.Width();
        itemMinWidth = childConstraint.minSize.Width();
    } else {
        // Use two confirmed boundaries to set item's layout param
        // For example left and middle, item's width will be (middle - left) *2
        // If offset difference is negative, which is the case simillar to
        // item's left aligns to container's right, right aligns to left
        // Item layout size will be (0, 0) due to this illegal align
        auto checkAlign = AlignDirection::MIDDLE;
        float widthValue = 0.0f;
        if (childFlexItemProperty->GetAligned(checkAlign)) {
            auto middleValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::LEFT;
            if (childFlexItemProperty->GetAligned(checkAlign)) {
                widthValue = middleValue - childFlexItemProperty->GetAlignValue(checkAlign);
                itemMaxWidth = 2.0f * std::max(widthValue, 0.0f);
                itemMinWidth = 2.0f * std::max(widthValue, 0.0f);
            } else {
                checkAlign = AlignDirection::RIGHT;
                widthValue = childFlexItemProperty->GetAlignValue(checkAlign) - middleValue;
                itemMaxWidth = 2.0f * std::max(widthValue, 0.0f);
                itemMinWidth = 2.0f * std::max(widthValue, 0.0f);
            }
        } else {
            auto checkAlign = AlignDirection::LEFT;
            auto leftValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::RIGHT;
            widthValue = childFlexItemProperty->GetAlignValue(checkAlign) - leftValue;
            itemMaxWidth = std::max(widthValue, 0.0f);
            itemMinWidth = std::max(widthValue, 0.0f);
        }
        if (LessNotEqual(widthValue, 0.0f)) {
            childConstraint.selfIdealSize.SetWidth(0.0f);
            childConstraint.selfIdealSize.SetHeight(0.0f);
            childWrapper->Measure(childConstraint);
            LOGE("Component %{public}s horizontal alignment illegal, will layout with size (0, 0)", nodeName.c_str());
            return;
        }
        childConstraint.selfIdealSize.SetWidth(itemMaxWidth);
    }
    if (!childFlexItemProperty->GetTwoVerticalDirectionAligned()) {
        itemMaxHeight = childConstraint.maxSize.Height();
        itemMinHeight = childConstraint.minSize.Height();
    } else {
        auto checkAlign = AlignDirection::CENTER;
        float heightValue = 0.0f;
        if (childFlexItemProperty->GetAligned(checkAlign)) {
            auto centerValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::TOP;
            if (childFlexItemProperty->GetAligned(checkAlign)) {
                heightValue = centerValue - childFlexItemProperty->GetAlignValue(checkAlign);
                itemMaxHeight = 2.0f * std::max(heightValue, 0.0f);
                itemMinHeight = 2.0f * std::max(heightValue, 0.0f);
            } else {
                checkAlign = AlignDirection::BOTTOM;
                heightValue = childFlexItemProperty->GetAlignValue(checkAlign) - centerValue;
                itemMaxHeight = 2.0f * std::max(heightValue, 0.0f);
                itemMinHeight = 2.0f * std::max(heightValue, 0.0f);
            }
        } else {
            auto checkAlign = AlignDirection::TOP;
            auto topValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::BOTTOM;
            heightValue = childFlexItemProperty->GetAlignValue(checkAlign) - topValue;
            itemMaxHeight = std::max(heightValue, 0.0f);
            itemMinHeight = std::max(heightValue, 0.0f);
        }
        if (LessNotEqual(heightValue, 0.0f)) {
            childConstraint.selfIdealSize.SetWidth(0.0f);
            childConstraint.selfIdealSize.SetHeight(0.0f);
            childWrapper->Measure(childConstraint);
            LOGE("Component %{public}s vertical alignment illegal, will layout with size (0, 0)", nodeName.c_str());
            return;
        }
        childConstraint.selfIdealSize.SetHeight(itemMaxHeight);
    }

    childConstraint.maxSize = SizeF(itemMaxWidth, itemMaxHeight);
    childConstraint.minSize = SizeF(itemMinWidth, itemMinHeight);
    childWrapper->Measure(childConstraint);
}

void RelativeContainerLayoutAlgorithm::CalcOffsetParam(LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto childWrapper = idNodeMap_[nodeName];
    auto containerSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    MinusPaddingToSize(padding_, containerSize);
    auto alignRules = childWrapper->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRulesValue();
    float offsetX = 0.0f;
    bool offsetXCalculated = false;
    float offsetY = 0.0f;
    bool offsetYCalculated = false;
    for (const auto& alignRule : alignRules) {
        if (idNodeMap_.find(alignRule.second.anchor) == idNodeMap_.end() &&
            !IsAnchorContainer(alignRule.second.anchor)) {
            LOGW("Anchor %{public}s of component %{public}s is not found, will be ignored",
                alignRule.second.anchor.c_str(), nodeName.c_str());
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < DIRECTION_RANGE) {
            if (!offsetXCalculated) {
                offsetX = CalcHorizontalOffset(alignRule.first, alignRule.second, containerSize.Width(), nodeName);
                offsetXCalculated = true;
            }
        } else {
            if (!offsetYCalculated) {
                offsetY = CalcVerticalOffset(alignRule.first, alignRule.second, containerSize.Height(), nodeName);
                offsetYCalculated = true;
            }
        }
    }
    recordOffsetMap_[nodeName] = OffsetF(offsetX, offsetY);
}

void RelativeContainerLayoutAlgorithm::CalcHorizontalLayoutParam(AlignDirection alignDirection,
    const AlignRule& alignRule, LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto childWrapper = idNodeMap_[nodeName];
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID_NOLOG(childLayoutProperty);
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    auto parentSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    MinusPaddingToSize(padding_, parentSize);
    switch (alignRule.horizontal) {
        case HorizontalAlign::START:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX());
            break;
        case HorizontalAlign::CENTER:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? parentSize.Width() / 2.0f
                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Width() / 2.0f +
                          recordOffsetMap_[alignRule.anchor].GetX());
            break;
        case HorizontalAlign::END:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor)
                                    ? parentSize.Width()
                                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Width() +
                                          recordOffsetMap_[alignRule.anchor].GetX());
            break;
        default:
            LOGE("Unsupported align direction");
            break;
    }
}

void RelativeContainerLayoutAlgorithm::CalcVerticalLayoutParam(AlignDirection alignDirection,
    const AlignRule& alignRule, LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto childWrapper = idNodeMap_[nodeName];
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID_NOLOG(childLayoutProperty);
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    auto parentSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    MinusPaddingToSize(padding_, parentSize);
    switch (alignRule.vertical) {
        case VerticalAlign::TOP:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY());
            break;
        case VerticalAlign::CENTER:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? parentSize.Height() / 2.0f
                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Height() / 2.0f +
                          recordOffsetMap_[alignRule.anchor].GetY());
            break;
        case VerticalAlign::BOTTOM:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor)
                                    ? parentSize.Height()
                                    : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Height() +
                                          recordOffsetMap_[alignRule.anchor].GetY());
            break;
        default:
            LOGE("Unsupported align direction");
            break;
    }
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffset(
    AlignDirection alignDirection, const AlignRule& alignRule, float containerWidth, const std::string& nodeName)
{
    float offsetX = 0.0f;
    auto childWrapper = idNodeMap_[nodeName];

    float flexItemWidth = childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    float anchorWidth = IsAnchorContainer(alignRule.anchor)
                            ? containerWidth
                            : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Width();
    switch (alignDirection) {
        case AlignDirection::LEFT:
            switch (alignRule.horizontal) {
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
                    LOGE("Unsupported align direction");
            }
            break;
        case AlignDirection::MIDDLE:
            switch (alignRule.horizontal) {
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
                    LOGE("Unsupported align direction");
            }
            break;
        case AlignDirection::RIGHT:
            switch (alignRule.horizontal) {
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
                    LOGE("Unsupported align direction");
            }
            break;
        default:
            LOGE("Unsupported layout position");
    }
    offsetX += IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX();
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffset(
    AlignDirection alignDirection, const AlignRule& alignRule, float containerHeight, const std::string& nodeName)
{
    float offsetY = 0.0f;
    auto childWrapper = idNodeMap_[nodeName];

    float flexItemHeight = childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    float anchorHeight = IsAnchorContainer(alignRule.anchor)
                             ? containerHeight
                             : idNodeMap_[alignRule.anchor]->GetGeometryNode()->GetMarginFrameSize().Height();
    switch (alignDirection) {
        case AlignDirection::TOP:
            switch (alignRule.vertical) {
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
                    LOGE("Unsupported align direction");
            }
            break;
        case AlignDirection::CENTER:
            switch (alignRule.vertical) {
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
                    LOGE("Unsupported align direction");
            }
            break;
        case AlignDirection::BOTTOM:
            switch (alignRule.vertical) {
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
                    LOGE("Unsupported align direction");
            }
            break;
        default:
            LOGE("Unsupported layout position");
    }
    offsetY += IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY();
    return offsetY;
}

} // namespace OHOS::Ace::NG