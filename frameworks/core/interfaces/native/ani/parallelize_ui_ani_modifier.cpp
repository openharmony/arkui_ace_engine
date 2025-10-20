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

#include "parallelize_ui_ani_modifier.h"
#include "base/log/log.h"
#include "core/components_ng/syntax/arkoala_parallelize_ui_adapter_node.h"

namespace OHOS::Ace::NG {

ani_long ConstructAdapterNode(ani_int id)
{
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(id);
    CHECK_NULL_RETURN(node, 0);
    node->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(node));
}

void Reset(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<ParallelizeUIAdapterNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->Reset();
}

void RegisterCallback(ArkUINodeHandle node, std::function<int32_t()>&& getCount,
    std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>&& registerCallback)
{
    auto frameNode = reinterpret_cast<ParallelizeUIAdapterNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->RegisterCallback(std::move(getCount), std::move(registerCallback));
}

const ArkUIAniParallelizeUIModifier* GetParallelizeUIAniModifier()
{
    static const ArkUIAniParallelizeUIModifier impl = {
        .constructAdapterNode = ConstructAdapterNode,
        .reset = Reset,
        .registerCallback = RegisterCallback,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG