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
#include "core/components_ng/pattern/shape/shape_model_static.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#if defined(PIXEL_MAP_SUPPORTED)
#include "pixel_map.h"
#include "base/image/pixel_map.h"
#endif

static const double STROKE_MITER_LIMIT_MIN_VALUE = 1.0;

namespace {
OHOS::Ace::RefPtr<OHOS::Ace::PixelMap> ConvertPixelMap(const Opt_image_PixelMap* value)
{
#if defined(PIXEL_MAP_SUPPORTED)
    CHECK_NULL_RETURN(value, nullptr);
    CHECK_EQUAL_RETURN(value->tag, InteropTag::INTEROP_TAG_UNDEFINED, nullptr);
    auto arkPixelMap = value->value;
    CHECK_NULL_RETURN(arkPixelMap, nullptr);
    return arkPixelMap->pixelMap;
#else
    return nullptr;
#endif
}
} // namespace

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
    auto frameNode = ShapeModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ShapeModifier
namespace ShapeInterfaceModifier {
void SetShapeOptionsImpl(Ark_NativePointer node,
                         const Opt_image_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, true);
    ShapeModelStatic::InitBox(frameNode, ConvertPixelMap(value));
}
} // ShapeInterfaceModifier
namespace ShapeAttributeModifier {
void SetViewPortImpl(Ark_NativePointer node,
                     const Opt_ViewportRect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvertPtr<ShapeOptions>(value);
    CHECK_NULL_VOID(options);
    ShapeModelStatic::SetViewPort(frameNode, options->x, options->y, options->width, options->height);
}
void SetStrokeImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelStatic::SetStroke(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetFillImpl(Ark_NativePointer node,
                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelStatic::SetFill(frameNode, Converter::OptConvertPtr<Color>(value).value_or(Color::BLACK));
}
void SetStrokeDashOffsetImpl(Ark_NativePointer node,
                             const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeDashOffset = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidatePositive(strokeDashOffset);
    Validator::ValidateNonPercent(strokeDashOffset);
    ShapeModelStatic::SetStrokeDashOffset(frameNode, strokeDashOffset);
}
void SetStrokeDashArrayImpl(Ark_NativePointer node,
                            const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::vector<std::optional<Dimension>>>(*value);
    if (!convValue) {
        ShapeModelNG::SetStrokeDashArray(frameNode, {});
        return;
    }
    auto dashArray = Converter::Squash(*convValue);
    // if odd,add twice
    auto dashArraySize = dashArray.size();
    if (dashArraySize & 1) {
        for (size_t i = 0; i < dashArraySize; i++) {
            dashArray.emplace_back(dashArray[i]);
        }
    }
    ShapeModelNG::SetStrokeDashArray(frameNode, std::move(dashArray));
}
void SetStrokeLineCapImpl(Ark_NativePointer node,
                          const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineCapStyle = Converter::OptConvertPtr<LineCapStyle>(value);
    auto intLineCapStyle = EnumToInt(enumLineCapStyle);
    ShapeModelStatic::SetStrokeLineCap(frameNode, intLineCapStyle);
}
void SetStrokeLineJoinImpl(Ark_NativePointer node,
                           const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineJoinStyle = Converter::OptConvertPtr<LineJoinStyle>(value);
    auto intLineJoinStyle = EnumToInt(enumLineJoinStyle);
    ShapeModelStatic::SetStrokeLineJoin(frameNode, intLineJoinStyle);
}
void SetStrokeMiterLimitImpl(Ark_NativePointer node,
                             const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto limit = Converter::OptConvertPtr<float>(value);
    if (limit && limit.value() < STROKE_MITER_LIMIT_MIN_VALUE) {
        limit = 1.0;
    }
    ShapeModelStatic::SetStrokeMiterLimit(frameNode, limit);
}
void SetStrokeOpacityImpl(Ark_NativePointer node,
                          const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvertPtr<float>(value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelStatic::SetStrokeOpacity(frameNode, strokeOpacity);
}
void SetFillOpacityImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvertPtr<float>(value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelStatic::SetFillOpacity(frameNode, strokeOpacity);
}
void SetStrokeWidthImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeWidth = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ShapeModelStatic::SetStrokeWidth(frameNode, strokeWidth);
}
void SetAntiAliasImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ShapeModelNG::SetAntiAlias(frameNode, true);
        return;
    }
    ShapeModelNG::SetAntiAlias(frameNode, *convValue);
}
void SetMeshImpl(Ark_NativePointer node,
                 const Opt_Array_Float64* value,
                 const Opt_Int32* column,
                 const Opt_Int32* row)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto mesh = Converter::OptConvertPtr<std::vector<float>>(value).value_or(std::vector<float>());
    auto columnValue = Converter::OptConvertPtr<int32_t>(column).value_or(0);
    auto rowValue = Converter::OptConvertPtr<int32_t>(row).value_or(0);
    auto meshSize = mesh.size();
    columnValue = columnValue > 0 ? columnValue : 0;
    rowValue = rowValue > 0 ? rowValue : 0;
    auto tempMeshSize = (columnValue + 1) * (rowValue + 1) * 2;
    if (static_cast<size_t>(tempMeshSize) != meshSize) {
        ShapeModelNG::SetBitmapMesh(frameNode, std::move(mesh), 0, 0);
        return;
    }
    ShapeModelNG::SetBitmapMesh(frameNode, std::move(mesh), columnValue, rowValue);
}
} // ShapeAttributeModifier
const GENERATED_ArkUIShapeModifier* GetShapeModifier()
{
    static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
        ShapeModifier::ConstructImpl,
        ShapeInterfaceModifier::SetShapeOptionsImpl,
        ShapeAttributeModifier::SetViewPortImpl,
        ShapeAttributeModifier::SetStrokeImpl,
        ShapeAttributeModifier::SetFillImpl,
        ShapeAttributeModifier::SetStrokeDashOffsetImpl,
        ShapeAttributeModifier::SetStrokeDashArrayImpl,
        ShapeAttributeModifier::SetStrokeLineCapImpl,
        ShapeAttributeModifier::SetStrokeLineJoinImpl,
        ShapeAttributeModifier::SetStrokeMiterLimitImpl,
        ShapeAttributeModifier::SetStrokeOpacityImpl,
        ShapeAttributeModifier::SetFillOpacityImpl,
        ShapeAttributeModifier::SetStrokeWidthImpl,
        ShapeAttributeModifier::SetAntiAliasImpl,
        ShapeAttributeModifier::SetMeshImpl,
    };
    return &ArkUIShapeModifierImpl;
}

}
