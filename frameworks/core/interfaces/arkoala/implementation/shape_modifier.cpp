/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

static const double STROKE_MITER_LIMIT_MIN_VALUE = 1.0;

namespace OHOS::Ace::NG {
struct ShapeOptions {
    std::optional<Dimension> x;
    std::optional<Dimension> y;
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};
}

namespace OHOS::Ace::NG::Converter {
template<>
ShapeOptions Convert(const Ark_Literal_Union_Number_String_height_width_x_y& src)
{
    ShapeOptions options;
    options.x = Converter::OptConvert<Dimension>(src.x);
    options.y = Converter::OptConvert<Dimension>(src.y);
    options.width = Converter::OptConvert<Dimension>(src.width);
    options.height = Converter::OptConvert<Dimension>(src.height);
    return options;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ShapeInterfaceModifier {
void SetShapeOptions0Impl(Ark_NativePointer node,
                          const Ark_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ShapeModelNG::SetSetShapeOptions0(frameNode, convValue);
    LOGE("ARKOALA ShapeModifier.SetShapeOptions -> Method is not implemented.");
}
void SetShapeOptions1Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //ShapeModelNG::SetSetShapeOptions1(frameNode, convValue);
}
} // ShapeInterfaceModifier
namespace ShapeAttributeModifier {
void ViewPortImpl(Ark_NativePointer node,
                  const Ark_Literal_Union_Number_String_height_width_x_y* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<ShapeOptions>(*value);
    CHECK_NULL_VOID(options);
    ShapeModelNG::SetViewPort(frameNode, options->x, options->y, options->width, options->height);
}
void StrokeImpl(Ark_NativePointer node,
                const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ShapeModelNG::SetStroke(frameNode, Converter::OptConvert<Color>(*value));
}
void FillImpl(Ark_NativePointer node,
              const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ShapeModelNG::SetFill(frameNode, Converter::OptConvert<Color>(*value));
}

void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeDashOffset = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeDashOffset);
    Validator::ValidateNonPercent(strokeDashOffset);
    ShapeModelNG::SetStrokeDashOffset(frameNode, strokeDashOffset);
}

void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Array_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ShapeModelNG::SetStrokeDashArray(frameNode, convValue);
    LOGE("ARKOALA ShapeModifier.StrokeDashArray -> Method is not implemented.");
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       Ark_LineCapStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineCapStyle = Converter::OptConvert<LineCapStyle>(value);
    auto intLineCapStyle = EnumToInt(enumLineCapStyle);
    ShapeModelNG::SetStrokeLineCap(frameNode, intLineCapStyle);
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        Ark_LineJoinStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineJoinStyle = Converter::OptConvert<LineJoinStyle>(value);
    auto intLineJoinStyle = EnumToInt(enumLineJoinStyle);
    ShapeModelNG::SetStrokeLineJoin(frameNode, intLineJoinStyle);
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto limit = Converter::OptConvert<float>(*value);
    if (limit && limit.value() < STROKE_MITER_LIMIT_MIN_VALUE) {
        limit = 1.0;
    }
    ShapeModelNG::SetStrokeMiterLimit(frameNode, limit);
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelNG::SetStrokeOpacity(frameNode, strokeOpacity);
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelNG::SetFillOpacity(frameNode, strokeOpacity);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeWidth = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ShapeModelNG::SetStrokeWidth(frameNode, strokeWidth);
}
void AntiAliasImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetAntiAlias(frameNode, Converter::Convert<bool>(value));
}
void MeshImpl(Ark_NativePointer node,
              const Array_CustomObject* value,
              const Ark_Number* column,
              const Ark_Number* row)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ShapeModelNG::SetMesh(frameNode, convValue);
    LOGE("ARKOALA ShapeModifier.MeshImpl -> Method is not implemented.");
}
} // ShapeAttributeModifier
const GENERATED_ArkUIShapeModifier* GetShapeModifier()
{
    static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
        ShapeInterfaceModifier::SetShapeOptions0Impl,
        ShapeInterfaceModifier::SetShapeOptions1Impl,
        ShapeAttributeModifier::ViewPortImpl,
        ShapeAttributeModifier::StrokeImpl,
        ShapeAttributeModifier::FillImpl,
        ShapeAttributeModifier::StrokeDashOffsetImpl,
        ShapeAttributeModifier::StrokeDashArrayImpl,
        ShapeAttributeModifier::StrokeLineCapImpl,
        ShapeAttributeModifier::StrokeLineJoinImpl,
        ShapeAttributeModifier::StrokeMiterLimitImpl,
        ShapeAttributeModifier::StrokeOpacityImpl,
        ShapeAttributeModifier::FillOpacityImpl,
        ShapeAttributeModifier::StrokeWidthImpl,
        ShapeAttributeModifier::AntiAliasImpl,
        ShapeAttributeModifier::MeshImpl,
    };
    return &ArkUIShapeModifierImpl;
}

}
