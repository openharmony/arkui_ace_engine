/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLABLE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLABLE_UTILS_H

#include <limits>

#include "base/geometry/axis.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class LayoutWrapper;

// FEAT-028: devices with total physical memory (boot vendor DDR size) not greater than this value
// (in GiB) are treated as low memory devices and enable the cached image decode window optimization.
constexpr int32_t LOW_MEMORY_DEVICE_DDR_SIZE_GIB = 8;

struct MoveOffsetParam {
    bool isVertical = false;
    float contentStartOffset = 0;
    float contentEndOffset = 0;
    bool noNeedMargin = false;
    bool isFromAccessibility = false;
};

struct ScrollableUtils {
    /**
     * @brief Disable lazyForEach prebuild cache item.
     *
     * @param node The host node.
     */
    static void DisableLazyForEachBuildCache(const RefPtr<UINode>& node);

    /**
     * @brief Checks if contentHeight needs to expand based on safeArea property.
     *
     * @param layoutProps The layout properties to check.
     * @param axis The scrollable axis.
     * @return The height expansion amount.
     */
    ACE_FORCE_EXPORT static float CheckHeightExpansion(const RefPtr<LayoutProperty>& layoutProps, Axis axis);

    /**
     * @brief Recycle items which are out of boundary.
     *
     * @param axis scroll direction
     * @param offset scroll offset, positive means scroll down, negative means scroll up.
     * @param start first item index
     * @param end last item index
     * @param wrapper layout wrapper
     */
    ACE_FORCE_EXPORT static void RecycleItemsOutOfBoundary(
        Axis axis, float offset, int32_t start, int32_t end, LayoutWrapper* wrapper);

    /**
     * @brief get moveoffset from parentFrameNode when curFrameNode focused.
     *
     * @param parentFrameNode parent framenode with scroll function
     * @param curFrameNode current focused framenode
     * @param isVertical vertical or not
     * @param contentStartOffset content start offset from parentFrameNode
     * @param contentEndOffset content end offset from parentFrameNode
     * @param isFromAccessibility whether the focus scroll request comes from accessibility
     */
    static float GetMoveOffset(
        const RefPtr<FrameNode>& parentFrameNode,
        const RefPtr<FrameNode>& curFrameNode,
        const MoveOffsetParam& param);

    /**
     * @brief get whether the main thread is busy.
     */
    static bool IsMainThreadBusy(const RefPtr<FrameNode>& frameNode);

    /**
     * @brief Check whether the child node is a lazy syntax node. This algorithm can be considered to be constant
     *        time complexity O(1) because the depth and number of child nodes of a FrameNode are limited.
     *
     * @param frameNode The scrollable frame node.
     */
    static bool IsChildLazy(const RefPtr<FrameNode>& frameNode, int32_t index);

    /**
     * @brief FEAT-028: pure function to judge whether a device memory tier should enable the
     *        cached image decode window on List/Grid/WaterFlow.
     *
     * @param deviceDdrSizeGiB total physical memory of the device in GiB (from boot vendor DDR size).
     * @return true when the value is valid and not greater than LOW_MEMORY_DEVICE_DDR_SIZE_GIB.
     */
    static bool IsLowMemoryDeviceForImageDecode(int32_t deviceDdrSizeGiB);

    /**
     * @brief FEAT-028: runtime wrapper of IsLowMemoryDeviceForImageDecode, reading
     *        SystemProperties::GetBootVendorDdrSize().
     */
    static bool IsCachedImageDecodeWindowEnabled();

    /**
     * @brief FEAT-028: pure function of the per-side cached image decode window size.
     *        Formula: cacheCount <= 0 keeps 0 (existing behavior); otherwise
     *        max(1, ceil(cacheCount * 20%)) clamped to [1, cacheCount], in the component's
     *        existing cache units (List/Grid cached rows, WaterFlow FlowItems).
     *
     * @param cacheCount per-side cache count in the component's existing cache units.
     * @return decode window size in the same units; 0 means the optimization is not applied.
     */
    static int32_t CalcCachedImageDecodeWindowCount(int32_t cacheCount);

    /**
     * @brief FEAT-028: pure function of the item index range that keeps image decode eligibility.
     *
     * @param startIndex first visible child index (-1 allowed as "no item on this side" sentinel).
     * @param endIndex last visible child index, must be >= 0.
     * @param cacheStartCount cached child count before the visible range.
     * @param cacheEndCount cached child count after the visible range.
     * @param decodeStartIndex output: first child index with decode eligibility.
     * @param decodeEndIndex output: last child index with decode eligibility.
     * @return false when the decode window is disabled for this range (high memory device is
     *         filtered by the caller, cacheCount == 0 keeps existing behavior).
     */
    static bool CalcCachedImageDecodeIndexRange(int32_t startIndex, int32_t endIndex, int32_t cacheStartCount,
        int32_t cacheEndCount, int32_t& decodeStartIndex, int32_t& decodeEndIndex);

    /**
     * @brief FEAT-028: apply one cached item's image decode eligibility to every Image inside its
     *        subtree (direct or nested Images share the same item eligibility).
     *
     * @param itemRoot root node of the cached item.
     * @param decodeActive true when the item is inside the image decode window.
     */
    static void SetCachedItemImagesDecodeActive(const RefPtr<UINode>& itemRoot, bool decodeActive);

    /**
     * @brief FEAT-028: apply image decode eligibility to a single child of a scroll container,
     *        used by predict-build/preload paths right after the child node is created.
     *
     * @param host the scroll container frame node (List/Grid/WaterFlow/ListItemGroup).
     * @param childIndex child index of the item inside the container.
     * @param startIndex first visible child index of the container.
     * @param endIndex last visible child index of the container.
     * @param cacheStartCount cached child count before the visible range.
     * @param cacheEndCount cached child count after the visible range.
     */
    static void UpdateCachedImageDecodeActiveForItem(const RefPtr<FrameNode>& host, int32_t childIndex,
        int32_t startIndex, int32_t endIndex, int32_t cacheStartCount, int32_t cacheEndCount);

    /**
     * @brief FEAT-028: update image decode eligibility for all already-built cached children of a
     *        scroll container. Children inside [startIndex - windowStart, endIndex + windowEnd]
     *        keep/regain decode eligibility, the remaining cached children keep the node cache but
     *        release decoded image resources immediately. Not-built children are skipped (the
     *        predict-build path applies eligibility on creation).
     *
     * @param host the scroll container frame node (List/Grid/WaterFlow/ListItemGroup).
     * @param startIndex first visible child index (-1 allowed as sentinel, see above).
     * @param endIndex last visible child index.
     * @param cacheStartCount cached child count before the visible range.
     * @param cacheEndCount cached child count after the visible range.
     * @param minItemIndex optional lower bound of the walk in child indexes, used by containers
     *        with non-item children (e.g. WaterFlow footer) so they are never toggled.
     * @param maxItemIndex optional upper bound of the walk in child indexes.
     */
    static void UpdateCachedImageDecodeRange(const RefPtr<FrameNode>& host, int32_t startIndex, int32_t endIndex,
        int32_t cacheStartCount, int32_t cacheEndCount,
        int32_t minItemIndex = std::numeric_limits<int32_t>::min(),
        int32_t maxItemIndex = std::numeric_limits<int32_t>::max());
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLABLE_UTILS_H
