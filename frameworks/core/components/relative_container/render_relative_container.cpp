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

#include "core/components/relative_container/render_relative_container.h"

#include "base/utils/utils.h"
#include "core/components/flex/render_flex_item.h"
#include "core/components/relative_container/relative_container_component.h"

namespace OHOS::Ace {

void RenderRelativeContainer::Update(const RefPtr<Component>& component)
{
    const auto relativeContainer = AceType::DynamicCast<RelativeContainerComponent>(component);
    if (!relativeContainer) {
        return;
    }
    MarkNeedLayout();
}

void RenderRelativeContainer::CollectNodesById()
{
    idNodeMap_.clear();
    for (const auto& child : GetChildren()) {
        auto flexItem = AceType::DynamicCast<RenderFlexItem>(child);
        if (flexItem) {
            idNodeMap_.emplace(flexItem->GetId(), flexItem);
            continue;
        }
        // Component who does not have align Rules will have default offset and layout param
        LayoutParam itemLayout;
        itemLayout.SetMinSize(Size(GetLayoutParam().GetMinSize().Width(), GetLayoutParam().GetMinSize().Height()));
        itemLayout.SetMaxSize(Size(GetLayoutParam().GetMaxSize().Width(), GetLayoutParam().GetMaxSize().Height()));
        child->Layout(itemLayout);
        child->SetPosition(Offset(0.0, 0.0));
    }
}

void RenderRelativeContainer::GetDependencyRelationship()
{
    for (const auto& child : GetChildren()) {
        auto flexItem = AceType::DynamicCast<RenderFlexItem>(child);
        if (!flexItem) {
            continue;
        }
        for (const auto& alignRule : flexItem->GetAlignRules()) {
            if (alignRule.second.anchor == "container") {
                continue;
            }
            if (reliedOnMap_.count(alignRule.second.anchor) == 0) {
                std::set<std::string> reliedList;
                reliedList.insert(flexItem->GetId());
                reliedOnMap_[alignRule.second.anchor] = reliedList;
                continue;
            }
            reliedOnMap_[alignRule.second.anchor].insert(flexItem->GetId());
        }
    }
}

void RenderRelativeContainer::BuildIncomingDegreeMap()
{
    for (const auto& child : GetChildren()) {
        std::set<std::string> anchorSet;
        auto flexItem = AceType::DynamicCast<RenderFlexItem>(child);
        if (!flexItem) {
            continue;
        }
        for (const auto& alignRule : flexItem->GetAlignRules()) {
            if (alignRule.second.anchor != "container") {
                anchorSet.insert(alignRule.second.anchor);
            }
        }
        incomingDegreeMap_[flexItem->GetId()] = anchorSet.size();
    }
}

bool RenderRelativeContainer::PreTopologicalLoopDetection()
{
    std::queue<std::string> visitedNode;
    std::queue<std::string> layoutQueue;
    
    for (const auto& child : GetChildren()) {
        auto flexItem = AceType::DynamicCast<RenderFlexItem>(child);
        if (!flexItem) {
            continue;
        }
        std::set<std::string> anchorSet;
        for (const auto& alignRule : flexItem->GetAlignRules()) {
            if (alignRule.second.anchor != "container") {
                anchorSet.insert(alignRule.second.anchor);
            }
        }
        incomingDegreeMap_[flexItem->GetId()] = anchorSet.size();
        if (incomingDegreeMap_[flexItem->GetId()] == 0) {
            layoutQueue.push(flexItem->GetId());
        }
    }
    std::map<std::string, uint32_t> incomingDegreeMapCopy;
    incomingDegreeMapCopy.insert(incomingDegreeMap_.begin(), incomingDegreeMap_.end());
    while (!layoutQueue.empty()) {
        auto currentNodeName = layoutQueue.front();
        layoutQueue.pop();
        auto reliedSet = reliedOnMap_[currentNodeName];
        for (const auto& node : reliedSet) {
            incomingDegreeMapCopy[node] -= 1;
            if (incomingDegreeMapCopy[node] == 0) {
                layoutQueue.push(node);
            }
        }
        visitedNode.push(currentNodeName);
    }
    if (visitedNode.size() != idNodeMap_.size()) {
        return false;
    }
    return true;
}

void RenderRelativeContainer::CalcHorizontalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
    const std::string& nodeName)
{
    auto flexItem = idNodeMap_[nodeName];
    if (!flexItem) {
        return;
    }
    double anchorHorizontalSize = alignRule.anchor == "container" ?
            GetLayoutSize().Width() : idNodeMap_[alignRule.anchor]->GetLayoutSize().Width();
    switch (alignRule.horizontal) {
        case HorizontalAlign::START:
            flexItem->SetAlignValue(alignDirection, 0.0);
            break;
        case HorizontalAlign::CENTER:
            flexItem->SetAlignValue(alignDirection, anchorHorizontalSize / 2);
            break;
        case HorizontalAlign::END:
            flexItem->SetAlignValue(alignDirection, anchorHorizontalSize);
            break;
        default:
            LOGE("Unsupported align direction");
    }
}

