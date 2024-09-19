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
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {
class WaterFlowLayoutBase : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(WaterFlowLayoutBase, LayoutAlgorithm);

public:
    virtual void SetCanOverScroll(bool canOverScroll) = 0;
    struct PredictLayoutParam {
        std::list<int32_t> items;
        LayoutConstraintF layoutConstraint;
    };

protected:
    void PreBuildItems(LayoutWrapper* layoutWrapper, const RefPtr<WaterFlowLayoutInfoBase>& info,
        const LayoutConstraintF& constraint, int32_t cachedCount);
        
    static int32_t GetUpdateIdx(LayoutWrapper* host, int32_t footerIdx);

private:
    std::list<int32_t> LayoutCachedItem(
        LayoutWrapper* wrapper, const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t cachedCount);
    static bool PredictBuildItem(RefPtr<LayoutWrapper> wrapper, const LayoutConstraintF& constraint);
    static void PostIdleTask(RefPtr<FrameNode> frameNode, const PredictLayoutParam& param);
};

enum class WaterFlowLayoutMode { TOP_DOWN = 0, SLIDING_WINDOW = 1 };
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_BASE_H
