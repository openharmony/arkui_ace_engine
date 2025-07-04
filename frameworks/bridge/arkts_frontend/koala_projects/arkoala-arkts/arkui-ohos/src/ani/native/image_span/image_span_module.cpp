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

#include "image_span_module.h"

#include "load.h"
#include "pixel_map_taihe_ani.h"
#include "utils/convert_utils.h"

namespace OHOS::Ace::Ani {

void SetImageSpanPixelMap([[maybe_unused]] ani_env* env, ani_object aniClass, ani_object node, ani_object pixelMapAni)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getImageSpanAniModifier() || !env) {
        return;
    }
    // only pass pointer to smart pointer, and do not operate on C pointer
    auto pixelMap = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapAni);
    modifier->getImageSpanAniModifier()->setPixelMap(arkNode, &pixelMap);
}

void SetImageSpanAltPixelMap([[maybe_unused]] ani_env* env, ani_object aniClass, ani_object node,
    ani_object pixelMapAni)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getImageSpanAniModifier() || !env) {
        return;
    }
    // only pass pointer to smart pointer, and do not operate on C pointer
    auto pixelMap = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapAni);
    modifier->getImageSpanAniModifier()->setAltPixelMap(arkNode, &pixelMap);
}
} // namespace OHOS::Ace::Ani
