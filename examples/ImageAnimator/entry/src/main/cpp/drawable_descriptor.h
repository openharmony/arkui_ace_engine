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
//
// Created on 2025/9/19.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CAPIDEMO_DRAWABLE_DESCRIPTOR_H
#define CAPIDEMO_DRAWABLE_DESCRIPTOR_H

#include <arkui/drawable_descriptor.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <memory>

#include "image_source.h"
#include "log.h"
#include "pixel_map.h"

struct AnimationParams {
    int32_t duration;
    int32_t iteration;
};

class DrawableDescriptor {
public:
    explicit DrawableDescriptor(ArkUI_DrawableDescriptor* drawable)
    {
        drawable_ = drawable;
    }

    ~DrawableDescriptor()
    {
        if (drawable_) {
            OH_ArkUI_DrawableDescriptor_Dispose(drawable_);
        }
    }

    static std::shared_ptr<DrawableDescriptor> CreateFromPixelMap(const std::shared_ptr<PixelMap>& pixelMap)
    {
        auto drawableNative = OH_ArkUI_DrawableDescriptor_CreateFromPixelMap(pixelMap->GetNativePixelMap());
        if (!drawableNative) {
            OH_LOG_ERROR(LogType::LOG_APP, "Test arkui drawable descriptor create from pixelmap failed.");
            return nullptr;
        }
        auto drawable = std::make_shared<DrawableDescriptor>(drawableNative);
        return drawable;
    }

    static std::shared_ptr<DrawableDescriptor> CreateFromPixelMapArray(PixelMaps maps, AnimationParams params)
    {
        auto drawableNative = OH_ArkUI_DrawableDescriptor_CreateFromAnimatedPixelMap(maps.pixelMaps, maps.size);
        if (!drawableNative) {
            OH_LOG_ERROR(LogType::LOG_APP, "Test arkui drawable descriptor create from pixelmap array failed.");
            return nullptr;
        }
        OH_ArkUI_DrawableDescriptor_SetAnimationDuration(drawableNative, params.duration);
        OH_ArkUI_DrawableDescriptor_SetAnimationIteration(drawableNative, params.iteration);
        auto drawable = std::make_shared<DrawableDescriptor>(drawableNative);
        return drawable;
    }

    static std::shared_ptr<DrawableDescriptor> CreateFromNapiValue(napi_env env, napi_value value)
    {
        ArkUI_DrawableDescriptor* drawableNative;
        auto code = OH_ArkUI_GetDrawableDescriptorFromNapiValue(env, value, &drawableNative);
        if (code != 0) {
            OH_LOG_ERROR(LogType::LOG_APP, "Test arkui drawable descriptor create from napi value failed.");
            return nullptr;
        }
        auto drawable = std::make_shared<DrawableDescriptor>(drawableNative);
        return drawable;
    }

    ArkUI_DrawableDescriptor* GetNativePointer()
    {
        return drawable_;
    }

private:
    DrawableDescriptor() = default;

    ArkUI_DrawableDescriptor* drawable_;
};

#endif // CAPIDEMO_DRAWABLE_DESCRIPTOR_H
