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
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "frameworks/base/geometry/shape.h"
#include "frameworks/core/interfaces/native/implementation/circle_shape_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CircleShapeAccessor {
void DestroyPeerImpl(Ark_CircleShape peer)
{
    CHECK_NULL_VOID(peer);
    delete peer;
}
Ark_CircleShape CtorImpl(const Opt_ShapeSize* options)
{
    auto peer = new CircleShapePeer();
    peer->shape = Referenced::MakeRefPtr<OHOS::Ace::Circle>();
    CHECK_NULL_RETURN(options, peer);

    auto dimension = Converter::OptConvert<Dimension>(options->value.width);
    peer->shape->SetWidth(dimension.value_or(Dimension()));

    dimension = Converter::OptConvert<Dimension>(options->value.height);
    peer->shape->SetHeight(dimension.value_or(Dimension()));

    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_CircleShape OffsetImpl(Ark_CircleShape peer,
                           const Ark_Position* offset)
{
    CHECK_NULL_RETURN(peer && offset && peer->shape, peer);
    auto dimensionOffset = Converter::Convert<DimensionOffset>(*offset);
    peer->shape->SetOffset(dimensionOffset);
    return peer;
}
Ark_CircleShape FillImpl(Ark_CircleShape peer,
                         const Ark_ResourceColor* color)
{
    CHECK_NULL_RETURN(peer && color && peer->shape, peer);
    auto aceColor = Converter::OptConvert<Color>(*color);
    peer->shape->SetColor(aceColor.value_or(Color::TRANSPARENT));
    return peer;
}
Ark_CircleShape PositionImpl(Ark_CircleShape peer,
                             const Ark_Position* position)
{
    CHECK_NULL_RETURN(peer && position && peer->shape, peer);
    auto acePosition = Converter::OptConvert<DimensionOffset>(*position);
    peer->shape->SetPosition(acePosition.value_or(DimensionOffset()));
    return peer;
}
Ark_CircleShape WidthImpl(Ark_CircleShape peer,
                          const Ark_Length* width)
{
    CHECK_NULL_RETURN(peer && width && peer->shape, peer);
    auto aceDimension = Converter::OptConvert<Dimension>(*width);
    Validator::ValidateNonNegative(aceDimension);
    peer->shape->SetWidth(aceDimension.value_or(Dimension()));
    return peer;
}
Ark_CircleShape HeightImpl(Ark_CircleShape peer,
                           const Ark_Length* height)
{
    CHECK_NULL_RETURN(peer && height && peer->shape, peer);
    auto aceDimension = Converter::OptConvert<Dimension>(*height);
    Validator::ValidateNonNegative(aceDimension);
    peer->shape->SetHeight(aceDimension.value_or(Dimension()));
    return peer;
}
Ark_CircleShape SizeImpl(Ark_CircleShape peer,
                         const Ark_SizeOptions* size)
{
    CHECK_NULL_RETURN(peer && size, peer);
    WidthImpl(peer, &size->width.value);
    HeightImpl(peer, &size->height.value);
    return peer;
}
} // CircleShapeAccessor
const GENERATED_ArkUICircleShapeAccessor* GetCircleShapeAccessor()
{
    static const GENERATED_ArkUICircleShapeAccessor CircleShapeAccessorImpl {
        CircleShapeAccessor::DestroyPeerImpl,
        CircleShapeAccessor::CtorImpl,
        CircleShapeAccessor::GetFinalizerImpl,
        CircleShapeAccessor::OffsetImpl,
        CircleShapeAccessor::FillImpl,
        CircleShapeAccessor::PositionImpl,
        CircleShapeAccessor::WidthImpl,
        CircleShapeAccessor::HeightImpl,
        CircleShapeAccessor::SizeImpl,
    };
    return &CircleShapeAccessorImpl;
}

}
