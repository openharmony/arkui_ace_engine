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
#include "visual_effect_module.h"

#include <mutex>

#include "load.h"
#include "log/log.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
ani_namespace GetOrCreateMaterialNamespace([[maybe_unused]] ani_env* env)
{
    static ani_namespace globalNamespace = nullptr; // cache global namespace
    static std::mutex mutex;
    if (globalNamespace) {
        return globalNamespace;
    }
    std::lock_guard<std::mutex> lock(mutex);
    if (globalNamespace) {
        return globalNamespace;
    }
    ani_namespace nmSpace = nullptr;
    ANI_CALL(env, FindNamespace("@ohos.arkui.uiMaterial.uiMaterial", &nmSpace), return nullptr);
    ani_ref refValue = nullptr;
    ANI_CALL(env, GlobalReference_Create(nmSpace, &refValue), return nullptr);
    globalNamespace = static_cast<ani_namespace>(refValue);
    return globalNamespace;
}

ani_enum GetOrCreateMaterialEnumClass([[maybe_unused]] ani_env* env)
{
    static ani_enum globalMaterialTypeEnum = nullptr;
    static std::mutex mutex;
    if (globalMaterialTypeEnum) {
        return globalMaterialTypeEnum;
    }
    std::lock_guard<std::mutex> lock(mutex);
    if (globalMaterialTypeEnum) {
        return globalMaterialTypeEnum;
    }
    ani_enum materialTypeEnum = nullptr;
    auto nmSpace = GetOrCreateMaterialNamespace(env);
    CHECK_NULL_RETURN(nmSpace, nullptr);
    ANI_CALL(env, FindEnum("@ohos.arkui.uiMaterial.uiMaterial.MaterialType", &materialTypeEnum), return nullptr);
    ani_ref globalMaterialTypeRef = nullptr;
    ANI_CALL(env, GlobalReference_Create(materialTypeEnum, &globalMaterialTypeRef), return nullptr);
    globalMaterialTypeEnum = static_cast<ani_enum>(globalMaterialTypeRef);
    return globalMaterialTypeEnum;
}

int32_t ParseMaterialOptionType(ani_env* env, ani_object aniOption)
{
    constexpr int32_t defaultType = 0; // NONE
    if (AniUtils::IsUndefined(env, aniOption)) {
        return defaultType;
    }
    ani_ref typeRef = nullptr;
    ANI_CALL(env, Object_GetPropertyByName_Ref(aniOption, "type", &typeRef), return defaultType);
    if (AniUtils::IsUndefined(env, typeRef)) {
        return defaultType;
    }
    ani_object typeObj = static_cast<ani_object>(typeRef);
    ani_enum materialTypeEnumClass = GetOrCreateMaterialEnumClass(env);
    CHECK_NULL_RETURN(materialTypeEnumClass, defaultType);
    ani_boolean isMaterialType = false;
    ANI_CALL(env, Object_InstanceOf(typeObj, materialTypeEnumClass, &isMaterialType), return defaultType);
    if (!isMaterialType) {
        HILOGW("type is not materialType enum class");
        return defaultType;
    }
    ani_int typeInt = 0;
    ani_enum_item typeItem = static_cast<ani_enum_item>(typeObj);
    ANI_CALL(env, EnumItem_GetValue_Int(typeItem, &typeInt), return defaultType);
    return static_cast<int32_t>(typeInt);
}

ani_long GetPropertyName(ani_env* env, ani_object obj, const char* name)
{
    ani_long propertyValue = 0L;
    ANI_CALL(env, Object_GetFieldByName_Long(obj, name, &propertyValue), return 0L);
    return propertyValue;
}

ani_object CallFromPtrMethod(ani_env* env, const char* methodName, ani_long ptr)
{
    ani_static_method method;
    ani_class myClass;
    ani_ref resultRef;
    ANI_CALL(env, FindClass("@ohos.arkui.shape.__ShapeInnerMethods__", &myClass), return nullptr);
    ANI_CALL(env, Class_FindStaticMethod(myClass, methodName, nullptr, &method), return nullptr);
    ANI_CALL(env, Class_CallStaticMethod_Ref(myClass, method, &resultRef, ptr), return nullptr);
    return static_cast<ani_object>(resultRef);
}

ani_long GetNativePtrFromMethod(ani_env* env, ani_object obj, const char* methodName)
{
    ani_long result = 0L;
    ANI_CALL(env, Object_CallMethodByName_Long(obj, methodName, nullptr, &result), return 0L);
    return result;
}
}
ani_long ExtractorsToRectShapePtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object obj)
{
    return GetPropertyName(env, obj, "basicShapeResult");
}

ani_object ExtractorsFromRectShapePtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    return CallFromPtrMethod(env, "RectFromPtr", ptr);
}

ani_long ExtractorsToCircleShapePtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object obj)
{
    return GetPropertyName(env, obj, "basicShapeResult");
}

ani_object ExtractorsFromCircleShapePtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    return CallFromPtrMethod(env, "CircleFromPtr", ptr);
}

ani_long ExtractorsToEllipseShapePtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    return GetPropertyName(env, obj, "basicShapeResult");
}
ani_object ExtractorsFromEllipseShapePtr(ani_env* env, ani_object aniClass, ani_long ptr)
{
    return CallFromPtrMethod(env, "EllipseFromPtr", ptr);
}
ani_long ExtractorsToPathShapePtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    return GetPropertyName(env, obj, "basicShapeResult");
}
ani_object ExtractorsFromPathShapePtr(ani_env* env, ani_object aniClass, ani_long ptr)
{
    return CallFromPtrMethod(env, "PathFromPtr", ptr);
}
ani_long ExtractorsToICurvePtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    return GetPropertyName(env, obj, "nativeContext");
}
ani_long ExtractorsToMatrix4TransitPtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    return GetPropertyName(env, obj, "matrix4Object");
}
ani_long ExtractorsToUiEffectFilterPtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    ani_long result = GetPropertyName(env, obj, "filterNativeObj");
    if (result != 0L) {
        return result;
    }

    return GetNativePtrFromMethod(env, obj, "getNativePtr");
}
ani_long ExtractorsToUiEffectVisualEffectPtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    ani_long result = GetPropertyName(env, obj, "visualEffectNativeObj");
    if (result != 0L) {
        return result;
    }

    return GetNativePtrFromMethod(env, obj, "getNativePtr");
}

ani_long ExtractorsToUiMaterialMaterialPtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    ani_long result = GetNativePtrFromMethod(env, obj, "getNativeObject");
    return result;
}

ani_long UiMaterialConstructMaterial(ani_env* env, ani_object aniClass, ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, 0);
    int32_t type = ParseMaterialOptionType(env, obj);
    auto* material = modifier->getVisualEffectAniModifier()->constructMaterial(type);
    return reinterpret_cast<ani_long>(material);
}

void UiMaterialDestroyMaterial(ani_env* env, ani_object aniClass, ani_long ptr)
{
    auto* pointer = reinterpret_cast<OHOS::Ace::UiMaterial*>(ptr);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    modifier->getVisualEffectAniModifier()->destroyMaterial(pointer);
}
} // namespace OHOS::Ace::Ani
