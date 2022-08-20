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
#include "base/utils/string_utils.h"
#include "core/common/window.h"
#include "core/components_v2/common/common_def.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/components_v2/grid_layout/grid_row_element.h"
#include "core/components_v2/grid_layout/render_grid_row.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace::V2 {

using ColumnInfo = GridContainerSize;

class ACE_EXPORT GridRowComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(GridRowComponent, ComponentGroup);

public:
    const RefPtr<ColumnInfo>& GetTotalCol() const
    {
        return totalCol_;
    }

    void SetTotalCol(const RefPtr<ColumnInfo>& cols)
    {
        totalCol_ = cols;
    }

    const RefPtr<BreakPoints>& GetBreakPoints() const
    {
        return breakPoints_;
    }

    void SetBreakPoints(const RefPtr<BreakPoints>& breakpoints)
    {
        breakPoints_ = breakpoints;
    }

    const RefPtr<Gutter>& GetGutter() const
    {
        return gutter_;
    }

    void SetGutter(const RefPtr<Gutter>& gutter)
    {
        gutter_ = gutter;
    }

    void SetHasContainerHeight(bool hasContainerHeight)
    {
        hasContainerHeight_ = hasContainerHeight;
    }

    bool HasContainerHeight()
    {
        return hasContainerHeight_;
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

    ACE_DEFINE_COMPONENT_EVENT(breakPointChange, void(std::string));

    void FirebreakPointEvent(const std::string& sizeType)
    {
        if (eventbreakPointChange_) {
            (*eventbreakPointChange_)(sizeType);
        }
    }

private:
    RefPtr<ColumnInfo> totalCol_ = AceType::MakeRefPtr<ColumnInfo>();
    RefPtr<BreakPoints> breakPoints_ = AceType::MakeRefPtr<BreakPoints>();
    RefPtr<Gutter> gutter_ = AceType::MakeRefPtr<Gutter>();
    GridRowDirection direction_ = GridRowDirection::Row;
    bool hasContainerHeight_ = false;
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRIDROW_H
