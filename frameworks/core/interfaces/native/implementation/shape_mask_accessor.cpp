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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "shape_mask_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ShapeMaskAccessor {
const auto ARK_DEFAULT_COLOR = Converter::ArkValue<Ark_Number>(DEFAULT_COLOR);
const auto ARK_DEFAULT_WIDTH = Converter::ArkValue<Ark_Number>(DEFAULT_WIDTH);

void DestroyPeerImpl(Ark_ShapeMask peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ShapeMask CtorImpl()
{
    return PeerUtils::CreatePeer<ShapeMaskPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetRectShapeImpl(Ark_ShapeMask peer,
                      const Ark_Rect* rect)
{
    if (peer && rect) {
        peer->SetRectShape(Converter::Convert<RefPtr<Ace::ShapeRect>>(*rect));
    }
}
void SetRoundRectShapeImpl(Ark_ShapeMask peer,
                           const Ark_RoundRect* roundRect)
{
    if (peer && roundRect) {
        peer->SetRoundRectShape(Converter::Convert<RefPtr<Ace::ShapeRect>>(*roundRect));
    }
}
void SetCircleShapeImpl(Ark_ShapeMask peer,
                        const Ark_Circle* circle)
{
    if (peer && circle) {
        peer->SetCircleShape(Converter::Convert<RefPtr<Ace::Circle>>(*circle));
    }
}
void SetOvalShapeImpl(Ark_ShapeMask peer,
                      const Ark_Rect* oval)
{
    if (peer && oval) {
        peer->SetOvalShape(Converter::Convert<RefPtr<Ace::ShapeRect>>(*oval));
    }
}
void SetCommandPathImpl(Ark_ShapeMask peer,
                        const Ark_CommandPath* path)
{
    if (peer && path) {
        peer->SetCommandPath(Converter::Convert<std::string>(*path));
    }
}
Ark_Number GetFillColorImpl(Ark_ShapeMask peer)
{
    CHECK_NULL_RETURN(peer, ARK_DEFAULT_COLOR);
    return Converter::ArkValue<Ark_Number>(peer->fillColor);
}
void SetFillColorImpl(Ark_ShapeMask peer,
                      const Ark_Number* fillColor)
{
    CHECK_NULL_VOID(peer && fillColor);
    peer->fillColor = Converter::Convert<int32_t>(*fillColor);
}
Ark_Number GetStrokeColorImpl(Ark_ShapeMask peer)
{
    CHECK_NULL_RETURN(peer, ARK_DEFAULT_COLOR);
    return Converter::ArkValue<Ark_Number>(peer->strokeColor);
}
void SetStrokeColorImpl(Ark_ShapeMask peer,
                        const Ark_Number* strokeColor)
{
    CHECK_NULL_VOID(peer && strokeColor);
    peer->strokeColor = Converter::Convert<int32_t>(*strokeColor);
}
Ark_Number GetStrokeWidthImpl(Ark_ShapeMask peer)
{
    CHECK_NULL_RETURN(peer, ARK_DEFAULT_WIDTH);
    return Converter::ArkValue<Ark_Number>(peer->strokeWidth);
}
void SetStrokeWidthImpl(Ark_ShapeMask peer,
                        const Ark_Number* strokeWidth)
{
    CHECK_NULL_VOID(peer && strokeWidth);
    peer->strokeWidth = Converter::Convert<float>(*strokeWidth);
}
} // ShapeMaskAccessor
const GENERATED_ArkUIShapeMaskAccessor* GetShapeMaskAccessor()
{
    static const GENERATED_ArkUIShapeMaskAccessor ShapeMaskAccessorImpl {
        ShapeMaskAccessor::DestroyPeerImpl,
        ShapeMaskAccessor::CtorImpl,
        ShapeMaskAccessor::GetFinalizerImpl,
        ShapeMaskAccessor::SetRectShapeImpl,
        ShapeMaskAccessor::SetRoundRectShapeImpl,
        ShapeMaskAccessor::SetCircleShapeImpl,
        ShapeMaskAccessor::SetOvalShapeImpl,
        ShapeMaskAccessor::SetCommandPathImpl,
        ShapeMaskAccessor::GetFillColorImpl,
        ShapeMaskAccessor::SetFillColorImpl,
        ShapeMaskAccessor::GetStrokeColorImpl,
        ShapeMaskAccessor::SetStrokeColorImpl,
        ShapeMaskAccessor::GetStrokeWidthImpl,
        ShapeMaskAccessor::SetStrokeWidthImpl,
    };
    return &ShapeMaskAccessorImpl;
}

}
