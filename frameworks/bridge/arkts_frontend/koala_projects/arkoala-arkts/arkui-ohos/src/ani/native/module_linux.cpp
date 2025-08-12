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
#include "content_slot/content_slot_module.h"
#include "custom_node/custom_node_module.h"
#include "syntax/lazy_for_each_module.h"
#include "syntax/syntax_module.h"
#include "list/list_children_main_size_module.h"
#include "load.h"
#include "log/log.h"
#include "water_flow/waterFlowSection_module.h"
#include "interop/interop_module.h"
#include "stateMgmt/stateMgmt_module.h"
#include "xcomponent/xcomponent_module_methods.h"
#include "condition_scope/condition_scope.h"

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
            "_CustomNode_QueryNavigationInfo",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryNavigationInfo)
        },
        ani_native_function {
            "_CustomNode_QueryNavDestinationInfo",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryNavDestinationInfo)
        },
        ani_native_function {
            "_CustomNode_QueryNavDestinationInfo0",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryNavDestinationInfo0)
        },
        ani_native_function {
            "_CustomNode_QueryRouterPageInfo",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryRouterPageInfo)
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
            "_Common_GetFocused_InstanceId",
            ":I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetFocusedInstanceId)
        },
        ani_native_function {
            "_CustomNode_Construct",
            "ILarkui/ArkCustomComponent/ArkCustomComponent;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructCustomNode)
        },
        ani_native_function {
            "_LazyForEachNode_Construct",
            "I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructLazyForEachNode)
        },
        ani_native_function {
            "_SyntaxNode_Construct",
            "I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructSyntaxNode)
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
            "JILarkui/component/common/DrawModifier;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawModifier)
        },
        ani_native_function {
            "_Invalidate",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Invalidate)
        },
        ani_native_function {
            "_SetOverlay_ComponentContent",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetOverlayComponentContent)
        },
        ani_native_function {
            "_SetWaterFlowOptions",
            "JLarkui/component/waterFlow/WaterFlowOptions;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowOptions)
        },
        ani_native_function {
            "_SetListChildrenMainSize",
            "JLarkui/component/common/ChildrenMainSize;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetListChildrenMainSize)
        },
        ani_native_function {
            "_Common_GetSharedLocalStorage",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetSharedLocalStorage)
        },
        ani_native_function {
            "_Animation_SetOrCreateAnimatableProperty",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetOrCreateAnimatableProperty)
        },
        ani_native_function {
            "_CreateViewStackProcessor",
            ":J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateViewStackProcessor)
        },
        ani_native_function {
            "_PopViewStackProcessor",
            ":J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PopViewStackProcessor)
        },
        ani_native_function {
            "_DeleteViewStackProcessor",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DeleteViewStackProcessor)
        },
        ani_native_function {
            "_BackgroundImage_PixelMap",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetBackgroundImagePixelMap)
        },
        ani_native_function {
            "_SetCustomCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetCustomCallback)
        },
        ani_native_function {
            "_RequireArkoalaNodeId",
            "I:I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RequireArkoalaNodeId)
        },
        ani_native_function {
            "_PersistentStorage_Get",
            "Lstd/core/String;:Lstd/core/String;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Get)
        },
        ani_native_function {
            "_PersistentStorage_Set",
            "Lstd/core/String;Lstd/core/String;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Set)
        },
        ani_native_function {
            "_PersistentStorage_Has",
            "Lstd/core/String;:Z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Has)
        },
        ani_native_function {
            "_PersistentStorage_Clear",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Clear)
        },
        ani_native_function {
            "_PersistentStorage_Delete",
            "Lstd/core/String;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Delete)
        },
        ani_native_function {
            "_Env_GetColorMode",
            ":I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetColorMode)
        },
        ani_native_function {
            "_Env_GetFontScale",
            ":F",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontScale)
        },
        ani_native_function {
            "_Env_GetFontWeightScale",
            ":F",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontWeightScale)
        },
        ani_native_function {
            "_Env_GetAccessibilityEnabled",
            ":Z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetAccessibilityEnabled)
        },
        ani_native_function {
            "_Env_GetLayoutDirection",
            ":Lstd/core/String;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLayoutDirection)
        },
        ani_native_function {
            "_Env_GetLanguageCode",
            ":Lstd/core/String;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLanguageCode)
        },
        ani_native_function {
            "_XComponent_SetXComponentOptions",
            "JLarkui/component/xcomponent/XComponentOptionsInternal;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetXComponentOptions)
        },
        ani_native_function {
            "_XComponent_SetXComponentParameters",
            "JLarkui/component/xcomponent/XComponentParametersInternal;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetXComponentParameters)
        },
        ani_native_function {
            "_XComponent_SetNativeXComponentParameters",
            "JI:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetNativeXComponentParameters)
        },
        ani_native_function {
            "_RemoveComponent_FromFrameNode",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RemoveComponentFromFrameNode)
        },
        ani_native_function {
            "_AddComponent_ToFrameNode",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::AddComponentToFrameNode)
        },
        ani_native_function {
            "_CheckIsUIThread",
            "I:I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CheckIsUIThread)
        },
        ani_native_function {
            "_IsDebugMode",
            "I:I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::IsDebugMode)
        },
        ani_native_function {
            "_OnMeasure_InnerMeasure",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::OnMeasureInnerMeasure)
        },
        ani_native_function {
            "_OnLayout_InnerLayout",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::OnLayoutInnerLayout)
        },
        ani_native_function {
            "_SetParallelScoped",
            "Z:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetParallelScoped)
        },
        ani_native_function {
            "_Common_SetCustomPropertyCallBack",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetCustomPropertyCallBack)
        },
        ani_native_function {
            "_Common_getCustomProperty",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetCustomProperty)
        },
        ani_native_function {
            "_ConditionScopeNode_Construct",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructConditionScope)
        },
        ani_native_function {
            "_Common_vp2px",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Vp2px)
        },
        ani_native_function {
            "_Common_px2vp",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Px2vp)
        },
        ani_native_function {
            "_Common_fp2px",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Fp2px)
        },
        ani_native_function {
            "_Common_px2fp",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Px2fp)
        },
        ani_native_function {
            "_Common_lpx2px",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Lpx2px)
        },
        ani_native_function {
            "_Common_px2lpx",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Px2lpx)
       }
    };

    auto bindRst = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (bindRst != ANI_OK) {
        HILOGE("Bind native methonds failed, bindRst:%{public}d", bindRst);
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
