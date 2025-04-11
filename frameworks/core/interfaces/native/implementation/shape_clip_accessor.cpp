/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "shape_clip_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ShapeClipAccessor {
void DestroyPeerImpl(Ark_ShapeClip peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ShapeClip CtorImpl()
{
    return PeerUtils::CreatePeer<ShapeClipPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetRectShapeImpl(Ark_ShapeClip peer,
                      const Ark_Rect* rect)
{
    if (peer && rect) {
        peer->SetRectShape(Converter::Convert<RefPtr<Ace::ShapeRect>>(*rect));
    }
}
void SetRoundRectShapeImpl(Ark_ShapeClip peer,
                           const Ark_RoundRect* roundRect)
{
    if (peer && roundRect) {
        peer->SetRoundRectShape(Converter::Convert<RefPtr<Ace::ShapeRect>>(*roundRect));
    }
}
void SetCircleShapeImpl(Ark_ShapeClip peer,
                        const Ark_Circle* circle)
{
    if (peer && circle) {
        peer->SetCircleShape(Converter::Convert<RefPtr<Ace::Circle>>(*circle));
    }
}
void SetOvalShapeImpl(Ark_ShapeClip peer,
                      const Ark_Rect* oval)
{
    if (peer && oval) {
        peer->SetOvalShape(Converter::Convert<RefPtr<Ace::ShapeRect>>(*oval));
    }
}
void SetCommandPathImpl(Ark_ShapeClip peer,
                        const Ark_CommandPath* path)
{
    if (peer && path) {
        peer->SetCommandPath(Converter::Convert<std::string>(*path));
    }
}
} // ShapeClipAccessor
const GENERATED_ArkUIShapeClipAccessor* GetShapeClipAccessor()
{
    static const GENERATED_ArkUIShapeClipAccessor ShapeClipAccessorImpl {
        ShapeClipAccessor::DestroyPeerImpl,
        ShapeClipAccessor::CtorImpl,
        ShapeClipAccessor::GetFinalizerImpl,
        ShapeClipAccessor::SetRectShapeImpl,
        ShapeClipAccessor::SetRoundRectShapeImpl,
        ShapeClipAccessor::SetCircleShapeImpl,
        ShapeClipAccessor::SetOvalShapeImpl,
        ShapeClipAccessor::SetCommandPathImpl,
    };
    return &ShapeClipAccessorImpl;
}

}
