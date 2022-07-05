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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_RENDER_GRID_COL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_RENDER_GRID_COL_H

#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {

class RenderGridCol : public RenderNode {
    DECLARE_ACE_TYPE(RenderGridCol, RenderNode);

public:
    ~RenderGridCol() override = default;

    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void SetSizeType(GridSizeType sizeType)
    {
        sizeType_ = sizeType;
    }
    GridSizeType GetSizeType() const
    {
        return sizeType_;
    }

    int32_t GetSpan(GridSizeType sizeType) const;
    int32_t GetOffset(GridSizeType sizeType) const;

    int32_t GetOrder(GridSizeType sizeType) const;

private:
    RefPtr<Component> component_;
    GridSizeType sizeType_ = GridSizeType::XS;
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_RENDER_GRID_COL_H