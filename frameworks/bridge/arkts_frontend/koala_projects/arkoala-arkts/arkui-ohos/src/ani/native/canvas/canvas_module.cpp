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

#include "canvas_module.h"

#include "load.h"
#include "pixel_map_taihe_ani.h"
#include "utils/ani_utils.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/interfaces/native/ani/canvas_ani_modifier.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"

namespace OHOS::Ace::Ani {
void CanvasModule::SetPixelMap(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_object pixelMapObj)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->setPixelMap(peer, reinterpret_cast<void*>(&mediaPixelMap));
}

ani_object CanvasModule::GetPixelMap(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_double sx, ani_double sy, ani_double sw, ani_double sh)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_RETURN(peer, nullptr);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, nullptr);
    auto* pixelMapPeer = reinterpret_cast<PixelMapPeer*>(canvasModifier->getPixelMap(peer, sx, sy, sw, sh));
    CHECK_NULL_RETURN(pixelMapPeer, nullptr);
    auto pixelMap = pixelMapPeer->pixelMap;
    CHECK_NULL_RETURN(pixelMap, nullptr);
    auto mediaPixelMap = pixelMap->GetPixelMapSharedPtr();
    CHECK_NULL_RETURN(mediaPixelMap, nullptr);
    return Media::PixelMapTaiheAni::CreateEtsPixelMap(env, mediaPixelMap);
}

void CanvasModule::DrawPixelMap0(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_object pixelMapObj, ani_double dx, ani_double dy)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->drawPixelMap0(peer, reinterpret_cast<void*>(&mediaPixelMap), dx, dy);
}

void CanvasModule::DrawPixelMap1(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_object pixelMapObj, ani_double dx, ani_double dy, ani_double dw, ani_double dh)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->drawPixelMap1(peer, reinterpret_cast<void*>(&mediaPixelMap), dx, dy, dw, dh);
}

void CanvasModule::DrawPixelMap2(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_object pixelMapObj, ani_double sx, ani_double sy, ani_double sw, ani_double sh, ani_double dx, ani_double dy,
    ani_double dw, ani_double dh)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->drawPixelMap2(peer, reinterpret_cast<void*>(&mediaPixelMap), sx, sy, sw, sh, dx, dy, dw, dh);
}

ani_long CanvasModule::ImageBitmapConstruct0(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string src, ani_int unit)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, {});
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, {});
    std::string str = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(src));
    return reinterpret_cast<ani_long>(canvasModifier->imageBitmapConstruct(str, nullptr, unit));
}

ani_long CanvasModule::ImageBitmapConstruct1(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object pixelMapObj, ani_int unit)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, {});
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, {});
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_RETURN(mediaPixelMap, {});
    return reinterpret_cast<ani_long>(
        canvasModifier->imageBitmapConstruct("", reinterpret_cast<void*>(&mediaPixelMap), unit));
}

} // namespace OHOS::Ace::Ani
