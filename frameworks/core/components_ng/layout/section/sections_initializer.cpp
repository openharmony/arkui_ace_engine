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
#include "sections_initializer.h"
namespace OHOS::Ace::NG {
std::vector<Section> WaterFlowSectionInitializer::Initialize(
    const std::vector<WaterFlowSections::Section>& sections, const RefPtr<WaterFlowLayoutProperty>& props)
{
    std::vector<Section> res(sections.size());
    int32_t itemIdx = 0;
    for (size_t i = 0; i < sections.size(); ++i) {
        res[i].lanes = std::vector<Lane>(sections[i].crossCount.value_or(1));

        res[i].minItem = itemIdx;
        itemIdx += sections[i].itemsCount;
        res[i].maxItem = itemIdx - 1;

        if (sections[i].rowsGap) {
            res[i].mainGap = sections[i].rowsGap->ConvertToPx();
        }
        if (sections[i].columnsGap) {
            res[i].crossGap = sections[i].columnsGap->ConvertToPx();
        }
        if (sections[i].margin) {
            const auto& constraint = props->GetLayoutConstraint().value_or(LayoutConstraintF {});
            res[i].margin = ConvertToMarginPropertyF(
                *sections[i].margin, constraint.scaleProperty, constraint.percentReference.Width());
        }
        res[i].userDefMainLen = sections[i].onGetItemMainSizeByIndex;
    }
    return res;
}

bool WaterFlowSectionInitializer::Compare(const std::vector<Section>& prev, const std::vector<Section>& cur)
{
    if (prev.size() != cur.size()) {
        return false;
    }
    for (size_t i = 0; i < prev.size(); ++i) {
        if (prev[i].lanes.size() == cur[i].lanes.size() && prev[i].mainGap == cur[i].mainGap &&
            prev[i].crossGap == cur[i].crossGap && prev[i].margin == cur[i].margin &&
            prev[i].minItem == cur[i].minItem && prev[i].maxItem == cur[i].maxItem) {
            continue;
        }
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::NG