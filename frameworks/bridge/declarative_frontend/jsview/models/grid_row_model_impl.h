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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_ROW_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_ROW_MODEL_IMPL_H

#include "core/components_ng/pattern/grid_row/grid_row_model.h"

namespace OHOS::Ace::Framework {
class GridRowModelImpl : public GridRowModel {
public:
    void Create() override;
    void Create(const RefPtr<V2::GridContainerSize>& col, const RefPtr<V2::Gutter>& gutter,
        const RefPtr<V2::BreakPoints>& breakpoints, V2::GridRowDirection direction) override;
    void SetOnBreakPointChange(std::function<void(const std::string)>&& onChange) override;
    void SetHeight() override;
    void SetAlignItems(FlexAlign alignItem) override {};
};
} // namespace OHOS::Ace::Framework

#endif