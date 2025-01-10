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

#include "staggered_section_filler.h"

#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "frameworks/core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
bool StaggeredFillAlgorithm::CanFillMoreAtStart(Axis axis)
{
    int32_t item = -1;
    for (const auto& section : sections_) {
        if (!section.lanes.empty()) {
            item = section.StartIdx();
            break;
        }
    }
    if (item == 0) {
        return false;
    }
    auto& section = GetSection(item);
    if (item == section.minItem) {
        section.PreparePrevSection(axis, GetSection(item - 1));
        section = GetSection(item - 1);
    }
    SectionStartFiller filler(section);
    return filler.CanFill();
}
bool StaggeredFillAlgorithm::CanFillMoreAtEnd(float viewportBound, Axis axis)
{
    int32_t item = -1;
    for (auto it = sections_.rbegin(); it != sections_.rend(); ++it) {
        if (!it->lanes.empty()) {
            item = it->EndIdx();
            break;
        }
    }
    auto& section = GetSection(item);
    if (item == section.maxItem) {
        section.PrepareNextSection(axis, GetSection(item + 1));
        section = GetSection(item + 1);
    }
    SectionEndFiller filler(section, viewportBound);
    return filler.CanFill();
}
void StaggeredFillAlgorithm::PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt)
{
    InitSections();

    if (InstanceOf<WaterFlowLayoutProperty>(props_)) {
        measurer_ =
            MakeRefPtr<FlowItemMeasurer>([this](int32_t index) { return GetSection(index).userDefMainLen(index); },
                axis, viewport.MainSize(axis), DynamicCast<WaterFlowLayoutProperty>(props_));
    }
}
bool StaggeredFillAlgorithm::CanFillMore(
    Axis axis, const SizeF& scrollWindowSize, const RectF& markItemRect, FillDirection direction)
{
    return direction == FillDirection::END ? CanFillMoreAtEnd(scrollWindowSize.MainSize(axis), axis)
                                           : CanFillMoreAtStart(axis);
}
RectF StaggeredFillAlgorithm::CalcItemRectBeforeMarkItem(
    const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const RectF& markItem)
{
    auto& section = GetSection(index);
    if (section.StartIdx() <= index || section.EndIdx() >= index) {
        return {};
    }

    if (index == section.maxItem) {
        GetSection(index + 1).PreparePrevSection(axis, section);
    }
    SectionStartFiller filler(section);
    filler.Fill(measurer_, node, index, viewport.MainSize(axis));
    return {};
}
RectF StaggeredFillAlgorithm::CalcItemRectAfterMarkItem(
    const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const RectF& markItem)
{
    auto& section = GetSection(index);
    if (!section.Contains(index)) {
        return {};
    }
    if (index == section.minItem) {
        GetSection(index - 1).PrepareNextSection(axis, section);
    }
    SectionEndFiller filler(section, viewport.MainSize(axis));
    filler.Fill(measurer_, node, index, viewport.MainSize(axis));
    return {};
}
RectF StaggeredFillAlgorithm::CalcMarkItemRect(
    const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const std::optional<OffsetF>& slidingOffset)
{
    auto& section = GetSection(index);
    if (!section.Contains(index)) {
        if (index != 0) {
            LOGW("non-init mark item not recorded previously %{public}d", index);
        }
        // check section endPos
        auto filler = SectionEndFiller(section, viewport.MainSize(axis));
        filler.Fill(measurer_, node, index, viewport.MainSize(axis));
    }

    if (slidingOffset) {
        float delta = slidingOffset->GetMainOffset(axis);
        for (auto& lane : section.lanes) {
            lane.startPos += delta;
            lane.endPos += delta;
        }
    }
    return {};
}
void StaggeredFillAlgorithm::InitSections()
{
    // factory method
    if (InstanceOf<WaterFlowLayoutProperty>(props_)) {
        auto newSections = WaterFlowSectionInitializer::Initialize(
            props_->GetHost()->GetPattern<WaterFlowPattern>()->GetSections()->GetSectionInfo(),
            DynamicCast<WaterFlowLayoutProperty>(props_));
        if (WaterFlowSectionInitializer::Compare(sections_, newSections)) {
            sections_ = newSections;
        }
    }
}
Section& StaggeredFillAlgorithm::GetSection(int32_t item)
{
    for (auto& section : sections_) {
        if (section.minItem <= item && section.maxItem >= item) {
            return section;
        }
    }
    static Section emptySection;
    return emptySection;
}
} // namespace OHOS::Ace::NG
