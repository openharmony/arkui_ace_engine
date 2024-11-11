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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GaugeInterfaceModifier {
void SetGaugeOptionsImpl(Ark_NativePointer node,
                         const Ark_GaugeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //GaugeModelNG::SetSetGaugeOptions(frameNode, convValue);
}
} // GaugeInterfaceModifier
namespace GaugeAttributeModifier {
void ValueImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetValue(frameNode, convValue);
}
void StartAngleImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetStartAngle(frameNode, convValue);
}
void EndAngleImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetEndAngle(frameNode, convValue);
}
void ColorsImpl(Ark_NativePointer node,
                const Ark_Type_GaugeAttribute_colors_colors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetColors(frameNode, convValue);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetStrokeWidth(frameNode, convValue);
}
void DescriptionImpl(Ark_NativePointer node,
                     const Callback_Any* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetDescription(frameNode, convValue);
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Ark_GaugeShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetTrackShadow(frameNode, convValue);
}
void IndicatorImpl(Ark_NativePointer node,
                   const Ark_GaugeIndicatorOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetIndicator(frameNode, convValue);
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          const Ark_Union_Boolean_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetPrivacySensitive(frameNode, convValue);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetContentModifier(frameNode, convValue);
}
} // GaugeAttributeModifier
const GENERATED_ArkUIGaugeModifier* GetGaugeModifier()
{
    static const GENERATED_ArkUIGaugeModifier ArkUIGaugeModifierImpl {
        GaugeInterfaceModifier::SetGaugeOptionsImpl,
        GaugeAttributeModifier::ValueImpl,
        GaugeAttributeModifier::StartAngleImpl,
        GaugeAttributeModifier::EndAngleImpl,
        GaugeAttributeModifier::ColorsImpl,
        GaugeAttributeModifier::StrokeWidthImpl,
        GaugeAttributeModifier::DescriptionImpl,
        GaugeAttributeModifier::TrackShadowImpl,
        GaugeAttributeModifier::IndicatorImpl,
        GaugeAttributeModifier::PrivacySensitiveImpl,
        GaugeAttributeModifier::ContentModifierImpl,
    };
    return &ArkUIGaugeModifierImpl;
}

}
