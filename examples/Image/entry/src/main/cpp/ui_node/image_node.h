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

#ifndef CAPI_IMAGE_NODE_H
#define CAPI_IMAGE_NODE_H

#include <string>

#include "image/drawable_descriptor.h"
#include "image/image_matrix.h"
#include "image/resizable_params.h"
#include "ui_node/ui_node.h"
#include "utils/self_enums.h"

namespace Self::UI {
    class ImageNode : public UINode {
    public:
        ImageNode() 
            : UINode(NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_IMAGE), "Image") {}

        void SetSrc(const std::string &src);

        void SetSrc(const std::shard_ptr<DrawableDescriptor> &drawable);

        void SetResizableParams(const std::shared_ptr<ResizableParams> &resizable);

        void SetImageMatrix(const std::shared_ptr<ImageMatrix> &matrix);

        void SetImageFit(ImageFit fit);
    
    private:
        std::shared_ptr<ResizableParams> resizableParams_;

        ArkUI_ObjectFit ConvertObjectFit(ImageFit fit);
    }
} // namespace Self::UI

#endif // CAPI_IMAGE_NODE_H