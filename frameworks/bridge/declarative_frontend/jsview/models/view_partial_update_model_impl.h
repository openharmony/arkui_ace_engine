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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_PARTIAL_UPDATE_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_PARTIAL_UPDATE_MODEL_IMPL_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_partial_update_model.h"
#include "core/pipeline/base/component.h"

namespace OHOS::Ace::Framework {

class ViewPartialUpdateModelImpl : public ViewPartialUpdateModel {
public:
    RefPtr<AceType> CreateNode(NodeInfoPU&& info) override;
    bool MarkNeedUpdate(const WeakPtr<AceType>& node) override;
    void FlushUpdateTask(const UpdateTask& task) override;
    void FinishUpdate(const WeakPtr<AceType>& viewNode, int32_t id,
        std::function<void(const UpdateTask&)>&& emplaceTaskFunc) override;
    bool AllowReusableV2Descendant(const WeakPtr<AceType>& viewNode) override
    {
        /* not used here */
        return false;
    }
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_PARTIAL_UPDATE_MODEL_IMPL_H
