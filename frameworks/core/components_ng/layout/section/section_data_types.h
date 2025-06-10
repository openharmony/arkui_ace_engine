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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_STAGGERED_DATA_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_STAGGERED_DATA_TYPES_H

#include <algorithm>
#include <deque>
#include <functional>
#include <vector>

#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
struct ItemInfo {
    int32_t idx = -1;
    float mainSize = 0.0f;
};

struct Lane {
    std::string ToString() const;

    float startPos = 0.0f;
    float endPos = 0.0f;
    std::deque<ItemInfo> items_;
    float crossLen = 0.0f;
};

struct Section {
    inline bool Contains(int32_t idx) const
    {
        return idx >= StartIdx() && idx <= EndIdx();
    }
    /**
     * @return index of first item currently in the section.
     */
    int32_t StartIdx() const;

    /**
     * @return index of last item currently in the section.
     */
    int32_t EndIdx() const;

    float StartPos() const;

    float EndPos() const;

    /**
     * @brief prepare next section's position and clear junk lanes.
     */
    void PrepareNextSection(Axis axis, Section& nextSection) const;
    /**
     * @brief prepare previous section's end position and clear junk lanes.
     */
    void PreparePrevSection(Axis axis, Section& prevSection) const;

    Lane& GetLane(int32_t item);

    /**
     * @brief clean out items that are above viewport.
     * @param start start position of the viewport.
     */
    void PruneFront(float start);

    /**
     * @brief clean out items that are below viewport.
     * @param end end position of the viewport.
     */
    void PruneBack(float end);

    void ClearItems();

    bool IsEmpty() const
    {
        return std::all_of(lanes.begin(), lanes.end(), [](const Lane& lane) { return lane.items_.empty(); });
    }

    std::string ToString() const;

    float mainGap = 0.0f;
    float crossGap = 0.0f;
    int32_t minItem = -1;
    int32_t maxItem = -1;
    MarginPropertyF margin;
    std::function<float(int32_t)> userDefMainLen;
    std::vector<Lane> lanes;
    std::unordered_map<int32_t, size_t> idxToLane;
};
} // namespace OHOS::Ace::NG

#endif
