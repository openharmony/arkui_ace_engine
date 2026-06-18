
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"
#include "core/components_ng/pattern/shape/rect_model_static.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/interfaces/native/utility/converter.h"

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

const Dimension DEFAULT_RADIUS(0.0f);
} // namespace OHOS::Ace::NG

namespace {
constexpr size_t MAX_RADIUS_ITEM_COUNT = 4;
}

namespace OHOS::Ace::NG::Converter {
template<>
RectRadius Convert(const Ark_RadiusItem& src)
{
    RectRadius radiusStruct;
    radiusStruct.radiusWidth = OptConvert<Dimension>(src.value0);
    radiusStruct.radiusHeight = OptConvert<Dimension>(src.value1);
    return radiusStruct;
}

template<>
RectOptions Convert(const Ark_RectOptions& src)
{
    RectOptions rectOptions;
    rectOptions.width = Converter::OptConvert<Dimension>(src.width);
    rectOptions.height = Converter::OptConvert<Dimension>(src.height);
    VisitUnion(src.radius,
        [&rectOptions](const Ark_Length& srcValue) {
            auto radius = OptConvert<Dimension>(srcValue);
            rectOptions.radiusWidth = radius;
            rectOptions.radiusHeight = radius;
        },
        [&rectOptions](const Array_RadiusItem& srcValue) {
            rectOptions.cornerRadius = Convert<std::vector<RectRadius>>(srcValue);
        },
        []() {});
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
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RectModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = RectModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace RectModifier

namespace RectInterfaceModifier {
void SetRectOptionsImpl(Ark_NativePointer node, const Opt_Union_RectOptions_RoundedRectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = Converter::OptConvertPtr<RectOptions>(options);
    CHECK_NULL_VOID(opt);
    if (opt->width) {
        ShapeAbstractModelNG::SetWidth(frameNode, opt->width.value());
    }
    if (opt->height) {
        ShapeAbstractModelNG::SetHeight(frameNode, opt->height.value());
    }
    if (!opt->radiusWidth || !opt->radiusHeight) {
        size_t length = std::min(opt->cornerRadius.size(), MAX_RADIUS_ITEM_COUNT);
        for (size_t i = 0; i < length; ++i) {
            const auto& radiusItem = opt->cornerRadius[i];
            const Dimension rx = radiusItem.radiusWidth.value_or(DEFAULT_RADIUS);
            const Dimension ry = radiusItem.radiusHeight.value_or(DEFAULT_RADIUS);
            RectModelNG::SetRadiusValue(frameNode, rx, ry, static_cast<int32_t>(i));
        }
        return;
    }
    const Dimension rx = opt->radiusWidth.value_or(DEFAULT_RADIUS);
    const Dimension ry = opt->radiusHeight.value_or(DEFAULT_RADIUS);
    RectModelNG::SetRadiusWidth(frameNode, rx);
    RectModelNG::SetRadiusHeight(frameNode, ry);
}
} // namespace RectInterfaceModifier

namespace RectAttributeModifier {
void SetRadiusWidthImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusWidth = Converter::OptConvert<Dimension>(*value);
    RectModelNG::SetRadiusWidth(frameNode, radiusWidth.value_or(DEFAULT_RADIUS));
}

void SetRadiusHeightImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusHeight = Converter::OptConvert<Dimension>(*value);
    RectModelNG::SetRadiusHeight(frameNode, radiusHeight.value_or(DEFAULT_RADIUS));
}

void SetRadiusImpl(Ark_NativePointer node, const Opt_Union_Length_Array_RadiusItem* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_Length& src) {
            auto radius = Converter::OptConvert<Dimension>(src).value_or(DEFAULT_RADIUS);
            RectModelNG::SetRadiusWidth(frameNode, radius);
            RectModelNG::SetRadiusHeight(frameNode, radius);
        },
        [frameNode](const Array_RadiusItem& src) {
            auto cornerRadius = Converter::Convert<std::vector<RectRadius>>(src);
            size_t length = std::min(cornerRadius.size(), MAX_RADIUS_ITEM_COUNT);
            for (size_t i = 0; i < length; ++i) {
                const auto& radiusItem = cornerRadius[i];
                const auto rx = radiusItem.radiusWidth.value_or(DEFAULT_RADIUS);
                const auto ry = radiusItem.radiusHeight.value_or(DEFAULT_RADIUS);
                RectModelNG::SetRadiusValue(frameNode, rx, ry, static_cast<int32_t>(i));
            }
        },
        [frameNode]() {
            RectModelNG::SetRadiusWidth(frameNode, DEFAULT_RADIUS);
            RectModelNG::SetRadiusHeight(frameNode, DEFAULT_RADIUS);
        });
}
} // namespace RectAttributeModifier

const GENERATED_ArkUIRectModifier* GetRectStaticModifier()
{
    static const GENERATED_ArkUIRectModifier arkUIRectModifierImpl {
        RectModifier::ConstructImpl,
        RectInterfaceModifier::SetRectOptionsImpl,
        RectAttributeModifier::SetRadiusWidthImpl,
        RectAttributeModifier::SetRadiusHeightImpl,
        RectAttributeModifier::SetRadiusImpl,
    };
    return &arkUIRectModifierImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier