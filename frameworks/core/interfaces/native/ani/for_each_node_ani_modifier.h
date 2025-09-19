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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_FOR_EACH_NODE_ANI_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_FOR_EACH_NODE_ANI_MODIFIER_H

#include "core/interfaces/ani/ani_api.h"
#include "core/components_ng/syntax/arkoala_for_each_node.h"

namespace OHOS::Ace::NG {

ani_long Construct(ani_int id, ani_boolean isRepeat)
{
    auto node = AceType::MakeRefPtr<ArkoalaForEachNode>(id, isRepeat);
    CHECK_NULL_RETURN(node, 0);
    node->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(node));
}

void FinishRender(ani_long node)
{
    auto* forEachNode = reinterpret_cast<NG::ArkoalaForEachNode*>(node);
    CHECK_NULL_VOID(forEachNode);
    forEachNode->FinishRender();
}

const ArkUIAniForEachNodeModifier* GetForEachNodeAniModifier()
{
    static const ArkUIAniForEachNodeModifier impl = {
        .construct = Construct,
        .finishRender = FinishRender
    };
    return &impl;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_FOR_EACH_NODE_ANI_MODIFIER_H
