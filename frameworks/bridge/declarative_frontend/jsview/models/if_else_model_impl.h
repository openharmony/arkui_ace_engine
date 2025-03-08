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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_MODEL_IF_ELSE_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_MODEL_IF_ELSE_IMPL_H

#include "core/components_ng/syntax/if_else_model.h"

namespace OHOS::Ace::Framework {

class IfElseModelImpl : public IfElseModel {
public:
    ~IfElseModelImpl() override = default;
    void Create() override;
    void Pop() override;
    void SetBranchId(int32_t value, std::list<int32_t>& removedElmtId, std::list<int32_t>& reservedElmtId) override;
    int32_t GetBranchId() override;
    bool CanRetake(const std::string& id) override
    {
        return false;
    }
    bool GetRetakenElmtIds(std::list<int32_t>& elmtIds) override
    {
        return false;
    }
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_MODEL_IF_ELSE_IMPL_H
