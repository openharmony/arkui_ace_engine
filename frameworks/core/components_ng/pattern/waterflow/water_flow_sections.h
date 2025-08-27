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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_SECTIONS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_SECTIONS_H

#include <cstdint>
#include <functional>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
using GetItemMainSizeByIndex = std::function<float(int32_t)>;

class ACE_FORCE_EXPORT WaterFlowSections : public virtual AceType {
    DECLARE_ACE_TYPE(WaterFlowSections, AceType);
public:
    struct Section {
        bool operator==(const Section& other) const
        {
            return itemsCount == other.itemsCount && crossCount == other.crossCount && columnsGap == other.columnsGap &&
                   rowsGap == other.rowsGap && margin == other.margin;
        }
        bool operator!=(const Section& other) const
        {
            return !(*this == other);
        }

        bool OnlyCountDiff(const Section& other) const
        {
            return crossCount == other.crossCount && columnsGap == other.columnsGap && rowsGap == other.rowsGap &&
                   margin == other.margin;
        }

        int32_t itemsCount = 0;
        std::optional<int32_t> crossCount;
        GetItemMainSizeByIndex onGetItemMainSizeByIndex;
        std::optional<Dimension> columnsGap;
        std::optional<Dimension> rowsGap;
        std::optional<MarginProperty> margin;
    };

    WaterFlowSections() = default;
    ~WaterFlowSections() override = default;
    void SetOnDataChange(std::function<void(int32_t start)>&& func)
    {
        onSectionDataChange_ = func;
    }

    void NotifySectionChange(
        int32_t start, int32_t deleteCount, const std::vector<WaterFlowSections::Section>& newSections);

    void SetNotifySectionChange(std::function<void(int32_t start)>&& func)
    {
        notifySectionChange_ = func;
    }

    /**
     * @brief Change section data.
     *
     * @param start index of the first modified section.
     * @param deleteCount number of sections to delete at index [start].
     * @param newSections to insert at index [start].
     */
    void ChangeData(size_t start, size_t deleteCount, const std::vector<Section>& newSections);

    // replace all sections from start
    void ReplaceFrom(size_t start, const std::vector<Section>& newSections);

    const std::vector<Section>& GetSectionInfo() const
    {
        return sections_;
    }

    const std::vector<Section>& GetPrevSectionInfo() const
    {
        return prevSections_;
    }

private:
    std::vector<Section> sections_;
    // for comparing and handling special case
    std::vector<Section> prevSections_;
    std::function<void(int32_t start)> onSectionDataChange_;
    std::function<void(int32_t start)> notifySectionChange_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_SECTIONS_H
