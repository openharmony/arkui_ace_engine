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

#include "detached_free_root_ani_modifier.h"

#include <memory>

#include "base/log/log.h"
#include "core/components_ng/syntax/static/detached_free_root_node.h"

namespace OHOS::Ace::NG {

ani_long ConstructDetachedFreeRoot(ani_int id)
{
    auto node = AceType::MakeRefPtr<DetachedFreeRootNode>(id);
    node->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(node));
}

const ArkUIAniDetachedFreeRootModifier* GetDetachedFreeRootModifier()
{
    static const ArkUIAniDetachedFreeRootModifier impl = { .constructDetachedFreeRoot = ConstructDetachedFreeRoot };
    return &impl;
}
} // namespace OHOS::Ace::NG
