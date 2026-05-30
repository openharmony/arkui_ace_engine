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

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_info.h"

#include <climits>

#include "base/log/dump_log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
float LazyColumnLayoutInfo::GetEstimateItemSize()
{
    if (!posMap_.empty()) {
        float totalSize = posMap_.rbegin()->second.endPos + space_ - posMap_.begin()->second.startPos;
        int32_t totalCount = static_cast<int32_t>(posMap_.size());
        if (totalCount > 0) {
            return totalSize / totalCount - space_;
        }
    }
    return 0.0f;
}

float LazyColumnLayoutInfo::UpdatePosMapStart(int32_t updatedStart, int32_t updatedEnd)
{
    auto startIter = posMap_.find(updatedStart);
    if (startIter == posMap_.end()) {
        TAG_LOGE(AceLogTag::ACE_LAZY_COLUMN, "Not find updatedStart:%{public}d", updatedStart);
        return 0;
    }
    float prevPos = 0.0f;
    int32_t prevIndex = updatedStart - 1;
    if (startIter != posMap_.begin()) {
        auto it = startIter;
        --it;
        prevPos = it->second.endPos + space_;
        if (it->first + 1 < updatedStart) {
            int32_t gap = updatedStart - it->first - 1;
            prevPos += gap * (estimateItemSize_ + space_);
        }
    } else {
        // h/f/s: the body baseline starts at headerMainSize_; the prefix sum is anchored there.
        prevPos = headerMainSize_ + updatedStart * (estimateItemSize_ + space_);
    }
    if (NearEqual(startIter->second.startPos, prevPos)) {
        return 0;
    }
    float delta = prevPos - startIter->second.startPos;
    for (auto it = startIter; it != posMap_.end() && it->first <= updatedEnd; it++) {
        UpdatePosWithIter(it, prevIndex, prevPos);
    }
    return delta;
}

void LazyColumnLayoutInfo::UpdatePosMapEnd(int32_t updatedEnd)
{
    auto endIter = posMap_.find(updatedEnd);
    if (endIter == posMap_.end()) {
        TAG_LOGE(AceLogTag::ACE_LAZY_COLUMN, "Not find updatedEnd:%{public}d", updatedEnd);
        return;
    }
    float endPos = endIter->second.endPos + space_;
    auto it = endIter;
    it++;
    if (it == posMap_.end()) {
        if (updatedEnd >= totalItemCount_ - 1) {
            totalMainSize_ = endIter->second.endPos;
        } else {
            int32_t count = totalItemCount_ - 1 - updatedEnd;
            totalMainSize_ = endPos + count * (estimateItemSize_ + space_) - space_;
        }
        return;
    }
    float nextPos = it->second.startPos;
    if (it->first > updatedEnd + 1) {
        nextPos -= (it->first - updatedEnd - 1) * (estimateItemSize_ + space_);
    }
    int32_t prevIndex = updatedEnd;
    float prevPos = endPos;
    if (!NearEqual(nextPos, endPos)) {
        for (; it != posMap_.end(); it++) {
            UpdatePosWithIter(it, prevIndex, prevPos);
        }
    } else {
        auto last = posMap_.rbegin();
        prevPos = last->second.endPos + space_;
        prevIndex = last->first;
    }
    if (prevIndex >= totalItemCount_ - 1) {
        totalMainSize_ = prevPos - space_;
    } else {
        float estSize = (totalItemCount_ - 1 - prevIndex) * (estimateItemSize_ + space_);
        totalMainSize_ = prevPos + estSize - space_;
    }
}

void LazyColumnLayoutInfo::UpdateTotalMainSize()
{
    if (posMap_.empty()) {
        return;
    }
    auto last = posMap_.rbegin();
    float prevPos = last->second.endPos + space_;
    int32_t prevIndex = last->first;
    if (prevIndex >= totalItemCount_ - 1) {
        totalMainSize_ = prevPos - space_;
    } else {
        float estSize = (totalItemCount_ - 1 - prevIndex) * (estimateItemSize_ + space_);
        totalMainSize_ = prevPos + estSize - space_;
    }
}

float LazyColumnLayoutInfo::UpdatePosWithIter(
    std::map<int32_t, ColumnItemMainPos>::iterator& it, int32_t& prevIndex, float& prevPos) const
{
    float delta = 0;
    if (it->first == prevIndex + 1) {
        delta = prevPos - it->second.startPos;
        it->second.startPos = prevPos;
        it->second.endPos += delta;
    } else if (it->first > prevIndex + 1) {
        prevPos += (it->first - prevIndex - 1) * (estimateItemSize_ + space_);
        delta = prevPos - it->second.startPos;
        it->second.startPos = prevPos;
        it->second.endPos += delta;
    }
    prevIndex = it->first;
    prevPos = it->second.endPos + space_;
    return delta;
}