void RenderRelativeContainer::CalcVerticalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
    const std::string& nodeName)
{
    auto flexItem = idNodeMap_[nodeName];
    if (!flexItem) {
        return;
    }
    double anchorVerticalSize = alignRule.anchor == "container" ?
            GetLayoutSize().Height() : idNodeMap_[alignRule.anchor]->GetLayoutSize().Height();
    switch (alignRule.vertical) {
        case VerticalAlign::TOP:
            flexItem->SetAlignValue(alignDirection, 0.0);
            break;
        case VerticalAlign::CENTER:
            flexItem->SetAlignValue(alignDirection, anchorVerticalSize / 2);
            break;
        case VerticalAlign::BOTTOM:
            flexItem->SetAlignValue(alignDirection, anchorVerticalSize);
            break;
        default:
            LOGE("Unsupported align direction");
    }
}

void RenderRelativeContainer::TopologicalSort(std::list<std::string>& renderList)
{
    std::queue<std::string> layoutQueue;
    for (const auto& child : GetChildren()) {
        auto flexItem = AceType::DynamicCast<RenderFlexItem>(child);
        if (!flexItem) {
            continue;
        }
        if (incomingDegreeMap_[flexItem->GetId()] == 0) {
            layoutQueue.push(flexItem->GetId());
        }
    }
    while (layoutQueue.size() > 0) {
        auto currentNodeName = layoutQueue.front();
        layoutQueue.pop();
        // reduce incoming degree of nodes relied on currentNode
        auto reliedList = reliedOnMap_[currentNodeName];
        for (const auto& node : reliedList) {
            incomingDegreeMap_[node] -= 1;
            if (incomingDegreeMap_[node] == 0) {
                layoutQueue.push(node);
            }
        }
        renderList.emplace_back(currentNodeName);
    }
}

