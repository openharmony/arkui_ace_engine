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

#include "node_adapter_module.h"

#include <memory>
#include <utility>

#include "animation/ani_global_reference.h"
#include "load.h"
#include "log/log.h"

namespace OHOS::Ace::Ani {
ani_long NodeAdapterConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object nodeAdapter)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    auto nodeAdapterRef = std::make_shared<AniGlobalReference>(env, nodeAdapter);
    auto onAttachToNode = [env, nodeAdapterRef](ani_double nodeId) {
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onAttachToNodePtr", nullptr, nodeId);
    };
    auto onDetachFromNode = [env, nodeAdapterRef]() {
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onDetachFromNodePtr", nullptr);
    };
    auto onGetId = [env, nodeAdapterRef](ani_double index) -> int32_t {
        ani_double nodeId = index;
        ani_double id;
        env->Object_CallMethodByName_Double(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onGetChildId", nullptr, &id, nodeId);
        return static_cast<int32_t>(id);
    };
    auto onCreateChild = [env, nodeAdapterRef](ani_double index) -> ani_long {
        ani_double nodeId = index;
        ani_long node;
        env->Object_CallMethodByName_Long(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onCreateNewNodePtr", nullptr, &node, nodeId);
        return node;
    };
    auto onDisposeChild = [env, nodeAdapterRef](ani_double node, ani_double id) {
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onDisposeNodePtr", nullptr, id, node);
    };

    auto onUpdateChild = [env, nodeAdapterRef](ani_double node, ani_double id) {
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onUpdateNodePtr", nullptr, id, node);
    };

    NodeAdapterInfo info = { .onAttachToNode = std::move(onAttachToNode),
        .onDetachFromNode = std::move(onDetachFromNode),
        .onGetId = std::move(onGetId),
        .onCreateChild = std::move(onCreateChild),
        .onDisposeChild = std::move(onDisposeChild),
        .onUpdateChild = std::move(onUpdateChild) };
    ani_long node = modifier->getNodeAdapterAniModifier()->nodeAdapterConstruct(std::move(info));
    return node;
}

void NodeAdapterDetachNodeAdapter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getNodeAdapterAniModifier()->nodeAdapterDetachNodeAdapter(ptr);
}

ani_boolean NodeAdapterAttachNodeAdapter(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    return modifier->getNodeAdapterAniModifier()->nodeAdapterAttachNodeAdapter(ptr, node);
}

void NodeAdapterDispose(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getNodeAdapterAniModifier()->nodeAdapterDispose(ptr);
}

void NodeAdapterNotifyItemReloaded(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getNodeAdapterAniModifier()->nodeAdapterNotifyItemReloaded(ptr);
}

void NodeAdapterSetTotalNodeCount(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double count)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getNodeAdapterAniModifier()->nodeAdapterSetTotalNodeCount(ptr, count);
}

void NodeAdapterNotifyItemChanged(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double start, ani_double count)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getNodeAdapterAniModifier()->nodeAdapterNotifyItemChanged(ptr, start, count);
}

void NodeAdapterNotifyItemRemoved(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double start, ani_double count)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getNodeAdapterAniModifier()->nodeAdapterNotifyItemRemoved(ptr, start, count);
}

void NodeAdapterNotifyItemInserted(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double start, ani_double count)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getNodeAdapterAniModifier()->nodeAdapterNotifyItemInserted(ptr, start, count);
}

void NodeAdapterNotifyItemMoved(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double from, ani_double to)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getNodeAdapterAniModifier()->nodeAdapterNotifyItemMoved(ptr, from, to);
}

ani_array_double NodeAdapterGetAllItems(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return {};
    }
    AniDoubleArray items = modifier->getNodeAdapterAniModifier()->nodeAdapterGetAllItems(ptr);
    ani_array_double result;
    auto size = items.size;
    if (size == 0) {
        delete[] items.data;
        return nullptr;
    }
    if (env->Array_New_Double(size, &result) != ANI_OK) {
        delete[] items.data;
        return result;
    }
    if (ANI_OK != env->Array_SetRegion_Double(result, 0, size, items.data)) {
        delete[] items.data;
        return nullptr;
    }
    delete[] items.data;
    return result;
}
} // namespace OHOS::Ace::Ani
