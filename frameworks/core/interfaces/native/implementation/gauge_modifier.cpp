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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GaugeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // GaugeModifier
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
void SetValueImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetValue(frameNode, convValue);
}
void SetStartAngleImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetStartAngle(frameNode, convValue);
}
void SetEndAngleImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetEndAngle(frameNode, convValue);
}
void SetColorsImpl(Ark_NativePointer node,
                   const Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_ResourceColor_LinearGradient_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetColors(frameNode, convValue);
}
void SetStrokeWidthImpl(Ark_NativePointer node,
                        const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetStrokeWidth(frameNode, convValue);
}
void SetDescriptionImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetDescription(frameNode, convValue);
}
void SetTrackShadowImpl(Ark_NativePointer node,
                        const Opt_GaugeShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetTrackShadow(frameNode, convValue);
}
void SetIndicatorImpl(Ark_NativePointer node,
                      const Opt_GaugeIndicatorOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetIndicator(frameNode, convValue);
}
void SetPrivacySensitiveImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetPrivacySensitive(frameNode, convValue);
}
void SetContentModifierImpl(Ark_NativePointer node,
                            const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GaugeModelNG::SetSetContentModifier(frameNode, convValue);
}
} // GaugeAttributeModifier
const GENERATED_ArkUIGaugeModifier* GetGaugeModifier()
{
    static const GENERATED_ArkUIGaugeModifier ArkUIGaugeModifierImpl {
        GaugeModifier::ConstructImpl,
        GaugeInterfaceModifier::SetGaugeOptionsImpl,
        GaugeAttributeModifier::SetValueImpl,
        GaugeAttributeModifier::SetStartAngleImpl,
        GaugeAttributeModifier::SetEndAngleImpl,
        GaugeAttributeModifier::SetColorsImpl,
        GaugeAttributeModifier::SetStrokeWidthImpl,
        GaugeAttributeModifier::SetDescriptionImpl,
        GaugeAttributeModifier::SetTrackShadowImpl,
        GaugeAttributeModifier::SetIndicatorImpl,
        GaugeAttributeModifier::SetPrivacySensitiveImpl,
        GaugeAttributeModifier::SetContentModifierImpl,
    };
    return &ArkUIGaugeModifierImpl;
}

}
