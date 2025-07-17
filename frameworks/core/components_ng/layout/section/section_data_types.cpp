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
#include "section_data_types.h"
namespace OHOS::Ace::NG {
int32_t Section::StartIdx() const
{
    int32_t minIdx = std::numeric_limits<int32_t>::max();
    for (const auto& lane : lanes) {
        if (lane.items_.empty()) {
            continue;
        }
        minIdx = std::min(minIdx, lane.items_.front().idx);
    }
    return minIdx;
}

int32_t Section::EndIdx() const
{
    int32_t maxIdx = std::numeric_limits<int32_t>::min();
    for (const auto& lane : lanes) {
        if (lane.items_.empty()) {
            continue;
        }
        maxIdx = std::max(maxIdx, lane.items_.back().idx);
    }
    return maxIdx;
}

float Section::StartPos() const
{
    if (lanes.empty()) {
        LOGW("section not ready");
        return 0.0f;
    }
    return std::min_element(lanes.begin(), lanes.end(), [](const Lane& lhs, const Lane& rhs) {
        return LessNotEqual(lhs.startPos, rhs.startPos);
    })->startPos;
}

float Section::EndPos() const
{
    if (lanes.empty()) {
        LOGW("section not ready");
        return 0.0f;
    }
    return std::max_element(lanes.begin(), lanes.end(), [](const Lane& lhs, const Lane& rhs) {
        return GreatNotEqual(lhs.endPos, rhs.endPos);
    })->endPos;
}

void Section::PrepareNextSection(Axis axis, Section& nextSection) const
{
    float pos = EndPos();
    pos += axis == Axis::VERTICAL ? margin.bottom.value_or(0.0f) + nextSection.margin.top.value_or(0.0f)
                                  : margin.right.value_or(0.0f) + nextSection.margin.left.value_or(0.0f);
    std::for_each(nextSection.lanes.begin(), nextSection.lanes.end(), [pos](Lane& lane) {
        lane.startPos = lane.endPos = pos;
        lane.items_.clear();
    });
}

void Section::PreparePrevSection(Axis axis, Section& prevSection) const
{
    float pos = StartPos();
    pos -= axis == Axis::VERTICAL ? margin.top.value_or(0.0f) + prevSection.margin.bottom.value_or(0.0f)
                                  : margin.left.value_or(0.0f) + prevSection.margin.right.value_or(0.0f);
    const float diff = prevSection.EndPos() - pos;
    if (NearZero(diff)) {
        return;
    }
    // use subtraction to keep the end positions staggered
    std::for_each(prevSection.lanes.begin(), prevSection.lanes.end(), [diff](Lane& lane) {
        lane.endPos -= diff;
        lane.startPos = lane.endPos;
        lane.items_.clear();
    });
}

void Section::PruneBack(float end)
{
    const int32_t startIdx = StartIdx();
    for (int32_t i = EndIdx(); i >= startIdx; --i) {
        auto& lane = GetLane(i);
        if (lane.items_.empty() || lane.items_.back().idx != i) {
            LOGW("corrupted item data");
            break;
        }
        float itemStartPos = lane.endPos - lane.items_.back().mainSize;
        if (LessNotEqual(itemStartPos, end)) {
            break;
        }
        lane.items_.pop_back();
        lane.endPos = itemStartPos - mainGap;
        if (lane.items_.empty()) {
            lane.endPos += mainGap;
        }
    }
}

void Section::PruneFront(float start)
{
    const int32_t endIdx = EndIdx();
    for (int32_t i = StartIdx(); i <= endIdx; ++i) {
        auto& lane = GetLane(i);
        if (lane.items_.empty() || lane.items_.front().idx != i) {
            LOGW("corrupted item data");
            break;
        }
        const float& itemLen = lane.items_.front().mainSize;
        const float itemEndPos = lane.startPos + itemLen;
        if (GreatNotEqual(itemEndPos, start)) {
            break;
        }
        lane.items_.pop_front();
        lane.startPos = itemEndPos + mainGap;
        if (lane.items_.empty()) {
            lane.startPos -= mainGap;
        }
    }
}

void Section::ClearItems()
{
    for (auto& lane : lanes) {
        lane.items_.clear();
        lane.startPos = 0.0f;
        lane.endPos = 0.0f;
    }
}

Lane& Section::GetLane(int32_t item)
{
    auto it = idxToLane.find(item);
    if (it != idxToLane.end() && it->second < lanes.size()) {
        return lanes[it->second];
    }
    LOGW("invalid item index");
    static Lane emptyLane;
    return emptyLane;
}

std::string Lane::ToString() const
{
    std::string res = "{StartPos: " + std::to_string(startPos) + " EndPos: " + std::to_string(endPos) + " ";
    if (items_.empty()) {
        res += "empty";
    } else {
        res += "Items [";
        for (const auto& item : items_) {
            res += std::to_string(item.idx) + " ";
        }
        res += "] ";
    }
    res += "}";
    return res;
}

std::string Section::ToString() const
{
    std::string str = "Section: ";
    str += "mainGap: " + std::to_string(mainGap) + ", ";
    str += "crossGap: " + std::to_string(crossGap) + ", ";
    str += "minItem: " + std::to_string(minItem) + ", ";
    str += "maxItem: " + std::to_string(maxItem) + ", ";
    str += "margin: " + margin.ToString() + ", ";
    str += "lanes: [";
    for (const auto& lane : lanes) {
        str += lane.ToString() + ", ";
    }
    str += "]";
    return str;
}
} // namespace OHOS::Ace::NG
