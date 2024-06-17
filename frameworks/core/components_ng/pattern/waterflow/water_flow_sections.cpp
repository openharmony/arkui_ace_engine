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
// push: start, 0, newSection
// update: start, 0, newSection
// splice: start, deleteCount, newSections
void WaterFlowSections::ChangeData(
    size_t start, size_t deleteCount, const std::vector<WaterFlowSections::Section>& newSections)
{
    start = std::min(start, sections_.size());
    deleteCount = std::min(deleteCount, sections_.size() - start);
    prevSections_ = sections_;

    TAG_LOGI(AceLogTag::ACE_WATERFLOW,
        "section changed, start:%{public}zu, deleteCount:%{public}zu, newSections:%{public}zu", start, deleteCount,
        newSections.size());
    if (start < sections_.size()) {
        auto it = sections_.begin() + static_cast<int32_t>(start);
        sections_.erase(it, it + static_cast<int32_t>(deleteCount));
        sections_.insert(it, newSections.begin(), newSections.end());
    } else {
        sections_.insert(sections_.end(), newSections.begin(), newSections.end());
    }

    // perform diff to get actual [start]
    for (; start < sections_.size(); ++start) {
        if (start >= prevSections_.size()) {
            break;
        }
        if (sections_[start] != prevSections_[start]) {
            // can skip re-init the first modified section with only an itemCount diff
            // to optimize the common scenario when developers add/remove items at the end
            if (sections_[start].OnlyCountDiff(prevSections_[start])) {
                ++start;
            }
            break;
        }
    }
    prevSections_.clear();

    if (onSectionDataChange_) {
        onSectionDataChange_(static_cast<int32_t>(start));
    }
}

// for c-api, replace all from start
void WaterFlowSections::ChangeDataCAPI(size_t start, const std::vector<WaterFlowSections::Section>& newSections)
{
    ChangeData(start, sections_.size(), newSections);
}
} // namespace OHOS::Ace::NG
