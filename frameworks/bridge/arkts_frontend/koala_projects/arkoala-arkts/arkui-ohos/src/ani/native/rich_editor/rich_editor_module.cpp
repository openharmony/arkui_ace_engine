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
 
#include "rich_editor_module.h"
 
#include "load.h"
#include "pixel_map_taihe_ani.h"
#include "utils/convert_utils.h"
#include "log/log.h"
#include "base/image/pixel_map.h"
 
namespace OHOS::Ace::Ani {
ani_long RichEditorTransferPixelMap(ani_env* env, [[maybe_unused]]ani_object aniClass, ani_object pixelMapObj)
{
    ani_long nativeObj {};
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getRichEditorAniModifier() || !env) {
        return nativeObj;
    }
    auto pixelMap = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    auto pixelMapPtr = reinterpret_cast<void*>(&pixelMap);
    return modifier->getRichEditorAniModifier()->transferPixelMap(pixelMapPtr);
}
} // namespace OHOS::Ace::Ani