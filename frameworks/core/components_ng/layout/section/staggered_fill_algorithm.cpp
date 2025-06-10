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

#include "staggered_fill_algorithm.h"

#include <algorithm>
#include <cstdint>

#include "staggered_section_filler.h"

#include "core/components_ng/base/fill_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"

namespace OHOS::Ace::NG {
std::optional<int32_t> StaggeredFillAlgorithm::StartIdx() const
{
    for (const auto& section : sections_) {
        if (!section.IsEmpty()) {
            return section.StartIdx();
        }
    }
    return std::nullopt;
}

std::optional<int32_t> StaggeredFillAlgorithm::EndIdx() const
{
    for (auto it = sections_.rbegin(); it != sections_.rend(); ++it) {
        if (!it->IsEmpty()) {
            return it->EndIdx();
        }
    }
    return std::nullopt;
}

void StaggeredFillAlgorithm::MarkJump()
{
    for (auto& section : sections_) {
        section.ClearItems();
    }
}

bool StaggeredFillAlgorithm::CanFillMoreAtStart(Axis axis)
{
    const auto item = StartIdx();
    if (!item) {
        return true;
    }
    if (*item == 0) {
        return false;
    }
    auto& section = GetSection(*item);
    if (*item == section.minItem) {
        section.PreparePrevSection(axis, GetSection(*item - 1));
        section = GetSection(*item - 1);
    }
    SectionStartFiller filler(section);
    return filler.CanFill();
}

bool StaggeredFillAlgorithm::CanFillMoreAtEnd(float viewportBound, Axis axis)
{
    auto item = EndIdx();
    CHECK_NULL_RETURN(item, true);
    auto& section = GetSection(*item);
    if (item == section.maxItem) {
        section.PrepareNextSection(axis, GetSection(*item + 1));
        section = GetSection(*item + 1);
    }
    SectionEndFiller filler(section, viewportBound);
    return filler.CanFill();
}

void StaggeredFillAlgorithm::PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt)
{
    InitSections(totalCnt, axis, viewport);

    measurer_ = Measurer::Construct(
        props_,
        [this](int32_t index) {
            auto& section = GetSection(index);
            return section.userDefMainLen ? section.userDefMainLen(index) : -1.0f;
        },
        axis, viewport);

    UpdateSyncCachedCnt();

    for (auto& section : sections_) {
        section.PruneFront(0.0f);
        section.PruneBack(viewport.MainSize(axis));
    }
}

bool StaggeredFillAlgorithm::CanFillMore(Axis axis, const SizeF& scrollWindowSize, int32_t idx, FillDirection direction)
{
    auto startIdx = StartIdx();
    auto endIdx = EndIdx();
    const bool isEdgeItem = direction == FillDirection::END ? idx == endIdx : idx == startIdx;
    if (GetSection(idx).Contains(idx) && !isEdgeItem) {
        return true;
    }
    if (direction == FillDirection::END ? CanFillMoreAtEnd(scrollWindowSize.MainSize(axis), axis)
                                        : CanFillMoreAtStart(axis)) {
        return true;
    }
    if (!startIdx || !endIdx) {
        return true;
    }
    return idx >= 0 && idx > *startIdx - syncCacheCnt_ && idx < *endIdx + syncCacheCnt_;
}

void StaggeredFillAlgorithm::FillPrev(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index)
{
    auto& section = GetSection(index);
    if (section.Contains(index)) {
        return;
    }

    if (index == section.maxItem) {
        GetSection(index + 1).PreparePrevSection(axis, section);
    }
    SectionStartFiller filler(section);
    filler.Fill(measurer_, node, index, 0.0f);
}

void StaggeredFillAlgorithm::FillNext(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index)
{
    auto& section = GetSection(index);
    if (section.Contains(index)) {
        return;
    }
    if (index == section.minItem) {
        GetSection(index - 1).PrepareNextSection(axis, section);
    }
    SectionEndFiller filler(section, viewport.MainSize(axis));
    filler.Fill(measurer_, node, index, viewport.MainSize(axis));
}

void StaggeredFillAlgorithm::FillMarkItem(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index)
{
    auto& section = GetSection(index);
    if (!section.Contains(index)) {
        if (!section.IsEmpty()) {
            LOGW("data is corrupted, section is %s when inserting mark item %d", section.ToString().c_str(), index);
        }
        auto filler = SectionEndFiller(section, viewport.MainSize(axis));
        filler.Fill(measurer_, node, index, viewport.MainSize(axis));
    }
}

void StaggeredFillAlgorithm::InitSections(int32_t totalCnt, Axis axis, const SizeF& frameSize)
{
    auto newSections = SectionInitializer::InitSections(props_, frameSize, axis, totalCnt);
    if (!SectionInitializer::Compare(sections_, newSections)) {
        sections_ = newSections;
    }
}

Section& StaggeredFillAlgorithm::GetSection(int32_t item)
{
    for (auto& section : sections_) {
        if (section.minItem <= item && section.maxItem >= item) {
            return section;
        }
    }
    LOGW("returning empty section for %{public}d", item);
    static Section emptySection;
    return emptySection;
}

void StaggeredFillAlgorithm::OnSlidingOffsetUpdate(float delta)
{
    if (StartIdx().value_or(0) == 0 && !sections_.empty()) {
        delta = std::min(delta, -sections_.begin()->StartPos()); // no overScroll in FillAlgorithm
    }
    std::for_each(sections_.begin(), sections_.end(), [delta](Section& section) {
        for (auto& lane : section.lanes) {
            lane.startPos += delta;
            lane.endPos += delta;
        }
    });
}

int32_t StaggeredFillAlgorithm::GetMarkIndex()
{
    for (auto& section : sections_) {
        section.PruneFront(0.0f);
    }
    return StartIdx().value_or(-1);
}

void StaggeredFillAlgorithm::UpdateSyncCachedCnt()
{
    if (InstanceOf<SwiperLayoutProperty>(props_)) {
        // SwiperLayout always measures 1 extra item in the opposite direction. set syncCache to 1 to adapt
        syncCacheCnt_ = 1;
    }
}
} // namespace OHOS::Ace::NG
