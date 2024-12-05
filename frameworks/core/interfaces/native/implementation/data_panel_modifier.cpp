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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
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

namespace OHOS::Ace::NG::Converter {
struct DataPanelOptions {
    std::optional<std::vector<double>> values;
    std::optional<double> max;
    std::optional<DataPanelType> type;
};

template<>
DataPanelOptions Convert(const Ark_DataPanelOptions& src)
{
    auto floatArray = Converter::OptConvert<std::vector<float>>(src.values);
    if (floatArray.has_value()) {
        for (size_t idx = 0; idx < floatArray.value().size(); idx++) {
            Validator::ValidateDataPanelValues(floatArray.value().at(idx));
        }
    }
    std::vector<double> doubleArray;
    std::copy(floatArray->begin(), floatArray->end(), std::back_inserter(doubleArray));

    return {
        .values = doubleArray,
        .max = Converter::OptConvert<float>(src.max),
        .type = Converter::OptConvert<DataPanelType>(src.type)
    };
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DataPanelModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
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
        DataPanelModelNG::SetValues(frameNode, panelOptions.value().values);
        DataPanelModelNG::SetMax(frameNode, panelOptions.value().max);
        DataPanelModelNG::SetType(frameNode, EnumToInt(panelOptions.value().type));
    } else {
        DataPanelModelNG::SetValues(frameNode, std::nullopt);
        DataPanelModelNG::SetMax(frameNode, std::nullopt);
        DataPanelModelNG::SetType(frameNode, std::nullopt);
    }
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
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetValueColors(frameNode, convValue);
    LOGE("DataPanel::ValueColorsImpl isn't implemented yet.");
}
void TrackBackgroundColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = value ? Converter::OptConvert<Color>(*value) : std::nullopt;
    DataPanelModelNG::SetTrackBackground(frameNode, color);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(width);
    DataPanelModelNG::SetStrokeWidth(frameNode, width);
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Ark_DataPanelShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetTrackShadow(frameNode, convValue);
    LOGW("DataPanel::TrackShadowImpl isn't implemented yet.");
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DataPanelModelNG::SetContentModifier(frameNode, convValue);
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
