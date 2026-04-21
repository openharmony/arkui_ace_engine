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

#ifndef CAPI_IMAGE_MATRIX_H
#define CAPI_IMAGE_MATRIX_H

#include "arkui/native_type.h"
#include <vector>
#include <string>

namespace Self::UI {
    struct TranslateOptions {
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
    };
    struct ScaleOptions {
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        float centerX = 0.0;
        float centerY = 0.0;
    };
    struct RotateOptions {
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        float centerX = 0.0;
        float centerY = 0.0;
        float angle = 0.0;
    };
    struct TransformOption {
        TranslateOptions translate;
        ScaleOptions scale;
        RotateOptions rotate;
        bool hasTrans = false;
        bool hasScale = false;
        bool hasRotate = false;
    };
    class ImageMatrix {
    public:
        explicit ImageMatrix(ArkUI_Matrix4 *matrix) : matrix4_(matrix), type_(0) {}
        explicit ImageMatrix(const std::vector<float> &matrix) : matrix_(matrix), type_(1) {}
        ~ImageMatrix() = default;

        static std::shared_ptr<ImageMatrix> Identity();

        bool Translate(const TranslateOptions &translate);

        bool Scale(const ScaleOptions &scale);
        
        bool Rotate(const RotateOptions &rotate);

        bool IsVector() { return type_ == 1; }

        ArkUI_Matrix4 *GetMatrix4() { return matrix4_; }

        std::vector<float> GetMatrix() {return matrix_; }

        std::string ToString();

    private:
        ImageMatrix() = default;

        int32_t type_ = 0;
        std::vector<float> matrix_;
        ArkUI_Matrix4 *matrix4_;
    };   
} // namespace Self::UI
#endif // CAPI_IMAGE_MATRIX_H