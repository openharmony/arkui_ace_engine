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

#include <stdint.h>
#include "grid_col_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {

class RenderGridCol : public RenderNode {
    DECLARE_ACE_TYPE(RenderGridCol, RenderNode);

public:

    ~RenderGridCol() override = default;

    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;

    int32_t GetSpan() const
    {
        if (component_) {
            LOGI("child component error return span 1");
            return 1;
        }
        return component_->GetSpan() < 1 ? 1 : component_->GetSpan();
    }

    int32_t GetOffset() const
    {
        if (component_) {
            LOGI("child component error return offset 0");
            return 0;
        }
        return component_->GetOffset();
    }

    int32_t GetOrder() const
    {
        if (component_) {
            LOGI("child component error return order 0");
            return 0;
        }
        return component_->GetOrder();
    }

private:
    RefPtr<GridColComponent> component_;

};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_RENDER_GRID_COL_H