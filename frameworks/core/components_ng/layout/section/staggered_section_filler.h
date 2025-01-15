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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_STAGGERED_SECTION_FILLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_STAGGERED_SECTION_FILLER_H
#include <queue>

#include "item_measurer.h"

#include "core/components_ng/layout/section/section_data_types.h"
namespace OHOS::Ace::NG {
class FrameNode;

class SectionFiller {
public:
    SectionFiller() = default;
    virtual ~SectionFiller() = default;
    /**
     * @brief Fill one item into the section.
     *
     * @param index of the item
     * @param viewportBound viewport limit to fill up to.
     * @return true if the item is filled successfully.
     */
    virtual bool Fill(const RefPtr<Measurer>& measurer, FrameNode* node, int32_t index, float viewportBound) = 0;
    virtual bool CanFill() const = 0;

    // [lane start/end position, lane index]
    using LanePos = std::pair<float, size_t>;

    ACE_DISALLOW_COPY_AND_MOVE(SectionFiller);
};

class SectionEndFiller : public SectionFiller {
public:
    SectionEndFiller(Section& section, float viewportBound) : section_(section)
    {
        PrepareEndPosQueue(section.lanes, section.mainGap, viewportBound);
    }

    bool Fill(const RefPtr<Measurer>& measurer, FrameNode* node, int32_t index, float viewportBound) override;

    bool CanFill() const override
    {
        return !q_.empty();
    }

private:
    void PrepareEndPosQueue(const std::vector<Lane>& lanes, float mainGap, float viewportBound);

    using EndPosQ = std::priority_queue<LanePos, std::vector<LanePos>, std::greater<>>;
    EndPosQ q_;

    Section& section_;
};

class SectionStartFiller : public SectionFiller {
public:
    explicit SectionStartFiller(Section& section) : section_(section)
    {
        PrepareStartPosQueue(section.lanes, section.mainGap, 0.0f);
    }

    bool Fill(const RefPtr<Measurer>& measurer, FrameNode* node, int32_t index, float viewportBound) override;

    bool CanFill() const override
    {
        return !q_.empty();
    }

private:
    void PrepareStartPosQueue(const std::vector<Lane>& lanes, float mainGap, float viewportBound);

    using StartPosQ = std::priority_queue<LanePos>;
    StartPosQ q_;

    Section& section_;
};
} // namespace OHOS::Ace::NG
#endif