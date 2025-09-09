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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_IMAGE_NATIVE_IMAGE_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_IMAGE_NATIVE_IMAGE_H

#include "ani.h"

namespace OHOS::Ace::Ani {
void ImageResizableOptions(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object latticeAni);
void ImageConstructPixelMap(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object pixelMapAni);
void ImageConstructDrawableDescriptor(
    ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object drawableAni, ani_int drawableType);
void ImageDrawingColorFilter(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object latticeAni);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_IMAGE_NATIVE_IMAGE_H
