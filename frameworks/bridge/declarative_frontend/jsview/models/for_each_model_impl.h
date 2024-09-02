/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_FOREACH_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_FOREACH_MODEL_IMPL_H


#include "core/components_ng/syntax/for_each_model.h"


namespace OHOS::Ace::Framework {

class ACE_EXPORT ForEachModelImpl : public ForEachModel {
public:
    virtual ~ForEachModelImpl() override = default;

    void Pop() override;

    // full update / classic code path
    void Create(const std::string& compilerGenId, const OHOS::Ace::ForEachFunc& ForEachFunc) override;
   
    // only supported by NG, unimplemented here
    void Create() override;
    std::list<std::string> GetCurrentIdList(int32_t nodeId) override;
    void SetNewIds(std::list<std::string>&& newIds) override;
    void CreateNewChildStart(const std::string& id) override;
    void CreateNewChildFinish(const std::string& id) override;
    void OnMove(std::function<void(int32_t, int32_t)>&& onMove) override {};
    void SetRemovedElmtIds(std::list<int32_t>& removedElmtId) override {};
};
}  // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_FOREACH_MODEL_IMPL_H
