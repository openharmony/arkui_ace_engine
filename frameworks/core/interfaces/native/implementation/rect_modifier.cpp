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

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include <algorithm>

namespace OHOS::Ace::NG {
struct RectRadius {
    std::optional<Dimension> radiusWidth;
    std::optional<Dimension> radiusHeight;
};
struct RectOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
    std::optional<Dimension> radiusWidth;
    std::optional<Dimension> radiusHeight;
    std::vector<RectRadius> cornerRadius;
};
} // OHOS::Ace::NG
namespace {
    constexpr int32_t MAX_RADIUS_ITEM_COUNT = 4;
}
namespace OHOS::Ace::NG::Converter {
template<>
RectRadius Convert(const Ark_RadiusItem & src)
{
    RectRadius radiusStruct;
    Dimension radiusWidthValue = Converter::Convert<Dimension>(src.value0);
    Dimension radiusHeightValue = Converter::Convert<Dimension>(src.value1);
    radiusStruct.radiusWidth = radiusWidthValue;
    radiusStruct.radiusHeight = radiusHeightValue;
    return radiusStruct;
}

template<>
RectOptions Convert(const Ark_RectOptions& src)
{
    RectOptions rectOptions;
    rectOptions.width = Converter::OptConvert<Dimension>(src.width);
    rectOptions.height = Converter::OptConvert<Dimension>(src.height);
    if (src.radius.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        rectOptions.radiusWidth = std::make_optional<Dimension>(Dimension(0));
        rectOptions.radiusHeight = std::make_optional<Dimension>(Dimension(0));
    } else {
        Converter::VisitUnion(
            src.radius.value,
            [&rectOptions](const Ark_Length& value) {
                Dimension radiusValue = Converter::Convert<Dimension>(value);
                rectOptions.radiusWidth = std::make_optional<Dimension>(radiusValue);
                rectOptions.radiusHeight = std::make_optional<Dimension>(radiusValue);
            },
            [&rectOptions](const Array_RadiusItem& value) {
                CHECK_NULL_VOID(value.array);
                int32_t length = value.length;
                length = std::min(length, MAX_RADIUS_ITEM_COUNT);
                for (int32_t i = 0; i < length; ++i) {
                    rectOptions.cornerRadius.emplace_back(Converter::Convert<RectRadius>(value.array[i]));
                }
            },
            []() {}
        );
    }
    return rectOptions;
}

template<>
RectOptions Convert(const Ark_RoundedRectOptions& src)
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
RectRadius Convert(const Array_Union_Number_String& src)
{
    RectRadius radiusStruct;
    radiusStruct.radiusWidth = std::make_optional<Dimension>(Dimension(0));
    radiusStruct.radiusHeight = std::make_optional<Dimension>(Dimension(0));
    return radiusStruct;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RectModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // auto frameNode = RectModelNG::CreateFrameNode(id);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
    return nullptr;
}
} // RectModifier
namespace RectInterfaceModifier {
void SetRectOptionsImpl(Ark_NativePointer node,
                        const Opt_Union_RectOptions_RoundedRectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto opt = Converter::OptConvert<RectOptions>(*options);
    CHECK_NULL_VOID(opt);
    if (opt->width) {
        ShapeAbstractModelNG::SetWidth(frameNode, opt->width.value());
    }

    if (opt->height) {
        ShapeAbstractModelNG::SetHeight(frameNode, opt->height.value());
    }

    if (!opt->radiusWidth || !opt->radiusHeight) {
        size_t length = std::min(opt->cornerRadius.size(), static_cast<size_t>(MAX_RADIUS_ITEM_COUNT));
        for (size_t i = 0; i < length; ++i) {
            const RectRadius radiusItem = opt->cornerRadius[i];
            const Dimension rx = radiusItem.radiusWidth.value();
            const Dimension ry = radiusItem.radiusHeight.value();
            RectModelNG::SetRadiusValue(frameNode, rx, ry, i);
        }
        return;
    }
    const Dimension rx = opt->radiusWidth.value();
    const Dimension ry = opt->radiusHeight.value();
    RectModelNG::SetRadiusWidth(frameNode, rx);
    RectModelNG::SetRadiusHeight(frameNode, ry);
}
} // RectInterfaceModifier
namespace RectAttributeModifier {
void RadiusWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusWidth = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(radiusWidth);
    RectModelNG::SetRadiusWidth(frameNode, radiusWidth.value());
}
void RadiusHeightImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusHeight = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(radiusHeight);
    RectModelNG::SetRadiusHeight(frameNode, radiusHeight.value());
}
void RadiusImpl(Ark_NativePointer node,
                const Opt_Union_Number_String_Array_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = Converter::OptConvert<RectRadius>(*value);
    CHECK_NULL_VOID(radius);
    CHECK_NULL_VOID(radius->radiusHeight);
    CHECK_NULL_VOID(radius->radiusWidth);
    RectModelNG::SetRadiusWidth(frameNode, radius->radiusWidth.value());
    RectModelNG::SetRadiusHeight(frameNode, radius->radiusHeight.value());
}
} // RectAttributeModifier
const GENERATED_ArkUIRectModifier* GetRectModifier()
{
    static const GENERATED_ArkUIRectModifier ArkUIRectModifierImpl {
        RectModifier::ConstructImpl,
        RectInterfaceModifier::SetRectOptionsImpl,
        RectAttributeModifier::RadiusWidthImpl,
        RectAttributeModifier::RadiusHeightImpl,
        RectAttributeModifier::RadiusImpl,
    };
    return &ArkUIRectModifierImpl;
}

}
