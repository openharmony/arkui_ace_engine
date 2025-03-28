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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_PATTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_PATTER_H

#include <optional>

#include "base/log/dump_log.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/grid_row/grid_row_event_hub.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_algorithm.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class GridRowLayoutPattern : public Pattern {
    DECLARE_ACE_TYPE(GridRowLayoutPattern, Pattern);

public:
    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<GridRowLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<GridRowLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<GridRowEventHub>();
    }

    void OnAttachToFrameNode() override;

    void OnDetachFromFrameNode(FrameNode* node) override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return { false, true, ScopeType::OTHERS };
    }

    void DumpInfo() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = DynamicCast<GridRowLayoutProperty>(host->GetLayoutProperty());
        CHECK_NULL_VOID(layoutProperty);
        auto columns = layoutProperty->GetColumns();
        if (columns.has_value()) {
            DumpLog::GetInstance().AddDesc(std::string("columns: ").append(columns.value().ToString().c_str()));
        }
        auto gutter = layoutProperty->GetGutter();
        if (gutter.has_value()) {
            DumpLog::GetInstance().AddDesc(std::string("gutter: ").append(gutter.value().ToString().c_str()));
        }
        auto breakPoints = layoutProperty->GetBreakPoints();
        if (breakPoints.has_value()) {
            DumpLog::GetInstance().AddDesc(std::string("breakPoints: ").append(breakPoints.value().ToString().c_str()));
        }
        auto direction = layoutProperty->GetDirection();
        if (direction.has_value()) {
            DumpLog::GetInstance().AddDesc(
                std::string("direction: ").append(std::to_string(static_cast<int32_t>(direction.value())).c_str()));
        }
        auto sizeType = layoutProperty->GetSizeType();
        if (sizeType.has_value()) {
            DumpLog::GetInstance().AddDesc(
                std::string("sizeType: ").append(std::to_string(static_cast<int32_t>(sizeType.value())).c_str()));
        }
        auto alignItems = layoutProperty->GetAlignItems();
        if (alignItems.has_value()) {
            DumpLog::GetInstance().AddDesc(
                std::string("alignItems: ").append(std::to_string(static_cast<int32_t>(alignItems.value())).c_str()));
        }
    }

private:
    std::optional<int32_t> callbackId_;

    void MarkDirty();
};
} // namespace OHOS::Ace::NG

#endif