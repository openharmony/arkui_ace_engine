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

#include "common_module.h"

#include <memory>

#include "load.h"

#include "base/utils/utils.h"
// #include "pixel_map_taihe_ani.h"

namespace OHOS::Ace::Ani {

ani_object GetHostContext([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ani_ref* context = modifier->getCommonAniModifier()->getHostContext();
    if (context) {
        ani_object context_object = reinterpret_cast<ani_object>(*context);
        return context_object;
    }
    return nullptr;
}

void SyncInstanceId([[maybe_unused]] ani_env* env, ani_object obj, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->syncInstanceId(id);
}

void RestoreInstanceId([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->restoreInstanceId();
}

ani_int GetCurrentInstanceId([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return -1;
    }
    return modifier->getCommonAniModifier()->getCurrentInstanceId();
}

ani_int GetFocusedInstanceId([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return -1;
    }
    return modifier->getCommonAniModifier()->getFocusedInstanceId();
}

void SetDrawCallback(ani_env* env, ani_object obj, ani_long ptr, ani_fn_object fnObj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->setDrawCallback(env, ptr, fnObj);
}

void SetDrawModifier(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int flag, ani_object drawModifier)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getArkUIAniDrawModifier()->setDrawModifier(env, ptr, flag, drawModifier);
}

void Invalidate(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getArkUIAniDrawModifier()->invalidate(env, ptr);
}

ani_long BuilderProxyNodeConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id)
{
    auto nodeId = reinterpret_cast<ArkUI_Int32>(id);
    ani_long nativeObj {};
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nativeObj);
    auto builderProxyNode = modifier->getCommonAniModifier()->builderProxyNodeConstruct(nodeId);
    CHECK_NULL_RETURN(builderProxyNode, nativeObj);
    return reinterpret_cast<ani_long>(builderProxyNode);
}

ani_object GetSharedLocalStorage([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ani_ref storage = modifier->getCommonAniModifier()->getSharedLocalStorage();
    if (storage) {
        ani_object storage_object = reinterpret_cast<ani_object>(storage);
        return storage_object;
    }
    return nullptr;
}

void SetBackgroundImagePixelMap([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object node,
    ani_object pixelMap, ani_int repeat)
{
    // auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    // auto pixelMapValue = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMap);
    // if (!pixelMapValue) {
    //     return;
    // }
    // auto pixelMapPtr = reinterpret_cast<void*>(&pixelMapValue);
    // const auto* modifier = GetNodeAniModifier();
    // if (!modifier || !modifier->getCommonAniModifier() || !env) {
    //     return;
    // }
    // modifier->getCommonAniModifier()->setBackgroundImagePixelMap(
    //     env, arkNode, reinterpret_cast<ani_ref>(pixelMapPtr), repeat);
}

void SetCustomCallback(ani_env* env, ani_object obj, ani_long ptr,
    ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->setCustomCallback(env, ptr, fnObjMeasure, fnObjLayout);
}

ani_int RequireArkoalaNodeId(ani_env* env, ani_object obj, ani_int capacity)
{
    auto idCapacity = reinterpret_cast<ArkUI_Int32>(capacity);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, -1);
    auto cursor = modifier->getCommonAniModifier()->requireArkoalaNodeId(idCapacity);
    return cursor;
}

ani_int CheckIsUIThread([[maybe_unused]] ani_env* env, ani_object obj, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    return modifier->getCommonAniModifier()->checkIsUIThread(id);
}

ani_int IsDebugMode([[maybe_unused]] ani_env* env, ani_object obj, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    return modifier->getCommonAniModifier()->isDebugMode(id);
}
void OnMeasureInnerMeasure(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->onMeasureInnerMeasure(env, ptr);
}

void OnLayoutInnerLayout(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->onLayoutInnerLayout(env, ptr);
}

void SetParallelScoped(ani_env* env, ani_object obj, ani_boolean parallel)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->setParallelScoped(parallel);
}

void GetAlignmentEnum(ani_env* env, ani_object align, AniOverlayOptions& opt)
{
    ani_enum enumType;
    if (ANI_OK != env->FindEnum("Larkui/component/enums/Alignment;", &enumType)) {
        return;
    }

    ani_boolean isAlignment = ANI_FALSE;
    if (ANI_OK != env->Object_InstanceOf(align, enumType, &isAlignment)) {
        return;
    }

    if (!isAlignment) {
        return;
    }

    ani_enum_item enumItem = static_cast<ani_enum_item>(align);
    ani_int value;
    if (ANI_OK != env->EnumItem_GetValue_Int(enumItem, &value)) {
        return;
    }
    opt.alignment = static_cast<int32_t>(value);
}

void ParseOverlayOptions(ani_env* env, ani_object options, AniOverlayOptions& opt)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(options, &isUndefined);
    if (isUndefined) {
        return;
    }
    ani_ref align;
    env->Object_GetPropertyByName_Ref(options, "align", &align);
    env->Reference_IsUndefined(align, &isUndefined);
    if (!isUndefined) {
        GetAlignmentEnum(env, static_cast<ani_object>(align), opt);
    }
    ani_ref overlayOffset;
    env->Object_GetPropertyByName_Ref(options, "offset", &overlayOffset);
    env->Reference_IsUndefined(overlayOffset, &isUndefined);
    if (!isUndefined) {
        ani_object offset = static_cast<ani_object>(overlayOffset);
        ani_ref x;
        if (ANI_OK == env->Object_GetPropertyByName_Ref(offset, "x", &x)) {
            ani_double param_value;
            env->Object_CallMethodByName_Double(static_cast<ani_object>(x), "unboxed", ":D", &param_value);
            opt.x = static_cast<float>(param_value);
        }
        ani_ref y;
        if (ANI_OK == env->Object_GetPropertyByName_Ref(offset, "y", &y)) {
            ani_double param_value;
            env->Object_CallMethodByName_Double(static_cast<ani_object>(y), "unboxed", ":D", &param_value);
            opt.y = static_cast<float>(param_value);
        }
    }
}

void SetOverlayComponentContent(ani_env* env, ani_object obj, ani_long ptr, ani_long buildNodePtr, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!env || !modifier) {
        return;
    }
    AniOverlayOptions opt;
    ParseOverlayOptions(env, options, opt);
    modifier->getCommonAniModifier()->setOverlayComponent(ptr, buildNodePtr, opt);
}
} // namespace OHOS::Ace::Ani
