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

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_info.h"
#include <climits>

#include "base/log/dump_log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
void LazyGridLayoutInfo::EstimateItemSize()
{
    float totalSize = posMap_.rbegin()->second.endPos + spaceWidth_ - posMap_.begin()->second.startPos;
    int32_t totalCount = (posMap_.rbegin()->first + 1 - posMap_.begin()->first) / lanes_;
    estimateItemSize_ = totalSize / totalCount - spaceWidth_;
}

float LazyGridLayoutInfo::UpdatePosMapStart()
{
    auto startIter = posMap_.find(updatedStart_);
    if (startIter == posMap_.end()) {
        TAG_LOGE(AceLogTag::ACE_LAZY_GRID, "Not find updatedStart_:%{public}d", updatedStart_);
        return 0;
    }
    float prevPos = 0.0f;
    if (startIter != posMap_.begin()) {
        auto it = startIter;
        --it;
        prevPos = it->second.endPos + spaceWidth_;
        if (it->first + 1 < updatedStart_) {
            int32_t lines = (updatedStart_ - LanesFloor(it->first)) / lanes_ - 1;
            prevPos += lines * (estimateItemSize_ + spaceWidth_);
        }
    } else {
        prevPos = (updatedStart_ / lanes_) * estimateItemSize_;
    }
    if (NearEqual(startIter->second.startPos, prevPos)) {
        return 0;
    }
    float delta = prevPos - startIter->second.startPos;
    for (auto it = startIter; it != posMap_.end() && it->first <= updatedEnd_; it++) {
        it->second.startPos += delta;
        it->second.endPos += delta;
    }
    return delta;
}

void LazyGridLayoutInfo::UpdatePosMapEnd()
{
    auto endIter = posMap_.find(updatedEnd_);
    if (endIter == posMap_.end()) {
        TAG_LOGE(AceLogTag::ACE_LAZY_GRID, "Not find updatedEnd_:%{public}d", updatedEnd_);
        return;
    }
    float endPos = endIter->second.endPos + spaceWidth_;
    auto it = endIter;
    it++;
    if (it == posMap_.end()) {
        if (updatedEnd_ >= totalItemCount_ - 1) {
            totalMainSize_ = endIter->second.endPos;
        } else {
            int32_t count = LineCount(updatedEnd_, totalItemCount_ - 1);
            totalMainSize_ = endPos + count * (estimateItemSize_ + spaceWidth_) - spaceWidth_;
        }
        return;
    }
    float nextPos = it->second.startPos;
    if (it->first > updatedEnd_ + 1) {
        nextPos -= (LineCount(updatedEnd_, it->first) - 1) * (estimateItemSize_ + spaceWidth_);
    }
    if (NearEqual(nextPos, endPos)) {
        return;
    }
    int32_t prevIndex = updatedEnd_;
    float prevPos = endPos;
    float delta = 0.0f;
    for (; it != posMap_.end(); it++) {
        delta = UpdatePosWithIter(it, prevIndex, prevPos);
    }
    if (prevIndex >= totalItemCount_ - 1) {
        totalMainSize_ = prevPos - spaceWidth_;
    } else {
        float estSize = LineCount(prevIndex, totalItemCount_ - 1) * (estimateItemSize_ + spaceWidth_);
        totalMainSize_ = prevPos + estSize - spaceWidth_;
    }
}

float LazyGridLayoutInfo::UpdatePosWithIter(
    std::map<int, GridItemMainPos>::iterator &it, int32_t& prevIndex, float& prevPos) const
{
    float delta = 0;
    if (it->first == prevIndex + 1) {
        delta = prevPos - it->second.startPos;
        it->second.startPos = prevPos;
        it->second.endPos += delta;
    } else if (it->first > prevIndex + 1) {
        prevPos += (LineCount(prevIndex, it->first) - 1) * (estimateItemSize_ + spaceWidth_);
        delta = prevPos - it->second.startPos;
        it->second.startPos = prevPos;
        it->second.endPos += delta;
    }
    prevIndex = it->first;
    if (it->second.laneIdx == lanes_ - 1) {
        prevPos = it->second.endPos + spaceWidth_;
    }
    return delta;
}

