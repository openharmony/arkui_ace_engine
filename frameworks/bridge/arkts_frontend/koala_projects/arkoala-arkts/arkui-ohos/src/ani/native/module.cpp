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

#include <array>

#include "ani.h"
#include "load.h"

namespace OHOS::Ace::Ani {

void TransferPixelMap([[maybe_unused]] ani_env* env, ani_object aniClass, ani_object node, ani_object pixelMap)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getImageAniModifier()->setPixelMap(arkNode, nullptr);
}

void SetWebOptions(ani_env* env, ani_object aniClass, ani_object node, ani_object object)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return;
    }
    ani_ref savePtr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &savePtr);
    auto onNWebId = [env, object = savePtr](int32_t nwebId) {
        if (env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "_setNWebId", "D:V", static_cast<ani_double>(nwebId)) != ANI_OK) {
            return;
        }
    };
    auto onHapPath = [env, object = savePtr](const std::string& hapPath) {
        ani_string aniHapPath = nullptr;
        if (env->String_NewUTF8(hapPath.c_str(), hapPath.size(), &aniHapPath) != ANI_OK) {
            env->GlobalReference_Delete(object);
            return;
        }
        if (env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "_setHapPath", "Lstd/core/String;:V", aniHapPath) != ANI_OK) {
            env->GlobalReference_Delete(object);
            return;
        }
        env->GlobalReference_Delete(object);
    };
    modifier->getWebAniModifier()->setWebOptions(arkNode, std::move(onNWebId), std::move(onHapPath));
}

} // namespace OHOS::Ace::Ani


ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_class cls;
    auto ani_status = env->FindClass("Larkui/ani/ArkUIAniModule/ArkUIAniModule;", &cls);
    if (ani_status != ANI_OK) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {
            "_Image_Transfer_PixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferPixelMap)
        },
        ani_native_function {
            "_Web_SetWebOptions",
            "JL@ohos/web/webview/webview/WebviewController;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWebOptions)
        }
    };

    env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    *result = ANI_VERSION_1;
    return ANI_OK;
}
