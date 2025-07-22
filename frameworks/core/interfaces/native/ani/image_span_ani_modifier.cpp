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

#include "base/image/drawing_color_filter.h"
#include "base/image/pixel_map.h"
#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_model_static.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/image/image_source_info.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

void SetImageSpanPixelMap(ArkUINodeHandle node, void* pixelMap)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pixelMap);
    auto imageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    ImageSourceInfo sourceInfo(PixelMap::CreatePixelMap(pixelMap));
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    if (sourceInfo.IsPixmap()) {
        const auto& pattern = frameNode->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSyncLoad(true);
    }
}

void SetAltPixelMap(ArkUINodeHandle node, void* pixelmap)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto imageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    if (pixelmap) {
        ImageSourceInfo sourceInfo(PixelMap::CreatePixelMap(pixelmap));
        imageLayoutProperty->UpdateAlt(sourceInfo);
    } else {
        imageLayoutProperty->ResetAlt();
    }
}

void SetImageSpanColorFilter(ArkUINodeHandle node, void* aniColorFilter)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    auto colorFilter = DrawingColorFilter::CreateDrawingColorFilterFromNative(aniColorFilter);
    ImageModelStatic::SetDrawingColorFilter(frameNode, colorFilter);
}

const ArkUIAniImageSpanModifier* GetImageSpanAniModifier()
{
    static const ArkUIAniImageSpanModifier impl = {
        .setPixelMap = OHOS::Ace::NG::SetImageSpanPixelMap,
        .setAltPixelMap = OHOS::Ace::NG::SetAltPixelMap,
        .setDrawingColorFilter = OHOS::Ace::NG::SetImageSpanColorFilter
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
