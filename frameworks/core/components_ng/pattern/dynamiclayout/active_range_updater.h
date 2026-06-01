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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMICLAYOUT_ACTIVE_RANGE_UPDATER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMICLAYOUT_ACTIVE_RANGE_UPDATER_H

#include <algorithm>
#include <vector>
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

class ActiveRangeUpdater {
public:
    ActiveRangeUpdater() = default;
    ~ActiveRangeUpdater() = default;

    void UpdateActiveRange(LayoutWrapper* layoutWrapper, Axis axis, float adjustOffset,
        const std::vector<int32_t>& inActiveChildren = {});

    const std::vector<int32_t>& GetVisibleIndexes() const
    {
        return visibleIndexes_;
    }

private:
    struct RangeInfo {
        bool inView = false;
        bool inVisible = false;
    };

    void UpdateLazyNodeRange(int32_t index, const RefPtr<UINode>& node);
    void UpdateUINodeRange(int32_t& index, const RefPtr<UINode>& node);
    RangeInfo CalculateItemRange(const RefPtr<FrameNode>& node);
    bool InitializeThreshold(LayoutWrapper* layoutWrapper, float adjustOffset);
    bool IsChildInActive(int32_t index) const;

    float startPos_ = 0.0f;
    float endPos_ = 0.0f;
    float startExtOffset_ = 0.0f;
    float endExtOffset_ = 0.0f;
    std::vector<int32_t> visibleIndexes_;
    std::vector<int32_t> inActiveChildren_;
    Axis axis_ = Axis::VERTICAL;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMICLAYOUT_ACTIVE_RANGE_UPDATER_H