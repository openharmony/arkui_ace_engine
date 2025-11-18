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
#ifndef CAPIDEMO_ARKUI_IMAGE_H
#define CAPIDEMO_ARKUI_IMAGE_H

#include <string>

#include "arkui_node.h"
#include "drawable_descriptor.h"
#include "image_source.h"

namespace NativeModule {

class ArkUIImageNode : public ArkUINode {
public:
    ArkUIImageNode() : ArkUINode(NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_IMAGE))
    {}

    void SetSrc(const std::string& src)
    {
        assert(handle_);
        ArkUI_AttributeItem item = { nullptr, 0, src.c_str() };
        nativeModule_->setAttribute(handle_, NODE_IMAGE_SRC, &item);
    }

    void SetDrawableDescriptor(const std::shared_ptr<DrawableDescriptor>& drawable)
    {
        assert(handle_);
        ArkUI_AttributeItem item = { .object = drawable->GetNativePointer() };
        nativeModule_->setAttribute(handle_, NODE_IMAGE_SRC, &item);
    }

    void SetObjectFit(ArkUI_ObjectFit fit)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .i32 = fit } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_IMAGE_OBJECT_FIT, &item);
    }

    void SetImageRepeat(ArkUI_ImageRepeat repeat)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .i32 = repeat } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_IMAGE_OBJECT_REPEAT, &item);
    }

    void SetImageSourceSize(std::pair<int32_t, int32_t> size)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .i32 = size.first }, { .i32 = size.second } };
        ArkUI_AttributeItem item = { value, 2 };
        nativeModule_->setAttribute(handle_, NODE_IMAGE_SOURCE_SIZE, &item);
    }

    void SetImageMatrix(std::vector<float> matrix)
    {
        assert(handle_);
        if (matrix.size() < 16) {
            return;
        }
        ArkUI_NumberValue value[] = { { .f32 = matrix[0] }, { .f32 = matrix[1] }, { .f32 = matrix[2] },
            { .f32 = matrix[3] }, { .f32 = matrix[4] }, { .f32 = matrix[5] }, { .f32 = matrix[6] },
            { .f32 = matrix[7] }, { .f32 = matrix[8] }, { .f32 = matrix[9] }, { .f32 = matrix[10] },
            { .f32 = matrix[11] }, { .f32 = matrix[12] }, { .f32 = matrix[13] }, { .f32 = matrix[14] },
            { .f32 = matrix[15] } };
        ArkUI_AttributeItem item = { value, 16 };
        nativeModule_->setAttribute(handle_, NODE_IMAGE_IMAGE_MATRIX, &item);
    }

    void SetMatchTextDirection(bool isMatch)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .i32 = static_cast<int32_t>(isMatch) } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_IMAGE_MATCH_TEXT_DIRECTION, &item);
    }
};
} // namespace NativeModule

#endif // CAPIDEMO_ARKUI_IMAGE_H
