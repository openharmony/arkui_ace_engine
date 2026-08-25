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

#include <algorithm>
#include <stack>

#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_accessibility_utils.h"
#include "core/components_ng/syntax/if_else_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
namespace {
Dimension FOCUS_SCROLL_MARGIN = 5.0_vp;

// FEAT-028: cached image decode window covers ceil(cacheCount * 20%) cached units per side,
// implemented with integer math as (cacheCount + 4) / 5 (see design ADR-2).
constexpr int32_t CACHE_IMAGE_DECODE_WINDOW_DENOMINATOR = 5;
constexpr int32_t CACHE_IMAGE_DECODE_WINDOW_ROUNDUP = 4;

std::optional<float> GetAccessibilityCenterLimitMoveOffset(
    const RefPtr<FrameNode>& parentFrameNode, const RefPtr<FrameNode>& curFrameNode, const MoveOffsetParam& param,
    float moveOffset)
{
    auto scrollMoveOffset = GetScrollAccessibilityCenterLimitMoveOffset(parentFrameNode, moveOffset);
    if (scrollMoveOffset.has_value()) {
        return scrollMoveOffset;
    }
    return GetListAccessibilityCenterLimitMoveOffset(parentFrameNode, curFrameNode, param);
}

std::vector<RefPtr<ForEachBaseNode>> GetForEachNodes(RefPtr<FrameNode>& host)
{
    std::vector<RefPtr<ForEachBaseNode>> foreachNodes;
    CHECK_NULL_RETURN(host, foreachNodes);
    for (const auto& child : host->GetChildren()) {
        if (!AceType::InstanceOf<ForEachBaseNode>(child)) {
            continue;
        }
        auto node = AceType::DynamicCast<ForEachBaseNode>(child);
        if (!node) {
            continue;
        }
        foreachNodes.push_back(node);
    }
    return foreachNodes;
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

void RecycleItemsByIndex(
    int32_t start, int32_t end, std::vector<RefPtr<ForEachBaseNode>>& lazyNodes, LayoutWrapper* wrapper)
{
    wrapper->RecycleItemsByIndex(start, end);
    for (const auto& node : lazyNodes) {
        node->RecycleItems(start, end);
    }
}
struct NodeRange {
    RefPtr<UINode> node;
    int32_t start = 0;
};

// FEAT-028: apply decode eligibility to every ImagePattern in the subtree of a cached item.
// Walks only already-built children; images of a cached item (direct or nested) share the
// item's eligibility (spec AC-1.5 / R-5, design ADR-3). The item node is borrowed (owned by
// its parent's child list during the call on UI thread), so a raw pointer is used to avoid
// touching the reference count.
void SetSubtreeImagesDecodeActive(UINode* itemRoot, bool decodeActive)
{
    CHECK_NULL_VOID(itemRoot);
    std::stack<UINode*> nodesStack;
    nodesStack.push(itemRoot);
    while (!nodesStack.empty()) {
        auto* current = nodesStack.top();
        nodesStack.pop();
        if (current == nullptr) {
            continue;
        }
        auto* frameNode = AceType::DynamicCast<FrameNode>(current);
        if (frameNode) {
            auto imagePattern = frameNode->GetPattern<ImagePattern>();
            if (imagePattern) {
                imagePattern->SetCachedImageDecodeActive(decodeActive);
            }
        }
        for (const auto& child : current->GetChildren()) {
            nodesStack.push(AceType::RawPtr(child));
        }
    }
}
} // namespace

void ScrollableUtils::DisableLazyForEachBuildCache(const RefPtr<UINode>& node)
{
    CHECK_NULL_VOID(node);
    for (const auto& child : node->GetChildren()) {
        auto lazyNode = AceType::DynamicCast<LazyForEachNode>(child);
        if (lazyNode) {
            lazyNode->EnablePreBuild(false);
        } else if (AceType::InstanceOf<IfElseNode>(child)) {
            DisableLazyForEachBuildCache(child);
        }
    }
}

float ScrollableUtils::CheckHeightExpansion(const RefPtr<LayoutProperty>& layoutProps, Axis axis)
{
    float expandHeight = 0.0f;
    auto&& safeAreaOpts = layoutProps->GetSafeAreaExpandOpts();
    bool canExpand = axis == Axis::VERTICAL && safeAreaOpts && (safeAreaOpts->edges & SAFE_AREA_EDGE_BOTTOM) &&
                     (safeAreaOpts->type & SAFE_AREA_TYPE_SYSTEM);
    if (canExpand) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    std::vector<RefPtr<ForEachBaseNode>> foreachNodes = GetForEachNodes(host);
    if (foreachNodes.empty()) {
        return;
    }
    if (offset >= 0) {
        int32_t inIndex = GetScrollDownOrRightItemIndex(axis, offset, start, end, host);
        if (inIndex >= end) {
            return;
        }
        RecycleItemsByIndex(inIndex + 1, end + 1, foreachNodes, wrapper);
    } else {
        int32_t outIndex = GetScrollUpOrLeftItemIndex(axis, offset, start, end, host);
        if (outIndex <= start) {
            return;
        }
        RecycleItemsByIndex(start, outIndex, foreachNodes, wrapper);
    }
}

float ScrollableUtils::GetMoveOffset(
    const RefPtr<FrameNode>& parentFrameNode,
    const RefPtr<FrameNode>& curFrameNode,
    const MoveOffsetParam& param)
{
    constexpr float notMove = 0.0f;
    CHECK_NULL_RETURN(parentFrameNode, notMove);
    CHECK_NULL_RETURN(curFrameNode, notMove);
    auto parentGeometryNode = parentFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(parentGeometryNode, notMove);
    auto parentFrameSize = parentGeometryNode->GetPaddingSize();
    auto parentPaddingOffset = parentGeometryNode->GetPaddingOffset(true) - parentGeometryNode->GetFrameOffset();
    auto curFrameOffsetToWindow = curFrameNode->GetTransformRelativeOffset();
    auto parentFrameOffsetToWindow = parentFrameNode->GetTransformRelativeOffset() + parentPaddingOffset;
    auto offsetToTarFrame = curFrameOffsetToWindow - parentFrameOffsetToWindow;
    auto curGeometry = curFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(curGeometry, notMove);
    auto curFrameSize = curGeometry->GetFrameSize();
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "Node: %{public}s/%{public}d - %{public}s-%{public}s on focus. Offset to target node: "
        "%{public}s/%{public}d - %{public}s-%{public}s is (%{public}f,%{public}f).",
        curFrameNode->GetTag().c_str(), curFrameNode->GetId(), curFrameOffsetToWindow.ToString().c_str(),
        curFrameSize.ToString().c_str(), parentFrameNode->GetTag().c_str(), parentFrameNode->GetId(),
        parentFrameOffsetToWindow.ToString().c_str(), parentFrameSize.ToString().c_str(), offsetToTarFrame.GetX(),
        offsetToTarFrame.GetY());

    float diffToTarFrame = param.isVertical ? offsetToTarFrame.GetY() : offsetToTarFrame.GetX();
    if (NearZero(diffToTarFrame)) {
        return notMove;
    }
    float focusMargin = param.noNeedMargin ? 0 : static_cast<float>(FOCUS_SCROLL_MARGIN.ConvertToPx());
    float curFrameLength = param.isVertical ? curFrameSize.Height() : curFrameSize.Width();
    float parentFrameLength = param.isVertical ? parentFrameSize.Height() : parentFrameSize.Width();
    float focusMarginStart = std::max(focusMargin, param.contentStartOffset);
    float focusMarginEnd = std::max(focusMargin, param.contentEndOffset);

    bool totallyShow = LessOrEqual(curFrameLength + focusMarginStart + focusMarginEnd, parentFrameLength);
    float startAlignOffset = -diffToTarFrame + focusMarginStart;
    float endAlignOffset = parentFrameLength - diffToTarFrame - curFrameLength - focusMarginEnd;
    bool start2End = LessOrEqual(diffToTarFrame, focusMarginStart);
    bool needScroll = !NearZero(startAlignOffset, 1.0f) && !NearZero(endAlignOffset, 1.0f) &&
                      (std::signbit(startAlignOffset) == std::signbit(endAlignOffset));
    if (needScroll) {
        float moveOffset = (totallyShow ^ start2End) ? endAlignOffset : startAlignOffset;
        if (!param.isFromAccessibility) {
            return moveOffset;
        }
        auto limitMoveOffset = GetAccessibilityCenterLimitMoveOffset(parentFrameNode, curFrameNode, param, moveOffset);
        if (!limitMoveOffset.has_value()) {
            return moveOffset;
        }
        return NearZero(limitMoveOffset.value(), 1.0f) ? notMove : limitMoveOffset.value();
    }
    return notMove;
}

bool ScrollableUtils::IsMainThreadBusy(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    return pipelineContext->GetIsRequestFrame();
}

bool ScrollableUtils::IsChildLazy(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    CHECK_NULL_RETURN(frameNode, false);
    std::stack<NodeRange> nodesStack;
    nodesStack.push({frameNode, 0});

    auto isChildLazyOrRepeat = [](const RefPtr<UINode>& child) -> bool {
        return AceType::InstanceOf<LazyForEachNode>(child) || AceType::InstanceOf<RepeatVirtualScroll2Node>(child);
    };
    auto inRange = [](int32_t start, int32_t end, int32_t val) -> bool { return val >= start && val < end; };
    while (!nodesStack.empty()) {
        auto node = nodesStack.top();
        nodesStack.pop();
        int32_t start = node.start;
        int32_t end = start;
        for (const auto& child : node.node->GetChildren()) {
            start = end;
            end = start + child->FrameCount();
            if (start > index) {
                break;
            }
            if (AceType::InstanceOf<FrameNode>(child)) {
                continue;
            }
            if (inRange(start, end, index)) {
                if (isChildLazyOrRepeat(child)) {
                    return true;
                }
                nodesStack.push({child, start});
            }
        }
    }
    return false;
}

