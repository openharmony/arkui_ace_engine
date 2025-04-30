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

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
struct ShapeViewPortOptions {
    Dimension x;
    Dimension y;
    Dimension width;
    Dimension height;
};
}

namespace OHOS::Ace::NG::Converter {
template<>
ShapeViewPortOptions Convert(const Ark_ViewportRect& src)
{
    ShapeViewPortOptions options;
    options.x = Converter::OptConvert<Dimension>(src.x).value_or(0.0_vp);
    options.y = Converter::OptConvert<Dimension>(src.y).value_or(0.0_vp);
    options.width = Converter::OptConvert<Dimension>(src.width).value_or(0.0_vp);
    options.height = Converter::OptConvert<Dimension>(src.height).value_or(0.0_vp);
    return options;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
    const Color STROKE_DEFAULT = Color::TRANSPARENT;
    const Color FILL_DEFAULT = Color::BLACK;
    const double STROKE_MITERLIMIT_DEFAULT = 4.0f;
} // namespace
namespace ShapeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ShapeModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ShapeModifier
namespace ShapeInterfaceModifier {
void SetShapeOptions0Impl(Ark_NativePointer node,
                          Ark_PixelMap value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ViewAbstract::SetFocusable(frameNode, true);
    RefPtr<PixelMap> pixelMap;
#if !defined(PREVIEW) && defined(PIXEL_MAP_SUPPORTED)
    pixelMap = Converter::Convert<RefPtr<PixelMap>>(value);
#endif
    ShapeModelNG::InitBox(frameNode, pixelMap);
}
void SetShapeOptions1Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, true);
    ShapeModelNG::InitBox(frameNode, nullptr);
}
} // ShapeInterfaceModifier
namespace ShapeAttributeModifier {
void ViewPortImpl(Ark_NativePointer node,
                  const Opt_ViewportRect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_EQUAL_VOID(value->tag, InteropTag::INTEROP_TAG_UNDEFINED);
    auto options = Converter::Convert<ShapeViewPortOptions>(value->value);
    ShapeModelNG::SetViewPort(frameNode, options.x, options.y, options.width, options.height);
}
void StrokeImpl(Ark_NativePointer node,
                const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    ShapeModelNG::SetStroke(frameNode, color.value_or(STROKE_DEFAULT));
}
void FillImpl(Ark_NativePointer node,
              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    ShapeModelNG::SetFill(frameNode, color.value_or(FILL_DEFAULT));
}
void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeDashOffset = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeDashOffset);
    Validator::ValidateNonPercent(strokeDashOffset);
    ShapeModelNG::SetStrokeDashOffset(frameNode, strokeDashOffset.value_or(Dimension(0.0)));
}
void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ShapeModelNG::SetStrokeDashArray(frameNode, {});
        return;
    }
    auto dashArray = Converter::Convert<std::vector<Dimension>>(value->value);
    // if odd,add twice
    auto length = value->value.length;
    if (static_cast<uint32_t>(length) == dashArray.size() && (static_cast<uint32_t>(length) & 1)) {
        for (int32_t i = 0; i < length; i++) {
            dashArray.emplace_back(dashArray[i]);
        }
    }
    ShapeModelNG::SetStrokeDashArray(frameNode, std::move(dashArray));
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto enumLineCapStyle = Converter::OptConvert<LineCapStyle>(*value);
    auto intLineCapStyle = EnumToInt(enumLineCapStyle);
    ShapeModelNG::SetStrokeLineCap(frameNode, intLineCapStyle.value_or(0));
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto enumLineJoinStyle = Converter::OptConvert<LineJoinStyle>(*value);
    auto intLineJoinStyle = EnumToInt(enumLineJoinStyle);
    ShapeModelNG::SetStrokeLineJoin(frameNode, intLineJoinStyle.value_or(0));
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto limit = Converter::OptConvert<float>(*value);
    ShapeModelNG::SetStrokeMiterLimit(frameNode, limit.value_or(STROKE_MITERLIMIT_DEFAULT));
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelNG::SetStrokeOpacity(frameNode, strokeOpacity.value_or(1.0));
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelNG::SetFillOpacity(frameNode, strokeOpacity.value_or(1.0));
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeWidth = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ShapeModelNG::SetStrokeWidth(frameNode, strokeWidth.value_or(1.0_vp));
}
void AntiAliasImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto antiAlias = Converter::OptConvert<bool>(*value);
    ShapeModelNG::SetAntiAlias(frameNode, antiAlias.value_or(false));
}
void MeshImpl(Ark_NativePointer node,
              const Array_Number* value,
              const Ark_Number* column,
              const Ark_Number* row)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(column);
    CHECK_NULL_VOID(row);
    std::vector<float> mesh;
    auto columnValue = Converter::Convert<int32_t>(*column);
    auto rowValue = Converter::Convert<int32_t>(*row);
    auto meshSize = value->length;
    auto tempMeshSize = static_cast<int64_t>(columnValue + 1) * (rowValue + 1) * 2;
    if (tempMeshSize != meshSize) {
        ShapeModelNG::SetBitmapMesh(frameNode, std::move(mesh), 0, 0);
        return;
    }
    mesh = Converter::Convert<std::vector<float>>(*value);
    ShapeModelNG::SetBitmapMesh(frameNode, std::move(mesh), columnValue, rowValue);
}
} // ShapeAttributeModifier
const GENERATED_ArkUIShapeModifier* GetShapeModifier()
{
    static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
        ShapeModifier::ConstructImpl,
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
