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
#include "log.h"

#include "common_module.h"
#include "content_slot_module.h"
#include "utils/convert_utils.h"
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
    auto ani_status = env->FindClass("Larkui/ani/arkts/ArkUIAniModule/ArkUIAniModule;", &cls);
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
        },
        ani_native_function {
            "_Web_SetWebController_ControllerHandler",
            "JL@ohos/web/webview/webview/WebviewController;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWebControllerControllerHandler)
        },
        ani_native_function {
            "_ConvertUtils_ConvertFromPixelMapAni",
            "L@ohos/multimedia/image/image/PixelMap;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConvertFromPixelMapAni)
        },
        ani_native_function {
            "_ConvertUtils_ConvertToPixelMapAni",
            "J:L@ohos/multimedia/image/image/PixelMap;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConvertToPixelMapAni)
        },
        ani_native_function {
            "_Common_GetHostContext",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetHostContext)
        },
        ani_native_function {
            "_Common_Sync_InstanceId",
            "I:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SyncInstanceId)
        },
        ani_native_function {
            "_Common_Restore_InstanceId",
            ":V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RestoreInstanceId)
        },
        ani_native_function {
            "_ContentSlot_construct",
            "I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ContentSlotConstruct)
        },
        ani_native_function {
            "_ContentSlotInterface_setContentSlotOptions",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetContentSlotOptions)
        },
        ani_native_function {
            "_SetDrawCallback",
            "JLstd/core/Function1;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawCallback)
        },
        ani_native_function {
            "_SetDrawModifier",
            "JLarkui/component/common/DrawModifier;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawModifier)
        },
        ani_native_function {
            "_Invalidate",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Invalidate)
        },
    };

    auto bindRst = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (bindRst != ANI_OK) {
        HILOGE("Bund native methonds failed, bindRst:%{public}d", bindRst);
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