bool ScrollableUtils::IsLowMemoryDeviceForImageDecode(int32_t deviceDdrSizeGiB)
{
    // An invalid DDR size (<= 0, parameter read failure) keeps the existing strategy (high memory).
    return deviceDdrSizeGiB > 0 && deviceDdrSizeGiB <= LOW_MEMORY_DEVICE_DDR_SIZE_GIB;
}

bool ScrollableUtils::IsCachedImageDecodeWindowEnabled()
{
    return IsLowMemoryDeviceForImageDecode(SystemProperties::GetBootVendorDdrSize());
}

int32_t ScrollableUtils::CalcCachedImageDecodeWindowCount(int32_t cacheCount)
{
    if (cacheCount <= 0) {
        // cacheCount == 0 keeps the existing behavior: no extra image decode window (AC-1.3 / R-3).
        return 0;
    }
    // max(1, ceil(cacheCount * 20%)) in the component's existing cache units, clamped to
    // [1, cacheCount] so the window never exceeds the full cache range (AC-1.1/AC-1.2 / R-2).
    int32_t windowCount = (cacheCount + CACHE_IMAGE_DECODE_WINDOW_ROUNDUP) / CACHE_IMAGE_DECODE_WINDOW_DENOMINATOR;
    return std::clamp(windowCount, 1, cacheCount);
}

bool ScrollableUtils::CalcCachedImageDecodeIndexRange(int32_t startIndex, int32_t endIndex, int32_t cacheStartCount,
    int32_t cacheEndCount, int32_t& decodeStartIndex, int32_t& decodeEndIndex)
{
    if (endIndex < 0 || startIndex > endIndex) {
        return false;
    }
    int32_t windowStart = CalcCachedImageDecodeWindowCount(cacheStartCount);
    int32_t windowEnd = CalcCachedImageDecodeWindowCount(cacheEndCount);
    if (windowStart <= 0 && windowEnd <= 0) {
        // No side has a positive cache count: no image decode window for this range.
        return false;
    }
    decodeStartIndex = startIndex - windowStart;
    decodeEndIndex = endIndex + windowEnd;
    return true;
}

void ScrollableUtils::SetCachedItemImagesDecodeActive(const RefPtr<UINode>& itemRoot, bool decodeActive)
{
    SetSubtreeImagesDecodeActive(AceType::RawPtr(itemRoot), decodeActive);
}

void ScrollableUtils::UpdateCachedImageDecodeActiveForItem(const RefPtr<FrameNode>& host, int32_t childIndex,
    int32_t startIndex, int32_t endIndex, int32_t cacheStartCount, int32_t cacheEndCount)
{
    // High memory devices keep the existing strategy (AC-2.1 / R-6).
    if (!IsCachedImageDecodeWindowEnabled()) {
        return;
    }
    int32_t decodeStartIndex = 0;
    int32_t decodeEndIndex = 0;
    if (!CalcCachedImageDecodeIndexRange(
            startIndex, endIndex, cacheStartCount, cacheEndCount, decodeStartIndex, decodeEndIndex)) {
        return;
    }
    if (childIndex < 0) {
        return;
    }
    CHECK_NULL_VOID(host);
    // Never force building: only already-created cached items are updated.
    auto* itemNode = host->GetFrameNodeChildByIndexWithoutBuild(childIndex);
    CHECK_NULL_VOID(itemNode);
    bool decodeActive = childIndex >= decodeStartIndex && childIndex <= decodeEndIndex;
    SetSubtreeImagesDecodeActive(itemNode, decodeActive);
}

void ScrollableUtils::UpdateCachedImageDecodeRange(const RefPtr<FrameNode>& host, int32_t startIndex, int32_t endIndex,
    int32_t cacheStartCount, int32_t cacheEndCount, int32_t minItemIndex, int32_t maxItemIndex)
{
    // High memory devices keep the existing strategy (AC-2.1 / R-6).
    if (!IsCachedImageDecodeWindowEnabled()) {
        return;
    }
    CHECK_NULL_VOID(host);
    int32_t decodeStartIndex = 0;
    int32_t decodeEndIndex = 0;
    if (!CalcCachedImageDecodeIndexRange(
            startIndex, endIndex, cacheStartCount, cacheEndCount, decodeStartIndex, decodeEndIndex)) {
        return;
    }
    // The node cache range itself is NOT narrowed (AC-1.4: only image decode eligibility changes).
    int32_t cacheStart = std::max(cacheStartCount, 0);
    int32_t cacheEnd = std::max(cacheEndCount, 0);
    int32_t totalStart = std::max(std::max(startIndex - cacheStart, 0), minItemIndex);
    int32_t totalEnd = std::min(endIndex + cacheEnd, maxItemIndex);
    for (int32_t index = totalStart; index <= totalEnd; ++index) {
        auto* itemNode = host->GetFrameNodeChildByIndexWithoutBuild(index);
        if (!itemNode) {
            continue;
        }
        bool decodeActive = index >= decodeStartIndex && index <= decodeEndIndex;
        SetSubtreeImagesDecodeActive(itemNode, decodeActive);
    }
}
} // namespace OHOS::Ace::NG
