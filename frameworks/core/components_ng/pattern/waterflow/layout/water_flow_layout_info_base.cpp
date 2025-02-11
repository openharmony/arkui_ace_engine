/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_info_base.h"

#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
namespace OHOS::Ace::NG {
RefPtr<WaterFlowLayoutInfoBase> WaterFlowLayoutInfoBase::Create(WaterFlowLayoutMode mode)
{
    switch (mode) {
        case WaterFlowLayoutMode::SLIDING_WINDOW:
            return MakeRefPtr<WaterFlowLayoutInfoSW>();
        default:
            return MakeRefPtr<WaterFlowLayoutInfo>();
    }
}

int32_t WaterFlowLayoutInfoBase::GetSegment(int32_t itemIdx) const
{
    if (segmentTails_.empty() || itemIdx < 0) {
        return 0;
    }
    auto cache = segmentCache_.find(itemIdx);
    if (cache != segmentCache_.end()) {
        return cache->second;
    }

    auto it = std::lower_bound(segmentTails_.begin(), segmentTails_.end(), itemIdx);
    if (it == segmentTails_.end()) {
        return static_cast<int32_t>(segmentTails_.size()) - 1;
    }
    int32_t idx = it - segmentTails_.begin();
    segmentCache_[itemIdx] = idx;
    return idx;
}

void WaterFlowLayoutInfoBase::InitMargins(
    const std::vector<WaterFlowSections::Section>& sections, const ScaleProperty& scale, float percentWidth)
{
    size_t n = sections.size();
    if (n == 0) {
        return;
    }
    margins_.resize(n);
    for (size_t i = 0; i < n; ++i) {
        if (sections[i].margin) {
            margins_[i] = ConvertToMarginPropertyF(*sections[i].margin, scale, percentWidth);
        }
    }
}

void WaterFlowLayoutInfoBase::UpdateDefaultCachedCount()
{
    thread_local float pageCount = SystemProperties::GetPageCount();
    if (pageCount <= 0.0f) {
        return;
    }
    int32_t itemCount = endIndex_ - startIndex_ + 1;
    if (itemCount <= 0) {
        return;
    }
    constexpr int32_t MAX_DEFAULT_CACHED_COUNT = 16;
    int32_t newCachedCount = static_cast<int32_t>(ceil(pageCount * itemCount));
    if (newCachedCount > MAX_DEFAULT_CACHED_COUNT) {
        TAG_LOGI(AceLogTag::ACE_WATERFLOW, "Default cachedCount exceed 16");
        defCachedCount_ = MAX_DEFAULT_CACHED_COUNT;
    } else {
        defCachedCount_ = std::max(newCachedCount, defCachedCount_);
    }
}
} // namespace OHOS::Ace::NG
