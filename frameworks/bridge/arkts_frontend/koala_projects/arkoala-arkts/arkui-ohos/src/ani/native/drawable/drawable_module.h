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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DRAWABLE_MODULE_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DRAWABLE_MODULE_H

#include "ani.h"

namespace OHOS::Ace::Ani {
void DrawableCreatePixelMapDrawable(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni, ani_object pixelAni);
void DrawableCreateLayeredDrawable(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_object foregroundAni, ani_object backgroundAni, ani_object maskAni);
void DrawableCreateAnimatedDrawable(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_array pixelmapsAni, ani_object optionsAni);
void DrawableCreateAnimatedDrawableByResource(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_long resourceObjectKPointer, ani_object optionsAni);
void DrawableCreateAnimatedDrawableByString(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_string resource, ani_object optionsAni);
ani_object DrawableCreatePixelMap(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni);
ani_object DrawableCreateForeground(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni);
ani_object DrawableCreateBackground(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni);
ani_object DrawableCreateMask(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni);
ani_string DrawableGetMaskClipPath(ani_env* env);
ani_object DrawableLoadSync(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni);
ani_object DrawableLoad(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni);
ani_object DrawableGetAnimationController(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object AnimatedDrawable, [[maybe_unused]] ani_string id);
void DrawableSetBlendMode(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni, ani_enum_item blendMode);
ani_object DrawableNativeTransferStatic(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object input, ani_string typeName);
void DrawableDestructDrawable([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_class aniClass, ani_long pointer);
void DrawableAnimationControllerStart(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController);
void DrawableAnimationControllerStop(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController);
void DrawableAnimationControllerPause(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController);
void DrawableAnimationControllerResume(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController);
ani_enum_item DrawableAnimationControllerGetStatus(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DRAWABLE_MODULE_H
