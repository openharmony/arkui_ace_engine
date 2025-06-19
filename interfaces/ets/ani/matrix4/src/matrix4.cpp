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

#include "frameworks/base/geometry/matrix4.h"

#include <algorithm>
#include <ani.h>
#include <array>
#include <chrono>
#include <future>
#include <iostream>
#include <map>
#include <string>
#include <thread>

namespace OHOS::Ace::MatrixAni {
constexpr int32_t MATRIX_LENGTH = 16;
class Matrix4_Obj {
public:
    explicit Matrix4_Obj(Matrix4 matrix) : matrix4x4(matrix) {}
    OHOS::Ace::Matrix4 matrix4x4;
};

static Matrix4_Obj* GetMatrixObj(ani_env* env, ani_object obj)
{
    ani_long matrix4x4;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "matrix4Object", &matrix4x4)) {
        return nullptr;
    }
    return reinterpret_cast<Matrix4_Obj*>(matrix4x4);
}

static ani_object Matrix4_Identity([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object)
{
    static const char* className = "L@ohos/matrix4/matrix4/Matrix4TransitInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        ani_object nullobj = nullptr;
        return nullobj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        ani_object nullobj = nullptr;
        return nullobj;
    }

    auto matrix4Object = new Matrix4_Obj(OHOS::Ace::Matrix4::CreateIdentity());
    ani_object matrix4_object = {};
    if (ANI_OK != env->Object_New(cls, ctor, &matrix4_object, reinterpret_cast<ani_long>(matrix4Object))) {
        ani_object nullobj = nullptr;
        return nullobj;
    }
    return matrix4_object;
}

Matrix4 ConvertToMatrix([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object option)
{
    Matrix4 result = Matrix4::CreateIdentity();
    ani_class arrayClass;
    if (ANI_OK != env->FindClass("Lescompat/Array;", &arrayClass)) {
        return result;
    }
    ani_boolean isArray;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(option), arrayClass, &isArray)) {
        return result;
    }
    ani_array inputArray = static_cast<ani_array>(option);
    ani_size length = 0;
    if (ANI_OK != env->Array_GetLength(inputArray, &length)) {
        return result;
    }
    int32_t inputSize = static_cast<int32_t>(length);
    if (inputSize != MATRIX_LENGTH) {
        return result;
    }
    // in column order
    ani_array_double doubleArray = static_cast<ani_array_double>(inputArray);
    for (int32_t i = 0; i < Matrix4::DIMENSION; i++) {
        for (int32_t j = 0; j < Matrix4::DIMENSION; j++) {
            ani_double value;
            auto index = static_cast<ani_size>(i * Matrix4::DIMENSION + j);
            if (ANI_OK != env->Array_GetRegion_Double(doubleArray, index, 1, &value)) {
                return result;
            }
            auto ret = static_cast<double>(value);
            result.Set(j, i, ret);
        }
    }
    return result;
}

static ani_object Matrix4_Init([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_object option)
{
    static const char* className = "L@ohos/matrix4/matrix4/Matrix4TransitInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        ani_object nullobj = nullptr;
        return nullobj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        ani_object nullobj = nullptr;
        return nullobj;
    }

    auto matrix = ConvertToMatrix(env, option);
    auto matrix4Object = new Matrix4_Obj(matrix);

    ani_object matrix4_object;
    if (ANI_OK != env->Object_New(cls, ctor, &matrix4_object, reinterpret_cast<ani_long>(matrix4Object))) {
        ani_object nullobj = nullptr;
        return nullobj;
    }
    return matrix4_object;
}

static ani_object Matrix4_Copy([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object)
{
    static const char* className = "L@ohos/matrix4/matrix4/Matrix4TransitInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        ani_object nullobj = nullptr;
        return nullobj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        ani_object nullobj = nullptr;
        return nullobj;
    }
    Matrix4_Obj* matrixObj = GetMatrixObj(env, object);
    if (matrixObj == nullptr) {
        return nullptr;
    }
    auto matrix4Object = new Matrix4_Obj(matrixObj->matrix4x4);
    ani_object matrix4_object;
    if (ANI_OK != env->Object_New(cls, ctor, &matrix4_object, reinterpret_cast<ani_long>(matrix4Object))) {
        ani_object nullobj = nullptr;
        return nullobj;
    }
    return matrix4_object;
}

bool ParseOption(ani_env* env, ani_object options, double& input, const char* property, const char* className)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    ani_ref property_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, property, &property_ref)) {
        return false;
    }
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(property_ref, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_double propertyValue;
    if (ANI_OK != env->Object_CallMethodByName_Double(static_cast<ani_object>(property_ref),
        "doubleValue", nullptr, &propertyValue)) {
        return false;
    }
    input = static_cast<int32_t>(propertyValue);
    return true;
}

static ani_object Matrix4_Scale([[maybe_unused]] ani_env* env, ani_object object, ani_object options)
{
    double xValue = 1.0;
    ParseOption(env, options, xValue, "x", "L@ohos/matrix4/matrix4/ScaleOption;");
    double yValue = 1.0;
    ParseOption(env, options, yValue, "y", "L@ohos/matrix4/matrix4/ScaleOption;");
    double zValue = 1.0;
    ParseOption(env, options, zValue, "z", "L@ohos/matrix4/matrix4/ScaleOption;");
    double centerXValue = 0.0;
    ParseOption(env, options, centerXValue, "centerX", "L@ohos/matrix4/matrix4/ScaleOption;");
    double centerYValue = 0.0;
    ParseOption(env, options, centerYValue, "centerY", "L@ohos/matrix4/matrix4/ScaleOption;");

    auto scaleMatrix = Matrix4::CreateScale(xValue, yValue, zValue);
    if (!NearZero(centerXValue) || !NearZero(centerYValue)) {
        auto translate1 = Matrix4::CreateTranslate(centerXValue, centerYValue, 0.0);
        auto translate2 = Matrix4::CreateTranslate(-centerXValue, -centerYValue, 0.0);
        scaleMatrix = scaleMatrix * translate2;
        scaleMatrix = translate1 * scaleMatrix;
    }

    Matrix4_Obj* matrixObj = GetMatrixObj(env, object);
    if (matrixObj == nullptr) {
        return nullptr;
    }
    matrixObj->matrix4x4 = scaleMatrix * matrixObj->matrix4x4;
    return object;
}

