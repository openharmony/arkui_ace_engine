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
#include <ani_signature_builder.h>
#include <array>
#include <iostream>

#include "base/memory/referenced.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/pipeline/pipeline_base.h"
#include "core/components_ng/base/inspector.h"
using namespace arkts::ani_signature;
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

// Cached global references for classes
static ani_ref gOffsetClass;
static ani_ref gSizeClass;
static ani_ref gTranslateResultClass;
static ani_ref gScaleResultClass;
static ani_ref gRotateResultClass;
static ani_ref gComponentInfoClass;

// Cached methods
static ani_method gOffsetCtor;
static ani_method gSizeCtor;
static ani_method gTranslateResultCtor;
static ani_method gScaleResultCtor;
static ani_method gRotateResultCtor;
static ani_method gComponentInfoCtor;
static std::string gComponentInfoSignature;

static ani_object CreateOffset(ani_env* env, ani_double x, ani_double y)
{
    CHECK_NULL_RETURN(env, nullptr);
    CHECK_NULL_RETURN(gOffsetClass, nullptr);
    CHECK_NULL_RETURN(gOffsetCtor, nullptr);

    ani_object obj = {};
    if (ANI_OK != env->Object_New(static_cast<ani_class>(gOffsetClass), gOffsetCtor, &obj, x, y)) {
        return nullptr;
    }
    return obj;
}

