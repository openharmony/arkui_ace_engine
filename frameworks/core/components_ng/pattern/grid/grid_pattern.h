/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/grid/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridPattern : public Pattern {
    DECLARE_ACE_TYPE(GridPattern, Pattern);

public:
    GridPattern() = default;
    ~GridPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<GridLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
        CHECK_NULL_RETURN(gridLayoutProperty, nullptr);
        std::vector<std::string> cols;
        StringUtils::StringSplitter(gridLayoutProperty->GetColumnsTemplate().value_or(""), ' ', cols);
        std::vector<std::string> rows;
        StringUtils::StringSplitter(gridLayoutProperty->GetRowsTemplate().value_or(""), ' ', rows);
        auto crossCount = cols.empty() ? Infinity<uint32_t>() : cols.size();
        auto mainCount = rows.empty() ? Infinity<uint32_t>() : rows.size();
        if (!gridLayoutProperty->IsVertical()) {
            std::swap(crossCount, mainCount);
        }
        return MakeRefPtr<GridLayoutAlgorithm>(gridLayoutInfo_, crossCount, mainCount);
    }

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void AddScrollEvent();
    bool UpdateScrollPosition(float offset, int32_t source);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

    GridLayoutInfo gridLayoutInfo_;
    RefPtr<ScrollableEvent> scrollableEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(GridPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H
