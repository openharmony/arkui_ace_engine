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

#include "image_ani_modifier.h"

#include "base/image/drawing_lattice.h"
#include "base/image/pixel_map.h"
#include "base/image/drawing_color_filter.h"
#include "base/log/log.h"
#include "core/components_ng/pattern/image/image_model_static.h"

namespace OHOS::Ace::NG {

void SetPixelMap(ArkUINodeHandle node, void* pixelMap)
{
    auto pixelMapRef = PixelMap::CreatePixelMap(pixelMap);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    ImageModelStatic::SetPixelMap(frameNode, pixelMapRef);
}

void SetDrawableDescriptor(ArkUINodeHandle node, void* drawableDescriptor, int type)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    ImageModelStatic::SetDrawableDescriptor(frameNode, drawableDescriptor, type);
}

void SetResizableLattice(ArkUINodeHandle node, void* aniLattice)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    auto lattice = DrawingLattice::CreateDrawingLatticeFromNative(aniLattice);
    ImageModelStatic::SetResizableLattice(frameNode, lattice);
}

void SetDrawingColorFilter(ArkUINodeHandle node, void* aniColorFilter)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    auto colorFilter = DrawingColorFilter::CreateDrawingColorFilterFromNative(aniColorFilter);
    ImageModelStatic::SetDrawingColorFilter(frameNode, colorFilter);
}

const ArkUIAniImageModifier* GetImageAniModifier()
{
    static const ArkUIAniImageModifier impl = {
        .setPixelMap = OHOS::Ace::NG::SetPixelMap,
        .setDrawableDescriptor = OHOS::Ace::NG::SetDrawableDescriptor,
        .setResizableLattice = OHOS::Ace::NG::SetResizableLattice,
        .setDrawingColorFilter = OHOS::Ace::NG::SetDrawingColorFilter,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG