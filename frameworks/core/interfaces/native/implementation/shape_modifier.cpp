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
#include "core/interfaces/native/generated/interface/node_api.h"
#if defined(PIXEL_MAP_SUPPORTED)
#include "pixel_map_ani.h"
#include "pixel_map.h"
#include "base/image/pixel_map.h"
#endif

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
ShapeOptions Convert(const Ark_ViewportRect& src)
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
namespace ShapeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // auto frameNode = ShapeModelNG::CreateFrameNode(id);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
    return nullptr;
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
    Media::PixelMapAni* pixelMapAni = reinterpret_cast<Media::PixelMapAni*>(value);
    CHECK_NULL_VOID(pixelMapAni);
    auto nativePixelMap = pixelMapAni->nativePixelMap_;
    CHECK_NULL_VOID(nativePixelMap);
    pixelMap = PixelMap::CreatePixelMap(&nativePixelMap);
#endif
    // ShapeModelNG::InitBox(frameNode, pixelMap);
}
void SetShapeOptions1Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, true);
    // ShapeModelNG::InitBox(frameNode, nullptr);
}
} // ShapeInterfaceModifier
namespace ShapeAttributeModifier {
void ViewPortImpl(Ark_NativePointer node,
                  const Opt_ViewportRect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvert<ShapeOptions>(*value);
    CHECK_NULL_VOID(options);
    // ShapeModelNG::SetViewPort(frameNode, options->x, options->y, options->width, options->height);
}
void StrokeImpl(Ark_NativePointer node,
                const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // ShapeModelNG::SetStroke(frameNode, Converter::OptConvert<Color>(*value));
}
void FillImpl(Ark_NativePointer node,
              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // ShapeModelNG::SetFill(frameNode, Converter::OptConvert<Color>(*value));
}

void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeDashOffset = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeDashOffset);
    Validator::ValidateNonPercent(strokeDashOffset);
    // ShapeModelNG::SetStrokeDashOffset(frameNode, strokeDashOffset);
}

void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::vector<Dimension>>(*value);
    if (!convValue) {
        // ShapeModelNG::SetStrokeDashArray(frameNode, {});
        return;
    }
    auto dashArray = *convValue;
    // if odd,add twice
    auto length = dashArray.size();
    if (length & 1) {
        for (int32_t i = 0; i < length; i++) {
            dashArray.emplace_back(dashArray[i]);
        }
    }
    // ShapeModelNG::SetStrokeDashArray(frameNode, std::move(dashArray));
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineCapStyle = Converter::OptConvert<LineCapStyle>(*value);
    auto intLineCapStyle = EnumToInt(enumLineCapStyle);
    // ShapeModelNG::SetStrokeLineCap(frameNode, intLineCapStyle);
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineJoinStyle = Converter::OptConvert<LineJoinStyle>(*value);
    auto intLineJoinStyle = EnumToInt(enumLineJoinStyle);
    // ShapeModelNG::SetStrokeLineJoin(frameNode, intLineJoinStyle);
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto limit = Converter::OptConvert<float>(*value);
    if (limit && limit.value() < STROKE_MITER_LIMIT_MIN_VALUE) {
        limit = 1.0;
    }
    // ShapeModelNG::SetStrokeMiterLimit(frameNode, limit);
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    // ShapeModelNG::SetStrokeOpacity(frameNode, strokeOpacity);
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    // ShapeModelNG::SetFillOpacity(frameNode, strokeOpacity);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeWidth = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    // ShapeModelNG::SetStrokeWidth(frameNode, strokeWidth);
}
void AntiAliasImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    // ShapeModelNG::SetAntiAlias(frameNode, *convValue);
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
        // ShapeModelNG::SetBitmapMesh(frameNode, std::move(mesh), 0, 0);
        return;
    }
    mesh = Converter::Convert<std::vector<float>>(*value);
    // ShapeModelNG::SetBitmapMesh(frameNode, std::move(mesh), columnValue, rowValue);
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
