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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_ITEM_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_ITEM_MODEL_IMPL_H

#include "core/components_ng/pattern/grid/grid_item_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace::Framework {

class GridItemModelImpl : public OHOS::Ace::GridItemModel {
public:
    void Create(NG::GridItemStyle gridItemStyle) override;
    void Create(std::function<void(int32_t)>&& deepRenderFunc, bool isLazy, NG::GridItemStyle gridItemStyle) override;
    void SetRowStart(int32_t value) override;
    void SetRowEnd(int32_t value) override;
    void SetColumnStart(int32_t value) override;
    void SetColumnEnd(int32_t value) override;
    void SetForceRebuild(bool value) override;
    void SetSelectable(bool value) override;
    void SetSelected(bool selected) override {};
    void SetSelectChangeEvent(std::function<void(bool)>&& changeEvent) override {};
    void SetOnSelect(std::function<void(bool)>&& onSelect) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_ITEM_MODEL_IMPL_H
