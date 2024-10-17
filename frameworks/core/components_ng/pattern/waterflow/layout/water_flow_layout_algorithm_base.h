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

namespace OHOS::Ace::NG {
class WaterFlowLayoutBase : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(WaterFlowLayoutBase, LayoutAlgorithm);

public:
    virtual void SetCanOverScroll(bool canOverScroll) = 0;

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

    static int32_t GetUpdateIdx(LayoutWrapper* host, int32_t footerIdx);

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
};

enum class WaterFlowLayoutMode { TOP_DOWN = 0, SLIDING_WINDOW = 1 };
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_BASE_H
