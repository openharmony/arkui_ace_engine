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
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_model_static.h"
#include "core/drawable/drawable_descriptor.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/drawing_color_filter_peer.h"
#include "core/interfaces/native/implementation/drawing_lattice_peer.h"

namespace OHOS::Ace::NG {

void SetPixelMap(ArkUINodeHandle node, void* pixelMap)
{
    auto pixelMapRef = PixelMap::CreatePixelMap(pixelMap);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    ImageModelStatic::SetPixelMap(frameNode, pixelMapRef);
}

void SetDrawableDescriptor(ArkUINodeHandle node, void* drawableDescriptor)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    ImageModelStatic::SetDrawableDescriptor(frameNode, static_cast<DrawableDescriptor*>(drawableDescriptor));
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

void* GetPixelMapPeer(void* pixelMapPtr)
{
    return reinterpret_cast<void*>(image_PixelMapPeer::Create(PixelMap::CreatePixelMap(pixelMapPtr)));
}

ani_long CreateColorFilterPeer(ani_long colorFilter)
{
    CHECK_EQUAL_RETURN(colorFilter, 0, 0);
    auto* rawPtr = reinterpret_cast<OHOS::Ace::ImageColorFilter*>(colorFilter);
    auto imageColorFilter = Referenced::Claim<OHOS::Ace::ImageColorFilter>(rawPtr);
    if (!imageColorFilter) {
        return 0;
    }
    auto* peer = new ColorFilterPeer();
    CHECK_NULL_RETURN(peer, 0);
    peer->SetColorFilter(imageColorFilter);
    auto pointer = reinterpret_cast<ani_long>(peer);
    return pointer;
}

ani_long GetColorFilter(ani_long colorFilterPeer)
{
    if (colorFilterPeer == 0) {
        return 0;
    }
    auto* peer = reinterpret_cast<ColorFilterPeer*>(colorFilterPeer);
    auto imageColorFilter = peer->GetColorFilter();
    if (!imageColorFilter) {
        return 0;
    }
    auto* rawPtr = Referenced::RawPtr(imageColorFilter);
    auto pointer = reinterpret_cast<ani_long>(rawPtr);
    return pointer;
}

void* GetDrawingColorFilterPeer(void* colorFilterMapPtr)
{
    return reinterpret_cast<void*>(drawing_ColorFilterPeer::Create(colorFilterMapPtr));
}

void* GetDrawingLatticePeer(void* drawingLatticePeerPtr)
{
    return reinterpret_cast<void*>(drawing_LatticePeer::Create(drawingLatticePeerPtr));
}

void SetImageOnErrorCallback(
    ArkUINodeHandle node, std::function<void(const ArkUIAniImageOnErrorParams &param)>&& callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!callback) {
        ImageModelNG::SetOnError(frameNode, nullptr);
        return;
    }
    std::function<void(const ArkUIAniImageOnErrorParams &param)>
        callbackFun = std::move(callback);
    std::function<void(const LoadImageFailEvent& info)> onErrorCallbackFun = [callbackFun](
                                                                                 const LoadImageFailEvent& info) {
        if (!callbackFun) {
            return;
        }
        ArkUIAniImageOnErrorParams params;
        params.errorMessage = info.GetErrorMessage();
        params.componentWidth = static_cast<int32_t>(info.GetComponentWidth());
        params.componentHeight = static_cast<int32_t>(info.GetComponentHeight());
        params.errorCode = static_cast<int32_t>(info.GetErrorInfo().errorCode);
        params.errorInfo = info.GetErrorInfo().errorMessage;
        callbackFun(params);
    };

    ImageModelNG::SetOnError(frameNode, std::move(onErrorCallbackFun));
}

const ArkUIAniImageModifier* GetImageAniModifier()
{
    static const ArkUIAniImageModifier impl = {
        .setPixelMap = OHOS::Ace::NG::SetPixelMap,
        .setDrawableDescriptor = OHOS::Ace::NG::SetDrawableDescriptor,
        .setResizableLattice = OHOS::Ace::NG::SetResizableLattice,
        .setDrawingColorFilter = OHOS::Ace::NG::SetDrawingColorFilter,
        .getPixelMapPeer = OHOS::Ace::NG::GetPixelMapPeer,
        .createColorFilterPeer = OHOS::Ace::NG::CreateColorFilterPeer,
        .getColorFilter = OHOS::Ace::NG::GetColorFilter,
        .getDrawingColorFilterPeer = OHOS::Ace::NG::GetDrawingColorFilterPeer,
        .getDrawingLatticePeer = OHOS::Ace::NG::GetDrawingLatticePeer,
        .setImageOnErrorCallback = OHOS::Ace::NG::SetImageOnErrorCallback,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG