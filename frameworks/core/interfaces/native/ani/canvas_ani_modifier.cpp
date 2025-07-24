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
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/canvas_renderer_type.h"
#include "core/interfaces/native/implementation/canvas_renderer_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/native/implementation/image_data_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
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

void* GetPixelMap(ArkUICanvasRenderer peer, ani_double sx, ani_double sy, ani_double sw, ani_double sh)
{
#if defined(PIXEL_MAP_SUPPORTED)
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    auto pixelMap = peerImpl->GetPixelMap(sx, sy, sw, sh);
    CHECK_NULL_RETURN(pixelMap, nullptr);
    PixelMapPeer* pixelMapPeer = new PixelMapPeer();
    pixelMapPeer->pixelMap = pixelMap;
    return reinterpret_cast<void*>(pixelMapPeer);
#else
    return nullptr;
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
    PixelMapPeer* pixelMapPeer = new PixelMapPeer();
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
    PixelMapPeer* pixelMapPeer = new PixelMapPeer();
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
    PixelMapPeer* pixelMapPeer = new PixelMapPeer();
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
    auto peer = Referenced::MakeRefPtr<ImageBitmapPeer>();
    peer->IncRefCount();
    if (pixelMapPtr) {
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixelMap = PixelMap::CreatePixelMap(pixelMapPtr);
        CHECK_NULL_RETURN(pixelMap, nullptr);
        peer->SetOptions(str, pixelMap, unit);
#endif
    } else {
        peer->SetOptions(str, nullptr, unit);
    }
    return reinterpret_cast<ArkUIImageBitmap>(Referenced::RawPtr(peer));
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

void GetImageData(ArkUICanvasRenderer peer, uint8_t** data, ani_double sx, ani_double sy, ani_double sw, ani_double sh)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    ImageSize imageSize = {
        .left = static_cast<double>(sx),
        .top = static_cast<double>(sy),
        .width = static_cast<double>(sw),
        .height = static_cast<double>(sh)
    };
    std::vector<uint8_t> vbuffer(0);
    uint32_t width = 0;
    uint32_t height = 0;
    peerImpl->GetImageData(vbuffer, imageSize, width, height);
    *data = reinterpret_cast<uint8_t*>(vbuffer.data());
}

void PutImageData0(ArkUICanvasRenderer peer, uint8_t* data, ani_size length, ani_double dx, ani_double dy,
    ani_int width, ani_int height)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    GeneratedModifier::CanvasRendererPeerImpl::PutImageDataParam params = {
        .x = std::make_optional<Dimension>(static_cast<float>(dx)),
        .y = std::make_optional<Dimension>(static_cast<float>(dy)),
        .size = GeneratedModifier::CanvasRendererPeerImpl::SizeParam::TWO_ARGS,
    };
    peerImpl->PutImageData(
        data, static_cast<size_t>(length), static_cast<int32_t>(width), static_cast<int32_t>(height), params);
}

void PutImageData1(ArkUICanvasRenderer peer, uint8_t* data, ani_size length, ani_double dx, ani_double dy,
    ani_int width, ani_int height, ani_double dirtyX, ani_double dirtyY, ani_double dirtyWidth, ani_double dirtyHeight)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<GeneratedModifier::CanvasRendererPeerImpl*>(peer);
    GeneratedModifier::CanvasRendererPeerImpl::PutImageDataParam params = {
        .x = std::make_optional<Dimension>(static_cast<float>(dx)),
        .y = std::make_optional<Dimension>(static_cast<float>(dy)),
        .dirtyX = std::make_optional<Dimension>(static_cast<float>(dirtyX)),
        .dirtyY = std::make_optional<Dimension>(static_cast<float>(dirtyY)),
        .dirtyWidth = std::make_optional<Dimension>(static_cast<float>(dirtyWidth)),
        .dirtyHeight = std::make_optional<Dimension>(static_cast<float>(dirtyHeight)),
        .size = GeneratedModifier::CanvasRendererPeerImpl::SizeParam::SIX_ARGS,
    };
    peerImpl->PutImageData(
        data, static_cast<size_t>(length), static_cast<int32_t>(width), static_cast<int32_t>(height), params);
}
} // namespace CanvasAniModifier

const ArkUIAniCanvasModifier* GetCanvasAniModifier()
{
    static const ArkUIAniCanvasModifier impl = { .setPixelMap = CanvasAniModifier::SetPixelMap,
        .getPixelMap = CanvasAniModifier::GetPixelMap,
        .drawPixelMap0 = CanvasAniModifier::DrawPixelMap0,
        .drawPixelMap1 = CanvasAniModifier::DrawPixelMap1,
        .drawPixelMap2 = CanvasAniModifier::DrawPixelMap2,
        .imageBitmapConstruct = CanvasAniModifier::ImageBitmapConstruct,
        .getCanvasDensity = CanvasAniModifier::GetCanvasDensity,
        .getSystemDensity = CanvasAniModifier::GetSystemDensity,
        .getImageData = CanvasAniModifier::GetImageData,
        .putImageData0 = CanvasAniModifier::PutImageData0,
        .putImageData1 = CanvasAniModifier::PutImageData1,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
