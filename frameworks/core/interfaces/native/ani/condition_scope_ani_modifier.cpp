/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "condition_scope_ani_modifier.h"

#include "core/components_ng/syntax/arkoala_condition_scope.h"
#include "base/log/log.h"

#include <memory>

namespace OHOS::Ace::NG {

ani_long ConstructConditionScope(ani_int id)
{
    auto node = AceType::MakeRefPtr<ConditionScopeNode>(id);
    node->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(node));
}

void MarkDirty(ani_long ptr)
{
    auto* node = reinterpret_cast<NG::ConditionScopeNode*>(ptr);
    CHECK_NULL_VOID(node);
    node->FlushUpdateAndMarkDirty();
}

const ArkUIAniConditionScopeModifier* GetConditionScopeAniModifier()
{
    static const ArkUIAniConditionScopeModifier impl = {
        .constructConditionScope = ConstructConditionScope,
        .markDirty = MarkDirty
    };
    return &impl;
}

} // namespace OHOS::Ace::NG