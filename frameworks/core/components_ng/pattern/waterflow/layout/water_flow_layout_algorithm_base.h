/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_BASE_H
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_info_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"

namespace OHOS::Ace::NG {
class WaterFlowLayoutBase : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(WaterFlowLayoutBase, LayoutAlgorithm);

public:

    void SetCanOverScrollStart(bool canOverScroll)
    {
        canOverScrollStart_ = canOverScroll;
    }

    void SetCanOverScrollEnd(bool canOverScroll)
    {
        canOverScrollEnd_ = canOverScroll;
    }

    virtual void StartCacheLayout()
    { /* callback when cache layout starts */
    }
    /**
     * @brief Measure the cache item and append it to a lane.
     *
     * @param itemIdx index of the cache item to add.
     * @param deadline of the preload task. Return early if deadline is reached.
     * @return true if the item is actually created and appended in lane.
     */
    virtual bool PreloadItem(LayoutWrapper* host, int32_t itemIdx, int64_t deadline) = 0;

    virtual void EndCacheLayout()
    { /* callback when cache layout ends */
    }

    // record the previous layout index range for selective clearing mechanism
    int32_t prevStartIndex_ = -1;
    int32_t prevEndIndex_ = -1;

    // Flag indicating if layout phase is completed.
    bool isLayouted_ = true;

    // Record the index range after measurement completion
    int32_t measuredStartIndex_ = -1;
    int32_t measuredEndIndex_ = -1;

protected:
    /**
     * @brief Register an IdleTask to preload (create/measure/layout) items in cache range.
     */
    void PreloadItems(LayoutWrapper* host, const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t cacheCount);

    /**
     * @brief immediately create & measure items in cache range.
     * need sync load to display cache items on screen.
     */
    void SyncPreloadItems(LayoutWrapper* host, const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t cacheCount);
    
    bool canOverScrollStart_ = false;
    bool canOverScrollEnd_ = false;

    static int32_t GetUpdateIdx(LayoutWrapper* host, int32_t footerIdx);

    void UpdateOverlay(LayoutWrapper* layoutWrapper);

    void GetExpandArea(
        const RefPtr<WaterFlowLayoutProperty>& layoutProperty, const RefPtr<WaterFlowLayoutInfoBase>& info);

    bool CheckNeedLayout(const RefPtr<LayoutWrapper>& layoutWrapper, bool isCache) const
    {
        return (!isCache && layoutWrapper->CheckNeedForceMeasureAndLayout()) || expandSafeArea_ ||
               layoutWrapper->IsIgnoreOptsValid();
    }

    /**
    * Init unlayouted items collection from layout info when not layouted.
    */
    void InitUnlayoutedItems();

    /**
     * Clear layout algorithms only for measured items to preserve component states
     */
    void ClearUnlayoutedItems(LayoutWrapper* layoutWrapper);

    /**
    * @brief Get the layout information for the current water flow layout algorithm.
    * @return RefPtr to the layout information base object.
    */
    virtual RefPtr<WaterFlowLayoutInfoBase> LayoutInfo() const = 0;

    bool syncLoad_ = false;

private:
    /**
     * @brief immediately create / measure a cache item during LayoutTask
     */
    virtual void SyncPreloadItem(LayoutWrapper* host, int32_t itemIdx) = 0;

    /**
     * @param force true if force to preload all items in cache range.
     */
    static std::list<int32_t> GeneratePreloadList(
        const RefPtr<WaterFlowLayoutInfoBase>& info, LayoutWrapper* host, int32_t cacheCount, bool force);
    static void PostIdleTask(const RefPtr<FrameNode>& frameNode);

    bool expandSafeArea_ = false;
};

enum class WaterFlowLayoutMode { TOP_DOWN = 0, SLIDING_WINDOW = 1 };
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_BASE_H
