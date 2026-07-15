/*
* Copyright (C) 2026 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

// Stub library for TDD testing on Linux host
// Provides ANI entry points matching module_linux.cpp
// All native methods return safe default values

#include <ani.h>
#include <cstdio>

// ===== Stub implementations =====

static void S_Void() {}
static void S_Void_i(int32_t) {}
static void S_Void_l(int64_t) {}
static void S_Void_ll(int64_t, int64_t) {}
static void S_Void_z(bool) {}

static int32_t S_0i() { return 0; }
static int32_t S_0i_i(int32_t) { return 0; }

static int64_t S_0l() { return 0; }
static int64_t S_0l_i(int32_t) { return 0; }

static bool S_False() { return false; }
static float S_1f() { return 1.0f; }
static void* S_Null() { return nullptr; }

// Method bindings for ANI (extracted to reduce function length)
static ani_native_function g_aniMethods[] = {
    {"_WithEnv_construct", "i:l", reinterpret_cast<const void*>(S_0l_i)},
    {"_WithEnv_removeSystemEnvProperty", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_WithEnv_setSystemEnvProperty", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_WithEnv_setCustomEnvProperty", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_WithEnv_removeCustomEnvProperty", "li:", reinterpret_cast<const void*>(S_Void_ll)},
    {"_CustomNode_findCustomValueByKey", "li:Y", reinterpret_cast<const void*>(S_Null)},
    {"_CustomNode_findSystemEnvValueByKey", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_CustomNode_registerOnCustomEnvUpdateCallback", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_CustomNode_registerOnSystemEnvUpdateCallback", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_CustomNode_QueryNavigationInfo", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_CustomNode_QueryNavDestinationInfo", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_CustomNode_QueryNavDestinationInfo0", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_CustomNode_QueryRouterPageInfo", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_Common_GetHostContext", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_Common_Sync_InstanceId", "i:", reinterpret_cast<const void*>(S_Void_i)},
    {"_Common_Restore_InstanceId", ":", reinterpret_cast<const void*>(S_Void)},
    {"_Common_Get_Current_InstanceId", ":i", reinterpret_cast<const void*>(S_0i)},
    {"_Common_GetFocused_InstanceId", ":i", reinterpret_cast<const void*>(S_0i)},
    {"_CustomNode_Construct", nullptr, reinterpret_cast<const void*>(S_0l_i)},
    {"_LazyForEachNode_Construct", "i:l", reinterpret_cast<const void*>(S_0l_i)},
    {"_Repeat_IsChildInAnimation", nullptr, reinterpret_cast<const void*>(S_False)},
    {"_Repeat_IsChildOnMainTree", nullptr, reinterpret_cast<const void*>(S_False)},
    {"_Repeat_IsAllowAnimation", nullptr, reinterpret_cast<const void*>(S_False)},
    {"_Repeat_IsImplicitAnimationOpen", nullptr, reinterpret_cast<const void*>(S_False)},
    {"_BuilderProxyNode_Construct", "i:l", reinterpret_cast<const void*>(S_0l_i)},
    {"_BuilderProxyNode_Mock_Construct", "i:l", reinterpret_cast<const void*>(S_0l_i)},
    {"_ContentSlot_construct", "i:l", reinterpret_cast<const void*>(S_0l_i)},
    {"_ContentSlotInterface_setContentSlotOptions", "ll:", reinterpret_cast<const void*>(S_Void_ll)},
    {"_SetDrawCallback", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_SetDrawModifier", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_Invalidate", "l:", reinterpret_cast<const void*>(S_Void_l)},
    {"_SetOverlay_ComponentContent", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_SetWaterFlowSection", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_SetListChildrenMainSize", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_Common_GetSharedLocalStorage", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_Animation_SetOrCreateAnimatableProperty", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_CreateViewStackProcessor", ":l", reinterpret_cast<const void*>(S_0l)},
    {"_PopViewStackProcessor", ":l", reinterpret_cast<const void*>(S_0l)},
    {"_DeleteViewStackProcessor", "l:", reinterpret_cast<const void*>(S_Void_l)},
    {"_BackgroundImage_PixelMap", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_SetCustomCallback", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_RequireArkoalaNodeId", "i:i", reinterpret_cast<const void*>(S_0i_i)},
    {"_PersistentStorage_Get", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_PersistentStorage_Set", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_PersistentStorage_Has", nullptr, reinterpret_cast<const void*>(S_False)},
    {"_PersistentStorage_Clear", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_PersistentStorage_Delete", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_Env_GetColorMode", ":i", reinterpret_cast<const void*>(S_0i)},
    {"_Env_GetFontScale", ":f", reinterpret_cast<const void*>(S_1f)},
    {"_Env_GetFontWeightScale", ":f", reinterpret_cast<const void*>(S_1f)},
    {"_Env_GetAccessibilityEnabled", ":z", reinterpret_cast<const void*>(S_False)},
    {"_Env_GetLayoutDirection", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_Env_GetLanguageCode", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_XComponent_SetXComponentControllerCallback", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_RemoveComponent_FromFrameNode", "ll:", reinterpret_cast<const void*>(S_Void_ll)},
    {"_AddComponent_ToFrameNode", "ll:", reinterpret_cast<const void*>(S_Void_ll)},
    {"_CheckIsUIThread", "i:i", reinterpret_cast<const void*>(S_0i_i)},
    {"_IsDebugMode", "i:i", reinterpret_cast<const void*>(S_0i_i)},
    {"_OnMeasure_InnerMeasure", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_OnLayout_InnerLayout", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_SetParallelScoped", "z:", reinterpret_cast<const void*>(S_Void_z)},
    {"_CheckThreadValid", "zl:", reinterpret_cast<const void*>(S_False)},
    {"_Common_SetCustomPropertyCallBack", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_Common_getCustomProperty", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_ConditionScopeNode_Construct", nullptr, reinterpret_cast<const void*>(S_0l)},
    {"_Common_vp2px", nullptr, reinterpret_cast<const void*>(S_0i)},
    {"_Common_px2vp", nullptr, reinterpret_cast<const void*>(S_0i)},
    {"_Common_fp2px", nullptr, reinterpret_cast<const void*>(S_0i)},
    {"_Common_px2fp", nullptr, reinterpret_cast<const void*>(S_0i)},
    {"_Common_lpx2px", nullptr, reinterpret_cast<const void*>(S_0i)},
    {"_Common_px2lpx", nullptr, reinterpret_cast<const void*>(S_0i)},
    {"_Common_SetImageCacheCount", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_Common_getWindowName", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_Common_setIsRecycleInvisibleImageMemory", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_Common_getWindowId", nullptr, reinterpret_cast<const void*>(S_0i)},
    {"_Common_getWindowWidthBreakpoint", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_Common_getWindowHeightBreakpoint", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_Common_SetImageRawDataCacheSize", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_SyntaxItem_Construct", "i:l", reinterpret_cast<const void*>(S_0l_i)},
    {"_ForEachNode_Construct", "i:l", reinterpret_cast<const void*>(S_0l_i)},
    {"_ForEach_IsImplicitAnimationOpen", nullptr, reinterpret_cast<const void*>(S_False)},
    {"_SetCustomCallbackWithCheck", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_SetCustomCallbackWithCheckForFrameNodes", nullptr, reinterpret_cast<const void*>(S_Void)},
    {"_GetCallingScopeUIContext", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_GetLastFocusedUIContext", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_GetLastForegroundUIContext", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_GetAllUIContexts", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_ResolveUIContext", nullptr, reinterpret_cast<const void*>(S_Null)},
    {"_DetachedFreeRoot_Construct", nullptr, reinterpret_cast<const void*>(S_0l)},
};

// Bind ANI methods to class
static ani_status BindAniMethods(ani_env* env, ani_class cls)
{
    for (auto& m : g_aniMethods) {
        ani_native_function one = m;
        env->Class_BindStaticNativeMethods(cls, &one, 1);
    }
    return ANI_OK;
}

extern "C" {
ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    *result = ANI_VERSION_1;
    ani_env* env;
    if (vm->GetEnv(ANI_VERSION_1, &env) != ANI_OK) {
        return ANI_ERROR;
    }
    ani_class cls;
    if (env->FindClass("arkui.ani.arkts.ArkUIAniModule.ArkUIAniModule", &cls) != ANI_OK) {
        return ANI_ERROR;
    }
    return BindAniMethods(env, cls);
}

} // extern "C"
