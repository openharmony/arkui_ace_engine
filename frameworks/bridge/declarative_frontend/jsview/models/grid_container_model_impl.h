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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_CONTAINER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_CONTAINER_MODEL_IMPL_H

#include "core/components_ng/pattern/grid_container/grid_container_model.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT GridContainerModelImpl : public GridContainerModel {
public:
    void Create(const RefPtr<GridContainerInfo>& containerInfo) override;

    void Pop() override;

    static RefPtr<GridContainerInfo> GetContainer()
    {
        return gridContainerStack_.empty() ? nullptr : gridContainerStack_.back();
    }

private:
    /*
     * GridContainer layout info is stored in box component in non-declarative_fronted bridge instead of
     * creating a new component.
     * Using thread_local stack is a compromise for compatibility, as child node cannot get info from its ancestors.
     * In NG framework, layout info is stored in a frameNode and this stack is obsoleted.
     */
    static thread_local std::vector<RefPtr<GridContainerInfo>> gridContainerStack_;
};

} // namespace OHOS::Ace::Framework

#endif