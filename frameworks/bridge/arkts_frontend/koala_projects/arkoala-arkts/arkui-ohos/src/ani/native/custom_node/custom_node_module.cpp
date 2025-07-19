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
    ani_method onDumpInspectorMethod;
    env->Class_FindMethod(static_cast<ani_class>(type), "onDumpInspector", ":Lstd/core/string",
        &onDumpInspectorMethod);
    auto onDumpInspector = [vm, weakRef, onDumpInspectorMethod]() {
        ani_env *env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        ani_boolean released;
        ani_ref localRef;
        ani_ref result{};
        env_weakReference(*weakRef, &released, &localRef);
        if (!released) {
            env->Object_CallMethod_Ref(static_cast<ani_object>(localRef), onDumpInspectorMethod, &result);
        }
        ani_string aniStr = static_cast<ani_string>(result);
        return AniUtils::ANIStringToStdString(env, aniStr);
    }

    ani_long customNode = modifier->getCustomNodeAniModifier()->constructCustomNode(id, std::move(onDumpInspector));
    return customNode;
}
 
} // namespace OHOS::Ace::Ani