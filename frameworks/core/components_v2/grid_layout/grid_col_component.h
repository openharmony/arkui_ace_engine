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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRIDCOL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRIDCOL_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_v2/grid_layout/grid_col_element.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/components_v2/grid_layout/render_grid_col.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace::V2 {

class GridColComponent : public SoleChildComponent {
    void SetSpan(const RefPtr<GridContainerSize>& span)
    {
        span_ = span;
    }

    void SetOffset(const RefPtr<GridContainerSize>& offset)
    {
        offset_ = offset;
    }

    void SetOrder(const RefPtr<GridContainerSize>& order)
    {
        order_ = order;
    }

    RefPtr<GridContainerSize> GetSpan() const
    {
        return span_;
    }

    RefPtr<GridContainerSize> GetOffset() const
    {
        return offset_;
    }

    RefPtr<GridContainerSize> GetOrder() const
    {
        return order_;
    }

    RefPtr<Element> CreateElement()
    {
        return AceType::MakeRefPtr<GridColElement>();
    }

    RefPtr<RenderNode> CreateRenderNode()
    {
        return RenderGridCol::Create();
    }

private:
    RefPtr<GridContainerSize> span_;
    RefPtr<GridContainerSize> offset_;
    RefPtr<GridContainerSize> order_;
};

} // namespace OHOS::Ace::V2
#endif