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

#include <securec.h>

#include "animate_impl.h"
#include "node/node_model.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"
#ifdef __cplusplus
extern "C" {
#endif

namespace {
constexpr int NUM_4 = 4;
}

ArkUI_Matrix4ScaleOptions* OH_ArkUI_Matrix4ScaleOptions_Create()
{
    ArkUI_Matrix4ScaleOptions* options = new ArkUI_Matrix4ScaleOptions;
    options->x = 1.0f;
    options->y = 1.0f;
    options->z = 1.0f;
    options->centerX = 0.0f;
    options->centerY = 0.0f;
    return options;
}

void OH_ArkUI_Matrix4ScaleOptions_Dispose(ArkUI_Matrix4ScaleOptions* options)
{
    CHECK_NULL_VOID(options);
    delete options;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetX(ArkUI_Matrix4ScaleOptions* options, const float scaleX)
{
    if (options) {
        options->x = scaleX;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetX(const ArkUI_Matrix4ScaleOptions* options, float* scaleX)
{
    if (!options || !scaleX) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *scaleX = options->x;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetY(ArkUI_Matrix4ScaleOptions* options, const float scaleY)
{
    if (options) {
        options->y = scaleY;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetY(const ArkUI_Matrix4ScaleOptions* options, float* scaleY)
{
    if (!options || !scaleY) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *scaleY = options->y;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetZ(ArkUI_Matrix4ScaleOptions* options, const float scaleZ)
{
    if (options) {
        options->z = scaleZ;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetZ(const ArkUI_Matrix4ScaleOptions* options, float* scaleZ)
{
    if (!options || !scaleZ) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *scaleZ = options->z;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterX(ArkUI_Matrix4ScaleOptions* options, const float centerX)
{
    if (options) {
        options->centerX = centerX;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterX(const ArkUI_Matrix4ScaleOptions* options, float* centerX)
{
    if (!options || !centerX) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *centerX = options->centerX;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_SetCenterY(ArkUI_Matrix4ScaleOptions* options, const float centerY)
{
    if (options) {
        options->centerY = centerY;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4ScaleOptions_GetCenterY(const ArkUI_Matrix4ScaleOptions* options, float* centerY)
{
    if (!options || !centerY) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *centerY = options->centerY;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Matrix4RotationOptions* OH_ArkUI_Matrix4RotationOptions_Create()
{
    ArkUI_Matrix4RotationOptions* options = new ArkUI_Matrix4RotationOptions;
    options->isSetX = false;
    options->isSetY = false;
    options->isSetZ = false;
    options->x = 0.0f;
    options->y = 0.0f;
    options->z = 0.0f;
    options->centerX = 0.0f;
    options->centerY = 0.0f;
    options->angle = 0.0f;
    return options;
}

void OH_ArkUI_Matrix4RotationOptions_Dispose(ArkUI_Matrix4RotationOptions* options)
{
    CHECK_NULL_VOID(options);
    delete options;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetX(ArkUI_Matrix4RotationOptions* options, const float x)
{
    if (options) {
        options->x = x;
        options->isSetX = true;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetX(const ArkUI_Matrix4RotationOptions* options, float* x)
{
    if (!options || !x || !options->isSetX) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *x = options->x;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetY(ArkUI_Matrix4RotationOptions* options, const float y)
{
    if (options) {
        options->y = y;
        options->isSetY = true;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetY(const ArkUI_Matrix4RotationOptions* options, float* y)
{
    if (!options || !y || !options->isSetY) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *y = options->y;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetZ(ArkUI_Matrix4RotationOptions* options, const float z)
{
    if (options) {
        options->z = z;
        options->isSetZ = true;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetZ(const ArkUI_Matrix4RotationOptions* options, float* z)
{
    if (!options || !z || !options->isSetZ) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *z = options->z;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetAngle(ArkUI_Matrix4RotationOptions* options, const float angle)
{
    if (options) {
        options->angle = angle;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetAngle(const ArkUI_Matrix4RotationOptions* options, float* angle)
{
    if (!options || !angle) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *angle = options->angle;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterX(ArkUI_Matrix4RotationOptions* options, const float centerX)
{
    if (options) {
        options->centerX = centerX;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterX(const ArkUI_Matrix4RotationOptions* options, float* centerX)
{
    if (!options || !centerX) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *centerX = options->centerX;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_SetCenterY(ArkUI_Matrix4RotationOptions* options, const float centerY)
{
    if (options) {
        options->centerY = centerY;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4RotationOptions_GetCenterY(const ArkUI_Matrix4RotationOptions* options, float* centerY)
{
    if (!options || !centerY) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *centerY = options->centerY;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Matrix4TranslationOptions* OH_ArkUI_Matrix4TranslationOptions_Create()
{
    ArkUI_Matrix4TranslationOptions* options = new ArkUI_Matrix4TranslationOptions;
    options->x = 0.0f;
    options->y = 0.0f;
    options->z = 0.0f;
    return options;
}

void OH_ArkUI_Matrix4TranslationOptions_Dispose(ArkUI_Matrix4TranslationOptions* options)
{
    CHECK_NULL_VOID(options);
    delete options;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetX(ArkUI_Matrix4TranslationOptions* options, const float x)
{
    if (options) {
        options->x = x;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetX(const ArkUI_Matrix4TranslationOptions* options, float* x)
{
    if (!options || !x) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *x = options->x;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetY(ArkUI_Matrix4TranslationOptions* options, const float y)
{
    if (options) {
        options->y = y;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetY(const ArkUI_Matrix4TranslationOptions* options, float* y)
{
    if (!options || !y) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *y = options->y;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_SetZ(ArkUI_Matrix4TranslationOptions* options, const float z)
{
    if (options) {
        options->z = z;
        return ARKUI_ERROR_CODE_NO_ERROR;
    }
    return ARKUI_ERROR_CODE_PARAM_INVALID;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4TranslationOptions_GetZ(const ArkUI_Matrix4TranslationOptions* options, float* z)
{
    if (!options || !z) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *z = options->z;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateIdentity()
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* matrix = impl->getNodeModifiers()->getMatrix4Modifier()->createMatrix4();
    ArkUI_Matrix4* matrixs = new ArkUI_Matrix4({ matrix });
    return matrixs;
}

ArkUI_Matrix4* OH_ArkUI_Matrix4_CreateByElements(const float* elements)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!elements || !impl) {
        return nullptr;
    }
    auto* matrixHandle = impl->getNodeModifiers()->getMatrix4Modifier()->createByElements(elements);
    ArkUI_Matrix4* matrixs = new ArkUI_Matrix4();
    matrixs->matrix = matrixHandle;
    return matrixs;
}

void OH_ArkUI_Matrix4_Dispose(ArkUI_Matrix4* matrix)
{
    CHECK_NULL_VOID(matrix);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    impl->getNodeModifiers()->getMatrix4Modifier()->dispose(matrix->matrix);
    matrix->matrix = nullptr;
    delete matrix;
}

ArkUI_Matrix4* OH_ArkUI_Matrix4_Copy(const ArkUI_Matrix4* matrix)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !impl) {
        return nullptr;
    }
    auto matrixCopy = impl->getNodeModifiers()->getMatrix4Modifier()->copy(matrix->matrix);
    ArkUI_Matrix4* matrixs = new ArkUI_Matrix4();
    matrixs->matrix = matrixCopy;
    return matrixs;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_Invert(ArkUI_Matrix4* matrix)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->invert(matrix->matrix);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_Combine(ArkUI_Matrix4* oriMatrix, const ArkUI_Matrix4* anotherMatrix)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!oriMatrix || !anotherMatrix || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->combine(oriMatrix->matrix, anotherMatrix->matrix);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_Translate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4TranslationOptions* translate)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !translate || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->translate(matrix->matrix, translate->x, translate->y, translate->z);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_Scale(ArkUI_Matrix4* matrix, const ArkUI_Matrix4ScaleOptions* scale)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !scale || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->scale(matrix->matrix, scale);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_Rotate(ArkUI_Matrix4* matrix, const ArkUI_Matrix4RotationOptions* rotate)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !rotate || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->rotate(matrix->matrix, rotate);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_Skew(ArkUI_Matrix4* matrix, const float skewX, const float skewY)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->skew(matrix->matrix, skewX, skewY);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_TransformPoint(
    const ArkUI_Matrix4* matrix, const ArkUI_PointF* oriPoint, ArkUI_PointF* result)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !oriPoint || !result || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->transformPoint(
        matrix->matrix, oriPoint->x, oriPoint->y, &(result->x), &(result->y));
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_SetPolyToPoly(
    ArkUI_Matrix4* matrix, const ArkUI_PointF* src, const ArkUI_PointF* dst, const uint32_t pointCount)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !src || !dst || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (pointCount > NUM_4) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    std::vector<std::pair<float, float>> srcPoints;
    std::vector<std::pair<float, float>> dstPoints;
    for (uint32_t i = 0; i < pointCount; i++) {
        srcPoints.push_back({ src[i].x, src[i].y });
        dstPoints.push_back({ dst[i].x, dst[i].y });
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->setPolyToPoly(matrix->matrix, srcPoints, dstPoints);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_Matrix4_GetElements(const ArkUI_Matrix4* matrix, float* result)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!matrix || !result || !impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getMatrix4Modifier()->getElements(matrix->matrix, result);
    return ARKUI_ERROR_CODE_NO_ERROR;
}
#ifdef __cplusplus
};
#endif