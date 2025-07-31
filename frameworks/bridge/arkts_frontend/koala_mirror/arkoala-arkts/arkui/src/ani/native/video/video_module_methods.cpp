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

#include "video_module_methods.h"

#include "base/utils/utils.h"
#include "pixel_map_taihe_ani.h"
#include "load.h"

namespace OHOS::Ace::Ani {

void SetVideoPixelMap(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object node, ani_object pixelMap)
{
    CHECK_NULL_VOID(env);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto videoModifier = modifier->getArkUIAniVideoModifier();
    CHECK_NULL_VOID(videoModifier);
    auto pixelMapValue = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMap);
    videoModifier->setPixelMap(arkNode, reinterpret_cast<void*>(&pixelMapValue));
}

} // namespace OHOS::Ace::Ani
