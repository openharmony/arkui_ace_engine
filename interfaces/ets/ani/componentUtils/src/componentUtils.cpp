/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani.h>
#include <array>
#include <iostream>

#include "base/memory/referenced.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/pipeline/pipeline_base.h"

namespace {
std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);

    utf8Buffer[bytes_written] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}
} // namespace

static ani_object getSize([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_object obj = {};
    static const char* className = "L@ohos/componentUtils/SizeInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "width", rectangle.size.Width())) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "height", rectangle.size.Height())) {
        return nullptr;
    }
    return obj;
}

static ani_object getLocalOffset([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_object obj = {};
    static const char* className = "L@ohos/componentUtils/OffsetInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "x", rectangle.localOffset.GetX())) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "y", rectangle.localOffset.GetY())) {
        return nullptr;
    }
    return obj;
}

static ani_object getWindowOffset([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_object obj = {};
    static const char* className = "L@ohos/componentUtils/OffsetInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "x", rectangle.windowOffset.GetX())) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "y", rectangle.windowOffset.GetY())) {
        return nullptr;
    }
    return obj;
}

static ani_object getScreenOffset([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_object obj = {};
    static const char* className = "L@ohos/componentUtils/OffsetInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        return nullptr;
    }
    auto x = rectangle.windowOffset.GetX() + rectangle.screenRect.GetOffset().GetX();
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "x", x)) {
        return nullptr;
    }
    auto y = rectangle.windowOffset.GetY() + rectangle.screenRect.GetOffset().GetY();
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "y", y)) {
        return nullptr;
    }
    return obj;
}

static ani_object getTranslateResult([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_object obj = {};
    static const char* className = "L@ohos/componentUtils/TranslateInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "x", rectangle.translate.x)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "y", rectangle.translate.y)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "z", rectangle.translate.z)) {
        return nullptr;
    }
    return obj;
}

static ani_object getScaleResult([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_object obj = {};
    static const char* className = "L@ohos/componentUtils/ScaleInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "x", rectangle.scale.x)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "y", rectangle.scale.y)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "z", rectangle.scale.z)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "centerX", rectangle.scale.centerX)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "centerY", rectangle.scale.centerY)) {
        return nullptr;
    }
    return obj;
}

static ani_object getRotateResult([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_object obj = {};
    static const char* className = "L@ohos/componentUtils/RotateInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "x", rectangle.rotate.x)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "y", rectangle.rotate.y)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "z", rectangle.rotate.z)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "angle", rectangle.rotate.angle)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "centerX", rectangle.rotate.centerX)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Double(obj, "centerY", rectangle.rotate.centerY)) {
        return nullptr;
    }
    return obj;
}

static ani_object getRransform([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    const int32_t size = 16;
    ani_array_double array = nullptr;
    env->Array_New_Double(size, &array);

    ani_double matrix4[size] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
    for (int32_t i = 0; i < size; i++) {
        matrix4[i] = ani_double(rectangle.matrix4[i]);
    }
    env->Array_SetRegion_Double(array, 0, size, matrix4);
    return array;
}

static ani_object getRectangleById([[maybe_unused]] ani_env* env, ani_string id)
{
    OHOS::Ace::NG::Rectangle rectangle;
    auto delegate = OHOS::Ace::EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return nullptr;
    }
    auto key = ANIUtils_ANIStringToStdString(env, id);
    delegate->GetRectangleById(key, rectangle);

    ani_object rectangleObj = {};
    static const char* className = "L@ohos/componentUtils/ComponentInfoInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &rectangleObj)) {
        return nullptr;
    }
    ani_object size_obj = getSize(env, rectangle);
    if (size_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "size", size_obj)) {
        return nullptr;
    }
    ani_object localOffset_obj = getLocalOffset(env, rectangle);
    if (localOffset_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "localOffset", localOffset_obj)) {
        return nullptr;
    }
    ani_object windowOffset_obj = getWindowOffset(env, rectangle);
    if (windowOffset_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "windowOffset", windowOffset_obj)) {
        return nullptr;
    }
    ani_object screenOffset_obj = getScreenOffset(env, rectangle);
    if (screenOffset_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "screenOffset", screenOffset_obj)) {
        return nullptr;
    }
    ani_object translate_obj = getTranslateResult(env, rectangle);
    if (translate_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "translate", translate_obj)) {
        return nullptr;
    }
    ani_object scale_obj = getScaleResult(env, rectangle);
    if (scale_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "scale", scale_obj)) {
        return nullptr;
    }
    ani_object rotate_obj = getRotateResult(env, rectangle);
    if (rotate_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "rotate", rotate_obj)) {
        return nullptr;
    }
    ani_object transform_obj = getRransform(env, rectangle);
    if (transform_obj == nullptr) {
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(rectangleObj, "transform", transform_obj)) {
        return nullptr;
    }
    return rectangleObj;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/componentUtils/componentUtils;", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function { "getRectangleById", nullptr, reinterpret_cast<void*>(getRectangleById) },
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
