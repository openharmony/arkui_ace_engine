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
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
struct RectOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
    std::optional<Dimension> radiusWidth;
    std::optional<Dimension> radiusHeight;
};
struct RectRadius {
    std::optional<Dimension> radiusWidth;
    std::optional<Dimension> radiusHeight;
};
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
RectOptions Convert(
    const Ark_Type_RectInterface_value_u0& src)
{
    RectOptions rectOptions;
    rectOptions.width = Converter::OptConvert<Dimension>(src.width);
    rectOptions.height = Converter::OptConvert<Dimension>(src.height);
    auto radius = Converter::OptConvert<RectRadius>(src.radius);
    if (radius->radiusWidth) {
        rectOptions.radiusWidth = radius->radiusWidth;
    }
    if (radius->radiusHeight) {
        rectOptions.radiusHeight = radius->radiusHeight;
    }
    return rectOptions;
}

template<>
RectOptions Convert(const Ark_Type_RectInterface_value_u1& src)
{
    RectOptions rectOptions;
    rectOptions.width = Converter::OptConvert<Dimension>(src.width);
    rectOptions.height = Converter::OptConvert<Dimension>(src.height);
    rectOptions.radiusWidth = Converter::OptConvert<Dimension>(src.radiusWidth);
    rectOptions.radiusHeight = Converter::OptConvert<Dimension>(src.radiusHeight);
    return rectOptions;
}

template<>
RectRadius Convert(const Ark_Number& src)
{
    RectRadius radiusStruct;
    radiusStruct.radiusWidth = Converter::OptConvert<Dimension>(src);
    radiusStruct.radiusHeight = Converter::OptConvert<Dimension>(src);
    return radiusStruct;
}

template<>
RectRadius Convert(const Ark_String& src)
{
    RectRadius radiusStruct;
    radiusStruct.radiusWidth = Converter::OptConvert<Dimension>(src);
    radiusStruct.radiusHeight = Converter::OptConvert<Dimension>(src);
    return radiusStruct;
}

template<>
RectRadius Convert(const Array_CustomObject& src)
{
    RectRadius radiusStruct;
    radiusStruct.radiusWidth = std::make_optional<Dimension>(Dimension(0));
    radiusStruct.radiusHeight = std::make_optional<Dimension>(Dimension(0));
    return radiusStruct;
}

template<>
Dimension Convert(const Array_CustomObject& src)
{
    return Dimension(0);
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RectInterfaceModifier {

void SetRectOptionsImpl(Ark_NativePointer node,
                        const Opt_Type_RectInterface_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<RectOptions>(*value);
    CHECK_NULL_VOID(options);
    if (options->width) {
        ShapeAbstractModelNG::SetWidth(frameNode, options->width.value());
    }

    if (options->height) {
        ShapeAbstractModelNG::SetHeight(frameNode, options->height.value());
    }

    if (!options->radiusWidth || !options->radiusHeight) {
        return;
    }
    const Dimension rx = options->radiusWidth.value();
    const Dimension ry = options->radiusHeight.value();
    RectModelNG::SetRadiusWidth(frameNode, rx);
    RectModelNG::SetRadiusHeight(frameNode, ry);
}
} // RectInterfaceModifier

namespace RectAttributeModifier {
void RadiusWidthImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto radiusWidth = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(radiusWidth);
    RectModelNG::SetRadiusWidth(frameNode, radiusWidth.value());
}
void RadiusHeightImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto radiusHeight = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(radiusHeight);
    RectModelNG::SetRadiusHeight(frameNode, radiusHeight.value());
}
void RadiusImpl(Ark_NativePointer node,
                const Ark_Union_Number_String_Array_Any* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto radius = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(radius);
    RectModelNG::SetRadiusWidth(frameNode, radius.value());
    RectModelNG::SetRadiusHeight(frameNode, radius.value());
}
} // RectAttributeModifier
const GENERATED_ArkUIRectModifier* GetRectModifier()
{
    static const GENERATED_ArkUIRectModifier ArkUIRectModifierImpl {
        RectInterfaceModifier::SetRectOptionsImpl,
        RectAttributeModifier::RadiusWidthImpl,
        RectAttributeModifier::RadiusHeightImpl,
        RectAttributeModifier::RadiusImpl,
    };
    return &ArkUIRectModifierImpl;
}
}
