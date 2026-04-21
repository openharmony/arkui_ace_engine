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

#include "image/image_matrix.h"

#include <hilog/log.h>

namespace Self::UI {
    std::shared_ptr<ImageMatrix> ImageMatrix::Identity() 
    {
        OH_LOG_INFO(LogType::LOG_APP, "matrix4 create identity");
        auto matrix = std::make_shared<ImageMatrix>(OH_ArkUI_Matrix4_CreateIdentity());
        return matrix;
    }

    bool ImageMatrix::Translate(const TranslateOptions& translate) 
    {
        ArkUI_Matrix4TranslationOptions *options = OH_ArkUI_Matrix4TranslationOptions_Create();
        auto code = OH_ArkUI_Matrix4TranslationOptions_SetX(options, translate.x);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4TranslationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "translate set x failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4TranslationOptions_SetY(options, translate.y);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4TranslationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "translate set y failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4TranslationOptions_SetZ(options, translate.z);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4TranslationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "translate set z failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4_Translate(matrix4_, options);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4TranslationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "matrix translate failed, code = %{public}d", code);
            return false;
        }
        OH_ArkUI_Matrix4TranslationOptions_Dispose(options);
        return true;
    }

    bool ImageMatrix::Scale(const ScaleOptions &scale) 
    {
        ArkUI_Matrix4ScaleOptions *options = OH_ArkUI_Matrix4ScaleOptions_Create();
        auto code = OH_ArkUI_Matrix4ScaleOptions_SetX(options, scale.x);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4ScaleOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "scale set x failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4ScaleOptions_SetY(options, scale.y);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4ScaleOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "scale set y failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4ScaleOptions_SetZ(options, scale.z);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4ScaleOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "scale set z failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4ScaleOptions_SetCenterX(options, scale.centerX);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4ScaleOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "scale set centerX failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4ScaleOptions_SetCenterY(options, scale.centerY);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4ScaleOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "scale set centerY failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4_Scale(matrix4_, options);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4ScaleOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "matrix scale failed, code = %{public}d", code);
            return false;
        }
        OH_ArkUI_Matrix4ScaleOptions_Dispose(options);
        return true;
    }

    bool ImageMatrix::Rotate(const RotateOptions &rotate) 
    {
        ArkUI_Matrix4RotationOptions *options = OH_ArkUI_Matrix4RotationOptions_Create();
        auto code = OH_ArkUI_Matrix4RotationOptions_SetX(options, rotate.x);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4RotationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "rotate set x failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4RotationOptions_SetY(options, rotate.y);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4RotationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "rotate set y failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4RotationOptions_SetZ(options, rotate.z);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4RotationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "rotate set z failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4RotationOptions_SetCenterX(options, rotate.centerX);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4RotationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "rotate set centerX failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4RotationOptions_SetCenterY(options, rotate.centerY);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4RotationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "rotate set centerY failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4RotationOptions_SetAngle(options, rotate.angle);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4RotationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "rotate set angle failed, code = %{public}d", code);
            return false;
        }
        code = OH_ArkUI_Matrix4_Rotate(matrix4_, options);
        if (code != ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR) {
            OH_ArkUI_Matrix4RotationOptions_Dispose(options);
            OH_LOG_ERROR(LogType::LOG_APP, "matrix rotate failed, code = %{public}d", code);
            return false;
        }
        OH_ArkUI_Matrix4RotationOptions_Dispose(options);
        return true;
    }

    std::string ImageMatrix::ToString() 
    {
        std::string result;
        result.append("[");
        if (!matrix_.empty()) {
            for (auto i: matrix_) {
                result.append(std::to_string(i));
                result.append(" ");
            }
        }
        if (matrix4_) {
            const int LEN = 16;
            float results[LEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            OH_ArkUI_Matrix4_GetElements(matrix4_, results);
            for (int i = 0; i < LEN; i++) {
                result.append(std::to_string(results[i]));
                result.append(" ");
            }
        }
        result.append("]");
        result.append(" ");
    }
} // namespace Self::UI
