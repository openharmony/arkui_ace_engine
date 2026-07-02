/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/dynamiclayout/active_range_updater.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace OHOS::Ace::NG {

void ActiveRangeUpdater::UpdateActiveRange(LayoutWrapper* layoutWrapper, Axis axis, float adjustOffset,
    const std::vector<int32_t>& inActiveChildren)
{
    CHECK_NULL_VOID(layoutWrapper);
    axis_ = axis;
    inActiveChildren_ = inActiveChildren;
    if (!InitializeThreshold(layoutWrapper, adjustOffset)) {
        return;
    }
    visibleIndexes_.clear();
    int32_t index = 0;
    UpdateUINodeRange(index, layoutWrapper->GetHostNode());
}

bool ActiveRangeUpdater::IsChildInActive(int32_t index) const
{
    return std::find(inActiveChildren_.begin(), inActiveChildren_.end(), index) != inActiveChildren_.end();
}

void ActiveRangeUpdater::UpdateLazyNodeRange(int32_t index, const RefPtr<UINode>& node)
{
    CHECK_NULL_VOID(node);
    RefPtr<FrameNode> cacheStartNode;
    RefPtr<FrameNode> cacheEndNode;
    std::list<RefPtr<FrameNode>> outViewNodes;
    auto parent = node->GetParentFrameNode();
    for (const auto& child : node->GetChildren()) {
        auto frameNode = AceType::DynamicCast<FrameNode>(child->GetFrameChildByIndex(0, false));
        CHECK_NULL_CONTINUE(frameNode);
        auto range = CalculateItemRange(frameNode);
        bool shouldInactive = false;
        if (!inActiveChildren_.empty() && parent) {
            shouldInactive = IsChildInActive(parent->GetChildTrueIndex(frameNode));
        }
        if (range.inView && !shouldInactive) {
            if (!cacheStartNode) {
                cacheStartNode = frameNode;
            }
            cacheEndNode = frameNode;
        } else {
            outViewNodes.emplace_back(frameNode);
        }
        if (range.inVisible && parent && !shouldInactive) {
            visibleIndexes_.push_back(parent->GetChildTrueIndex(frameNode));
        }
    }
    if (cacheStartNode && cacheEndNode) {
        int32_t startIndex = node->GetFrameNodeIndex(cacheStartNode, true);
        int32_t endIndex = node->GetFrameNodeIndex(cacheEndNode, true);
        node->DoSetActiveChildRange(startIndex, endIndex, 0, 0, false);
    } else {
        node->DoSetActiveChildRange(-1, -1, 0, 0, false);
    }
    if (parent && !outViewNodes.empty()) {
        parent->RemoveFromPartFrameNodeChildren(outViewNodes);
    }
}

void ActiveRangeUpdater::UpdateUINodeRange(int32_t& index, const RefPtr<UINode>& node)
{
    CHECK_NULL_VOID(node);
    for (const auto& child : node->GetChildren()) {
        if (AceType::InstanceOf<LazyForEachNode>(child) ||
            AceType::InstanceOf<RepeatVirtualScroll2Node>(child)) {
            UpdateLazyNodeRange(index, child);
            index += child->FrameCount();
        } else if (AceType::InstanceOf<FrameNode>(child)) {
            auto range = CalculateItemRange(AceType::DynamicCast<FrameNode>(child));
            bool shouldInactive = IsChildInActive(index);
            if (range.inView && !shouldInactive) {
                child->SetActive(true);
                child->SetJSViewActive(true);
            } else {
                child->SetActive(false);
                child->SetJSViewActive(false);
            }
            if (range.inVisible && !shouldInactive) {
                visibleIndexes_.push_back(index);
            }
            index += 1;
        } else {
            UpdateUINodeRange(index, child);
        }
    }
}

ActiveRangeUpdater::RangeInfo ActiveRangeUpdater::CalculateItemRange(const RefPtr<FrameNode>& node)
{
    RangeInfo range;
    CHECK_NULL_RETURN(node, range);
    CHECK_NULL_RETURN(node->IsActive(), range);

    auto geoNode = node->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, range);

    float itemStartPos = 0.0f;
    float itemEndPos = 0.0f;
    if (axis_ == Axis::VERTICAL) {
        itemStartPos = geoNode->GetFrameOffset().GetY();
        itemEndPos = itemStartPos + geoNode->GetFrameSize().Height();
    } else {
        itemStartPos = geoNode->GetFrameOffset().GetX();
        itemEndPos = itemStartPos + geoNode->GetFrameSize().Width();
    }
    range.inView = GreatOrEqual(itemEndPos, startPos_ - startExtOffset_) &&
        LessOrEqual(itemStartPos, endPos_ + endExtOffset_);
    range.inVisible = GreatOrEqual(itemEndPos, startPos_) && LessOrEqual(itemStartPos, endPos_);
    return range;
}

bool ActiveRangeUpdater::InitializeThreshold(LayoutWrapper* layoutWrapper, float adjustOffset)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);

    auto contentLayoutConstraint = layoutProperty->GetContentLayoutConstraint();
    CHECK_NULL_RETURN(contentLayoutConstraint, false);

    auto posRef = contentLayoutConstraint->viewPosRef;
    if (!posRef.has_value() || posRef.value().axis != axis_) {
        return false;
    }

    auto geometry = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometry, false);
    float referencePos = posRef.value().referencePos;
    if (posRef.value().referenceEdge == ReferenceEdge::START) {
        startPos_ = posRef.value().viewPosStart - referencePos - adjustOffset;
        endPos_ = posRef.value().viewPosEnd - referencePos - adjustOffset;
    } else {
        float mainSize = geometry->GetPaddingSize().MainSize(axis_);
        startPos_ = posRef.value().viewPosStart - (referencePos - mainSize) - adjustOffset;
        endPos_ = posRef.value().viewPosEnd - (referencePos - mainSize) - adjustOffset;
    }
    const auto& padding = geometry->GetPadding();
    if (padding) {
        float paddingOffset = axis_ == Axis::VERTICAL ? padding->top.value_or(0) : padding->left.value_or(0);
        startPos_ += paddingOffset;
        endPos_ += paddingOffset;
    }
    startExtOffset_ = posRef.value().viewExtStart;
    endExtOffset_ = posRef.value().viewExtEnd;
    return true;
}

} // namespace OHOS::Ace::NG