float LazyGridLayoutInfo::UpdateSpaceStart()
{
    int32_t prevIndex = -1;
    float prevPos = 0.0f;
    float delta = 0.0f;
    for (auto it = posMap_.begin(); it != posMap_.end() && it->first < updatedStart_; it++) {
        delta = UpdatePosWithIter(it, prevIndex, prevPos);
    }
    return delta;
}

void LazyGridLayoutInfo::UpdatePosMap()
{
    AdjustRefPos adjust;
    float prevTotalMainSize_ = totalMainSize_;
    if (!Positive(estimateItemSize_)) {
        EstimateItemSize();
    }
    if (updatedStart_ < INT_MAX) {
        adjust.start = UpdatePosMapStart();
        UpdatePosMapEnd();
        adjust.end = totalMainSize_ - prevTotalMainSize_ - adjust.start;
        updatedStart_ = INT_MAX;
        updatedEnd_ = -1;
    }
}

void LazyGridLayoutInfo::SetSpace(float space)
{
    if (!NearEqual(space, spaceWidth_)) {
        int32_t prevIndex = -1;
        float prevPos = 0.0f;
        for (auto it = posMap_.begin(); it != posMap_.end(); it++) {
            UpdatePosWithIter(it, prevIndex, prevPos);
        }
    }
    spaceWidth_ = space;
}

void LazyGridLayoutInfo::SetLanes(int32_t lanes)
{
    if (lanes_ != lanes) {
        posMap_.clear();
    }
    lanes_ = lanes;
}

void LazyGridLayoutInfo::SetPosMap(int32_t index, const GridItemMainPos& pos)
{
    posMap_[index] = pos;
    updatedStart_ = std::min(index, updatedStart_);
    updatedEnd_ = std::max(index, updatedEnd_);
}

int32_t LazyGridLayoutInfo::LanesFloor(int32_t index) const
{
    if (lanes_ > 1) {
        return index - index % lanes_;
    }
    return index;
}

int32_t LazyGridLayoutInfo::LanesCeil(int32_t index) const
{
    int32_t tmpIndex = (lanes_ <= 1) ? index : (index - index % lanes_ + lanes_ - 1);
    tmpIndex = tmpIndex >= totalItemCount_ ? totalItemCount_ - 1 : tmpIndex;
    return tmpIndex;
}

int32_t LazyGridLayoutInfo::LineCount(int32_t start, int32_t end) const
{
    if (lanes_ > 1) {
        return (LanesFloor(end) - LanesFloor(start)) / lanes_;
    }
    return end - start;
}

bool LazyGridLayoutInfo::NeedPredict() const
{
    return ((GreatNotEqual(layoutedStart_, cacheStartPos_) && layoutedStartIndex_ > 0) ||
        (LessNotEqual(layoutedEnd_, cacheEndPos_) && layoutedEndIndex_ < totalItemCount_ - 1));
}

void LazyGridLayoutInfo::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("itemStartIndex:" + std::to_string(startIndex_));
    DumpLog::GetInstance().AddDesc("itemEndIndex:" + std::to_string(endIndex_));
    DumpLog::GetInstance().AddDesc("itemTotalCount:" + std::to_string(totalItemCount_));
    DumpLog::GetInstance().AddDesc("spaceWidth:" + std::to_string(spaceWidth_));
    DumpLog::GetInstance().AddDesc("totalMainSize:" + std::to_string(totalMainSize_));
}

void LazyGridLayoutInfo::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("itemStartIndex", startIndex_);
    json->Put("itemEndIndex", endIndex_);
    json->Put("itemTotalCount", totalItemCount_);
    json->Put("spaceWidth", spaceWidth_);
    json->Put("totalMainSize", totalMainSize_);
}
} // namespace OHOS::Ace::NG
