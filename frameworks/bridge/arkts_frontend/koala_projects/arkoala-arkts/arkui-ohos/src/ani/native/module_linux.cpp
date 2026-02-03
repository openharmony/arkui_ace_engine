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
#include "detached_free_root_node/detached_free_root_node.h"
#include "syntax/lazy_for_each_module.h"
#include "syntax/syntax_module.h"
#include "syntax/for_each_module.h"
#include "list/list_module.h"
#include "list/list_item_group_module.h"
#include "load.h"
#include "log/log.h"
#include "water_flow/water_flow_module.h"
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
    auto ani_status = env->FindClass("arkui.ani.arkts.ArkUIAniModule.ArkUIAniModule", &cls);
    if (ani_status != ANI_OK) {
        return ANI_ERROR;
    }

    std::array staticMethods = {
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
            "i:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SyncInstanceId)
        },
        ani_native_function {
            "_Common_Restore_InstanceId",
            ":",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RestoreInstanceId)
        },
        ani_native_function {
            "_Common_Get_Current_InstanceId",
            ":i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetCurrentInstanceId)
        },
        ani_native_function {
            "_Common_GetFocused_InstanceId",
            ":i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetFocusedInstanceId)
        },
        ani_native_function {
            "_Common_SetImageCacheCount",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageCacheCount)
        },
        ani_native_function {
            "_Common_SetImageRawDataCacheSize",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageRawDataCacheSize)
        },
        ani_native_function {
            "_CustomNode_Construct",
            "iC{arkui.ArkCustomComponent.ArkCustomComponent}:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructCustomNode)
        },
        ani_native_function {
            "_LazyForEachNode_Construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructLazyForEachNode)
        },
        ani_native_function {
            "_BuilderProxyNode_Construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::BuilderProxyNodeConstruct)
        },
        ani_native_function {
            "_ContentSlot_construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ContentSlotConstruct)
        },
        ani_native_function {
            "_ContentSlotInterface_setContentSlotOptions",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetContentSlotOptions)
        },
        ani_native_function {
            "_SetDrawCallback",
            "lC{std.core.Function1}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawCallback)
        },
        ani_native_function {
            "_SetDrawModifier",
            "liC{arkui.component.common.DrawModifier}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawModifier)
        },
        ani_native_function {
            "_Invalidate",
            "l:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Invalidate)
        },
        ani_native_function {
            "_SetOverlay_ComponentContent",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetOverlayComponentContent)
        },
        ani_native_function {
            "_SetWaterFlowSection",
            "lC{arkui.component.waterFlow.WaterFlowSections}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowSection)
        },
        ani_native_function {
            "_SetListChildrenMainSize",
            "lC{arkui.component.common.ChildrenMainSize}:",
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
            ":l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateViewStackProcessor)
        },
        ani_native_function {
            "_PopViewStackProcessor",
            ":l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PopViewStackProcessor)
        },
        ani_native_function {
            "_DeleteViewStackProcessor",
            "l:",
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
            "i:i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RequireArkoalaNodeId)
        },
        ani_native_function {
            "_PersistentStorage_Get",
            "C{std.core.String}:C{std.core.String}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Get)
        },
        ani_native_function {
            "_PersistentStorage_Set",
            "C{std.core.String}C{std.core.String}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Set)
        },
        ani_native_function {
            "_PersistentStorage_Has",
            "C{std.core.String}:z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Has)
        },
        ani_native_function {
            "_PersistentStorage_Clear",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Clear)
        },
        ani_native_function {
            "_PersistentStorage_Delete",
            "C{std.core.String}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Delete)
        },
        ani_native_function {
            "_Env_GetColorMode",
            ":i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetColorMode)
        },
        ani_native_function {
            "_Env_GetFontScale",
            ":f",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontScale)
        },
        ani_native_function {
            "_Env_GetFontWeightScale",
            ":f",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontWeightScale)
        },
        ani_native_function {
            "_Env_GetAccessibilityEnabled",
            ":z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetAccessibilityEnabled)
        },
        ani_native_function {
            "_Env_GetLayoutDirection",
            ":C{std.core.String}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLayoutDirection)
        },
        ani_native_function {
            "_Env_GetLanguageCode",
            ":C{std.core.String}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLanguageCode)
        },
        ani_native_function {
            "_XComponent_SetXComponentControllerCallback",
            "lC{arkui.component.xcomponent.XComponentOptionsInternal}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetXComponentControllerCallback)
        },
        ani_native_function {
            "_RemoveComponent_FromFrameNode",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RemoveComponentFromFrameNode)
        },
        ani_native_function {
            "_AddComponent_ToFrameNode",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::AddComponentToFrameNode)
        },
        ani_native_function {
            "_CheckIsUIThread",
            "i:i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CheckIsUIThread)
        },
        ani_native_function {
            "_IsDebugMode",
            "i:i",
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
            "z:",
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
        },
        ani_native_function {
            "_Common_getWindowName",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowName)
        },
        ani_native_function {
            "_Common_setIsRecycleInvisibleImageMemory",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetIsRecycleInvisibleImageMemory)
        },
        ani_native_function {
            "_Common_getWindowId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowId)
        },
        ani_native_function {
            "_Common_getWindowWidthBreakpoint",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowWidthBreakpoint)
        },
        ani_native_function {
            "_Common_getWindowHeightBreakpoint",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowHeightBreakpoint)
        },
        ani_native_function {
            "_SyntaxItem_Construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructSyntaxItem)
        },
        ani_native_function {
            "_ForEachNode_Construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructForEachNode)
        },
        ani_native_function {
            "_SetCustomCallbackWithCheck",
            "lC{arkui.FrameNode.FrameNode}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetCustomCallbackWithCheck)
        },
        ani_native_function {
            "_ResolveUIContext",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ResolveUIContext)
       },
       ani_native_function {
            "_DetachedFreeRoot_Construct",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructDetachedFreeRoot)
       }
    };

    auto bindRst = env->Class_BindStaticNativeMethods(cls, staticMethods.data(), staticMethods.size());
    if (bindRst != ANI_OK) {
        HILOGE("Bind native methonds failed, bindRst:%{public}d", bindRst);
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