void RenderRelativeContainer::CalcLayoutParam(std::map<AlignDirection, AlignRule> alignRules, LayoutParam& itemLayout,
    const std::string& nodeName)
{
    auto flexItem = idNodeMap_[nodeName];
    double itemMaxWidth = 0.0;
    double itemMaxHeight = 0.0;
    double itemMinWidth = 0.0;
    double itemMinHeight = 0.0;
    Offset containerOffset = GetPosition();
    // set first two boudnaries of each direction
    for (const auto& alignRule : alignRules) {
        if (static_cast<uint32_t>(alignRule.first) < DIRECTION_RANGE) {
            if (!flexItem->GetTwoHorizontalDirectionAligned()) {
                CalcHorizontalLayoutParam(alignRule.first, alignRule.second, nodeName);
            }
        } else {
            if (!flexItem->GetTwoVerticalDirectionAligned()) {
                CalcVerticalLayoutParam(alignRule.first, alignRule.second, nodeName);
            }
        }
    }
    // If less than two boundaries have been set, width will use container's width
    if (!flexItem->GetTwoHorizontalDirectionAligned()) {
        itemMaxWidth = GetLayoutParam().GetMaxSize().Width();
        itemMinWidth = GetLayoutParam().GetMinSize().Width();
    } else {
        // Use two confirmed boundaries to set item's layout param
        // For example left and middle, item's width will be (middle - left) *2
        // If offset difference is negative, which is the case simillar to
        // item's left aligns to container's right, right aligns to left
        // Item layout size will be (0, 0) due to this illegal align
        auto checkAlign = AlignDirection::MIDDLE;
        double widthValue = 0.0;
        if (flexItem->GetAligned(checkAlign)) {
            auto middleValue = flexItem->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::LEFT;
            if (flexItem->GetAligned(checkAlign)) {
                widthValue = middleValue - flexItem->GetAlignValue(checkAlign);
                itemMaxWidth = 2 * (widthValue > 0.0 ? widthValue : 0.0);
                itemMinWidth = 2 * (widthValue > 0.0 ? widthValue : 0.0);
            } else {
                checkAlign = AlignDirection::RIGHT;
                widthValue = flexItem->GetAlignValue(checkAlign) - middleValue;
                itemMaxWidth = 2 * (widthValue > 0.0 ? widthValue : 0.0);
                itemMinWidth = 2 * (widthValue > 0.0 ? widthValue : 0.0);
            }
        } else {
            auto checkAlign = AlignDirection::LEFT;
            auto leftValue = flexItem->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::RIGHT;
            widthValue = flexItem->GetAlignValue(checkAlign) - leftValue;
            itemMaxWidth = widthValue > 0.0 ? widthValue : 0.0;
            itemMinWidth = widthValue > 0.0 ? widthValue : 0.0;
        }
        if (widthValue <= 0.0) {
            itemLayout.SetMinSize(Size(0.0, 0.0));
            itemLayout.SetMaxSize(Size(0.0, 0.0));
            LOGW("Horizontal alignment illegal, node %{public}s will layout with size (0, 0)", nodeName.c_str());
            return;
        }
    }
    if (!flexItem->GetTwoVerticalDirectionAligned()) {
        itemMaxHeight = GetLayoutParam().GetMaxSize().Height();
        itemMinHeight = GetLayoutParam().GetMinSize().Height();
    } else {
        double heightValue = 0.0;
        auto checkAlign = AlignDirection::CENTER;
        if (flexItem->GetAligned(checkAlign)) {
            auto centerValue = flexItem->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::TOP;
            if (flexItem->GetAligned(checkAlign)) {
                heightValue = centerValue - flexItem->GetAlignValue(checkAlign);
                itemMaxHeight = 2 * (heightValue > 0 ? heightValue : 0.0);
                itemMinHeight = 2 * (heightValue > 0 ? heightValue : 0.0);
            } else {
                checkAlign = AlignDirection::BOTTOM;
                heightValue = flexItem->GetAlignValue(checkAlign) - centerValue;
                itemMaxHeight = 2 * (heightValue > 0 ? heightValue : 0.0);
                itemMinHeight = 2 * (heightValue > 0 ? heightValue : 0.0);
            }
        } else {
            auto checkAlign = AlignDirection::TOP;
            auto topValue = flexItem->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::BOTTOM;
            heightValue = flexItem->GetAlignValue(checkAlign) - topValue;
            itemMaxHeight = heightValue > 0.0 ? heightValue : 0.0;
            itemMinHeight = heightValue > 0.0 ? heightValue : 0.0;
        }
        if (heightValue <= 0.0) {
            itemLayout.SetMinSize(Size(0.0, 0.0));
            itemLayout.SetMaxSize(Size(0.0, 0.0));
            LOGW("Vertical alignment illegal, node %{public}s will layout with size (0, 0)", nodeName.c_str());
            return;
        }
    }
    itemLayout.SetMinSize(Size(itemMinWidth, itemMinHeight));
    itemLayout.SetMaxSize(Size(itemMaxWidth, itemMaxHeight));
}

