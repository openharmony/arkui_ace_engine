/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_SYNTAX_NODE_ANI_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_SYNTAX_NODE_ANI_MODIFIER_H

#include "core/interfaces/ani/ani_api.h"
#include "core/components_ng/syntax/arkoala_syntax_node.h"

namespace OHOS::Ace::NG {

ani_long ConstructSyntaxNode(ani_int id)
{
    auto node = AceType::MakeRefPtr<ArkoalaSyntaxNode>(id);
    CHECK_NULL_RETURN(node, 0);
    node->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(node));
}

const ArkUIAniSyntaxNodeModifier* GetSyntaxNodeAniModifier()
{
    static const ArkUIAniSyntaxNodeModifier impl = { .constructSyntaxNode = ConstructSyntaxNode };
    return &impl;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_SYNTAX_NODE_ANI_MODIFIER_H
