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

#include "video_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_model_static.h"
#if defined(PIXEL_MAP_SUPPORTED)
#include "pixel_map.h"
#include "base/image/pixel_map.h"
#endif

namespace OHOS::Ace::NG {

void SetVideoPixelMap(ArkUINodeHandle node, void* pixelMap)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pixelMap);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMapRef = PixelMap::CreatePixelMap(pixelMap);
    VideoModelStatic::SetPosterSourceByPixelMap(frameNode, pixelMapRef);
#endif
}

const ArkUIAniVideoModifier* GetVideoAniModifier()
{
    static const ArkUIAniVideoModifier impl = { .setPixelMap = OHOS::Ace::NG::SetVideoPixelMap };
    return &impl;
}

} // namespace OHOS::Ace::NG