static ani_object getSize([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    CHECK_NULL_RETURN(gSizeClass, nullptr);
    CHECK_NULL_RETURN(gSizeCtor, nullptr);
    ani_object obj = {};
    ani_double width = rectangle.size.Width();
    ani_double height = rectangle.size.Height();
    if (ANI_OK != env->Object_New(static_cast<ani_class>(gSizeClass), gSizeCtor, &obj, width, height)) {
        return nullptr;
    }
    return obj;
}

static ani_object getLocalOffset([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    return CreateOffset(env, rectangle.localOffset.GetX(), rectangle.localOffset.GetY());
}

static ani_object getWindowOffset([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    return CreateOffset(env, rectangle.windowOffset.GetX(), rectangle.windowOffset.GetY());
}

static ani_object getScreenOffset([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    ani_double x = rectangle.windowOffset.GetX() + rectangle.screenRect.GetOffset().GetX();
    ani_double y = rectangle.windowOffset.GetY() + rectangle.screenRect.GetOffset().GetY();
    return CreateOffset(env, x, y);
}

static ani_object getTranslateResult([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    CHECK_NULL_RETURN(gTranslateResultClass, nullptr);
    CHECK_NULL_RETURN(gTranslateResultCtor, nullptr);
    ani_object obj = {};
    ani_double x = rectangle.translate.x;
    ani_double y = rectangle.translate.y;
    ani_double z = rectangle.translate.z;
    if (ANI_OK !=
        env->Object_New(static_cast<ani_class>(gTranslateResultClass), gTranslateResultCtor, &obj, x, y, z)) {
        return nullptr;
    }
    return obj;
}

static ani_object getScaleResult([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    CHECK_NULL_RETURN(gScaleResultClass, nullptr);
    CHECK_NULL_RETURN(gScaleResultCtor, nullptr);
    ani_object obj = {};
    ani_double x = rectangle.scale.x;
    ani_double y = rectangle.scale.y;
    ani_double z = rectangle.scale.z;
    ani_double centerX = rectangle.scale.centerX;
    ani_double centerY = rectangle.scale.centerY;
    if (ANI_OK !=
        env->Object_New(static_cast<ani_class>(gScaleResultClass), gScaleResultCtor,
            &obj, x, y, z, centerX, centerY)) {
        return nullptr;
    }
    return obj;
}

static ani_object getRotateResult([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    CHECK_NULL_RETURN(gRotateResultClass, nullptr);
    CHECK_NULL_RETURN(gRotateResultCtor, nullptr);
    ani_object obj = {};
    ani_double x = rectangle.rotate.x;
    ani_double y = rectangle.rotate.y;
    ani_double z = rectangle.rotate.z;
    ani_double centerX = rectangle.rotate.centerX;
    ani_double centerY = rectangle.rotate.centerY;
    ani_double angle = rectangle.rotate.angle;
    if (ANI_OK !=
        env->Object_New(static_cast<ani_class>(gRotateResultClass), gRotateResultCtor,
            &obj, x, y, z, centerX, centerY, angle)) {
        return nullptr;
    }
    return obj;
}

static ani_object getTransform([[maybe_unused]] ani_env* env, OHOS::Ace::NG::Rectangle rectangle)
{
    const int32_t size = 16;
    std::vector<double> matrixArray(size);
    for (int32_t i = 1; i < size; i++) {
        matrixArray[i] = rectangle.matrix4[i];
    }

    ani_fixedarray_double doubleArray;
    if (ANI_OK != env->FixedArray_New_Double(matrixArray.size(), &doubleArray)) {
        return nullptr;
    }
    const auto *data = reinterpret_cast<const ani_double*>(matrixArray.data());
    if (ANI_OK != env->FixedArray_SetRegion_Double(doubleArray, 0, matrixArray.size(), data)) {
        return nullptr;
    }
    ani_array array;
    if (ANI_OK != env->Array_New(1, doubleArray, &array)) {
        return nullptr;
    }
    return array;
}

static ani_object getRectangleById([[maybe_unused]] ani_env* env, ani_string id)
{
    OHOS::Ace::NG::Rectangle rectangle;
    auto key = ANIUtils_ANIStringToStdString(env, id);
    OHOS::Ace::NG::Inspector::GetRectangleById(key, rectangle);
    ani_object size_obj = getSize(env, rectangle);
    CHECK_NULL_RETURN(size_obj, nullptr);
    ani_object localOffset_obj = getLocalOffset(env, rectangle);
    CHECK_NULL_RETURN(localOffset_obj, nullptr);
    ani_object windowOffset_obj = getWindowOffset(env, rectangle);
    CHECK_NULL_RETURN(windowOffset_obj, nullptr);
    ani_object screenOffset_obj = getScreenOffset(env, rectangle);
    CHECK_NULL_RETURN(screenOffset_obj, nullptr);
    ani_object translate_obj = getTranslateResult(env, rectangle);
    CHECK_NULL_RETURN(translate_obj, nullptr);
    ani_object scale_obj = getScaleResult(env, rectangle);
    CHECK_NULL_RETURN(scale_obj, nullptr);
    ani_object rotate_obj = getRotateResult(env, rectangle);
    CHECK_NULL_RETURN(rotate_obj, nullptr);
    ani_object transform_obj = getTransform(env, rectangle);
    CHECK_NULL_RETURN(transform_obj, nullptr);
    ani_object rectangleObj = {};
    CHECK_NULL_RETURN(gComponentInfoClass, nullptr);
    CHECK_NULL_RETURN(gComponentInfoCtor, nullptr);
    if (ANI_OK != env->Object_New(static_cast<ani_class>(gComponentInfoClass), gComponentInfoCtor, &rectangleObj,
        size_obj, localOffset_obj, windowOffset_obj, screenOffset_obj, translate_obj, scale_obj, rotate_obj,
        transform_obj)) {
        return nullptr;
    }
    return rectangleObj;
}

bool InitCachedClass(
    ani_env* env, const char* className, ani_ref* outGlobalRef, ani_method* outCtor, const char* signature)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(cls), outGlobalRef)) {
        return false;
    }
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", signature, outCtor)) {
        return false;
    }
    return true;
}
} // namespace

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    if (!InitCachedClass(env,
        "@ohos.arkui.componentUtils.componentUtils.OffsetInner", &gOffsetClass, &gOffsetCtor, "dd:")) {
        return ANI_ERROR;
    }
    if (!InitCachedClass(env, "@ohos.arkui.componentUtils.componentUtils.SizeInner", &gSizeClass, &gSizeCtor, "dd:")) {
        return ANI_ERROR;
    }
    if (!InitCachedClass(env, "@ohos.arkui.componentUtils.componentUtils.TranslateResultInner",
        &gTranslateResultClass, &gTranslateResultCtor, "ddd:")) {
        return ANI_ERROR;
    }
    if (!InitCachedClass(env, "@ohos.arkui.componentUtils.componentUtils.ScaleResultInner",
        &gScaleResultClass, &gScaleResultCtor, "ddddd:")) {
        return ANI_ERROR;
    }
    if (!InitCachedClass(env, "@ohos.arkui.componentUtils.componentUtils.RotateResultInner",
        &gRotateResultClass, &gRotateResultCtor, "dddddd:")) {
        return ANI_ERROR;
    }

    {
        ani_class cls;
        if (ANI_OK != env->FindClass("@ohos.arkui.componentUtils.componentUtils.ComponentInfoInner", &cls)) {
            return ANI_ERROR;
        }
        if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(cls), &gComponentInfoClass)) {
            return ANI_ERROR;
        }

        SignatureBuilder signatureBuilder {};
        signatureBuilder
            .AddClass("@ohos.arkui.componentUtils.componentUtils.Size")
            .AddClass("@ohos.arkui.componentUtils.componentUtils.Offset")
            .AddClass("@ohos.arkui.componentUtils.componentUtils.Offset")
            .AddClass("@ohos.arkui.componentUtils.componentUtils.Offset")
            .AddClass("@ohos.arkui.componentUtils.componentUtils.TranslateResult")
            .AddClass("@ohos.arkui.componentUtils.componentUtils.ScaleResult")
            .AddClass("@ohos.arkui.componentUtils.componentUtils.RotateResult")
            .AddClass("std.core.Tuple16");
        gComponentInfoSignature = signatureBuilder.BuildSignatureDescriptor();
        if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", gComponentInfoSignature.c_str(), &gComponentInfoCtor)) {
            return ANI_ERROR;
        }
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("@ohos.arkui.componentUtils.componentUtils", &ns)) {
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
