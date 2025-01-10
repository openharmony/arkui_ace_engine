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
inline float Section::StartPos() const
{
    if (lanes.empty()) {
        LOGW("section not ready");
        return 0.0f;
    }
    return std::min_element(lanes.begin(), lanes.end(), [](const Lane& lhs, const Lane& rhs) {
        return LessNotEqual(lhs.startPos, rhs.startPos);
    })->startPos;
}
inline float Section::EndPos() const
{
    if (lanes.empty()) {
        LOGW("section not ready");
        return 0.0f;
    }
    return std::max_element(lanes.begin(), lanes.end(), [](const Lane& lhs, const Lane& rhs) {
        return GreatNotEqual(lhs.endPos, rhs.endPos);
    })->endPos;
}
void Section::PrepareNextSection(Axis axis,Section& nextSection) const
{
    float pos = EndPos();
    pos += axis == Axis::VERTICAL ? margin.bottom.value_or(0.0f) + nextSection.margin.top.value_or(0.0f)
                                  : margin.right.value_or(0.0f) + nextSection.margin.left.value_or(0.0f);
    std::for_each(nextSection.lanes.begin(), nextSection.lanes.end(), [pos]( Lane& lane) {
        lane.startPos = lane.endPos = pos;
        lane.items_.clear();
    });
}
void Section::PreparePrevSection(Axis axis,Section& prevSection) const
{
    float pos = StartPos();
    pos -= axis == Axis::VERTICAL ? margin.top.value_or(0.0f) + prevSection.margin.bottom.value_or(0.0f)
                                  : margin.left.value_or(0.0f) + prevSection.margin.right.value_or(0.0f);
    const float diff = prevSection.EndPos() - pos;
    if (NearZero(diff)) {
        return;
    }
    // use subtraction to keep the end positions staggered
    std::for_each(prevSection.lanes.begin(), prevSection.lanes.end(), [diff]( Lane& lane) {
        lane.endPos -= diff;
        lane.startPos = lane.endPos;
        lane.items_.clear();
    });
}
 }
