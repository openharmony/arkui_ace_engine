/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "layout_synchronizer.h"

#include "core/components_ng/layout/section/staggered_fill_algorithm.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/list/list_pattern.h"
#include "frameworks/core/components_ng/pattern/swiper/swiper_pattern.h"
#include "frameworks/core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
void LayoutSynchronizer::Sync(const RefPtr<LayoutProperty>& props, StaggeredFillAlgorithm& fillAlgo)
{
    const auto truth = GetLayoutTruth(props);
    if (truth.startIdx != fillAlgo.StartIdx() || truth.endIdx != fillAlgo.EndIdx()) {
        LOGW("Item ranges are out of sync: component range = %d - %d, fill range = %d - %d", truth.startIdx,
            truth.endIdx, fillAlgo.StartIdx().value_or(-1), fillAlgo.EndIdx().value_or(-1));
    } else if (truth.startPos != fillAlgo.StartPos()) {
        float diff = truth.startPos - fillAlgo.StartPos().value_or(0.0f);
        fillAlgo.OnSlidingOffsetUpdate(diff);
        LOGI("LayoutSynchronizer adjusted offset in FillAlgorithm by %f", diff);
    }
}

LayoutSynchronizer::LayoutState LayoutSynchronizer::GetLayoutTruth(const RefPtr<LayoutProperty>& props)
{
    CHECK_NULL_RETURN(props, {});
    auto host = props->GetHost();
    CHECK_NULL_RETURN(host, {});
    if (auto waterFlow = host->GetPattern<WaterFlowPattern>(); waterFlow) {
        return LayoutState { waterFlow->GetStoredOffset() + waterFlow->GetPendingDelta(), waterFlow->GetBeginIndex(),
            waterFlow->GetEndIndex() };
    }
    if (auto list = host->GetPattern<ListPattern>(); list) {
        return LayoutState { list->GetStartPos(), list->GetStartIndex(), list->GetEndIndex() };
    }
    if (auto swiper = host->GetPattern<SwiperPattern>(); swiper) {
        return LayoutState { swiper->GetStartPos(), swiper->GetStartIndex(), swiper->GetEndIndex() };
    }
    return {};
}
} // namespace OHOS::Ace::NG
