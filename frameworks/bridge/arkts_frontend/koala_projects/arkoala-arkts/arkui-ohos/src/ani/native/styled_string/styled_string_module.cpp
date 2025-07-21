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

#include "styled_string_module.h"

#include "load.h"
#include "log/log.h"
#include "pixel_map_taihe_ani.h"
#include "core/interfaces/native/ani/styled_string_ani_modifier.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"

namespace OHOS::Ace::Ani {

void StyledStringModule::SetPixelMap([[maybe_unused]] ani_env* env, ani_object aniClass, ani_long peerPtr,
    ani_object pixelMapObj)
{
    auto* peer = reinterpret_cast<ArkUIStyledString>(peerPtr);
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(env);
    // only pass pointer to smart pointer, and do not operate on C pointer
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* styledStringModifier = modifier->getStyledStringAniModifier();
    CHECK_NULL_VOID(styledStringModifier);
    styledStringModifier->setPixelMap(peer, reinterpret_cast<void*>(&mediaPixelMap));
}

ani_object StyledStringModule::GetPixelMap(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr)
{
    auto* peer = reinterpret_cast<ArkUIStyledString>(peerPtr);
    CHECK_NULL_RETURN(peer, nullptr);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    auto* styledStringModifier = modifier->getStyledStringAniModifier();
    CHECK_NULL_RETURN(styledStringModifier, nullptr);
    auto* pixelMapPeer = reinterpret_cast<PixelMapPeer*>(styledStringModifier->getPixelMap(peer));
    CHECK_NULL_RETURN(pixelMapPeer, nullptr);
    auto pixelMap = pixelMapPeer->pixelMap;
    CHECK_NULL_RETURN(pixelMap, nullptr);
    auto mediaPixelMap = pixelMap->GetPixelMapSharedPtr();
    CHECK_NULL_RETURN(mediaPixelMap, nullptr);
    return Media::PixelMapTaiheAni::CreateEtsPixelMap(env, mediaPixelMap);
}

} // namespace OHOS::Ace::Ani
