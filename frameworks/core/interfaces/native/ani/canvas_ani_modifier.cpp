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

#include "canvas_ani_modifier.h"

#include "base/utils/utils.h"
#if defined(PIXEL_MAP_SUPPORTED)
#include "base/image/pixel_map.h"
#endif
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/canvas_renderer_type.h"
#include "core/interfaces/native/implementation/canvas_renderer_peer_impl.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_canvas_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/native/implementation/image_data_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace CanvasAniModifier {

void SetPixelMap(ArkUICanvasRenderer peer, void* pixelMapPtr)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(pixelMapPtr);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapPtr);
    CHECK_NULL_VOID(pixelMap);
    peerImpl->SetPixelMap(pixelMap);
#endif
}

void DrawPixelMap0(ArkUICanvasRenderer peer, void* pixelMapPtr, ani_double dx, ani_double dy)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(pixelMapPtr);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapPtr);
    CHECK_NULL_VOID(pixelMap);
    image_PixelMapPeer* pixelMapPeer = new image_PixelMapPeer();
    pixelMapPeer->pixelMap = pixelMap;
    GeneratedModifier::CanvasRendererPeerImpl::DrawImageParam params = {
        .dx = static_cast<double>(dx),
        .dy = static_cast<double>(dy),
        .size = GeneratedModifier::CanvasRendererPeerImpl::SizeParam::TWO_ARGS,
    };
    peerImpl->DrawPixelMap(pixelMapPeer, params);
#endif
}

void DrawPixelMap1(
    ArkUICanvasRenderer peer, void* pixelMapPtr, ani_double dx, ani_double dy, ani_double dw, ani_double dh)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(pixelMapPtr);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapPtr);
    CHECK_NULL_VOID(pixelMap);
    image_PixelMapPeer* pixelMapPeer = new image_PixelMapPeer();
    pixelMapPeer->pixelMap = pixelMap;
    GeneratedModifier::CanvasRendererPeerImpl::DrawImageParam params = {
        .dx = static_cast<double>(dx),
        .dy = static_cast<double>(dy),
        .dWidth = static_cast<double>(dw),
        .dHeight = static_cast<double>(dh),
        .size = GeneratedModifier::CanvasRendererPeerImpl::SizeParam::FOUR_ARGS,
    };
    peerImpl->DrawPixelMap(pixelMapPeer, params);
#endif
}

void DrawPixelMap2(ArkUICanvasRenderer peer, void* pixelMapPtr, ani_double sx, ani_double sy, ani_double sw,
    ani_double sh, ani_double dx, ani_double dy, ani_double dw, ani_double dh)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(pixelMapPtr);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapPtr);
    CHECK_NULL_VOID(pixelMap);
    image_PixelMapPeer* pixelMapPeer = new image_PixelMapPeer();
    pixelMapPeer->pixelMap = pixelMap;
    GeneratedModifier::CanvasRendererPeerImpl::DrawImageParam params = {
        .sx = static_cast<double>(sx),
        .sy = static_cast<double>(sy),
        .sWidth = static_cast<double>(sw),
        .sHeight = static_cast<double>(sh),
        .dx = static_cast<double>(dx),
        .dy = static_cast<double>(dy),
        .dWidth = static_cast<double>(dw),
        .dHeight = static_cast<double>(dh),
        .size = GeneratedModifier::CanvasRendererPeerImpl::SizeParam::EIGHT_ARGS,
    };
    peerImpl->DrawPixelMap(pixelMapPeer, params);
#endif
}

ArkUIImageBitmap ImageBitmapConstruct(const std::string& str, void* pixelMapPtr, ArkUI_Int32 unit)
{
    auto peer = PeerUtils::CreatePeer<ImageBitmapPeer>();
    if (pixelMapPtr) {
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixelMap = PixelMap::CreatePixelMap(pixelMapPtr);
        CHECK_NULL_RETURN(pixelMap, nullptr);
        peer->SetOptions(str, pixelMap, unit);
#endif
    } else {
        peer->SetOptions(str, nullptr, unit);
    }
    return reinterpret_cast<ArkUIImageBitmap>(peer);
}

ani_double GetCanvasDensity(ArkUICanvasRenderer peer)
{
    CHECK_NULL_RETURN(peer, 1.0);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, 1.0);
    return peerImpl->GetDensity();
}

ani_double GetSystemDensity()
{
    return PipelineBase::GetCurrentDensity();
}

void GetImageData(ArkUICanvasRenderer peer, uint8_t* buffer, ani_double sx, ani_double sy, ani_double sw, ani_double sh)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    ImageSize imageSize = {
        .left = static_cast<double>(sx),
        .top = static_cast<double>(sy),
        .width = static_cast<double>(sw),
        .height = static_cast<double>(sh)
    };
    peerImpl->GetImageData(imageSize, buffer);
}

