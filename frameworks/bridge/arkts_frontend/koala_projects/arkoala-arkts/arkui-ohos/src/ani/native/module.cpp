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

#include "web_module_methods.h"

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
