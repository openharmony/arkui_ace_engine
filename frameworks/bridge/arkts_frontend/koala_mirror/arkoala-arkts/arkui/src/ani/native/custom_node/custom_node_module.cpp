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

#include "custom_node_module.h"
#include "load.h"

#include <memory>
 
namespace OHOS::Ace::Ani {
 
ani_long ConstructCustomNode(ani_env* env, [[maybe_unused]] ani_object aniClass,
                             ani_int id, ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }

    // ani_object obj from ts is supposed to be processed here

    ani_long customNode = modifier->getCustomNodeAniModifier()->constructCustomNode(id);
    return customNode;
}

ani_object QueryNavigationInfo(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ani_object res = modifier->getCustomNodeAniModifier()->queryNavigationInfo(env, node);
    return res;
}

ani_object QueryNavDestinationInfo(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ani_object res = modifier->getCustomNodeAniModifier()->queryNavDestinationInfo(env, node);
    return res;
}

ani_object QueryNavDestinationInfo0(ani_env* env, [[maybe_unused]] ani_object, ani_long node, ani_boolean isInner)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ani_object res = modifier->getCustomNodeAniModifier()->queryNavDestinationInfo0(env, node, isInner);
    return res;
}

ani_object QueryRouterPageInfo(ani_env* env, [[maybe_unused]] ani_object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ani_object res = modifier->getCustomNodeAniModifier()->queryRouterPageInfo(env, node);
    return res;
}
} // namespace OHOS::Ace::Ani