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
#include "core/interfaces/native/implementation/ellipse_shape_peer.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EllipseShapeAccessor {
void DestroyPeerImpl(Ark_EllipseShape peer)
{
    delete peer;
}
Ark_EllipseShape CtorImpl(const Opt_ShapeSize* options)
{
    auto peer = new EllipseShapePeer();
    peer->shape = AceType::MakeRefPtr<Ellipse>();
    std::optional<Ark_ShapeSize> shapeSize = options ? Converter::OptConvert<Ark_ShapeSize>(*options) : std::nullopt;
    if (shapeSize) {
        auto width = Converter::OptConvert<CalcDimension>(shapeSize->width);
        Validator::ValidateNonNegative(width);
        if (width) {
            peer->shape->SetWidth(*width);
        }
        auto height = Converter::OptConvert<CalcDimension>(shapeSize->height);
        Validator::ValidateNonNegative(height);
        if (height) {
            peer->shape->SetHeight(*height);
        }
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EllipseShape OffsetImpl(Ark_EllipseShape peer,
                            const Ark_Position* offset)
{
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(offset, peer);
    auto x = Converter::OptConvert<CalcDimension>(offset->x);
    auto y = Converter::OptConvert<CalcDimension>(offset->y);
    if (x && y) {
        peer->shape->SetOffset(DimensionOffset(*x, *y));
    }
    return peer;
}
Ark_EllipseShape FillImpl(Ark_EllipseShape peer,
                          const Ark_ResourceColor* color)
{
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(color, peer);
    auto clr = Converter::OptConvert<Color>(*color);
    if (clr) {
        peer->shape->SetColor(*clr);
    }
    return peer;
}
Ark_EllipseShape PositionImpl(Ark_EllipseShape peer,
                              const Ark_Position* position)
{
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(position, peer);
    DimensionOffset pos;
    auto x = Converter::OptConvert<CalcDimension>(position->x);
    if (x) {
        pos.SetX(*x);
    }
    auto y = Converter::OptConvert<CalcDimension>(position->y);
    if (y) {
        pos.SetY(*y);
    }
    peer->shape->SetPosition(pos);
    return peer;
}
Ark_EllipseShape WidthImpl(Ark_EllipseShape peer,
                           const Ark_Length* width)
{
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(width, peer);
    auto size = Converter::OptConvert<CalcDimension>(*width);
    Validator::ValidateNonNegative(size);
    if (size) {
        peer->shape->SetWidth(*size);
    }
    return peer;
}
Ark_EllipseShape HeightImpl(Ark_EllipseShape peer,
                            const Ark_Length* height)
{
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(height, peer);
    auto size = Converter::OptConvert<CalcDimension>(*height);
    Validator::ValidateNonNegative(size);
    if (size) {
        peer->shape->SetHeight(*size);
    }
    return peer;
}
Ark_EllipseShape SizeImpl(Ark_EllipseShape peer,
                          const Ark_SizeOptions* size)
{
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(size, peer);
    auto width = Converter::OptConvert<CalcDimension>(size->width);
    Validator::ValidateNonNegative(width);
    if (width) {
        peer->shape->SetWidth(*width);
    }
    auto height = Converter::OptConvert<CalcDimension>(size->height);
    Validator::ValidateNonNegative(height);
    if (height) {
        peer->shape->SetHeight(*height);
    }
    return peer;
}
} // EllipseShapeAccessor
const GENERATED_ArkUIEllipseShapeAccessor* GetEllipseShapeAccessor()
{
    static const GENERATED_ArkUIEllipseShapeAccessor EllipseShapeAccessorImpl {
        EllipseShapeAccessor::DestroyPeerImpl,
        EllipseShapeAccessor::CtorImpl,
        EllipseShapeAccessor::GetFinalizerImpl,
        EllipseShapeAccessor::OffsetImpl,
        EllipseShapeAccessor::FillImpl,
        EllipseShapeAccessor::PositionImpl,
        EllipseShapeAccessor::WidthImpl,
        EllipseShapeAccessor::HeightImpl,
        EllipseShapeAccessor::SizeImpl,
    };
    return &EllipseShapeAccessorImpl;
}
}