void CopyFromBuffer(Ace::ImageData& imageData, uint8_t* buffer, size_t bufferLength, int32_t imgWidth)
{
    for (int32_t i = std::max(imageData.dirtyY, 0); i < imageData.dirtyY + imageData.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData.dirtyX, 0); j < imageData.dirtyX + imageData.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufferLength > static_cast<size_t>(idx + 3)) { // idx + 3: The 4th byte format: alpha
                uint8_t alpha = buffer[idx + 3];               // idx + 3: The 4th byte format: alpha
                uint8_t red = buffer[idx];                     // idx: the 1st byte format: red
                uint8_t green = buffer[idx + 1];               // idx + 1: The 2nd byte format: green
                uint8_t blue = buffer[idx + 2];                // idx + 2: The 3rd byte format: blue
                imageData.data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
            }
        }
    }
}

void PutImageData0(ArkUICanvasRenderer peer, uint8_t* buffer, ani_size bufferLength, ani_double dx, ani_double dy,
    ani_int width, ani_int height)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    Ace::ImageData imageData = {
        .x = static_cast<int32_t>(dx),
        .y = static_cast<int32_t>(dy),
        .dirtyWidth = static_cast<int32_t>(width),
        .dirtyHeight = static_cast<int32_t>(height),
        .data = std::vector<uint32_t>(),
    };
    CopyFromBuffer(imageData, buffer, static_cast<size_t>(bufferLength), static_cast<int32_t>(width));
    peerImpl->PutImageData(imageData);
}

void PutImageData1(ArkUICanvasRenderer peer, uint8_t* buffer, ani_size bufferLength, ani_double dx, ani_double dy,
    ani_int width, ani_int height, ani_double dirtyX, ani_double dirtyY, ani_double dirtyWidth, ani_double dirtyHeight)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    Ace::ImageData imageData = {
        .x = static_cast<int32_t>(dx),
        .y = static_cast<int32_t>(dy),
        .dirtyX = static_cast<int32_t>(dirtyX),
        .dirtyY = static_cast<int32_t>(dirtyY),
        .dirtyWidth = static_cast<int32_t>(dirtyWidth),
        .dirtyHeight = static_cast<int32_t>(dirtyHeight),
        .data = std::vector<uint32_t>(),
    };
    auto imgWidth = static_cast<int32_t>(width);
    auto imgHeight = static_cast<int32_t>(height);
    imageData.dirtyWidth = imageData.dirtyX < 0 ? std::min(imageData.dirtyX + imageData.dirtyWidth, imgWidth)
                                                : std::min(imgWidth - imageData.dirtyX, imageData.dirtyWidth);
    imageData.dirtyHeight = imageData.dirtyY < 0 ? std::min(imageData.dirtyY + imageData.dirtyHeight, imgHeight)
                                                 : std::min(imgHeight - imageData.dirtyY, imageData.dirtyHeight);

    CopyFromBuffer(imageData, buffer, static_cast<size_t>(bufferLength), imgWidth);
    peerImpl->PutImageData(imageData);
}

void* GetDrawingCanvas(ArkUIDrawingRenderingContext peer)
{
    auto peerImpl = reinterpret_cast<GeneratedModifier::DrawingRenderingContextPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    auto drawingCanvasPeer = peerImpl->GetCanvas();
    CHECK_NULL_RETURN(drawingCanvasPeer, nullptr);
    return reinterpret_cast<void*>(drawingCanvasPeer->GetCanvas());
}

ani_int GetCanvasId(ArkUICanvasRenderingContext peer)
{
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, -1);
    return peerImpl->GetCanvasId();
}

void SetAttachCallbackId(ArkUICanvasRenderingContext peer, ani_int attachCallbackId)
{
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->SetAttachCallbackId(attachCallbackId);
}

void SetDetachCallbackId(ArkUICanvasRenderingContext peer, ani_int detachCallbackId)
{
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->SetDetachCallbackId(detachCallbackId);
}
} // namespace CanvasAniModifier

const ArkUIAniCanvasModifier* GetCanvasAniModifier()
{
    static const ArkUIAniCanvasModifier impl = { .setPixelMap = CanvasAniModifier::SetPixelMap,
        .drawPixelMap0 = CanvasAniModifier::DrawPixelMap0,
        .drawPixelMap1 = CanvasAniModifier::DrawPixelMap1,
        .drawPixelMap2 = CanvasAniModifier::DrawPixelMap2,
        .imageBitmapConstruct = CanvasAniModifier::ImageBitmapConstruct,
        .getCanvasDensity = CanvasAniModifier::GetCanvasDensity,
        .getSystemDensity = CanvasAniModifier::GetSystemDensity,
        .getImageData = CanvasAniModifier::GetImageData,
        .putImageData0 = CanvasAniModifier::PutImageData0,
        .putImageData1 = CanvasAniModifier::PutImageData1,
        .getDrawingCanvas = CanvasAniModifier::GetDrawingCanvas,
        .getCanvasId = CanvasAniModifier::GetCanvasId,
        .setAttachCallbackId = CanvasAniModifier::SetAttachCallbackId,
        .setDetachCallbackId = CanvasAniModifier::SetDetachCallbackId,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
