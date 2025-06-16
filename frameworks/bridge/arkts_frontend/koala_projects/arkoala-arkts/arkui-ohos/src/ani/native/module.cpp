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
#include "animation/animation_ani_impl.h"
#include "common/common_module.h"
#include "componentSnapshot/componentSnapshot_module.h"
#include "content_slot/content_slot_module.h"
#include "custom_node/custom_node_module.h"
#include "drag_and_drop/native_drag_drop_global.h"
#include "load.h"
#include "log/log.h"
#include "utils/convert_utils.h"
#include "water_flow/waterFlowSection_module.h"
#include "web/web_module_methods.h"

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
            "_Web_SetWebOptions",
            "JL@ohos/web/webview/webview/WebviewController;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWebOptions)
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
            "_Common_Get_Current_InstanceId",
            ":I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetCurrentInstanceId)
        },
        ani_native_function {
            "_CustomNode_Construct",
            "ILarkui/ArkCustomComponent/ArkCustomComponent;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructCustomNode)
        },
        ani_native_function {
            "_BuilderProxyNode_Construct",
            "I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::BuilderProxyNodeConstruct)
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
        ani_native_function {
            "_SetWaterFlowOptions",
            "JLarkui/component/waterFlow/WaterFlowOptions;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowOptions)
        },
        ani_native_function {
            "_DragEvent_Set_Data",
            "JL@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetData)
        },
        ani_native_function {
            "_DragEvent_Get_Data",
            "J:L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventGetData)
        },
        ani_native_function {
            "_DragEvent_Get_Summary",
            "J:L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventGetSummary)
        },
        ani_native_function {
            "_DragEvent_Set_PixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetPixelMap)
        },
        ani_native_function {
            "_DragEvent_Set_ExtraInfo",
            "JLstd/core/String;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetExtraInfo)
        },
        ani_native_function {
            "_DragEvent_Set_CustomNode",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetCustomNode)
        },
        ani_native_function {
            "_Drag_Set_AllowDrop_Null",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragSetAllowDropNull)
        },
        ani_native_function {
            "_Drag_Set_AllowDrop",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragSetAllowDrop)
        },
        ani_native_function {
            "_Drag_Set_DragPreview",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragSetDragPreview)
        },
        ani_native_function {
            "_DragEvent_ConvertFromPixelMapToAniPointer",
            "L@ohos/multimedia/image/image/PixelMap;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConvertFromPixelMapToAniPointer)
        },
        ani_native_function {
            "_ComponentSnapshot_createFromBuilderWithCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateFromBuilderWithCallback)
        },
        ani_native_function {
            "_ComponentSnapshot_createFromBuilderWithPromise",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateFromBuilderWithPromise)
        },
        ani_native_function {
            "_Animation_SetOrCreateAnimatableProperty",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetOrCreateAnimatableProperty)
        },
    };

    auto bindRst = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (bindRst != ANI_OK) {
        HILOGE("Bind native methonds failed, bindRst:%{public}d", bindRst);
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
