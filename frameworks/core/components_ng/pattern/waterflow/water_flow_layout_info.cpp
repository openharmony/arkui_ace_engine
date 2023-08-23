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

#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"

#include <algorithm>

namespace OHOS::Ace::NG {
int32_t WaterFlowLayoutInfo::GetCrossIndex(int32_t itemIndex)
{
    for (const auto& crossItems : waterFlowItems_) {
        auto iter = crossItems.second.find(itemIndex);
        if (iter != crossItems.second.end()) {
            return crossItems.first;
        }
    }
    return -1;
}

void WaterFlowLayoutInfo::UpdateStartIndex()
{
    auto nextPosition = GetCrossIndexForNextItem();
    auto mainHeight = GetMainHeight(nextPosition.crossIndex, nextPosition.lastItemIndex);
    // need more items for currentOffset_
    if (LessOrEqual(currentOffset_ + mainHeight, 0.0f)) {
        return;
    }

    int32_t tempStartIndex = -1;
    for (const auto& crossItems : waterFlowItems_) {
        for (const auto& iter : crossItems.second) {
            if (GreatNotEqual(iter.second.first + iter.second.second + currentOffset_, 0.0f)) {
                tempStartIndex = tempStartIndex != -1 ? std::min(tempStartIndex, iter.first) : iter.first;
                break;
            }
        }
    }
    startIndex_ = tempStartIndex;
}

int32_t WaterFlowLayoutInfo::GetEndIndexByOffset(float offset) const
{
    int32_t endIndex = 0;
    bool found = false;
    for (const auto& crossItems : waterFlowItems_) {
        for (const auto& iter : crossItems.second) {
            if (GreatNotEqual(iter.second.first + iter.second.second + offset, 0)) {
                endIndex = std::max(endIndex, iter.first);
                found = true;
                break;
            }
        }
    }
    return found ? endIndex : -1;
}

float WaterFlowLayoutInfo::GetMaxMainHeight() const
{
    float result = 0.0f;
    for (const auto& crossItems : waterFlowItems_) {
        if (crossItems.second.empty()) {
            continue;
        }
        auto lastItem = crossItems.second.rbegin();
        auto crossMainHeight = lastItem->second.first + lastItem->second.second;
        if (NearEqual(result, 0.0f)) {
            result = crossMainHeight;
        }
        if (LessNotEqual(result, crossMainHeight)) {
            result = crossMainHeight;
        }
    }
    return result;
}

float WaterFlowLayoutInfo::GetMainHeight(int32_t crossIndex, int32_t itemIndex)
{
    float result = 0.0f;
    auto cross = waterFlowItems_.find(crossIndex);
    if (cross == waterFlowItems_.end()) {
        return result;
    }
    auto item = cross->second.find(itemIndex);
    if (item == cross->second.end()) {
        return result;
    }
    result = item->second.first + item->second.second;
    return result;
}

float WaterFlowLayoutInfo::GetStartMainPos(int32_t crossIndex, int32_t itemIndex)
{
    float result = 0.0f;
    auto cross = waterFlowItems_.find(crossIndex);
    if (cross == waterFlowItems_.end()) {
        return result;
    }
    auto item = cross->second.find(itemIndex);
    if (item == cross->second.end()) {
        return result;
    }
    result = item->second.first;
    return result;
}

bool WaterFlowLayoutInfo::IsAllCrossReachend(float mainSize) const
{
    bool result = true;
    for (const auto& crossItems : waterFlowItems_) {
        if (crossItems.second.empty()) {
            result = false;
            break;
        }
        auto lastItem = crossItems.second.rbegin();
        auto lastOffset = lastItem->second.first + lastItem->second.second;
        if (LessNotEqual(lastOffset + currentOffset_, mainSize)) {
            result = false;
            break;
        }
    }
    return result;
}

FlowItemIndex WaterFlowLayoutInfo::GetCrossIndexForNextItem() const
{
    FlowItemIndex position = { 0, -1 };
    auto minHeight = 0.0f;
    auto crossSize = static_cast<int32_t>(waterFlowItems_.size());
    for (int32_t i = 0; i < crossSize; ++i) {
        const auto& crossItems = waterFlowItems_.at(i);
        if (crossItems.empty()) {
            position.crossIndex = i;
            position.lastItemIndex = -1;
            break;
        }
        auto lastItem = crossItems.rbegin();
        auto lastOffset = lastItem->second.first + lastItem->second.second;
        if (NearEqual(minHeight, 0.0f)) {
            minHeight = lastOffset;
            position.crossIndex = i;
            position.lastItemIndex = lastItem->first;
        }
        if (LessNotEqual(lastOffset, minHeight)) {
            position.crossIndex = i;
            position.lastItemIndex = lastItem->first;
            minHeight = lastOffset;
            // first item height in this cross is 0
            if (NearZero(minHeight)) {
                break;
            }
        }
    }

    return position;
}

void WaterFlowLayoutInfo::Reset()
{
    itemEnd_ = false;
    itemStart_ = false;
    offsetEnd_ = false;

    jumpIndex_ = -1;

    startIndex_ = 0;
    endIndex_ = 0;
    waterFlowItems_.clear();
}

int32_t WaterFlowLayoutInfo::GetCrossCount() const
{
    return static_cast<int32_t>(waterFlowItems_.size());
}

int32_t WaterFlowLayoutInfo::GetMainCount() const
{
    int32_t maxMainCount = 0;
    for (const auto& crossItems : waterFlowItems_) {
        if (crossItems.second.empty()) {
            continue;
        }
        auto mainCount = static_cast<int32_t>(std::count_if(crossItems.second.begin(), crossItems.second.end(),
            [start = startIndex_, end = endIndex_](const std::pair<const int, std::pair<float, float>>& crossItem) {
                return crossItem.first >= start && crossItem.first <= end;
            }));
        maxMainCount = std::max(maxMainCount, mainCount);
    }
    return maxMainCount;
}

void WaterFlowLayoutInfo::ClearCacheAfterIndex(int32_t currentIndex)
{
    for (auto& crossItems : waterFlowItems_) {
        if (crossItems.second.empty()) {
            continue;
        }
        auto clearFrom = std::find_if(crossItems.second.begin(), crossItems.second.end(),
            [currentIndex](const std::pair<const int, std::pair<float, float>>& crossItem) {
                return crossItem.first > currentIndex;
            });
        crossItems.second.erase(clearFrom, crossItems.second.end());
    }
}
} // namespace OHOS::Ace::NG