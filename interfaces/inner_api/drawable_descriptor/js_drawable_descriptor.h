/*
 * Copyright (C) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_INNER_API_DRAWABLE_DESCRIPTOR_NEW_JS_DRAWABLE_DESCRIPTOR_H
#define INTERFACES_INNER_API_DRAWABLE_DESCRIPTOR_NEW_JS_DRAWABLE_DESCRIPTOR_H

#include "drawable_descriptor.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/marcos.h"

namespace OHOS {
namespace Ace {
namespace Napi {
class JsDrawableDescriptor {
public:
    static DRAWABLE_FORCE_EXPORT napi_value Export(napi_env env, napi_value exports);

    static DRAWABLE_FORCE_EXPORT napi_value ToNapi(napi_env, DrawableDescriptor*,
        DrawableDescriptor::DrawableType type = DrawableDescriptor::DrawableType::LAYERED);

    static DRAWABLE_FORCE_EXPORT constexpr char MODULE_NAME[] = "arkui.drawableDescriptor";

private:
    struct AnimationOptions {
        int32_t duration = -1;
        int32_t iterations = 1;
        bool autoPlay = true;
        std::vector<int32_t> durations;
    };

    static napi_value InitDrawable(napi_env env);
    static napi_value InitLayeredDrawable(napi_env env);
    static napi_value InitAnimatedDrawable(napi_env env);
    static napi_value InitPixelMapDrawable(napi_env env);
    static void ParseAnimationOptions(napi_env env, napi_value napiOptions, AnimationOptions& options);
    static napi_value DrawableConstructor(napi_env env, napi_callback_info info);
    static napi_value AnimatedConstructor(napi_env env, napi_callback_info info);
    static napi_value PixelMapConstructor(napi_env env, napi_callback_info info);
    static napi_value LayeredConstructor(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void* nativeObject, void* finalize);
    static void NewDestructor(napi_env env, void* nativeObject, void* finalize);

    // drawable descriptor and pixel map drawable descriptor methods
    static napi_value GetPixelMap(napi_env env, napi_callback_info info);
    static napi_value CreateLoadResult(napi_env env, int32_t width, int32_t height);
    static napi_value Load(napi_env env, napi_callback_info info);
    static void LoadExecute(napi_env env, void* data);
    static void LoadComplete(napi_env env, napi_status status, void* data);
    static napi_value LoadSync(napi_env env, napi_callback_info info);

    // animated drawable descriptor methods
    static napi_value GetAnimationController(napi_env env, napi_callback_info info);
    static napi_value GetStatus(napi_env env, napi_callback_info info);
    static napi_value Start(napi_env env, napi_callback_info info);
    static napi_value Stop(napi_env env, napi_callback_info info);
    static napi_value Pause(napi_env env, napi_callback_info info);
    static napi_value Resume(napi_env env, napi_callback_info info);

    // layered drawable descriptor methods
    static napi_value GetForeground(napi_env env, napi_callback_info info);
    static napi_value GetBackground(napi_env env, napi_callback_info info);
    static napi_value GetMask(napi_env env, napi_callback_info info);
    static napi_value GetMaskClipPath(napi_env env, napi_callback_info info);

    static thread_local napi_ref baseConstructor_;
    static thread_local napi_ref layeredConstructor_;
    static thread_local napi_ref animatedConstructor_;
    static thread_local napi_ref pixelMapConstructor_;
};
} // namespace Napi
} // namespace Ace
} // namespace OHOS
#endif // INTERFACES_INNER_API_DRAWABLE_DESCRIPTOR_NEW_JS_DRAWABLE_DESCRIPTOR_H
