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

#include "log/log.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
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
    return GetPropertyName(env, obj, "filterNativeObj");
}
ani_long ExtractorsToUiEffectVisualEffectPtr(ani_env* env, ani_object aniClass, ani_object obj)
{
    return GetPropertyName(env, obj, "visualEffectNativeObj");
}
} // namespace OHOS::Ace::Ani