void RenderRelativeContainer::PerformLayout()
{
    Size containerSize = GetLayoutParam().GetMaxSize();
    if (containerSize.IsInfinite()) {
        SetLayoutSize(viewPort_);
    } else {
        SetLayoutSize(containerSize);
    }
    if (GetChildren().empty()) {
        LOGD("RenderRelativeContainer: No child in Relative container");
        return;
    }
    idNodeMap_.clear();
    reliedOnMap_.clear();
    incomingDegreeMap_.clear();
    CollectNodesById();
    GetDependencyRelationship();
    if (!PreTopologicalLoopDetection()) {
        LOGE("Perform Layout failed, components has loop dependency");
        return;
    }
    TopologicalSort(renderList_);
    for (const auto& nodeName : renderList_) {
        auto flexItem = idNodeMap_[nodeName];
        if (!flexItem) {
            continue;
        }
        auto alignRules = flexItem->GetAlignRules();
        LayoutParam itemLayout;
        CalcLayoutParam(alignRules, itemLayout, nodeName);
        flexItem->Layout(itemLayout);

        double offsetX = 0.0;
        bool offsetXCalculated = false;
        double offsetY = 0.0;
        bool offsetYCalculated = false;
        for (const auto& alignRule : alignRules) {
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
        LOGI("Item %{public}s set offsetX %{public}f, offsetY is %{public}f", nodeName.c_str(),
            offsetX, offsetY);
        flexItem->SetPosition(Offset(offsetX, offsetY));
    }
}

double RenderRelativeContainer::CalcHorizontalOffset(AlignDirection alignDirection, const AlignRule& alignRule,
    double containerWidth, const std::string& nodeName)
{
    double offsetX = 0.0;
    auto flexItem = idNodeMap_[nodeName];
    double flexItemWidth = flexItem->GetLayoutSize().Width();
    double anchorWidth = alignRule.anchor == "container" ?
        containerWidth : anchorWidth = idNodeMap_[alignRule.anchor]->GetLayoutSize().Width();
    switch (alignDirection) {
        case AlignDirection::LEFT:
            switch (alignRule.horizontal) {
                case HorizontalAlign::START:
                    offsetX = 0.0;
                    break;
                case HorizontalAlign::CENTER:
                    offsetX = anchorWidth / 2;
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
                    offsetX = (-1) * flexItemWidth / 2;
                    break;
                case HorizontalAlign::CENTER:
                    offsetX = anchorWidth / 2 - flexItemWidth / 2;
                    break;
                case HorizontalAlign::END:
                    offsetX = anchorWidth - flexItemWidth / 2;
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
                    offsetX = anchorWidth / 2 - flexItemWidth;
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
    offsetX += alignRule.anchor == "container" ? 0.0 : idNodeMap_[alignRule.anchor]->GetPosition().GetX();
    return offsetX;
}

double RenderRelativeContainer::CalcVerticalOffset(AlignDirection alignDirection, const AlignRule& alignRule,
    double containerHeight, const std::string& nodeName)
{
    double offsetY = 0.0;
    auto flexItem = idNodeMap_[nodeName];
    double flexItemHeight = flexItem->GetLayoutSize().Height();
    double anchorHeight = alignRule.anchor == "container" ?
        containerHeight : idNodeMap_[alignRule.anchor]->GetLayoutSize().Height();
    switch (alignDirection) {
        case AlignDirection::TOP:
            switch (alignRule.vertical) {
                case VerticalAlign::TOP:
                    offsetY = 0.0;
                    break;
                case VerticalAlign::CENTER:
                    offsetY = anchorHeight / 2;
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
                    offsetY = (-1) * flexItemHeight / 2;
                    break;
                case VerticalAlign::CENTER:
                    offsetY = anchorHeight / 2 - flexItemHeight / 2;
                    break;
                case VerticalAlign::BOTTOM:
                    offsetY = anchorHeight - flexItemHeight / 2;
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
                    offsetY = anchorHeight / 2 - flexItemHeight;
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
    offsetY += alignRule.anchor == "container" ? 0.0 : idNodeMap_[alignRule.anchor]->GetPosition().GetY();
    return offsetY;
}

} // namespace OHOS::Ace