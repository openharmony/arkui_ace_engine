/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef MYAPPLICATION_ARKUIIMAGENODE_H
#define MYAPPLICATION_ARKUIIMAGENODE_H

#include "native_drawing/drawing_types.h"
#include "native_drawing/drawing_lattice.h"

#include "ArkUINode.h"

#include "image/image_matrix.h"

#include <string>

namespace NativeModule {

enum class ImageFit { COVER = 0, CONTAIN = 1, MATRIX = 2, NONE = 3};

class ArkUIImageNode : public ArkUINode {
public:
    ArkUIImageNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_IMAGE)){}
    
    void SetSrc(const std::string &src)
    {
        ArkUI_AttributeItem item;
        item = {nullptr, 0, src.c_str()};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_SRC, &item);
    }
    
    void SetSlice(ArkUI_NumberValue values[])
    {
        ArkUI_AttributeItem item;
        item = {.value = values, .size = 4};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_RESIZABLE, &item);
    }
    
    void SetLattice(OH_Drawing_Lattice *lattice)
    {
        ArkUI_AttributeItem item;
        item = {.object = lattice};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_RESIZABLE, &item);
    }
    
    void SetObjectFit(ArkUI_ObjectFit objectFit)
    {
        ArkUI_NumberValue values[] = {{.i32 = objectFit}};
        ArkUI_AttributeItem item;
        item = {.value = values, .size = 1};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_OBJECT_FIT, &item);
    }
    
    void SetOrientation(ArkUI_ImageRotateOrientation orientation)
    {
        ArkUI_NumberValue values[] = {{.i32 = orientation}};
        ArkUI_AttributeItem item;
        item = {.value = values, .size = 1};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_ORIENTATION, &item);
    }
    
    void SetObjectRepeat(ArkUI_ImageRepeat repeat)
    {
        ArkUI_NumberValue values[] = {{.i32 = repeat}};
        ArkUI_AttributeItem item;
        item = {.value = values, .size = 1};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_OBJECT_REPEAT, &item);
    }
    
    void SetAntialiased(bool flag)
    {
        ArkUI_NumberValue values[] = {{.i32 = flag}};
        ArkUI_AttributeItem item;
        item = {.value = values, .size = 1};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_ANTIALIASED, &item);
    }
    
    void SetImageMatrix(const std::shared_ptr<ImageMatrix> &matrix) 
    {
        ArkUI_AttributeItem item;
        if (matrix->IsVector()) {
            auto vec = matrix->GetMatrix();
            if (vec.size() < 16) {
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
    
    void SetImageFit(ImageFit fit) 
    {
        ArkUI_NumberValue value[] = {{.i32 = ConvertObjectFit(fit)}};
        ArkUI_AttributeItem item = {.value = value, .size = 1};
        nativeModule_->setAttribute(handle_, NODE_IMAGE_OBJECT_FIT, &item);
    }

    ArkUI_ObjectFit ConvertObjectFit(ImageFit fit) 
    {
        switch(fit) {
            case ImageFit::COVER:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_COVER;
            case ImageFit::CONTAIN:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_CONTAIN;
            case ImageFit::MATRIX:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_NONE_MATRIX;
            case ImageFit::NONE:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_NONE;
            default:
                return ArkUI_ObjectFit::ARKUI_OBJECT_FIT_COVER;
        }
    }
};
}
#endif