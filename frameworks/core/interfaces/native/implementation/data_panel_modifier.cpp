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
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace {
constexpr float DATA_PANEL_VALUE_MIN = 0.0;
}

namespace OHOS::Ace::NG::Validator {
void ValidateDataPanelValues(float& value)
{
    value = std::max(value, DATA_PANEL_VALUE_MIN);
}
}

// need check
namespace OHOS::Ace::NG::Converter {

template<>
Gradient Convert(const Ark_Union_ResourceColor_LinearGradient& src)
{
    Gradient dst;
    Converter::VisitUnion(src,
        [&dst](const Ark_ResourceColor& value) {
            auto colorOpt = Converter::OptConvert<Color>(value);
            auto gradientOpt = colorOpt.has_value() ?
                std::optional<Gradient>{SliderModelNG::CreateSolidGradient(colorOpt.value())} : std::nullopt;
            if (gradientOpt.has_value()) {
                dst = gradientOpt.value();
            }
        },
        [&dst](const Ark_LinearGradient& value) {
            auto gradientOpt = Converter::OptConvert<Gradient>(value);
            if (gradientOpt.has_value()) {
                dst = gradientOpt.value();
            }
        },
        []() {}
    );
    return dst;
}

template<>
DataPanelShadow Convert(const Ark_DataPanelShadowOptions& src)
{
    DataPanelShadow shadow;
    auto radiusOpt = Converter::OptConvert<float>(src.radius);
    Validator::ValidatePositive(radiusOpt);
    if (radiusOpt.has_value()) {
        shadow.radius = FloatToDouble(radiusOpt.value()).value();
    }

    auto offsetXOpt = FloatToDouble(Converter::OptConvert<float>(src.offsetX));
    if (offsetXOpt.has_value()) {
        shadow.offsetX = offsetXOpt.value();
    }

    auto offsetYOpt = FloatToDouble(Converter::OptConvert<float>(src.offsetY));
    if (offsetYOpt.has_value()) {
        shadow.offsetY = offsetYOpt.value();
    }

    auto colorsOpt = Converter::OptConvert<std::vector<Gradient>>(src.colors);
    if (colorsOpt.has_value()) {
        const auto &colors = *colorsOpt;
        if (find_if(colors.begin(), colors.end(), [](auto item) {return item.GetColors().size() == 0;})
            == colors.end()) {
            shadow.colors = std::move(colorsOpt.value());
        }
    }

    return shadow;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DataPanelModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // DataPanelModifier
namespace DataPanelInterfaceModifier {
void SetDataPanelOptionsImpl(Ark_NativePointer node,
                             const Ark_DataPanelOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
}
} // DataPanelInterfaceModifier
namespace DataPanelAttributeModifier {
void CloseEffectImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, Converter::Convert<bool>(value));
}
void ValueColorsImpl(Ark_NativePointer node,
                     const Array_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto convArray = Converter::Convert<std::vector<Gradient>>(*value);
    if (convArray.size() > 0) {
        if (find_if(convArray.begin(), convArray.end(), [](auto item) {return item.GetColors().size() == 0;})
            != convArray.end()) {
            // need check
            // DataPanelModelNG::SetValueColors(frameNode, std::nullopt);
            return;
        }
        DataPanelModelNG::SetValueColors(frameNode, convArray);
    } else {
        // need check
        // DataPanelModelNG::SetValueColors(frameNode, std::nullopt);
    }
}
void TrackBackgroundColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = value ? Converter::OptConvert<Color>(*value) : std::nullopt;
    // need check
    // DataPanelModelNG::SetTrackBackground(frameNode, color);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(width);
    // need check
    // DataPanelModelNG::SetStrokeWidth(frameNode, width);
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Ark_DataPanelShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::Convert<DataPanelShadow>(*value)
        : DataPanelShadow { .isShadowVisible = false };
    DataPanelModelNG::SetShadowOption(frameNode, convValue);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("DataPanel::ContentModifierImpl isn't implemented. Ark_CustomObject isn't supported.");
}
} // DataPanelAttributeModifier
const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier()
{
    static const GENERATED_ArkUIDataPanelModifier ArkUIDataPanelModifierImpl {
        DataPanelModifier::ConstructImpl,
        DataPanelInterfaceModifier::SetDataPanelOptionsImpl,
        DataPanelAttributeModifier::CloseEffectImpl,
        DataPanelAttributeModifier::ValueColorsImpl,
        DataPanelAttributeModifier::TrackBackgroundColorImpl,
        DataPanelAttributeModifier::StrokeWidthImpl,
        DataPanelAttributeModifier::TrackShadowImpl,
        DataPanelAttributeModifier::ContentModifierImpl,
    };
    return &ArkUIDataPanelModifierImpl;
}

}
