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
#include "core/interfaces/native/implementation/rect_shape_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace {
const size_t RADIUS_ARRAY_LENGTH = 4;
enum RADIUS { TOP_LEFT_RADIUS = 0, TOP_RIGHT_RADIUS = 1, BOTTOM_RIGHT_RADIUS = 2, BOTTOM_LEFT_RADIUS = 3 };

inline void SetWidth(RefPtr<ShapeRect>& shape, std::optional<Dimension> value)
{
    Validator::ValidateNonNegative(value);
    if (value) {
        shape->SetWidth(value.value());
    }
}

inline void SetHeight(RefPtr<ShapeRect>& shape, std::optional<Dimension> value)
{
    Validator::ValidateNonNegative(value);
    if (value) {
        shape->SetHeight(value.value());
    }
}

inline void SetRadiusWidth(RefPtr<ShapeRect>& shape, std::optional<Dimension> value)
{
    Validator::ValidateNonNegative(value);
    if (value) {
        shape->SetRadiusWidth(value.value());
    }
}

inline void SetRadiusHeight(RefPtr<ShapeRect>& shape, std::optional<Dimension> value)
{
    Validator::ValidateNonNegative(value);
    if (value) {
        shape->SetRadiusHeight(value.value());
    }
}

void ApplyRadius(const Ark_Union_Number_String_Array_Union_Number_String& radius, RefPtr<ShapeRect>& shape)
{
    Converter::VisitUnion(
        radius,
        [&shape](const Ark_Number& numberRadius) {
            auto value = Converter::OptConvert<Dimension>(numberRadius);
            SetRadiusWidth(shape, value);
            SetRadiusHeight(shape, value);
        },
        [&shape](const Ark_String& stringRadius) {
            auto value = Converter::OptConvert<Dimension>(stringRadius);
            SetRadiusWidth(shape, value);
            SetRadiusHeight(shape, value);
        },
        [&shape](const Array_Union_Number_String& arrayRadius) {
            auto convArray = Converter::Convert<std::vector<std::optional<Dimension>>>(arrayRadius);
            if (convArray.size() == RADIUS_ARRAY_LENGTH) {
                auto topLeft = convArray[TOP_LEFT_RADIUS];
                Validator::ValidateNonNegative(topLeft);
                if (topLeft) {
                    shape->SetTopLeftRadius(Radius(topLeft.value()));
                }
                auto topRight = convArray[TOP_RIGHT_RADIUS];
                Validator::ValidateNonNegative(topRight);
                if (topRight) {
                    shape->SetTopRightRadius(Radius(topRight.value()));
                }
                auto bottomRight = convArray[BOTTOM_RIGHT_RADIUS];
                Validator::ValidateNonNegative(bottomRight);
                if (bottomRight) {
                    shape->SetBottomRightRadius(Radius(bottomRight.value()));
                }
                auto bottomLeft = convArray[BOTTOM_LEFT_RADIUS];
                Validator::ValidateNonNegative(bottomLeft);
                if (bottomLeft) {
                    shape->SetBottomLeftRadius(Radius(bottomLeft.value()));
                }
            }
        },
        []() {}
    );
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RectShapeAccessor {
void DestroyPeerImpl(Ark_RectShape peer)
{
    delete peer;
}
Ark_RectShape CtorImpl(const Opt_Union_RectShapeOptions_RoundRectShapeOptions* options)
{
    Ark_RectShape peer = new RectShapePeer();
    RefPtr<ShapeRect> shape = Referenced::MakeRefPtr<ShapeRect>();
    peer->shape = shape;
    CHECK_NULL_RETURN(options, peer);

    Converter::VisitUnion(
        *options,
        [&shape](const Ark_RectShapeOptions& rectShapeOptions) {
            auto width = Converter::OptConvert<Dimension>(rectShapeOptions.width);
            SetWidth(shape, width);
            auto height = Converter::OptConvert<Dimension>(rectShapeOptions.height);
            SetHeight(shape, height);
            auto radius = Converter::GetOpt(rectShapeOptions.radius);
            if (radius) {
                ApplyRadius(radius.value(), shape);
            }
        },
        [&shape](const Ark_RoundRectShapeOptions& roundRectShapeOptions) {
            auto width = Converter::OptConvert<Dimension>(roundRectShapeOptions.width);
            SetWidth(shape, width);
            auto height = Converter::OptConvert<Dimension>(roundRectShapeOptions.height);
            SetHeight(shape, height);
            auto radiusWidth = Converter::OptConvert<Dimension>(roundRectShapeOptions.radiusWidth);
            SetRadiusWidth(shape, radiusWidth.value());
            auto radiusHeight = Converter::OptConvert<Dimension>(roundRectShapeOptions.radiusHeight);
            SetRadiusHeight(shape, radiusHeight.value());
        },
        []() {}
    );
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_RectShape OffsetImpl(Ark_RectShape peer,
                         const Ark_Position* offset)
{
    if (peer && peer->shape && offset) {
        auto convValue = Converter::Convert<DimensionOffset>(*offset);
        peer->shape->SetOffset(convValue);
    }
    return peer;
}
Ark_RectShape FillImpl(Ark_RectShape peer,
                       const Ark_ResourceColor* color)
{
    if (peer && peer->shape && color) {
        auto convValue = Converter::OptConvert<Color>(*color);
        if (convValue) {
            peer->shape->SetColor(convValue.value());
        }
    }
    return peer;
}
Ark_RectShape PositionImpl(Ark_RectShape peer,
                           const Ark_Position* position)
{
    if (peer && peer->shape && position) {
        auto convValue = Converter::Convert<DimensionOffset>(*position);
        peer->shape->SetPosition(convValue);
    }
    return peer;
}
Ark_RectShape WidthImpl(Ark_RectShape peer,
                        const Ark_Length* width)
{
    if (peer && peer->shape && width) {
        SetWidth(peer->shape, Converter::OptConvert<Dimension>(*width));
    }
    return peer;
}
Ark_RectShape HeightImpl(Ark_RectShape peer,
                         const Ark_Length* height)
{
    if (peer && peer->shape && height) {
        SetHeight(peer->shape, Converter::OptConvert<Dimension>(*height));
    }
    return peer;
}
Ark_RectShape SizeImpl(Ark_RectShape peer,
                       const Ark_SizeOptions* size)
{
    if (peer && peer->shape && size) {
        SetWidth(peer->shape, Converter::OptConvert<Dimension>(size->width));
        SetHeight(peer->shape, Converter::OptConvert<Dimension>(size->height));
    }
    return peer;
}
Ark_RectShape RadiusWidthImpl(Ark_RectShape peer,
                              const Ark_Union_Number_String* rWidth)
{
    if (peer && peer->shape && rWidth) {
        auto convValue = Converter::OptConvert<Dimension>(*rWidth);
        SetRadiusWidth(peer->shape, convValue);
    }
    return peer;
}
Ark_RectShape RadiusHeightImpl(Ark_RectShape peer,
                               const Ark_Union_Number_String* rHeight)
{
    if (peer && peer->shape && rHeight) {
        auto convValue = Converter::OptConvert<Dimension>(*rHeight);
        SetRadiusHeight(peer->shape, convValue);
    }
    return peer;
}
Ark_RectShape RadiusImpl(Ark_RectShape peer,
                         const Ark_Union_Number_String_Array_Union_Number_String* radius)
{
    if (peer && peer->shape && radius) {
        ApplyRadius(*radius, peer->shape);
    }
    return peer;
}
} // RectShapeAccessor
const GENERATED_ArkUIRectShapeAccessor* GetRectShapeAccessor()
{
    static const GENERATED_ArkUIRectShapeAccessor RectShapeAccessorImpl {
        RectShapeAccessor::DestroyPeerImpl,
        RectShapeAccessor::CtorImpl,
        RectShapeAccessor::GetFinalizerImpl,
        RectShapeAccessor::OffsetImpl,
        RectShapeAccessor::FillImpl,
        RectShapeAccessor::PositionImpl,
        RectShapeAccessor::WidthImpl,
        RectShapeAccessor::HeightImpl,
        RectShapeAccessor::SizeImpl,
        RectShapeAccessor::RadiusWidthImpl,
        RectShapeAccessor::RadiusHeightImpl,
        RectShapeAccessor::RadiusImpl,
    };
    return &RectShapeAccessorImpl;
}

}
