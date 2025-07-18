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

#include "base/image/pixel_map.h"
#include "base/log/log.h"
#include "core/components_ng/render/paragraph.h"
#include "core/interfaces/native/ani/styled_string_ani_modifier.h"
#include "core/interfaces/native/implementation/paragraph_style_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"

namespace OHOS::Ace::NG {
namespace StyledStringAniModifier {

void SetPixelMap(ArkUIStyledString peer, void* pixelMapPtr)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(pixelMapPtr);
    auto peerImpl = reinterpret_cast<ParagraphStylePeer*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto span = peerImpl->span;
    CHECK_NULL_VOID(span);
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapPtr);
    CHECK_NULL_VOID(pixelMap);
    span->SetPixelMap(pixelMap);
}

void* GetPixelMap(ArkUIStyledString peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto peerImpl = reinterpret_cast<ParagraphStylePeer*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);

    auto span = peerImpl->span;
    auto spanParagraphStyle = span->GetParagraphStyle();
    if (spanParagraphStyle.leadingMargin.has_value()) {
        auto pixelMap = spanParagraphStyle.leadingMargin.value().pixmap;
        CHECK_NULL_RETURN(pixelMap, nullptr);
        PixelMapPeer* pixelMapPeer = new PixelMapPeer();
        pixelMapPeer->pixelMap = pixelMap;
        return reinterpret_cast<void*>(pixelMapPeer);
    }
    return nullptr;
}

}
const ArkUIAniStyledStringModifier* GetStyledStringAniModifier()
{
    static const ArkUIAniStyledStringModifier impl = {
        .setPixelMap = StyledStringAniModifier::SetPixelMap,
        .getPixelMap = StyledStringAniModifier::GetPixelMap,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
