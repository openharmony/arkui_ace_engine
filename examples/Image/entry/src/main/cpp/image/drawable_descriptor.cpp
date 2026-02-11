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

#include "image/drawable_descriptor.h"

#include <memory>

#include <arkui/native_node_napi.h>
#include <vector>
#include "utils/log.h"

namespace Self::UI {
    std::shared_ptr<DrawableDescriptor> DrawableDescriptor::CreateFromNapiValue(napi_env env, napi_value value) 
    {
        ArkUI_DrawableDescriptor *drawableNative;
        auto code = OH_ArkUI_GetDrawableDescriptorFromNapiValue(env, value, &drawableNative);
        if (code != 0) {
            OH_LOG_ERROR(LogType::LOG_APP, "drawable descriptor create from napi value filed");
            return nullptr;
        }
        auto drawable = std::make_shared<DrawableDescriptor>(drawableNative);
        return drawable;
    }

    std::shared_ptr<DrawableDescriptor> DrawableDescriptor::CreateFromResource(napi_env env, napi_value value) 
    {
        ArkUI_DrawableDescriptor *drawableNative;
        auto code = OH_ArkUI_GetDrawableDescriptorFromResourceNapiValue(env, value, &drawableNative);
        if (code != 0) {
            OH_LOG_ERROR(LogType::LOG_APP, "drawable descriptor create from resource value filed");
            return nullptr;
        }
        auto drawable = std::make_shared<DrawableDescriptor>(drawableNative);
        return drawable;
    }

    std::shared_ptr<DrawableDescriptor>
    DrawableDescriptor::CreateAnimatedDrawable(const std::vector<std::shared_ptr<PixelMap>> &pixelMaps) 
    {
        ArkUI_DrawableDescriptor *drawableNative;
        auto natives = ConvertVectorToArray(pixelMaps);
        auto code = OH_ArkUI_DrawableDescriptor_CreateFromAnimatedPixelMap(natives.data(), natives.size());
        if (code != 0) {
            OH_LOG_ERROR(LogType::LOG_APP, "drawable descriptor create from pixel filed");
            return nullptr;
        }
        auto drawable = std::make_shared<DrawableDescriptor>(drawableNative);
        drawable->type_ = DrawableType::ANIMATED;
        return drawable;
    }

    std::vector<OH_PixelmapNative *>
    DrawableDescriptor::ConvertVectorToArray(const std::vector<std::shared_ptr<PixelMap>> &pixelMaps) 
    {
        std::vector<OH_PixelmapNative *> natives;
        for (int32_t i = 0; i < pixelMaps.size(); i++) {
            natives.push_back(pixelMaps[i]->GetNativePointer());
        }
        return natives;
    }

    void DrawableDescriptor::SetIteration(int32_t iteration) 
    {
        if (type_ != DrawableType::ANIMATED || !drawable_) {
            return;
        }
        OH_ArkUI_DrawableDescriptor_SetAnimationDuration(drawable_, iteration);
        iterations_ = iteration;
    }

    void DrawableDescriptor::SetTotalDuration(int32_t totalDuration) 
    {
        if (type_ != DrawableType::ANIMATED || !drawable_) {
            return;
        }
        OH_ArkUI_DrawableDescriptor_SetAnimationIteration(drawable_, totalDuration);
        totalDuration_ = totalDuration;
    }
} // namespace Self::UI
