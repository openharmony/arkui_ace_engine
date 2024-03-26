/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
namespace {
std::vector<RefPtr<LazyForEachNode>> GetLazyForEachNodes(RefPtr<FrameNode>& host)
{
    std::vector<RefPtr<LazyForEachNode>> lazyNodes;
    for (const auto& child : host->GetChildren()) {
        if (!AceType::InstanceOf<LazyForEachNode>(child)) {
            continue;
        }
        auto lazyNode = AceType::DynamicCast<LazyForEachNode>(child);
        if (!lazyNode) {
            continue;
        }
        lazyNodes.push_back(lazyNode);
    }
    return lazyNodes;
}

bool OutOfBottomOrRightBoundary(
    Axis axis, RefPtr<GeometryNode>& childGeoNode, float offset, RefPtr<GeometryNode>& hostGeoNode)
{
    auto nodeOffset = childGeoNode->GetFrameOffset();
    auto hostSize = hostGeoNode->GetFrameSize();
    if (axis == Axis::VERTICAL) {
        return (nodeOffset.GetY() + offset) > hostSize.Height();
    } else if (axis == Axis::HORIZONTAL) {
        return (nodeOffset.GetX() + offset) > hostSize.Width();
    } else {
        return false;
    }
}

bool OutOfTopOrLeftBoundary(Axis axis, RefPtr<GeometryNode>& geoNode, float offset)
{
    auto nodeSize = geoNode->GetFrameSize();
    auto nodeOffset = geoNode->GetFrameOffset();
    if (axis == Axis::VERTICAL) {
        return nodeSize.Height() + nodeOffset.GetY() + offset < 0;
    } else if (axis == Axis::HORIZONTAL) {
        return nodeSize.Width() + nodeOffset.GetX() + offset < 0;
    } else {
        return false;
    }
}

int32_t GetScrollDownOrRightItemIndex(Axis axis, float offset, int32_t start, int32_t end, RefPtr<FrameNode>& host)
{
    auto inIndex = end;
    auto hostGeoNode = host->GetGeometryNode();
    for (; inIndex >= start; inIndex--) {
        auto child = host->GetChildByIndex(inIndex);
        if (!child) {
            continue;
        }
        auto childGeoNode = child->GetGeometryNode();
        if (!OutOfBottomOrRightBoundary(axis, childGeoNode, offset, hostGeoNode)) {
            break;
        }
    }
    return inIndex;
}

int32_t GetScrollUpOrLeftItemIndex(Axis axis, float offset, int32_t start, int32_t end, RefPtr<FrameNode>& host)
{
    auto outIndex = start;
    for (; outIndex <= end; outIndex++) {
        auto child = host->GetChildByIndex(outIndex);
        if (!child) {
            continue;
        }
        auto geoNode = child->GetGeometryNode();
        if (!OutOfTopOrLeftBoundary(axis, geoNode, offset)) {
            break;
        }
    }
    return outIndex;
}

void RecycleItemsByIndex(int32_t start, int32_t end,
                         std::vector<RefPtr<LazyForEachNode>>& lazyNodes, LayoutWrapper* wrapper)
{
    wrapper->RecycleItemsByIndex(start, end);
    for (const auto& node : lazyNodes) {
        node->RecycleItems(start, end);
    }
}
} // namespace

float ScrollableUtils::CheckHeightExpansion(const RefPtr<LayoutProperty>& layoutProps, Axis axis)
{
    float expandHeight = 0.0f;
    auto&& safeAreaOpts = layoutProps->GetSafeAreaExpandOpts();
    bool canExpand = axis == Axis::VERTICAL && safeAreaOpts && (safeAreaOpts->edges & SAFE_AREA_EDGE_BOTTOM) &&
                     (safeAreaOpts->type & SAFE_AREA_TYPE_SYSTEM);
    if (canExpand) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, {});
        auto safeArea = pipeline->GetSafeArea();
        expandHeight = safeArea.bottom_.Length();
    }
    return expandHeight;
}

void ScrollableUtils::RecycleItemsOutOfBoundary(
    Axis axis, float offset, int32_t start, int32_t end, LayoutWrapper* wrapper)
{
    if (start >= end || start < 0 || end < 0 || offset == 0) {
        return;
    }
    if (axis != Axis::HORIZONTAL && axis != Axis::VERTICAL) {
        return;
    }

    auto host = wrapper->GetHostNode();
    std::vector<RefPtr<LazyForEachNode>> lazyNodes = GetLazyForEachNodes(host);
    if (lazyNodes.empty()) {
        return;
    }
    if (offset >= 0) {
        int32_t inIndex = GetScrollDownOrRightItemIndex(axis, offset, start, end, host);
        if (inIndex >= end) {
            return;
        }
        RecycleItemsByIndex(inIndex + 1, end + 1, lazyNodes, wrapper);
    } else {
        int32_t outIndex = GetScrollUpOrLeftItemIndex(axis, offset, start, end, host);
        if (outIndex <= start) {
            return;
        }
        RecycleItemsByIndex(start, outIndex, lazyNodes, wrapper);
    }
}

} // namespace OHOS::Ace::NG
