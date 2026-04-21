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

#ifndef CAPI_DRAWABLE_DESCRIPTOR_H
#define CAPI_DRAWABLE_DESCRIPTOR_H

#include <memory>

#include "image/pixel_map.h"
#include <napi/native_api.h>
#include <arkui/drawable_descriptor.h>

namespace Self::UI {
    class DrawableDescriptor {
    public:
        enum class DrawableType { PIXELMAP = 0, ANIMATED = 1, LAYERED = 2};

        explicit DrawableDescriptor(ArkUI_DrawableDescriptor *drawable) { drawable_ = drawable; }

        ~DrawableDescriptor() 
        {
            if (drawable_) {
                OH_ArkUI_DrawableDescriptor_Dispose(drawable_);
            }
        }

        static std::shared_ptr<DrawableDescriptor> CreateFromNapiValue(napi_env env, napi_value value);
        static std::shared_ptr<DrawableDescriptor> CreateFromResource(napi_env env, napi_value value);
        static std::shared_ptr<DrawableDescriptor> 
            CreateAnimatedDrawable(const std::vector<std::shared_ptr<PixelMap>> &pixelMaps);

        ArkUI_DrawableDescriptor *GetNativePointer() { return drawable_; }

        void SetIteration(int32_t iteration);

        void SetTotalDuration(int32_t totalDuration);

        int32_t GetIterations() { return iterations_; }

        int32_t GetTotalDuration() { return totalDuration_; }

    private:
        static std::vector<OH_PixelmapNative *>
            ConvertVectorToArray(const std::vector<std::shared_ptr<PixelMap>> &pixelMaps);

        int32_t totalDuration_ = -1;
        int32_t iterations_ = 1;
        DrawableType type_;
        ArkUI_DrawableDescriptor *drawable_;
    };
} // namespace Self::UI

#endif // CAPI_DRAWABLE_DESCRIPTOR_H
