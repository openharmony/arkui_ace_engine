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

#include "ui_node/image_node.h"

namespace Self::UI {
    void ImageNode::SetSrc(const std::string &src) 
    {
        assert(handle_);
        ArkUI_AttributeItem item = {nullptr, 0, src.c_str()};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_SRC, &item);
    }

    void ImageNode::SetSrc(const std::shared_ptr<DrawableDescriptor> &drawable) 
    {
        assert(handle_);
        if (drawable) {
            ArkUI_AttributeItem item = {.object = drawable->GetNativePointer()};
            nativeModule_->setAttribute(handle_, NODE_IMAGE_SRC, &item);
        }
    }

    void ImageNode::SetResizableParams(const std::shared_ptr<ResizableParams> &resizable) 
    {
        assert(handle_);
        auto type = resizable->GetType();
        resizableParams_ = resizable;
        ArkUI_AttributeItem item;
        if (type == ResizableType::SLICE) {
            auto slice = resizable->GetSlice();
            OH_LOG_INFO(LogType::LOG_APP, "slice is %{public}s", slice.ToString().c_str());
            ArkUI_NumberValue values[] = {
                {.f32 = (slice.left)}, {.f32 = (slice.top)}, {.f32 = (slice.right)}, {.f32 = (slice.bottom)}};
            item = {.value = values, .size = sizeof(ArkUI_NumberValue)};
        }
        if (type == ResizableType::LATTICE) {
            auto latticeV = resizable->GetLatticeV();
            OH_LOG_INFO(LogType::LOG_APP, "lattice is %{public}s", latticeV.ToString().c_str());
            item = {.object = resizable->GetLattice()};
        }
        nativeModule_->setAttribute(handle_, NODE_IMAGE_RESIZABLE, &item);
    }

    void ImageNode::SetImageMatrix(const std::shared_ptr<ImageMatrix> &matrix) 
    {
        assert(handle_);
        ArkUI_AttributeItem item;
        if (matrix->IsVector()) {
            auto vec = matrix->GetMatrix();
            const int LEN = 16;
            if (vec.size() < LEN) {
                OH_LOG_ERROR(LogType::LOG_APP, "set image matrix failed, vec size small than sixteen");
                return;
            }
            SetImageFit(ImageFit::MATRIX);
            ArkUI_NumberValue value[] = {{.f32 = vec[0]}, {.f32 = vec[1]}, {.f32 = vec[2]}, {.f32 = vec[3]},
                                         {.f32 = vec[4]}, {.f32 = vec[5]}, {.f32 = vec[6]}, {.f32 = vec[7]},
                                         {.f32 = vec[8]}, {.f32 = vec[9]}, {.f32 = vec[10]}, {.f32 = vec[11]},
                                         {.f32 = vec[12]}, {.f32 = vec[13]}, {.f32 = vec[14]}, {.f32 = vec[15]}};
            item = {.value = value, .size = sizeof(value) / sizeof(ArkUI_NumberValue)};
            nativeModule_->setAttribute(handle_, NODE_IMAGE_IMAGE_MATRIX, &item);
        } else {
            item = {.object = matrix->GetMatrix4()};
            SetImageFit(ImageFit::MATRIX);
            nativeModule_->setAttribute(handle_, NODE_IMAGE_IMAGE_MATRIX, &item);
        }
    }

    void ImageNode::SetImageFit(ImageFit fit) 
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{.i32 = ConvertObjectFit(fit)}};
        ArkUI_AttributeItem item = {.value = value, .size = 1};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_OGJECT_FIT, &item);
    }

    ArkUI_ObjectFit ImageNode::ConvertObjectFit(ImageFit fit) 
    {
        switch(fit) {
            case ImageFit::COVER:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_COVER;
            case ImageFit::CONTAIN:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_CONTAIN;
            case ImageFit::MATRIX:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_MATRIX;
            case ImageFit::NONE:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_NONE;
            default:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_COVER;
        }
    }
} // namespace Self::UI