static ani_object Matrix4_Rotate([[maybe_unused]] ani_env* env, ani_object object, ani_object options)
{
    double dx = 0.0;
    ParseOption(env, options, dx, "x", "L@ohos/matrix4/matrix4/RotateOption;");
    double dy = 0.0;
    ParseOption(env, options, dy, "y", "L@ohos/matrix4/matrix4/RotateOption;");
    double dz = 0.0;
    ParseOption(env, options, dz, "z", "L@ohos/matrix4/matrix4/RotateOption;");
    double angle = 0.0;
    ParseOption(env, options, angle, "angle", "L@ohos/matrix4/matrix4/RotateOption;");
    double centerX = 0.0;
    ParseOption(env, options, centerX, "centerX", "L@ohos/matrix4/matrix4/RotateOption;");
    double centerY = 0.0;
    ParseOption(env, options, centerY, "centerY", "L@ohos/matrix4/matrix4/RotateOption;");

    auto rotateMatrix = Matrix4::CreateRotate(angle, dx, dy, dz);
    if (!NearZero(centerX) || !NearZero(centerY)) {
        auto translate1 = Matrix4::CreateTranslate(centerX, centerY, 0.0);
        auto translate2 = Matrix4::CreateTranslate(-centerX, -centerY, 0.0);
        rotateMatrix = rotateMatrix * translate2;
        rotateMatrix = translate1 * rotateMatrix;
    }

    Matrix4_Obj* matrixObj = GetMatrixObj(env, object);
    if (matrixObj == nullptr) {
        return nullptr;
    }
    matrixObj->matrix4x4 = rotateMatrix * matrixObj->matrix4x4;
    return object;
}

static ani_object Matrix4_Translate([[maybe_unused]] ani_env* env, ani_object object, ani_object options)
{
    double dx = 0.0;
    ParseOption(env, options, dx, "x", "L@ohos/matrix4/matrix4/TranslateOption;");
    double dy = 0.0;
    ParseOption(env, options, dy, "y", "L@ohos/matrix4/matrix4/TranslateOption;");
    double dz = 0.0;
    ParseOption(env, options, dz, "z", "L@ohos/matrix4/matrix4/TranslateOption;");

    Matrix4_Obj* matrixObj = GetMatrixObj(env, object);
    if (matrixObj == nullptr) {
        return nullptr;
    }
    matrixObj->matrix4x4 =
        Matrix4::CreateTranslate(static_cast<float>(dx), static_cast<float>(dy), static_cast<float>(dz)) *
        matrixObj->matrix4x4;
    return object;
}

static ani_object Matrix4_Invert([[maybe_unused]] ani_env* env, ani_object object)
{
    Matrix4_Obj* matrixObj = GetMatrixObj(env, object);
    if (matrixObj == nullptr) {
        return nullptr;
    }
    matrixObj->matrix4x4 = Matrix4::Invert(matrixObj->matrix4x4);
    return object;
}

static ani_object Matrix4_Combine([[maybe_unused]] ani_env* env, ani_object object, ani_object option)
{
    Matrix4_Obj* matrixOption = GetMatrixObj(env, option);
    if (matrixOption == nullptr) {
        return nullptr;
    }

    Matrix4_Obj* matrixObj = GetMatrixObj(env, object);
    if (matrixObj == nullptr) {
        return nullptr;
    }
    matrixObj->matrix4x4 = matrixOption->matrix4x4 * matrixObj->matrix4x4;
    return object;
}

ani_status BindMatrix(ani_env* env)
{
    static const char* className = "L@ohos/matrix4/matrix4;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "identity", nullptr, reinterpret_cast<void*>(Matrix4_Identity) },
        ani_native_function { "init", nullptr, reinterpret_cast<void*>(Matrix4_Init) },
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status BindMatrixTransit(ani_env* env)
{
    static const char* className = "L@ohos/matrix4/matrix4/Matrix4TransitInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "copy", nullptr, reinterpret_cast<void*>(Matrix4_Copy) },
        ani_native_function { "scale", nullptr, reinterpret_cast<void*>(Matrix4_Scale) },
        ani_native_function { "rotate", nullptr, reinterpret_cast<void*>(Matrix4_Rotate) },
        ani_native_function { "translate", nullptr, reinterpret_cast<void*>(Matrix4_Translate) },
        ani_native_function { "invert", nullptr, reinterpret_cast<void*>(Matrix4_Invert) },
        ani_native_function { "combine", nullptr, reinterpret_cast<void*>(Matrix4_Combine) },
    };
    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        return ANI_ERROR;
    };
    return ANI_OK;
}
} // namespace OHOS::Ace::MatrixAni

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_status ret = OHOS::Ace::MatrixAni::BindMatrix(env);
    if (ret != ANI_OK) {
        return ret;
    }

    ani_status ret1 = OHOS::Ace::MatrixAni::BindMatrixTransit(env);
    if (ret1 != ANI_OK) {
        return ret1;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}