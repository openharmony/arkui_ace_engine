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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRIDROW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRIDROW_H

#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/common/window.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/components_v2/grid_layout/grid_row_element.h"
#include "core/components_v2/grid_layout/render_grid_row.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace::V2 {

using ColumnInfo = GridContainerSize;

class ACE_EXPORT GridRowComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(GridRowComponent, ComponentGroup);

public:
    RefPtr<ColumnInfo> GetTotalCol() const
    {
        return totalCol_;
    }

    void SetTotalCol(const RefPtr<ColumnInfo>& cols)
    {
        totalCol_ = cols;
    }

    RefPtr<BreakPoints> GetBreakPoints() const
    {
        return breakPoints_;
    }

    void SetBreakPoints(const RefPtr<BreakPoints>& breakpoints)
    {
        breakPoints_ = breakpoints;
    }

    RefPtr<Getter> GetGetter() const
    {
        return getter_;
    }

    void SetGetter(const RefPtr<Getter>& getter)
    {
        getter_ = getter;
    }

    RefPtr<Element> CreateElement() override;

    RefPtr<RenderNode> CreateRenderNode() override;

    void SetDirection(const GridRowDirection direction)
    {
        direction_ = direction;
    }

    GridRowDirection GetDirection() const
    {
        return direction_;
    }

private:
    RefPtr<ColumnInfo> totalCol_ = AceType::MakeRefPtr<ColumnInfo>();
    RefPtr<BreakPoints> breakPoints_ = AceType::MakeRefPtr<BreakPoints>();
    RefPtr<Getter> getter_ = AceType::MakeRefPtr<Getter>();
    GridRowDirection direction_ = GridRowDirection::Row;
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRIDROW_H
