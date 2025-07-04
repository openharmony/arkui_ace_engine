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
namespace TextPickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TextPickerModifier
namespace TextPickerInterfaceModifier {
void SetTextPickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TextPickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //TextPickerModelNG::SetSetTextPickerOptions(frameNode, convValue);
}
} // TextPickerInterfaceModifier
namespace TextPickerAttributeModifier {
void SetDefaultPickerItemHeightImpl(Ark_NativePointer node,
                                    const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetDefaultPickerItemHeight(frameNode, convValue);
}
void SetCanLoopImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetCanLoop(frameNode, convValue);
}
void SetDisappearTextStyleImpl(Ark_NativePointer node,
                               const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetDisappearTextStyle(frameNode, convValue);
}
void SetTextStyleImpl(Ark_NativePointer node,
                      const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetTextStyle(frameNode, convValue);
}
void SetSelectedTextStyleImpl(Ark_NativePointer node,
                              const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetSelectedTextStyle(frameNode, convValue);
}
void SetDisableTextStyleAnimationImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetDisableTextStyleAnimation(frameNode, convValue);
}
void SetDefaultTextStyleImpl(Ark_NativePointer node,
                             const Opt_TextPickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetDefaultTextStyle(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_OnTextPickerChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetOnChange(frameNode, convValue);
}
void SetOnScrollStopImpl(Ark_NativePointer node,
                         const Opt_TextPickerScrollStopCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetOnScrollStop(frameNode, convValue);
}
void SetOnEnterSelectedAreaImpl(Ark_NativePointer node,
                                const Opt_TextPickerEnterSelectedAreaCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetOnEnterSelectedArea(frameNode, convValue);
}
void SetSelectedIndexImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Array_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetSelectedIndex(frameNode, convValue);
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetDivider(frameNode, convValue);
}
void SetGradientHeightImpl(Ark_NativePointer node,
                           const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetGradientHeight(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSetDigitalCrownSensitivity(frameNode, convValue);
}
} // TextPickerAttributeModifier
const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
{
    static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
        TextPickerModifier::ConstructImpl,
        TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
        TextPickerAttributeModifier::SetDefaultPickerItemHeightImpl,
        TextPickerAttributeModifier::SetCanLoopImpl,
        TextPickerAttributeModifier::SetDisappearTextStyleImpl,
        TextPickerAttributeModifier::SetTextStyleImpl,
        TextPickerAttributeModifier::SetSelectedTextStyleImpl,
        TextPickerAttributeModifier::SetDisableTextStyleAnimationImpl,
        TextPickerAttributeModifier::SetDefaultTextStyleImpl,
        TextPickerAttributeModifier::SetOnChangeImpl,
        TextPickerAttributeModifier::SetOnScrollStopImpl,
        TextPickerAttributeModifier::SetOnEnterSelectedAreaImpl,
        TextPickerAttributeModifier::SetSelectedIndexImpl,
        TextPickerAttributeModifier::SetDividerImpl,
        TextPickerAttributeModifier::SetGradientHeightImpl,
        TextPickerAttributeModifier::SetEnableHapticFeedbackImpl,
        TextPickerAttributeModifier::SetDigitalCrownSensitivityImpl,
    };
    return &ArkUITextPickerModifierImpl;
}

}
