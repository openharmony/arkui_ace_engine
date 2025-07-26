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
#include "utils/ani_utils.h"

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
    ani_vm* vm = nullptr;
    env->GetVM(&vm);

    std::shared_ptr<ani_wref> weakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        env->WeakReference_Delete(*wref);
    });

    env->WeakReference_Create(obj, weakRef.get());

    ani_type type;
    env->Object_GetType(obj, &type);

    ani_method onPageShowMethod;
    env->Class_FindMethod(static_cast<ani_class>(type), "onPageShow", ":V", &onPageShowMethod);
    auto&& onPageShow = [vm, weakRef, onPageShowMethod]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);

        ani_boolean released;
        ani_ref localRef;
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onPageShowMethod);
        }
    };

    ani_method onPageHideMethod;
    env->Class_FindMethod(static_cast<ani_class>(type), "onPageHide", ":V", &onPageHideMethod);
    auto&& onPageHide = [vm, weakRef, onPageHideMethod]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);

        ani_boolean released;
        ani_ref localRef;
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onPageHideMethod);
        }
    };

    ani_method onBackPressMethod;
    env->Class_FindMethod(static_cast<ani_class>(type), "onBackPress", ":z", &onBackPressMethod);
    auto&& onBackPress = [vm, weakRef, onBackPressMethod]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);

        ani_boolean released;
        ani_ref localRef;
        ani_boolean result = ani_boolean(false);
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Boolean(static_cast<ani_object>(localRef), onBackPressMethod, &result);
        }
        return result;
    };

    ani_method pageTransitionMethod;
    env->Class_FindMethod(static_cast<ani_class>(type), "pageTransition", ":V", &pageTransitionMethod);
    auto pageTransition = [vm, weakRef, pageTransitionMethod]() {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        ani_boolean released;
        ani_ref localRef;
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), pageTransitionMethod);
        }
    };

    ani_method onCleanupMethod;
    env->Class_FindMethod(static_cast<ani_class>(type), "onCleanup", nullptr, &onCleanupMethod);
    auto onCleanupFunc = [vm, weakRef, onCleanupMethod]() {
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }
        ani_boolean released;
        ani_ref localRef;
        if (ANI_OK != env->WeakReference_GetReference(*weakRef, &released, &localRef)) {
            return;
        }

        if (!released) {
            env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onCleanupMethod);
        }
    };

    ani_method onDumpInspectorMethod;
    env->Class_FindMethod(static_cast<ani_class>(type), "onDumpInspector", ":Lstd/core/String;",
        &onDumpInspectorMethod);
    auto onDumpInspector = [vm, weakRef, onDumpInspectorMethod]() {
        ani_env *env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        ani_boolean released;
        ani_ref localRef;
        ani_ref result{};
        env->WeakReference_GetReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Ref(static_cast<ani_object>(localRef), onDumpInspectorMethod, &result);
        }
        ani_string aniStr = static_cast<ani_string>(result);
        return AniUtils::ANIStringToStdString(env, aniStr);
    };

    ani_long customNode = modifier->getCustomNodeAniModifier()->constructCustomNode(
        id, std::move(onPageShow), std::move(onPageHide), std::move(onBackPress), std::move(pageTransition),
        std::move(onCleanupFunc), std::move(onDumpInspector)
    );
    return customNode;
}

void RequestFrame(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }

    modifier->getCustomNodeAniModifier()->requestFrame();
    return;
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