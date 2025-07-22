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
#include "core/interfaces/native/implementation/canvas_renderer_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/native/implementation/image_data_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"

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

} // namespace CanvasAniModifier

const ArkUIAniCanvasModifier* GetCanvasAniModifier()
{
    static const ArkUIAniCanvasModifier impl = { .setPixelMap = CanvasAniModifier::SetPixelMap,
        .getPixelMap = CanvasAniModifier::GetPixelMap,
        .drawPixelMap0 = CanvasAniModifier::DrawPixelMap0,
        .drawPixelMap1 = CanvasAniModifier::DrawPixelMap1,
        .drawPixelMap2 = CanvasAniModifier::DrawPixelMap2,
        .imageBitmapConstruct = CanvasAniModifier::ImageBitmapConstruct,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
