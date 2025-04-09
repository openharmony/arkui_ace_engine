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
#include "core/interfaces/native/utility/peer_utils.h"
#include "shape_mask_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
RefPtr<Ace::ShapeRect> Convert(const Ark_Rect& src)
{
    auto dst = AceType::MakeRefPtr<Ace::ShapeRect>();
    float left = Converter::Convert<float>(src.left);
    float top = Converter::Convert<float>(src.top);
    float right = Converter::Convert<float>(src.right);
    float bottom = Converter::Convert<float>(src.bottom);
    auto width = Dimension(right - left);
    auto height = Dimension(bottom - top);
    auto deltaX = Dimension(left);
    auto deltaY = Dimension(top);
    auto position = DimensionOffset(deltaX, deltaY);
    dst->SetWidth(width);
    dst->SetHeight(height);
    dst->SetPosition(position);
    return dst;
}
template<>
Ace::Radius Convert(const Ark_Vector2& src)
{
    Ace::Radius dst;
    auto x = Converter::Convert<float>(src.x);
    auto y = Converter::Convert<float>(src.y);
    dst.SetX(Dimension(x));
    dst.SetY(Dimension(y));
    return dst;
}
template<>
Ace::Corner Convert(const Ark_CornerRadius& src)
{
    return Ace::Corner {
        .topLeftRadius = Converter::Convert<Ace::Radius>(src.topLeft),
        .topRightRadius = Converter::Convert<Ace::Radius>(src.topRight),
        .bottomLeftRadius = Converter::Convert<Ace::Radius>(src.bottomLeft),
        .bottomRightRadius = Converter::Convert<Ace::Radius>(src.bottomRight),
    };
}
template<>
RefPtr<Ace::ShapeRect> Convert(const Ark_RoundRect& src)
{
    auto dst = Converter::Convert<RefPtr<Ace::ShapeRect>>(src.rect);
    auto corners = Converter::Convert<Ace::Corner>(src.corners);
    dst->SetTopLeftRadius(corners.topLeftRadius);
    dst->SetTopRightRadius(corners.topRightRadius);
    dst->SetBottomLeftRadius(corners.bottomLeftRadius);
    dst->SetBottomRightRadius(corners.bottomRightRadius);
    return dst;
}
template<>
RefPtr<Ace::Circle> Convert(const Ark_Circle& src)
{
    auto dst = AceType::MakeRefPtr<Ace::Circle>();
    auto centerX = Converter::Convert<float>(src.centerX);
    auto centerY = Converter::Convert<float>(src.centerY);
    auto radius = Converter::Convert<float>(src.radius);
    auto position = DimensionOffset(Dimension(centerX), Dimension(centerY));
    dst->SetPosition(position);
    dst->SetRadius(Dimension(radius));
    return dst;
}
template<>
std::string Convert(const Ark_CommandPath& src)
{
    return Converter::Convert<std::string>(src.commands);
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace ShapeMaskAccessor {
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
    return {};
}
void SetFillColorImpl(Ark_ShapeMask peer,
                      const Ark_Number* fillColor)
{
}
Ark_Number GetStrokeColorImpl(Ark_ShapeMask peer)
{
    return {};
}
void SetStrokeColorImpl(Ark_ShapeMask peer,
                        const Ark_Number* strokeColor)
{
}
Ark_Number GetStrokeWidthImpl(Ark_ShapeMask peer)
{
    return {};
}
void SetStrokeWidthImpl(Ark_ShapeMask peer,
                        const Ark_Number* strokeWidth)
{
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
