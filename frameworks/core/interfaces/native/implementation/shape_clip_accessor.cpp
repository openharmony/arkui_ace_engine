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
#include "core/interfaces/native/implementation/shape_clip_peer.h"

namespace OHOS::Ace::NG {
namespace Converter {
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
ShapeClipPeer::Rect Convert(const Ark_Rect& src)
{
    ShapeClipPeer::Rect dst;
    float left = Converter::Convert<float>(src.left);
    float top = Converter::Convert<float>(src.top);
    float right = Converter::Convert<float>(src.right);
    float bottom = Converter::Convert<float>(src.bottom);
    return ShapeClipPeer::Rect {
        .width = Dimension(right - left),
        .height = Dimension(bottom - top),
        .position = DimensionOffset(Dimension(left), Dimension(top)),
    };
}
template<>
ShapeClipPeer::RoundRect Convert(const Ark_RoundRect& src)
{
    return ShapeClipPeer::RoundRect {
        .rect = Converter::Convert<ShapeClipPeer::Rect>(src.rect),
        .corners = Converter::Convert<Ace::Corner>(src.corners),
    };
}
template<>
ShapeClipPeer::Circle Convert(const Ark_Circle& src)
{
    auto centerX = Converter::Convert<float>(src.centerX);
    auto centerY = Converter::Convert<float>(src.centerY);
    auto radius = Converter::Convert<float>(src.radius);
    return ShapeClipPeer::Circle {
        .position = DimensionOffset(Dimension(centerX), Dimension(centerY)),
        .radius = Dimension(radius),
    };
}
template<>
std::string Convert(const Ark_CommandPath& src)
{
    return Converter::Convert<std::string>(src.commands);
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ShapeClipAccessor {
void DestroyPeerImpl(Ark_ShapeClip peer)
{
    delete peer;
}
Ark_ShapeClip CtorImpl()
{
    return new ShapeClipPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetRectShapeImpl(Ark_ShapeClip peer,
                      const Ark_Rect* rect)
{
    if (peer && rect) {
        peer->SetRectShape(Converter::Convert<ShapeClipPeer::Rect>(*rect));
    }
}
void SetRoundRectShapeImpl(Ark_ShapeClip peer,
                           const Ark_RoundRect* roundRect)
{
    if (peer && roundRect) {
        peer->SetRoundRectShape(Converter::Convert<ShapeClipPeer::RoundRect>(*roundRect));
    }
}
void SetCircleShapeImpl(Ark_ShapeClip peer,
                        const Ark_Circle* circle)
{
    if (peer && circle) {
        peer->SetCircleShape(Converter::Convert<ShapeClipPeer::Circle>(*circle));
    }
}
void SetOvalShapeImpl(Ark_ShapeClip peer,
                      const Ark_Rect* oval)
{
    if (peer && oval) {
        peer->SetOvalShape(Converter::Convert<ShapeClipPeer::Rect>(*oval));
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
