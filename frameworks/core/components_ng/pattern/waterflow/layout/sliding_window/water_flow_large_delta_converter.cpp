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
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_large_delta_converter.h"

#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
namespace OHOS::Ace::NG {

int32_t WaterFlowLargeDeltaConverter::Convert(float delta)
{
    using std::abs, std::round, std::max;
    const float offset = info_.StartPos() + delta;
    const int32_t startIdx = info_.StartIndex();
    const auto curSec = static_cast<uint32_t>(info_.GetSegment(startIdx));
    if (curSec >= info_.lanes_.size() || curSec >= info_.mainGap_.size()) {
        return -1;
    }

    const auto crossCnt = static_cast<float>(info_.lanes_[curSec].size());
    const float average = info_.GetAverageItemHeight() + info_.mainGap_[curSec];
    if (NearZero(average)) {
        return -1;
    }

    int32_t result = startIdx - static_cast<int32_t>(round(offset * crossCnt / average));
    return max(result, 0);
}
} // namespace OHOS::Ace::NG
