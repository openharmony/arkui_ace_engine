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
#include "core/components_ng/pattern/data_panel/data_panel_model_static.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace {
constexpr float DATA_PANEL_VALUE_MIN = 0.0;
constexpr double DATA_PANEL_VALUE_MAX = 100.0;
constexpr size_t DATA_PANEL_COUNT_MAX = 9;
}

namespace OHOS::Ace::NG::Validator {
void ValidateDataPanelValues(float& value)
{
    if (LessOrEqual(value, DATA_PANEL_VALUE_MIN)) {
        value = 0.0;
    }
}
}

namespace OHOS::Ace::NG::Converter {
struct DataPanelOptions {
    std::optional<std::vector<double>> values;
    std::optional<double> max;
    // std::optional<DataPanelType> type;
};

template<>
DataPanelOptions Convert(const Ark_DataPanelOptions& src)
{
    std::vector<double> doubleArray;
    auto optMax = Converter::OptConvert<float>(src.max);
    double max = optMax.has_value() ? optMax.value() : DATA_PANEL_VALUE_MAX;
    auto floatArray = Converter::OptConvert<std::vector<float>>(src.values);
    if (floatArray.has_value()) {
        double dataSum = 0.0;
        size_t count = std::min(floatArray.value().size(), DATA_PANEL_COUNT_MAX);
        for (size_t idx = 0; idx < count; idx++) {
            float& value = floatArray.value().at(idx);
            Validator::ValidateDataPanelValues(value);
            // if the sum of values exceeds the maximum value, only fill in to the maximum value
            if (GreatOrEqual(dataSum + value, max) && GreatNotEqual(max, DATA_PANEL_VALUE_MIN)) {
                doubleArray.emplace_back(max - dataSum);
                break;
            }
            dataSum += value;
            doubleArray.emplace_back(value);
        }
        if (LessOrEqual(max, DATA_PANEL_VALUE_MIN)) {
            max = dataSum;
        }
    }

    return {
        .values = doubleArray,
        .max = max,
        // .type = Converter::OptConvert<DataPanelType>(src.type)
    };
}

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
    // auto frameNode = DataPanelModelNG::CreateFrameNode(id);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
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
    auto panelOptions = Converter::OptConvert<Converter::DataPanelOptions>(*options);
    if (panelOptions.has_value()) {
        DataPanelModelStatic::SetValues(frameNode, panelOptions.value().values);
        DataPanelModelStatic::SetMax(frameNode, panelOptions.value().max);
        // DataPanelModelStatic::SetType(frameNode, EnumToInt(panelOptions.value().type));
    } else {
        DataPanelModelStatic::SetValues(frameNode, std::nullopt);
        DataPanelModelStatic::SetMax(frameNode, std::nullopt);
        DataPanelModelStatic::SetType(frameNode, std::nullopt);
    }
}
} // DataPanelInterfaceModifier
namespace DataPanelAttributeModifier {
void CloseEffectImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    DataPanelModelNG::SetCloseEffect(frameNode, *convValue);
}
void ValueColorsImpl(Ark_NativePointer node,
                     const Opt_Array_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convArray = Converter::OptConvert<std::vector<Gradient>>(*value).value_or(std::vector<Gradient>{});
    if (convArray.size() > 0) {
        if (find_if(convArray.begin(), convArray.end(), [](auto item) {return item.GetColors().size() == 0;})
            != convArray.end()) {
                DataPanelModelStatic::SetValueColors(frameNode, std::nullopt);
            return;
        }
        DataPanelModelStatic::SetValueColors(frameNode, convArray);
    } else {
        DataPanelModelStatic::SetValueColors(frameNode, std::nullopt);
    }
}
void TrackBackgroundColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = value ? Converter::OptConvert<Color>(*value) : std::nullopt;
    DataPanelModelStatic::SetTrackBackground(frameNode, color);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(width);
    DataPanelModelStatic::SetStrokeWidth(frameNode, width);
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Opt_DataPanelShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<DataPanelShadow>(*value) : std::nullopt;
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    DataPanelModelNG::SetShadowOption(frameNode, *convValue);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
