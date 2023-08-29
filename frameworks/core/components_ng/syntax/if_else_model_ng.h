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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_IF_ELSE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_IF_ELSE_MODEL_NG_H

#include <cstdint>

#include "base/utils/macros.h"
#include "core/components_ng/syntax/if_else_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT IfElseModelNG : public OHOS::Ace::IfElseModel {
public:
    ~IfElseModelNG() override = default;
    void Create() override;
    void Pop() override;
    void SetBranchId(int32_t value, std::list<int32_t>& removedElmtId) override;
    int32_t GetBranchId() override;
    bool CanRetake(const std::string& id) override;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_IF_ELSE_MODEL_NG_H