void LazyColumnLayoutInfo::UpdatePosMap()
{
    // Exclude the constant footer so it does not leak into the inter-frame adjustOffset.
    float prevTotalMainSize_ = totalMainSize_ - footerMainSize_;
    if (!Positive(estimateItemSize_)) {
        auto estimateItemSize = GetEstimateItemSize();
        if (Positive(estimateItemSize)) {
            estimateItemSize_ = estimateItemSize;
        }
    }
    if (updatedStart_ < INT_MAX) {
        if (cachedUpdatedStart_ < updatedStart_) {
            UpdatePosMapStart(cachedUpdatedStart_, updatedStart_ - 1);
        }
        adjustOffset_.start = UpdatePosMapStart(updatedStart_, updatedEnd_);
        if (cachedUpdatedEnd_ > updatedEnd_) {
            UpdatePosMapStart(updatedEnd_ + 1, cachedUpdatedEnd_);
            UpdatePosMapEnd(cachedUpdatedEnd_);
        } else {
            UpdatePosMapEnd(updatedEnd_);
        }
    } else if (cachedUpdatedStart_ < INT_MAX) {
        UpdatePosMapStart(cachedUpdatedStart_, cachedUpdatedEnd_);
        UpdatePosMapEnd(cachedUpdatedEnd_);
        adjustOffset_.start = endIndex_ < 0 ? 0.0f : totalMainSize_ - prevTotalMainSize_;
    } else if (spaceUpdated_) {
        UpdateTotalMainSize();
        adjustOffset_.start = endIndex_ < 0 ? 0.0f : totalMainSize_ - prevTotalMainSize_;
    } else {
        adjustOffset_.start = 0.0f;
    }
    adjustOffset_.end = totalMainSize_ - prevTotalMainSize_ - adjustOffset_.start;
    updatedStart_ = INT_MAX;
    updatedEnd_ = -1;
    cachedUpdatedStart_ = INT_MAX;
    cachedUpdatedEnd_ = -1;
    spaceUpdated_ = false;
}

void LazyColumnLayoutInfo::SetSpace(float space)
{
    if (!NearEqual(space, space_)) {
        space_ = space;
        int32_t prevIndex = -1;
        // h/f/s: body baseline is headerMainSize_; without this anchor the first item snaps back to 0 and overlaps
        // the header whenever space changes at runtime.
        float prevPos = headerMainSize_;
        for (auto it = posMap_.begin(); it != posMap_.end(); it++) {
            UpdatePosWithIter(it, prevIndex, prevPos);
        }
        updatedStart_ = INT_MAX;
        updatedEnd_ = -1;
        cachedUpdatedStart_ = INT_MAX;
        cachedUpdatedEnd_ = -1;
        spaceUpdated_ = true;
    }
}

void LazyColumnLayoutInfo::SetTotalItemCount(int32_t count)
{
    totalItemCount_ = count;
    auto it = posMap_.upper_bound(count - 1);
    posMap_.erase(it, posMap_.end());
    if (count == 0) {
        updatedStart_ = INT_MAX;
        updatedEnd_ = -1;
        startIndex_ = -1;
        endIndex_ = -1;
        visibleStartIndex_ = -1;
        visibleEndIndex_ = -1;
        cachedUpdatedStart_ = INT_MAX;
        cachedUpdatedEnd_ = -1;
        totalMainSize_ = 0.0f;
    }
}

void LazyColumnLayoutInfo::SetPosMap(int32_t index, const ColumnItemMainPos& pos)
{
    posMap_[index] = pos;
    updatedStart_ = std::min(index, updatedStart_);
    updatedEnd_ = std::max(index, updatedEnd_);
}

void LazyColumnLayoutInfo::SetCachedPosMap(int32_t index, const ColumnItemMainPos& pos)
{
    posMap_[index] = pos;
    cachedUpdatedStart_ = std::min(index, cachedUpdatedStart_);
    cachedUpdatedEnd_ = std::max(index, cachedUpdatedEnd_);
}

bool LazyColumnLayoutInfo::NeedPredict() const
{
    return ((GreatNotEqual(layoutedStart_, cacheStartPos_) && layoutedStartIndex_ > 0) ||
        (LessNotEqual(layoutedEnd_, cacheEndPos_) && layoutedEndIndex_ < totalItemCount_ - 1));
}

void LazyColumnLayoutInfo::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("itemStartIndex:" + std::to_string(startIndex_));
    DumpLog::GetInstance().AddDesc("itemEndIndex:" + std::to_string(endIndex_));
    DumpLog::GetInstance().AddDesc("itemTotalCount:" + std::to_string(totalItemCount_));
    DumpLog::GetInstance().AddDesc("headerMainSize:" + std::to_string(headerMainSize_));
    DumpLog::GetInstance().AddDesc("footerMainSize:" + std::to_string(footerMainSize_));
    DumpLog::GetInstance().AddDesc("space:" + std::to_string(space_));
    DumpLog::GetInstance().AddDesc("totalMainSize:" + std::to_string(totalMainSize_));
}

void LazyColumnLayoutInfo::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("itemStartIndex", startIndex_);
    json->Put("itemEndIndex", endIndex_);
    json->Put("itemTotalCount", totalItemCount_);
    json->Put("headerMainSize", headerMainSize_);
    json->Put("footerMainSize", footerMainSize_);
    json->Put("space", space_);
    json->Put("totalMainSize", totalMainSize_);
}
} // namespace OHOS::Ace::NG
