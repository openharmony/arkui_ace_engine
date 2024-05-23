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

#include "frameworks/core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::NG {
void WaterFlowSections::ChangeData(
    int32_t start, int32_t deleteCount, const std::vector<WaterFlowSections::Section>& newSections)
{
    if (deleteCount == 1 && newSections.size() == 1) {
        // prepare for checking special case
        prevSection_ = {sections_[start], start};
    } else {
        prevSection_ = std::nullopt;
    }

    TAG_LOGI(AceLogTag::ACE_WATERFLOW,
        "section changed, start:%{public}d, deleteCount:%{public}d, newSections:%{public}zu", start, deleteCount,
        newSections.size());
    if (static_cast<size_t>(start) < sections_.size()) {
        auto it = sections_.begin() + start;
        sections_.erase(it, it + deleteCount);
        sections_.insert(it, newSections.begin(), newSections.end());
    } else {
        sections_.insert(sections_.end(), newSections.begin(), newSections.end());
    }

    if (onSectionDataChange_) {
        // push: start, 0, newSection
        // update: start, 0, newSection
        // splice: start, deleteCount, newSections
        onSectionDataChange_(start);
    }
}

// for c-api, replace all
void WaterFlowSections::ChangeDataNow(
    int32_t start, int32_t deleteCount, const std::vector<WaterFlowSections::Section>& newSections)
{
    prevSections_ = sections_;

    TAG_LOGI(AceLogTag::ACE_WATERFLOW,
        "section changed, start:%{public}d, deleteCount:%{public}d, newSections:%{public}zu", start, deleteCount,
        newSections.size());
    if (static_cast<size_t>(start) < sections_.size()) {
        auto it = sections_.begin() + start;
        auto oldSize = sections_.size();
        auto eraseCount = std::min(deleteCount, static_cast<int32_t>(oldSize) - start);
        sections_.erase(it, it + eraseCount);
        sections_.insert(sections_.begin() + start, newSections.begin(), newSections.end());
    } else {
        sections_.insert(sections_.end(), newSections.begin(), newSections.end());
    }

    if (onSectionDataChangeNow_) {
        // push: start, 0, newSection
        // update: start, 0, newSection
        // splice: start, deleteCount, newSections
        onSectionDataChangeNow_(start);
    }
}

bool WaterFlowSections::IsSpecialUpdate() const
{
    if (sections_.empty() || !prevSection_) {
        return false;
    }
    const int32_t start = prevSection_->second;
    if (start >= static_cast<int32_t>(sections_.size())) {
        return false;
    }
    const auto& cur = sections_[start];
    const auto& prev = prevSection_->first;
    return cur.itemsCount != prev.itemsCount && cur.crossCount == prev.crossCount &&
           cur.columnsGap == prev.columnsGap && cur.rowsGap == prev.rowsGap && cur.margin == prev.margin;
}

bool WaterFlowSections::IsSpecialUpdateCAPI(int32_t updateIndex) const
{
    if (sections_.empty()) {
        return false;
    }
    if (prevSections_.size() != sections_.size()) {
        return false;
    }
    for (size_t i = 0; i < sections_.size(); ++i) {
        if (!sections_[i].OnlyCountChange(prevSections_[i])) {
            return false;
        }
    }
    return true;
}
} // namespace OHOS::Ace::NG
