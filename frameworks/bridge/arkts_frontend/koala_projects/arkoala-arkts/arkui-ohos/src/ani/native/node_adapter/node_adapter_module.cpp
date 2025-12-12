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
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onAttachToNodePtr", "d:", nodeId);
    };
    auto onDetachFromNode = [env, nodeAdapterRef]() {
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onDetachFromNodePtr", ":");
    };
    auto onGetId = [env, nodeAdapterRef](ani_int index) -> int32_t {
        ani_int nodeId = index;
        ani_int id;
        env->Object_CallMethodByName_Int(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onGetChildId", "i:i", &id, nodeId);
        return static_cast<int32_t>(id);
    };
    auto onCreateChild = [env, nodeAdapterRef](ani_double index) -> ani_long {
        ani_double nodeId = index;
        ani_long node;
        env->Object_CallMethodByName_Long(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onCreateNewNodePtr", "d:l", &node, nodeId);
        return node;
    };
    auto onDisposeChild = [env, nodeAdapterRef](ani_double node, ani_double id) {
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onDisposeNodePtr", "dd:", id, node);
    };

    auto onUpdateChild = [env, nodeAdapterRef](ani_double node, ani_double id) {
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(nodeAdapterRef->GetValue()), "onUpdateNodePtr", "dd:", id, node);
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

ani_array NodeAdapterGetAllItems(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    AniDoubleArray items = modifier->getNodeAdapterAniModifier()->nodeAdapterGetAllItems(ptr);
    ani_array result;
    auto size = items.size;
    if (size == 0 || items.data == nullptr) {
        return nullptr;
    }

    ani_ref undef {};
    if (env->GetUndefined(&undef) != ANI_OK) {
        return nullptr;
    }
    if (env->Array_New(size, undef, &result) != ANI_OK) {
        return nullptr;
    }

    ani_class doubleClass {};
    if (env->FindClass("std.core.Double", &doubleClass) != ANI_OK) {
        return nullptr;
    }
    ani_method doubleCtor {};
    if (env->Class_FindMethod(doubleClass, "<ctor>", "d:", &doubleCtor) != ANI_OK) {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i) {
        ani_object boxedDouble {};
        if (env->Object_New(doubleClass, doubleCtor, &boxedDouble, items.data[i]) != ANI_OK) {
            return nullptr;
        }
        if (ANI_OK != env->Array_Set(result, i, boxedDouble)) {
            return nullptr;
        }
    }
    return result;
}
} // namespace OHOS::Ace::Ani
