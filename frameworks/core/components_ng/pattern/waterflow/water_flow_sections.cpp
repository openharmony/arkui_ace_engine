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
    auto it = sections_.begin() + start;
    sections_.erase(it, it + deleteCount);
    sections_.insert(it, newSections.begin(), newSections.end());

    if (onSectionDataChange_) {
        // push: start, 0, newSection
        // update: start, 0, newSection
        // splice: start, deleteCount, newSections
        onSectionDataChange_(start, deleteCount, newSections);
    }
}
} // namespace OHOS::Ace::NG
