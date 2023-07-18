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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H

#include <cstdint>
#include <map>

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
struct FlowItemIndex {
    int32_t crossIndex = 0;
    int32_t lastItemIndex = 0;
};

struct FlowItemPosition {
    int32_t crossIndex = 0;
    float startMainPos = 0;
};

class WaterFlowLayoutInfo {
public:
    int32_t GetCrossIndex(int32_t itemIndex);
    void UpdateStartIndex();
    int32_t GetEndIndexByOffset(float offset) const;
    float GetMaxMainHeight() const;
    bool IsAllCrossReachend(float mainSize) const;
    FlowItemIndex GetCrossIndexForNextItem() const;
    float GetMainHeight(int32_t crossIndex, int32_t itemIndex);
    float GetStartMainPos(int32_t crossIndex, int32_t itemIndex);
    void Reset();
    int32_t GetCrossCount() const;
    int32_t GetMainCount() const;
    void ClearCacheAfterIndex(int32_t currentIndex);

    float currentOffset_ = 0.0f;
    float prevOffset_ = 0.0f;
    float lastMainSize_ = 0.0f;
    float maxHeight_ = 0.0f;

    bool itemEnd_ = false;
    bool itemStart_ = false;
    bool offsetEnd_ = false;

    int32_t jumpIndex_ = -1;

    int32_t startIndex_ = 0;
    int32_t endIndex_ = 0;
    int32_t footerIndex_ = -1;
    int32_t childrenCount_ = 0;
    // Map structure: [crossIndex, [index, (mainOffset, itemMainSize)]],
    std::map<int32_t, std::map<int32_t, std::pair<float, float>>> waterFlowItems_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H